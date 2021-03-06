// Room: /u/qingyun/jyzj/xiepo1.c
// Written by qingyun
// Updated by jpei

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"雪山斜坡"NOR);
	set("long", @LONG
你手脚着地，沿着雪山斜坡，一步一步向着有阳光之处爬去，但此峭壁本
就极陡，加上冻结冰雪，更是滑溜无比，一不小心就会滑跌。
LONG	);

	set("outdoors", "昆仑山");
	set("no_clean_up", 0);
	
	setup();
}

void init()
{
	add_action("do_climb", ({"climb", "pa"}));
}

int do_climb(string arg)
{
	object me = this_player();
        if(me->is_busy() || me->is_fighting())
              return notify_fail("你正忙着呢！\n");
	if (arg == "east") {
		message("vision", me->name() + "向着太阳升起的地方爬去。\n", environment(me), ({me}));
		write("你向东面的雪山斜坡爬去。\n");
		me->move(__DIR__"xiepo2");
                me->start_busy(1);
		message("vision", me->name() + "爬了过来。\n", environment(me), ({me}));
		return 1;
	}
	if (arg == "west") {
		message_vision("$N向西边的松树爬去。\n", me);
		me->move(__DIR__"songshu");
                me->start_busy(1);
		message("vision", me->name() + "从雪山斜坡爬了过来，小心翼翼地爬上了松树。\n", environment(me), ({me}));
		return 1;
	}
	return 0;
}
