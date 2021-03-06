// lianhuan.c  夺命连环掌
// Create by lsxk@hsbbs 2007/5/15

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return CYN"夺命连环掌"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
         lev = ((int)me->query_skill("tiezhang-zhangfa", 1) + (int)me->query_skill("strike", 1))/2;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「夺命连环掌」绝技只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
/*            if( me->query_temp("tzzf") ){
                if ( (int)me->query_skill("tiezhang-zhangfa",1) < 400 ) 
                    return notify_fail("你必须空手才能使用「夺命连环掌」！\n");
                 }
            else   */
                return notify_fail("你拿着武器怎么能使用「夺命连环掌」绝技?\n");   
//        }

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 250 )
                return notify_fail("你的铁掌掌法还不够娴熟，使不出「夺命连环掌」绝技。\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「夺命连环掌」绝技进行攻击。\n");  

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 250 )
                return notify_fail("你的归元吐呐法等级还不够，使不出「夺命连环掌」绝技。\n");

        if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("你的基本内功等级还不够，使不出「夺命连环掌」绝技。\n");

        if( me->query("max_neili") < 3500 )
                return notify_fail("你现在内力修为太差，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("neili") < 800 )
                return notify_fail("你现在真气太弱，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("max_jingli") < 2500 )
                return notify_fail("你现在精力修为太差，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("jingli") < 600 )
                return notify_fail("你现在精力太差，使不出「夺命连环掌」。\n"); 

        message_vision(CYN"\n$N突然大喝一声，双掌犹如狂风骤雨般的拍向$n，正是铁掌掌法之精髓「夺命连环掌」绝技！\n"NOR,me,target);
        me->add_temp("apply/strike", lev/6);
        me->add_temp("apply/attack", lev/8);
        me->add_temp("apply/strength",(int)me->query("str"));
        me->add_temp("apply/dodge", -lev/6);
        me->set_temp("tiezhang", 1);
//        me->set_temp("action_flag", member_array("strike", keys(me->query_skill_prepare())));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("apply/strike", -lev/6);
        me->add_temp("apply/attack", -lev/8);
        me->add_temp("apply/strength",-(int)me->query("str"));
        me->add_temp("apply/dodge", lev/6);
        me->start_busy(1+random(2));
        me->start_perform(5,"「夺命连环掌」");
        me->add("neili", -500);
        me->delete_temp("tiezhang");
        return 1;
}
