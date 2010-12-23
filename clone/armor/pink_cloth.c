// pink_cloth.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(HIM"粉红绸衫"NOR, ({ "pink cloth", "cloth" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM"这件粉红色的绸衫上面绣着几只黄鹊，闻起来还有一股淡香。\n"NOR);
		set("unit", "件");
		set("value", 600);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 1);
		set("female_only", 1);
	}
	setup();
}

