// rsg.c

#include <ansi.h>

inherit ITEM;

void init()
{
	if (environment() == this_player()) {
		add_action("do_eat", "eat");
		add_action("do_eat", "chi");
	}
}

void create()
{
	set_name(HIG "神仙果" NOR, ({"shenxian guo","guo"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"猪八戒曾经吃过的东西，看起来象一个白白胖胖的小男孩。\n"
		"有恢复体力，增加功力的神奇效果。\n");
		set("value", 100);
		set("unit", "枚");
		//set("no_drop", 1);
        //set("unique", 2);
        //set("treasure", 1);
	}
}

int do_eat(string arg)
{
	object me = this_player();
	if (!id(arg)) return 0;
	message_vision(HIG "$N吃下一枚"
	+name()+
	HIG "，顿时觉得精力旺盛，甚至不再感到干渴饥饿。\n"
	NOR,me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	me->reincarnate();

	//destruct(this_object());
	return 1;
}
