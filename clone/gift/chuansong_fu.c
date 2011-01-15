// chuansong_fu.c

#include <ansi.h>

inherit ITEM;

void init()
{
	if (environment() == this_player()) {
		add_action("do_fly", "fly");
	}
}

void create()
{
	set_name(HIY "传送符" NOR, ({"chuansong fu","fu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"一张黄灿灿的符，看上去金光闪闪，隐隐可见有烟雾在其上缭绕。\n"
		"你心中一动，这符似乎可以带你去任何地方。\n");
		set("value", 100);
		set("unit", "张");
	}
}

int do_fly(string arg)
{
	object me = this_player();
	string dest;

	switch (arg)
	{
		case "yz":
		case "yangzhou":
		case "扬州":
			dest = "/d/city/kedian";
			break;
		case "wg":
		case "wuguan":
		case "武馆":
			dest = "/d/wuguan/damen";
			break;
		default:
			dest = arg;
			break;
	}
	
	message_vision(HIG "$N将一张"
	+name()+
	HIG "贴在脑门上，口中念念有词，忽然一阵烟雾涌起，$N消失不见了。\n"
	NOR,me);

	return me->move(dest);
}
