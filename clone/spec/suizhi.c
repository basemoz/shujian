// suizhi.c 碎纸片 For mj 9yang quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIR"碎纸片"NOR, ({ "suizhi pian"}));
    set("long",HIR"这是一片皱巴巴的碎纸片，纸片已经泛黄，里面的字已然模糊不清。\n"NOR);

    set("unit","片");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/suizhi");
    set("rest",1);
    set("desc","传说是明教张教主之物!");
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
                    return notify_fail("你要查看什么?\n");
      	
            if (!restrict()) {return notify_fail("本周你已经不能再使用"+this_object()->query("name")+"了。\n");}   

    me->set_temp("sj_credit/quest/mj/jiuyang",1);
    write(HIW"你反复查看这张"HIR"碎纸片"HIW"，希望能从上面查到点什么。突然，两个模糊的字的映入你的眼帘——“"HIR"九阳..."HIW"”!\n"NOR);
	degree();
	return 1;
}	 
