// Write By Yanyang@SJ 2001.9.20
// Room: /d/changan/eastchl.c

inherit ROOM;

void create()
{
        set("short", "东门城楼");
        set("long", @LONG
东门上的城楼，呈正方形，与左右两侧的箭楼共同组成东长乐门。往下望
是出城进城川流不息的人群。城中的房屋连绵不断，在这里还可以依稀的看到
城中心的钟楼。城楼上有流动的岗哨，严密监守着城周围一切动态。
LONG
        );
        set("outdoors", "长安");

        set("exits", ([
                "down"  : __DIR__"eastmen",
                "south" : __DIR__"eastjl2",
                "north" : __DIR__"eastjl1",
        ]));

        set("incity",1);
	setup();
}

