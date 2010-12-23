// shougong.c 收功

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HIW"收功"NOR; }

void remove_effect(object me);

int exert(object me)
{
//	int amount;

//	if( !wizardp(me) || !me->query("env/huntian_test") )    return notify_fail("暂时关闭。\n"); 

	if( !me->query_temp("htqg/powerup") )
		return notify_fail("你并没有使用「混天」神功。\n");

	if( me->query_temp("htqg/shougong") )
		return notify_fail("你正在将内力收回丹田。\n");

	if( me->query_temp("htqg/powerup") > 0 ) {
		message_vision(HIW"$N闭目凝神，全身骨节“噼啪”做响，想要散去体内劲力。\n" NOR, me);
		me->set_temp("htqg/shougong", 1);
		if( me->is_fighting() )
			me->start_busy(random(2));
	} else return notify_fail("你现在无法收功。\n");
	return 1;
}

int help(object me)
{
        write("\n混天气功「收功」：\n");
        write(@HELP
        混天气功运功后，若要提前取消运功，需要运「收功」来达到。
        要求：
                混天气功运功中。
HELP
        );
        return 1;
}
