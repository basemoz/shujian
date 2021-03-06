//By lsxk@hsbbs 2007/10/19
//群魔乱舞

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIB"群魔"HIR"乱舞"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

    if(me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你的内功不是化功大发，无法使用群魔乱舞！\n");
    if( (int)me->query_skill("huagong-dafa", 1) < 250 )
                return notify_fail("你的内功还未练成，不能使用群魔乱舞！\n");
    if( (int)me->query_skill("tianshan-zhang", 1) < 250 ) 
                return notify_fail("你的天山杖法还未练成，不能使用群魔乱舞！\n");
    if((int)me->query_skill("staff", 1) < 250 )
                return notify_fail("你的基本杖法不够娴熟，不能在使用天下无狗。\n");
    if((int)me->query_skill("poison", 1) < 180 )
                return notify_fail("你的毒技不够娴熟，不能在使用群魔乱舞。\n");
    if((int)me->query_dex(1) < 41 )
                return notify_fail("你的身法还不够灵巧，不能使用群魔乱舞。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang"
        || me->query_skill_mapped("parry") != "tianshan-zhang")
                return notify_fail("你现在使得了群魔乱舞么？\n");
                
    if((int)me->query("max_neili") < 4500 )
                return notify_fail("你的内力修为不够，不能使用群魔乱舞！\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("你现在真气不足，不能使用群魔乱舞！\n");

        message_vision(HIB"\n$N突然一声怪叫，脚步飘忽不定，瞬间已然向$n挥出数招，气势吓人之极！\n"NOR,me,target);

    me->start_perform(3+random(2),"「群魔乱舞」");
    i = (int)me->query_skill("tianshan-zhang",1);
        me->add("neili", -300);
        me->add_temp("apply/attack",  i);
        me->add_temp("apply/damage",  i/2);
        me->set_temp("tsz/lw",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",  -i);
        me->add_temp("apply/damage",  -i/2);
        me->delete_temp("tsz/lw");

    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(WHT"\n天山杖法「"HIB"群魔"HIR"乱舞"WHT"」："NOR"\n");
   write(@HELP

   要求：  最大内力 4500 以上；
           内力 2000 以上；
           天山杖法等级 250 以上；
           化功大法等级 250 以上；
           后天身法 41 以上；
           毒技等级 180 以上；
           激发招架为天山杖法。

HELP
   );
   return 1;
}
