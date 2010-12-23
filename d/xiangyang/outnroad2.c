// /d/xiangyang/outnroad2.c

inherit ROOM;
void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道往北进入陕西、河南境内。南边通向襄阳城。
LONG
	);
        set("outdoors", "襄阳");
        set("xyjob", 1);
	set("exits", ([
		"north" : __DIR__"outnroad3",
		"south" : __DIR__"outnroad1",
		"northeast" : __DIR__"junying",
	]));

	setup();
}
