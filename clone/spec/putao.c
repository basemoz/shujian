//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIG"ÉñÆæÆÏÌÑ"NOR, ({ "putao"}));
	set("long","ÕâÊÇÒ»´®ÓÉ´ïÄ¦´«ÈëÖĞÍÁµ"HIG"ÉñÆæÆÏÌÑ"NOR"£¬³Ô(eat)ÏÂËü»á·¢ÉúÆæ¹ÖµÄÊÂÇé¡£\n");

	set("unit","´®");
	set_weight(100);
	set("value",3000000);
  set("no_give",1);
  set("no_drop",1);
  set("no_get",1);
	set("degree",3);
	set("flag","spec/putao");
	set("rest",9);
	set("desc","Ôö¼ÓÇ±ÄÜÒ»Ç§µã¡£");
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
      		return notify_fail("ÄãÒª³ÔÊ²Ã´?\n");
      	
      	if (!restrict()) {return notify_fail("±¾ÖÜÄãÒÑ¾­²»ÄÜÔÙ³Ô"+this_object()->query("name")+"ÁË¡£\n");}   

	me->add("potential",1000);
	write(HIY"Äã³ÔÏÂÒ»¿Å"HIG"ÉñÆæÆÏÌÑ"HIY"·¢ÏÖ×Ô¼ºµÄÇ±ÄÜ´óÔö!\n"NOR);
	degree();
	return 1;
}	 