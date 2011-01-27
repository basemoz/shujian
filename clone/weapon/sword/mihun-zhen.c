// 针
#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_UNIQUE;
void create()
{
	set_name(HIW "迷魂神针" NOR, ({ "mihun shenzhen", "zhen", "needle", "shenzhen" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("long", "一枚透明的细针，散发着若有若无的香气，吸入之下似乎能让人迷失本心。\n");
		set("value", 2000);
		set("rigidity", 10);
		set("sharpness", 10);
		set("material", "steel");
		set("unique", 2);
		set("needle", 1);
		set("weapon_prop/dodge", 2);
		set("wield_msg", "$N打开沙纸，轻轻捻起一枚$n。\n");
		set("unwield_msg", "$N将$n用砂纸包起来，藏回怀中。\n");		
		set("treasure", 1);
		set("poisoned", "miyao");
		set("poison_number", 500);
	}
	init_sword(45);
	setup();
}
