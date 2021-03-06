//yitian.c 倚天
// By Spiderii@ty
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIC"倚天诀"NOR; }

int perform(object me, object target)
{
      string msg; 
      int i;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "sword")
         return notify_fail("你手中无剑，如何使得出倚天！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("倚天只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yitian-tulong",1) < 180 )
         return notify_fail("你的倚天屠龙功还不够娴熟，尚使不出倚天！\n");
      
      if((int)me->query_skill("literate",1) < 180 )
         return notify_fail("你的读书写字等级不够，不能写出倚天！\n");

      if((int)me->query_skill("sword",1) < 180)
         return notify_fail("你的基本剑法等级不够，不能写出倚天！\n");  
      
      if((int)me->query("max_neili") < 1500 )
         return notify_fail("你的内力修为似乎不够! \n");
      
      if((int)me->query("neili") < 500 )
         return notify_fail("你的当前内力似乎不够！\n"); 

      if( target->is_busy() )
         return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

      if (me->query_skill_mapped("sword") != "yitian-tulong"
       || me->query_skill_mapped("parry") != "yitian-tulong")
         return notify_fail("你现在无法写出「倚天」！\n");

      i = random((int)(me->query_skill("yitian-tulong",1)/100));
      if(i < 1) i=1;
      if(i > 8) i=8;                                                                                 
      msg = HIC"$N一转身，陡然间以手中"+weapon->query("name")+HIC"做笔，使出了倚天屠龙功的倚天一诀，当真是银钩铁划，\n"+
               "劲峭凌厉，淋漓酣畅，雄浑刚健，俊逸处如风飘，如雪舞，厚重处,如虎蹲，如象步！\n" NOR;
      me->add("neili", - 200);
      if((random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/5)
        &&  random(me->query("combat_exp")) > target->query("combat_exp")/2) {
            target->start_busy(i+2);
            msg += HIR"$n如何看的出其中的奥妙，但觉$N招招不离自己周身要穴，无奈下只得勉力护住面门胸口\n"+
                      "要害，突感膝头一麻，原来已被$N趁势点了穴道。\n"NOR;
      }
      else {
            me->start_busy(2);
            msg += HIY"哪知$p略通文采，恍惚间似觉$P那一横之後会跟著写那一直，倒也守得井井有条，\n"+
                      "丝毫不见败象。\n"NOR;
      }
      message_vision(msg, me, target);
      me->start_perform(3,"「倚天诀」");
      return 1;
}
