// yywzk.c ԧ�������� For gb kanglong quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIW"ԧ"HIM"��"HIY"��"HIG"��"HIC"��"NOR, ({ "wuzhenkuai", "yuanyang wuzhenkuai"}));
    set("long",CYN"�����һ�����������������"HIW"ԧ"HIM"��"HIY"��"HIG"��"HIC"��"CYN"��ɫ��ζ��ȫ��ֱ����Ŀ�ˮ�����˳�����\n"NOR);

    set("unit","��");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/yywzk");
    set("rest",0);
    set("desc","��˵�д���������������ԧ�������ڣ�");
    set("credit",650);
	setup();
}
/*
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
*/
