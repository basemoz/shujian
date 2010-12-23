// daopu.c 破旧刀谱 For 雪山飞狐之胡家刀法 quest by lsxk@hsbbs /2007/7/20
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIB"破旧刀谱"NOR, ({"pojiu daopu"}));
    set("long",HIC"这竟然是一本记录了胡家刀法的刀谱,这刀谱已经非常破旧，谱上招试已经很难辨认。\n"NOR);

    set("unit","本");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/daopu");
    set("rest",1);
    set("desc","传说谱中记录的正是响誉江湖的胡家刀法!");
    set("credit",1000);
	setup();
}

void init()
{
    add_action("do_bianren","bianren");
  
}

int do_bianren(string arg)
{
	object me=this_player();
	
	    
    if (arg!="pojiu daopu")
                    return notify_fail("你要辨认什么?\n");
      	
            if (!restrict()) {return notify_fail("本周你已经不能再使用"+this_object()->query("name")+"了。\n");}   

    me->set_temp("sj_credit/quest/public/hjdf",1);
    write(HIW"你想极力去辨认刀谱中的招试，但是刀谱实在太破了，你还是无法学到任何东西!\n"+
          "但是你觉得，如果有人能略微指点你一下，或许你就能掌握这门绝技。\n"NOR);
	degree();
	return 1;
}	 
