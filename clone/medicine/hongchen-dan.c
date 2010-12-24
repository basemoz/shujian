// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 

// renshen-guo.c 人参果
// suppose to be able to be given and got,
// please let me know before changing...weiqi980417

#include <ansi.h>
#define HM_LEVEL				600
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

	// 天赋
	this_player()->set("str", 100);
    this_player()->set("per", 100);
    this_player()->set("int", 100);
    this_player()->set("con", 100);
    this_player()->set("dex", 100);
    this_player()->set("kar", 100);
    this_player()->set("pur", 100);

	// 战斗经验
    this_player()->set("combat_exp", 30000000);

	// 身体素质
    this_player()->set("neili", 100000);
    this_player()->set("max_neili", 100000);
    this_player()->set("jingli", 100000);
    this_player()->set("max_jingli", 100000);
    this_player()->set("eff_jingli", 100000);
    this_player()->set("qi", 100000);
    this_player()->set("max_qi", 100000);
    this_player()->set("eff_qi", 100000);
    this_player()->set("jing", 100000);
    this_player()->set("max_jing", 100000);
    this_player()->set("eff_jing", 100000);

	// 职业技能
    this_player()->set_skill("nongsang", 200);
    this_player()->set_skill("zhizao", 200);
    this_player()->set_skill("duanzao", 200);
    this_player()->set_skill("caikuang", 200);

	// 杂学
    this_player()->set_skill("medicine", HM_LEVEL);
	this_player()->set_skill("jingmai-xue", HM_LEVEL);
    this_player()->set_skill("literate", HM_LEVEL);
    this_player()->set_skill("buddhism", HM_LEVEL);
    this_player()->set_skill("daode-jing", HM_LEVEL);
    this_player()->set_skill("trade", HM_LEVEL);
    this_player()->set_skill("poison", HM_LEVEL);
	
	// 基本武学
    this_player()->set_skill("unarmed", HM_LEVEL);
    this_player()->set_skill("claw", HM_LEVEL);
    this_player()->set_skill("cuff", HM_LEVEL);
    this_player()->set_skill("finger", HM_LEVEL);
    this_player()->set_skill("hand", HM_LEVEL);
    this_player()->set_skill("strike", HM_LEVEL);
    this_player()->set_skill("leg", HM_LEVEL);
    this_player()->set_skill("force", HM_LEVEL);
    this_player()->set_skill("dodge", HM_LEVEL);
    this_player()->set_skill("parry", HM_LEVEL);
   	this_player()->set_skill("sword", HM_LEVEL);

	// 特殊招式
    this_player()->set_skill("beiming-shengong", HM_LEVEL);
    this_player()->set_skill("lingbo-weibu", HM_LEVEL);
    this_player()->set_skill("yiyang-zhi", HM_LEVEL);
    this_player()->set_skill("liumai-shenjian", HM_LEVEL);

	// 特殊招式激活
    this_player()->map_skill("parry", "yiyang-zhi");
    this_player()->map_skill("finger", "yiyang-zhi");
    this_player()->map_skill("force", "beiming-shengong");
    this_player()->map_skill("dodge", "lingbo-weibu");

	message_vision(HIW "$N把红尘丹往嘴里一塞，忍不住大叫一声：红尘丹啊红尘丹，不愧是红尘丹！ \n说罢兴奋得都快晕了过去。\n" NOR, me);  

	destruct(this_object());
	
	return 1;
}

