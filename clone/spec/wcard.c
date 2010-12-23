//flowray 2005.6.16
#include <ansi.h>

inherit SPEC;


void create()
{
	set_name (HIY"清池贵宾卡"NOR, ({ "wcard","vip card","card"}));
	set("long","出示(show)这张贵宾卡,可以自由的出入清池。\n");

	set("unit","张");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",30);
	set("flag","spec/wcard");
	set("rest",30);
	set("desc","可以到清池洗澡。");
	set("credit",10);
	setup();
}

void init()
{
	add_action("do_show","show");   
}

int do_show(string str)
{
	object env,me = this_player();
	string path;
	
	if (!restrict()) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
	
	if (!str)
		return notify_fail("你要出示什么？\n");
    	
	if ( str != "card")
		return notify_fail("你要出示什么？\n");
    
	env=environment(me);	
	path=file_name(env);
	
	if (path != "/d/changan/qingchi")
		return notify_fail("没事秀什么秀,你以为你的卡很酷呀？\n");
		
	if (me->query_tmp("pay_wash"))
		return notify_fail("小丫环说道：“你还是快点进去洗澡吧！”\n");
		
	me->set_temp("pay_wash",1);
	write(HIY"你神气地拿出贵宾卡在小丫环眼前晃了晃。\n"NOR);
	write("小丫环说道：“原来是贵客驾临,快快请进！”\n");
	
	degree();
	
	return 1;
}	 