#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
    int skill;
    
    if ((int)me->query_skill("youming-zhao", 1) < 120 )
        return notify_fail("你的幽冥鬼爪等级不够，不能呼唤鬼魂！\n");    
    if ((int)me->query_skill("claw", 1) < 120 )
        return notify_fail("你的基本爪法极不够娴熟，不能呼唤鬼魂！\n");    
    if( objectp(me->query_temp("weapon")) )
      return notify_fail("你必须空手使用「金刚伏魔」！\n");
    if (me->query_skill_prepared("claw") != "youming-zhao"
        || me->query_skill_mapped("claw") != "youming-zhao"
        || me->query_skill_mapped("parry") != "youming-zhao")
                return notify_fail("你现在无法呼唤出鬼魂进行攻击！\n"); 
    if ((int)me->query("neili") < 500 )
        return notify_fail("你现在真气太弱，不能呼唤鬼魂！\n");
    if ((int)me->query("max_neili") < 1000 )
        return notify_fail("你现在内力太弱，不能呼唤鬼魂！\n");
    if ( (int)me->query_temp("幽冥", 1) ) 
        return notify_fail("你已经呼唤出了自己的魂魄！\n");
    
    message_vision(HIR"突然$N咬破舌尖，高声叫唤天地鬼神，如同疯子一般！跟着地面变得有如水动，
只见一条"HIB"鬼影"HIR"从地底冒出，飞于半空，身行飘渺不定，时而象一火球，时而象一黑影！\n"NOR, me);
    me->start_busy(2);
    me->add("neili", -500);    
    skill = me->query_skill("youming-zhao", 1)/5;
    me->set_temp("幽冥", 1);
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), skill+2);
    return 1;
}

void remove_effect(object me)
{
    message_vision(HIR"地面的波动渐渐减弱，那条"HIB"鬼影"HIR"于半空徘徊了一阵，就消失在地底了！\n"NOR, me);
    me->delete_temp("幽冥");
    return;
}
