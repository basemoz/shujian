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
   set_name(HIW "�˲ι�" NOR, ({"renshen guo", "renshenguo", "guo"}));
   set_weight(100);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("unit", "ö");
     set("long", "�װ����ֵ�һö�˲ι�����ǧ��һ��������ǧ��һ���������ǧ��ŵ��죬ʵ����ؼ���鱦��\n");
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

	howmany = (int)me->query("rsg_eaten");

	me->set("food", (int)me->max_food_capacity());
	me->set("water", (int)me->max_water_capacity());

	me->set("eff_jing", (int)me->query("max_jing"));
	me->set("jing", (int)me->query("max_jing"));
	me->set("eff_qi", (int)me->query("max_qi"));
	me->set("qi", (int)me->query("max_qi"));
	me->set("jingli", (int)me->query("max_jingli"));
	me->set("neili", (int)me->query("max_neili"));

	me->set("rsg_eaten", howmany+1);

	message_vision(HIW "$N���˲ι�������һ�����̲�ס���һ�����˲ι����˲ι����������˲ι��� \n˵���˷ܵö������˹�ȥ��\n" NOR, me);  

	//me->set("obstacle/wuzhuang","done");
	//me->unconcious();
	//destruct(this_object());

	return 1;
}

