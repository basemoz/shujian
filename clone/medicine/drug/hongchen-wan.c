// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 

// renshen-guo.c 人参果
// suppose to be able to be given and got,
// please let me know before changing...weiqi980417

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
   add_action("do_eat", "eat");
}

void create()
{
   set_name(HIW "红尘丹" NOR, ({"hongchen dan", "hongchendan", "dan"}));
   set_weight(100);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("unit", "枚");
     set("long", "黑黑的不起眼的药丸，吃了之后纵横游戏，游戏红尘。\n");
     set("value", 500000);
     set("drug_type", "补品");
   }
  
   set("is_monitored",1);
   setup();
}

int do_eat(string arg)
{
	int howmany;

	object me = this_player();

	if (!id(arg)) return notify_fail("你要吃什么？\n");

	me->set("per", 100);
	me->set("kar", 100);
	me->set("str", 500);
	me->set("int", 500);
	me->set("dex", 500);
	me->set("con", 500);
	
	//me->set("max_qi", 100000);
	//me->set("max_jing", 100000);
	me->set("max_neili", 10000);
	me->set("max_jingli", 10000);
	me->set("combat_exp", 50000000);
	
	me->set_skill("literate", 2000);	// 读书认字
	me->set_skill("unarmed", 2000);	// 基本拳脚
	me->set_skill("dodge", 2000);	// 基本剑法
	me->set_skill("sword", 2000);	// 基本剑法
	me->set_skill("parry", 2000);	// 基本招架
	me->set_skill("force", 2000);	// 基本内功
	
	me->set_skill("beiming-shengong", 2000); // 北冥神功
	me->set_skill("liumai-shenjian", 2000);  // 六脉神剑
	me->set_skill("lingboweibu", 2000);      // 凌波微步

	me->map_skill("sword", "liumai-shenjian");
	me->map_skill("force", "beiming-shengong");
	me->map_skill("dodge", "lingboweibu");
	me->map_skill("parry", "liumai-shenjian");
	me->map_skill("unarmed", "liumai-shenjian");

	me->set("food", (int)me->max_food_capacity());
	me->set("water", (int)me->max_water_capacity());
	
	me->set("eff_jing", (int)me->query("max_jing"));
	me->set("jing", (int)me->query("max_jing"));
	me->set("eff_qi", (int)me->query("max_qi"));
	me->set("qi", (int)me->query("max_qi"));
	me->set("jingli", (int)me->query("max_jingli"));
	me->set("neili", (int)me->query("max_neili"));

	message_vision(HIW "$N把红尘丹往嘴里一塞，忍不住大叫一声：红尘丹啊红尘丹，不愧是红尘丹！ \n说罢兴奋得都快晕了过去。\n" NOR, me);  

	destruct(this_object());
	
	return 1;
}

