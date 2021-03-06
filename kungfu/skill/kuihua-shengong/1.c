//by yueying@SJTY 6/7/2008
//葵花挪移大法
#include <ansi.h>
void remove_effect(object me, int amount);
inherit F_SSERVER;
int exert(object me, object target)
{
    int skill,sk,dex,wx;
    if( target != me ) 
        return notify_fail("葵花挪移大法只能对自己使用。\n");
    if( (int)me->query("neili") < 1000  ) 
        return notify_fail("你的内力不够。\n");
    if ((int)me->query_temp("apply/shade_vision"))
        return notify_fail("你已经在运功中了。\n");
    skill = me->query_skill("kuihua-shengong",1);
        if (skill<90) return notify_fail("你的葵花心法还不够娴熟。\n");
    skill = skill + me->query_skill("dodge") / 2;
    sk = skill;
    skill = skill / 3;
    if (me->query("gender") == "女性") skill = skill*2/3;
    dex = (int)me->query_skill("kuihua-shengong",1);
    wx = me->query_int();
    dex = to_int(dex/100*wx);
     
    message_vision( HIW "$N微一凝神，运起葵花心法，整个人如同被烟雾笼罩一般，飘忽不定。\n"
        HIB"  鬼魅至极\n" NOR, me);
    me->add("neili",-300);
    me->set_temp("apply/shade_vision",1);
    me->add_temp("apply/dexerity",skill*3/2);
    me->add_temp("apply/parry",skill);
    me->add_temp("apply/attack",skill);
    me->add_temp("apply/armor",dex);
    me->add_temp("apply/constitution",skill);
    if( wizardp(me) || me->query("env/debug"))
                tell_object(me, "你的「"HIW"葵花挪移大法"NOR"」增加：「"HIW"有效身法 "NOR"」"+skill*3/2+"；「"HIW"命中率"NOR"」 "+skill+"；「"HIW"招架 "NOR"」"+skill+"；「"HIW"根骨 "NOR"」"+skill+"；「"HIW"护甲 "NOR"」"+dex+" ；「"HIW"持续时间"NOR"」 "+sk/2+"。\n"NOR);
    if( me->query("gender") == "女性" )
    tell_object(me, "无性的「"HIW"葵花挪移大法"NOR"」增加：「"HIW"有效身法 "NOR"」"+sk*3/6+"；「"HIW"命中率"NOR"」 "+sk/3+"；「"HIW"招架 "NOR"」"+sk/3+"；「"HIW"根骨 "NOR"」"+skill+"；「"HIW"护甲 "NOR"」"+dex+" ；「"HIW"持续时间"NOR"」 "+sk/2+"。\n"NOR);
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), sk/2);
    if( me->is_fighting() ) me->start_busy(1);
    return 1;
}
void remove_effect(object me, int amount)
{
    if (!me)    return;
    me->delete_temp("apply/shade_vision");
    me->add_temp("apply/dodge",-amount);
    me->add_temp("apply/parry",-amount);
    me->add_temp("apply/attack",-amount);
    me->add_temp("apply/armor",-amount);
    me->add_temp("apply/constitution",-amount);
    message_vision( BOLD "$N的葵花心法运行完毕，全身忽的一顿，现出整个身形。\n" NOR, me);
}
void reset() { }
int clean_up() { return 1; }


