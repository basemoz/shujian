// book1.c 天龙八部4
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW"乾达婆篇"NOR, ({"qiandapo pian","shu","book"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是天龙八部的之四--乾达婆篇。\n");
		set("unit", "本");
	     }
}
