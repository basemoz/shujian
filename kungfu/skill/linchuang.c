// linchuang-shu.c
// by akuma

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if ( me->query_skill("force", 1) < 50 )
	return notify_fail("你的内功如此不济，研习此临床医术又有何用？\n");

    if ( me->query_skill("linchuang-shu", 1) == me->query_skill("force", 1)+20 )
	return notify_fail("你的内功已经无法支持你研习更高深的临床医术了。\n");

    if ( me->query_skill("linchuang-shou", 1) == me->query_skill("literate", 1)+50 )
	return notify_fail("你的读书识字水平难以使你理解更高深的临床医术了。\n");

    return 1;
}
