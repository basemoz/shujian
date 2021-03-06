//wuji.c

#include <ansi.h>
void remove_effect(object me,int skill);


string exert_name() {return HIG"日月无极"NOR;}

int exert(object me)
{      
       int skill;
       skill = me->query_skill("xuantia-wuji");
	if ( !me->is_fighting())
		return notify_fail("你只能在战斗中使用「无极」！\n");

	if( (int)me->query_skill("xuantian-wuji", 1) < 200 )
		return notify_fail("你的玄天无极功修为不够，无法使用「无极」！\n");

	if (me->query_skill_mapped("force") != "xuantian-wuji")
		return notify_fail("其它内功有「无极」吗？\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("你目前的内力太少了，无法使用「日月无极」！\n");

	if( (int)me->query("max_neili") < 3500 )
		return notify_fail("你的内力修为这么差，还想使用「日月无极」？\n");

       if( (int)me->query_int() < 40 )
                 return notify_fail("你的悟性还不够，使不出「日月无极」来。\n");

       if( (int)me->query_con() < 48 )
                 return notify_fail("你的根骨还不够，使不出「日月无极」来。\n");

	if( me->query_temp("kl/riyue"))
		return notify_fail("你正在运用「日月无极」心法！\n");
     
	if( me->query_temp("kl/taxue"))
		return notify_fail("你正在运用「踏雪」心法！\n");

	message_vision(HIW "$N微一凝神，运起玄天无极心法，只见$N全身被一团真气围绕。\n" NOR, me);
       me->start_busy(1);
       me->add_temp("apply/parry", me->query_skill("xuantian-wuji", 1)/2);
       me->add_temp("apply/armor", me->query_skill("xuantian-wuji", 1)/2);
	me->add("neili", -400);
	me->set_temp("kl/riyue",1);
	call_out("remove_effect", 1, me, skill);
	me->start_exert(2, "「无极」");
	return 1;
}
void remove_effect(object me, int skill)
{
	
	 if (objectp(me)) {
                if (me->is_fighting()) {
                        call_out("remove_effect", 1, me, skill);
                        return;
                }

           me->delete_temp("kl/riyue");
	    
           me->add_temp("apply/parry", -me->query_skill("xuantian-wuji", 1)/2);
           me->add_temp("apply/armor", -me->query_skill("xuantian-wuji", 1)/2);
           message_vision(WHT"\n$N的玄天无极功运行完毕，将内力收回丹田。\n"NOR, me);
	    return;

	}
}


int help(object me)
{
        write(WHT"\n玄天无极功「日月无极」："NOR"\n");
        write(@HELP
        此「无极」一式，乃是以昆仑派内功心法玄天无极功作为基础，
        以无上玄功化日月精华为无极气盾，提高自身防御的同时，有
        几率使对方攻击无效！

        要求:  玄天无极功 200 级以上；
               最大内力 3500 点；
               当前内力 5000 点；
               不可与 踏雪 同时使用。
              
HELP
        );
        return 1;
}


