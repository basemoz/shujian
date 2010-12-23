// xunlei-jian perform
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;
        j = me->query_skill("xunlei-jian", 1);
        weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("「迅雷破地」只能在战斗中对对手使用。\n");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "xunlei-jian"
               || me->query_skill_mapped("parry") != "xunlei-jian")
                return notify_fail("你必须在使用剑时才能使出「迅雷破地」\n");
        if(me->query_skill("xunlei-jian", 1) < 100 )
                return notify_fail("你的迅雷剑还不够娴熟，使不出「迅雷破地」。\n");
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你现在内力太弱，使不出「迅雷破地」。\n");
        if( (int)me->query("neili") < 400 )
                return notify_fail("你现在真气太弱，使不出「迅雷破地」。\n");
        me->add_temp("apply/attack", j * 2);
        me->add_temp("apply/damage", j / 2);
        msg = HIB"\n$N猛然伏地，使出迅雷十六剑之「迅雷破地」，顿时一片白光直向前滚去！\n\n"NOR;
        message_vision(msg, me, target);
        me->set_temp("kl/podi",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);

        if(me->is_fighting(target) && (int)me->query_skill("xunlei-jian", 1) > 350 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    
else
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

        if(me->is_fighting(target) && (int)me->query_skill("xunlei-jian", 1) > 350 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
else
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
       me->add("neili",-j*2);
       me->add("jingli",-j);    
       me->add_temp("apply/attack", -j * 2);
       me->add_temp("apply/damage", -j / 2);
       me->delete_temp("kl/podi");
       me->start_perform(3+random(2),"「迅雷破地」");
       return 1;
}
string perform_name(){ return MAG"迅雷破地"NOR; }
int help(object me)
{
write(MAG"\n巡雷剑法之「迅雷破地」："NOR"\n\n");
write(@HELP
          要求：  当前内力 400 以上；
          最大内力 1000 以上；
          迅雷剑法等级 100 以上；
          激发剑法为迅雷剑法；
          激发招架为迅雷剑法；
          必须手拿武器。
          注意：350级后飞跃，终极算法。
HELP
);
return 1;
}
