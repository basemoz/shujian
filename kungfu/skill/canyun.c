// canyun 风卷残云

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev, lev2;
        lev = me->query_skill("longzhua-gong", 1)/6;
        lev2 = me->query_skill("claw", 1)/6;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「风卷残云」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「风卷残云」！\n");   
        if( (int)me->query_skill("longzhua-gong", 1) < 120 )
                return notify_fail("你的龙爪功还不够娴熟，使不出「风卷残云」绝技。\n");
        if (me->query_skill_prepared("claw") != "longzhua-gong"
        || me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("你现在无法使用「风卷残云」进行攻击。\n");  

        if( (int)me->query_skill("yijin-jing", 1) < 120 )
                return notify_fail("你的易筋经等级还不够，使不出「风卷残云」绝技。\n");
        if( me->query("max_neili") < 1000 )
                return notify_fail("你现在内力太弱，使不出「风卷残云」。\n");      
        if( (int)me->query("neili") < 800 )
                return notify_fail("你现在真气太弱，使不出「风卷残云」。\n");
        message_vision(RED"\n$N突然大喝一声，纵身而上，双手犹如狂风骤雨，使出「风卷残云」，漫天爪影带着气浪有如怒海狂滔一般！\n"NOR,me);
        me->add_temp("apply/claw", lev+lev2);
	me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) {
                if( random(me->query("combat_exp"))>target->query("combat_exp")/2)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                else
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
        me->add_temp("apply/claw", -lev-lev2);
        me->start_busy(3);
        me->add("neili", -400);
        return 1;
}
