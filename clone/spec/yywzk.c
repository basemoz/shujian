// yywzk.c 鸳鸯五珍脍 For gb kanglong quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIW"鸳"HIM"鸯"HIY"五"HIG"珍"HIC"脍"NOR, ({ "wuzhenkuai", "yuanyang wuzhenkuai"}));
    set("long",CYN"这便是一盆大内御厨亲手做的"HIW"鸳"HIM"鸯"HIY"五"HIG"珍"HIC"脍"CYN"，色香味具全，直把你的口水都引了出来。\n"NOR);

    set("unit","盆");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/yywzk");
    set("rest",0);
    set("desc","传说中大内御厨亲手做的鸳鸯五珍脍！");
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
                    return notify_fail("你要查看什么?\n");
      	
            if (!restrict()) {return notify_fail("本周你已经不能再使用"+this_object()->query("name")+"了。\n");}   

    me->set_temp("sj_credit/quest/mj/jiuyang",1);
    write(HIW"你反复查看这张"HIR"碎纸片"HIW"，希望能从上面查到点什么。突然，两个模糊的字的映入你的眼帘——“"HIR"九阳..."HIW"”!\n"NOR);
	degree();
	return 1;
}	 
*/
