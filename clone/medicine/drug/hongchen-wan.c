// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 

// renshen-guo.c �˲ι�
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
   set_name(HIW "�쳾��" NOR, ({"hongchen dan", "hongchendan", "dan"}));
   set_weight(100);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("unit", "ö");
     set("long", "�ںڵĲ����۵�ҩ�裬����֮���ݺ���Ϸ����Ϸ�쳾��\n");
     set("value", 500000);
     set("drug_type", "��Ʒ");
   }
  
   set("is_monitored",1);
   setup();
}

int do_eat(string arg)
{
	int howmany;

	object me = this_player();

	if (!id(arg)) return notify_fail("��Ҫ��ʲô��\n");

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
	
	me->set_skill("literate", 2000);	// ��������
	me->set_skill("unarmed", 2000);	// ����ȭ��
	me->set_skill("dodge", 2000);	// ��������
	me->set_skill("sword", 2000);	// ��������
	me->set_skill("parry", 2000);	// �����м�
	me->set_skill("force", 2000);	// �����ڹ�
	
	me->set_skill("beiming-shengong", 2000); // ��ڤ��
	me->set_skill("liumai-shenjian", 2000);  // ������
	me->set_skill("lingboweibu", 2000);      // �貨΢��

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

	message_vision(HIW "$N�Ѻ쳾��������һ�����̲�ס���һ�����쳾�����쳾���������Ǻ쳾���� \n˵���˷ܵö������˹�ȥ��\n" NOR, me);  

	destruct(this_object());
	
	return 1;
}

