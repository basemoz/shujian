//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIG"��������"NOR, ({ "putao"}));
	set("long","����һ���ɴ�Ħ���������"HIG"��������"NOR"����(eat)�����ᷢ����ֵ����顣\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
  set("no_give",1);
  set("no_drop",1);
  set("no_get",1);
	set("degree",3);
	set("flag","spec/putao");
	set("rest",9);
	set("desc","����Ǳ��һǧ�㡣");
	set("credit",10);
	setup();
}

void init()
{
	add_action("do_eat","eat");
  
}

int do_eat(string arg)
{
	object me=this_player();
	
	    
	if (arg!="putao")
      		return notify_fail("��Ҫ��ʲô?\n");
      	
      	if (!restrict()) {return notify_fail("�������Ѿ������ٳ�"+this_object()->query("name")+"�ˡ�\n");}   

	me->add("potential",1000);
	write(HIY"�����һ��"HIG"��������"HIY"�����Լ���Ǳ�ܴ���!\n"NOR);
	degree();
	return 1;
}	 