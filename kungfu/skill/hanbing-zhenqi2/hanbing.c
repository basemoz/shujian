// by darken@SJ
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HIW"寒冰诀"NOR; }

int exert(object me)
{
	string msg;
	int lv;
	lv = me->query_skill("force");

	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用「寒冰诀」。\n");
	
	if (me->query_temp("ss/hb"))
		return notify_fail("你正在使用「寒冰诀」。\n");

	if ((int)me->query_skill("hanbing-zhenqi",1) < 100)
		return notify_fail("以你目前的内功修为尚无法使用「寒冰诀」。\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("以你目前的内力修为尚无法使用「寒冰诀」。\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你的内力不够。\n");

	msg = HIW"$N深吸一口气，一道寒气便开始流转在身旁。\n"NOR;
	me->set_temp("ss/hb", 1);
	me->add("neili", -250);
	message_vision(msg, me);
	
	if ((int)me->query_skill("hanbing-zhenqi",1) < 350)
	{
		me->start_busy(random(2));
		me->start_exert(1, "「寒冰诀」");
	}
	call_out("remove_effect", lv/5 + random(10), me);
	return 1;
}

void remove_effect(object me)
{
	if (!me || !me->query_temp("ss/hb")) return;
	message_vision(HIW"$N手上的寒气渐渐的散去了。\n"NOR,me);
	me->delete_temp("ss/hb");
}

int help(object me)
{
	write(HIW"\n寒冰真气之「寒冰诀」："NOR"\n\n");
        write(@HELP
	要求：  最大内力  1000 以上；
                当前内力  500  以上；
                寒冰真气  100  级以上；
HELP
        );
        return 1;
}