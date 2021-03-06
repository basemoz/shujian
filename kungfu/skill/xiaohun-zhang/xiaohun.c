// xiaohun-zhang perform xiaohun
// by dubei 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string *pictures = ({"心惊肉跳","杞人忧天","无中生有","拖泥带水","徘徊空谷","力不从心","行尸走肉", "庸人自扰" });
int perform(object me)
{

      object target;
      string arg,picture;
      int i, j, z;       
     i = me->query_skill("xiaohun-zhang", 1)/2;
     j = me->query_skill("yunu-xinjing", 1)/2; 
     z = me->query_skill("force",1)/2; 
     picture = pictures[random(sizeof(pictures))];
 
 

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("「销魂」只能在战斗中对对手使用。\n");

        if (me->query_skill_prepared("strike") != "xiaohun-zhang"
           || me->query_skill_mapped("strike") != "xiaohun-zhang"
                    || me->query_skill_mapped("parry") != "xiaohun-zhang"
                    || me->query_skill_mapped("force") != "yunu-xinjing")
           return notify_fail("你现在难以使用「销魂」绝技！\n"); 

        if(me->query_skill("xiaohun-zhang", 1) < 150 )
                return notify_fail("你的销魂掌法火候不够，使不出「销魂」绝技。\n");

        if(me->query_skill("strike", 1) < 150 )
                return notify_fail("你的基本功还不够娴熟，使不出「销魂」绝技。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功等级不够，使不出「销魂」绝技。\n");

 
        if( (int)me->query_str() < 30)
                return notify_fail("你的膂力还不够强劲，使不出「销魂」绝技。\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「销魂」绝技。\n");
 
       if(me->query_skill("yunu-xinjing", 1) < 150 )   
                return notify_fail("你的玉女心经修为不够，无法使用「消魂」绝技。\n");  

       if(me->query_temp("xhz_xiaohun")) 
       return notify_fail("你现在正在使用「消魂」绝技。\n"); 

       if (me->query("eff_qi")*2 >=me->query("max_qi"))
        return notify_fail("以你现在的心境难以使用发挥出消魂绝技。\n"); 

        if (me->query("neili") < 800)
        return notify_fail("你的内力不够。\n");
        if (me->query("jingli") < 800)
        return notify_fail("你的精力不够。\n");
        me->add("neili", -i*2);
        me->add("jingli", -i*2);
        me->add_temp("apply/strength", i);
        me->add_temp("apply/attack", j); 
        me->set_temp("xhz_xiaohun", 1);
        call_out("check_fight", 1, me, i, j, z);
        target->start_busy(2);
        message_vision(HIY"$N心想今日身陷绝境已然无幸,不由万念俱灰,一股凄然之意自心而升.没精打采的挥袖卷出，拍出一掌"+picture+",
但见掌风激荡,恍恍惚惚，隐隐约约！刹时黯然销魂掌威力顿增,势不可挡.\n"NOR,me,target);
        return 1;
}
void remove_effect(object me, int i, int j)
{
    if(me->query_temp("xhz_xiaohun")){ 
    me->add_temp("apply/strength", -i);
    me->add_temp("apply/attack", -j);
         
    me->delete_temp("xhz_xiaohun");
    tell_object(me, HIR"你「消魂」绝技运行完毕，气回丹田.\n" NOR);
     }
//    else tell_object(me, "。\n" NOR);
}
void check_fight(object me, int i, int j, int z)
{
  

    if (!me) return;
    if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query("eff_qi")*2 > me->query("max_qi"))
    {
        remove_effect(me, i, j);
        return;
    }
    if (z < 1 || !me->is_fighting()) {
        remove_effect(me, i, j);
        return;
    }
    call_out("check_fight", 1, me, i, j, z-1);
}



