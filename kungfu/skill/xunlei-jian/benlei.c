// xunlei.c 迅雷剑
#include <ansi.h>
//改名叫奔雷快剑---by daidai 2007-06-26
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                 return notify_fail("「奔雷快剑」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if((int)me->query_skill("xunlei-jian",1) < 100 )
            return notify_fail("你的迅雷剑法还不够火候，使不出「奔雷快剑」。\n");
        if((int)me->query_skill("xuantian-wuji",1) < 100 )
                return notify_fail("你的玄天无级功还不够火候，使不出「奔雷快剑」。\n");
        if((string)me->query_skill_mapped("sword") != "xunlei-jian" && userp(me))
                return notify_fail("你现在无法使用这个绝招！\n");
        if((string)me->query_skill_mapped("force") != "xuantian-wuji" && userp(me))
                return notify_fail("你不用玄天无级内功支持是无法使用这个绝招的！\n");
        if((string)me->query_skill_mapped("parry") != "xunlei-jian" && userp(me))
                  return notify_fail("你现在无法使用这个绝招！\n");
        if((int)me->query_temp("xunlei_jian") )
               return notify_fail("你现在已经在向对手使用了。\n");
        if((int)me->query_temp("xunlei") )
        return notify_fail("你现在已经在向对手使用「迅雷十六剑」了。\n");
        if((int)me->query("max_neili", 1) < 1000 )
               return notify_fail("你的内力修为不够使用「奔雷快剑」！\n");
        if((int)me->query("max_jingli") < 500 )
         return notify_fail("你的精力修为不够使用「奔雷快剑」！\n");
        if((int)me->query("neili")<500)
                return notify_fail("你的真气不够！\n"); 
        attack_time = random((int)me->query_skill("xunlei-jian",1) / 25)+1;
        if(attack_time < 2)
               attack_time = 2;
        if(attack_time > 4)  attack_time = 4;
        msg = HBMAG "$N手中"+weapon->name()+HBMAG"呜呜做响，剑尖指天，突然身形拔高，不待$n反应过来又连续向$n攻去！\n"NOR;
        message_vision(msg, me, target);
        lvl = ((me->query_skill("xunlei-jian", 1) + me->query_skill("xuantian-wuji", 1)))/ 8;
       me->set_temp("kl/xunlei", 1);
       me->add_temp("apply/dexerity", lvl);
        for(i = 0; i < attack_time; i++)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
       me->delete_temp("kl/xunlei");
     me->start_perfrom(attack_time,"「奔雷快剑」");
        me->add("neili", -300);
        me->add("jingli", -80);
        me->set_temp("xunlei_jian", 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl :),
           random(attack_time)+4);
        return 1;
}
void remove_effect(object me, object target)
{
        int lvl;
        lvl = ((me->query_skill("xunlei-jian", 1) + me->query_skill("xuantian-wuji", 1)))/ 8;
        me->delete_temp("xunlei_jian");
        me->add_temp("apply/dexerity", -lvl);
        if (me->is_fighting(target) )
       message_vision(MAG"$N的攻势渐渐慢了下来，$n缓过劲来松了口气。\n"NOR,me,target);
}
