// suizhi.c ��ֽƬ For mj 9yang quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIR"��ֽƬ"NOR, ({ "suizhi pian"}));
    set("long",HIR"����һƬ��Ͱ͵���ֽƬ��ֽƬ�Ѿ����ƣ����������Ȼģ�����塣\n"NOR);

    set("unit","Ƭ");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/suizhi");
    set("rest",1);
    set("desc","��˵�������Ž���֮��!");
    set("credit",500);
	setup();
}

void init()
{
    add_action("do_chakan","chakan");
  
}

int do_chakan(string arg)
{
	object me=this_player();
	
	    
    if (arg!="suizhi pian")
                    return notify_fail("��Ҫ�鿴ʲô?\n");
      	
            if (!restrict()) {return notify_fail("�������Ѿ�������ʹ��"+this_object()->query("name")+"�ˡ�\n");}   

    me->set_temp("sj_credit/quest/mj/jiuyang",1);
    write(HIW"�㷴���鿴����"HIR"��ֽƬ"HIW"��ϣ���ܴ�����鵽��ʲô��ͻȻ������ģ�����ֵ�ӳ���������������"HIR"����..."HIW"��!\n"NOR);
	degree();
	return 1;
}	 
