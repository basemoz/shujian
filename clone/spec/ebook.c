//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIC"��Ӣ֮��"NOR, ({ "ebook","book"}));
	set("long","����һ��"HIC"��Ӣ֮��"NOR"���Ķ�("HIY"read"NOR")����������Ӣһ���ɳ���\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);	
	set("degree",1);
	set("flag","spec/ebook");
    set("rest",10);
    set("desc","���Сʱ֮�ھ���ӳɡ�");
    set("credit",60);
	setup();
}

void init()
{
	add_action("do_read","read");
  
}

int do_read(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("��Ҫ��ʲô?\n");
      		
	if (arg!="book")
      		return notify_fail("��Ҫ��ʲô?\n");
      	
      		
      	if (!restrict()) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}   

	
	if(!mapp(me->query_conditions_by_type("db_exp")))
		me->apply_condition("db_exp", 900);
	else
		me->add_condition("db_exp", 900);
	
	write(HIY"��ϸϸ�Ķ�"HIC"��Ӣ֮��"HIY"��������,��ʲô�����°빦����\n"NOR);

	degree();
	return 1;
}	 
