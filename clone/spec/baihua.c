//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIM"�ٻ���"NOR, ({"baihua wan","wan"}));
	set("long",HIW"�ɼ��ٻ�֮�ﾫ�����Ƶ�������ҩ��\n"NOR);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("unit","��");
	set_weight(100);
	set("value",3000000);
	
	set("degree",1);
	set("flag","spec/baihua");
	set("desc","�������Ƹ�����̵����ˡ�");
	set("credit",2);	
	setup();
}

void init()
{
	add_action("do_fu","fu");
  
}

int do_fu(string arg)
{
	object me=this_player();
      	
      		
      	if (arg!="wan")
      		return notify_fail("��Ҫ����ʲô?\n"); 
	
	if (me->is_busy()) {return notify_fail("����æ���ء�\n");}
			
	if((!mapp(me->query_conditions_by_type("hurt"))) && (!mapp(me->query_conditions_by_type("wound"))))
		{return notify_fail("�����û���ܵ�ʲô���˰ɡ�\n");}
	
	me->clear_conditions_by_type("hurt");
	me->clear_conditions_by_type("wound");
		
	write(HIW"���һ�¿�"HIM"�ٻ���"HIW"����һ������������Ƣ��\n�������Ȭ���ˡ�\n"NOR);
	degree();
	return 1;
}	 