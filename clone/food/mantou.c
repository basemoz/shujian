// mantou.c 馒头

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("馒头",({"man tou", "mantou", "tou" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个刚从蒸笼里拿出来的白馒头，还冒着热气～～～\n");
		set("unit", "个");
		set("value", 40);
		set("food_remaining", 2);
		set("food_supply", 40);
	 }
}