// zuijiu.c 醉酒

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int drunk, limit, i, lvl;
      object weapon;
      
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("「八仙醉打」只能在战斗中对对手使用。\n");

      if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "zui-gun")
                return notify_fail("你现在无法使用「八仙醉打」。\n");
                
      if( (int)me->query_temp("zui-gun") )
                return notify_fail("你刚使了一遍「八仙醉打」，先等酒醒再说吧！\n");
            
      if( (int)me->query_skill("zui-gun",1) < 100 )
                return notify_fail("你的醉棍不够娴熟，不会使用「八仙醉打」！\n");
      
      if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("你现在所使的内功无法使出「八仙醉打」。\n");

      if( (int)me->query_skill("yijin-jing",1) < 100 )
                return notify_fail("你的易筋经等级不够，不能使用「八仙醉打」！\n");  
       
      if( (int)me->query_str() < 25 )
                return notify_fail("你的臂力不够强，不能使用「八仙醉打」！\n");
      
      if( (int)me->query("max_neili") < 1300 )
                return notify_fail("你的内力太弱，不能使用「八仙醉打」！\n");
            
      	drunk = me->query_condition("drunk");
      	limit = (me->query("con") + (int)me->query("max_neili") / 50) * 2;
      	lvl = (int)me->query_skill("zui-gun", 1);
      	if( drunk <= limit/4 && lvl < 180) 
                return notify_fail("你没有一点醉意，怎么使得出「八仙醉打」？\n");
      	if( drunk >= limit && lvl < 240) 
                return notify_fail("你现在是真正的烂醉如泥，酒鬼！\n");

      	lvl /= 20;
      	lvl--;
      	if(lvl > 8) lvl = 8;  
      	if(lvl < 1) return notify_fail("你的等级太低，无法使用出「八仙醉打」！\n");

      	if( (int)me->query("neili") < 100*lvl )
                return notify_fail("你的内力太少了，无法使用出「八仙醉打」！\n");
          
      	message_vision(HIY"\n$N突然一个醉嗝，顿时借着酒劲猛打，醉棍威力大增！\n"NOR,me);
      	me->set_temp("zuijiu", 1);
      	for(i=0; i < lvl; i++){
      	   	if(!me->is_killing(target->query("id")) 
      	   	&& !target->is_killing(me->query("id"))
      	   	&& !target->is_fighting(me))
      	   	break;
           	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?2:0);
           	me->add_temp("zuijiu", 1);
           	me->receive_damage("neili", 100);
      		me->receive_damage("jingli", 20);
      	}
      	me->delete_temp("zuijiu");
      	i = me->query_skill("club")/2;
      	me->set_temp("zui-gun", 1);
      	call_out("remove_effect", i, me);    
      	me->start_busy(3);

        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("zui-gun");
        tell_object(me, HIG"\n你经过一段时间，总算酒醒了。\n"NOR); 
}

