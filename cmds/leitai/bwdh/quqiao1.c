//quqiao.c 曲桥

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIY"曲桥"NOR);
	set("long", @LONG
一座小巧精制的曲桥横跨在池塘上，池塘就这样被一分为二。池塘里的水
碧绿清澈，上面浮着些盛开的睡莲，透过睡莲的缝隙隐约可见几尾红色金鲤在
水中悠闲地缓缓游动。远处靠墙窗下的一丛芭蕉，火红的花朵开的正热闹，给
这宁静的池塘带来无限生机。
LONG
	);

	set("exits", ([
		"west" : __DIR__"huilang3",
		"southeast" : __DIR__"quqiao2",
		"east" : __DIR__"jiashan",
		"northeast" : __DIR__"quqiao4",
	]));
        
	set("outdoors", "试剑山庄");
	setup();
}

#include "sjsz_room.h";
