// Room: /d/tianshan/dadao4.c
// By Linux

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
这是一条青石板铺成的大道，每块青石都是长约八尺，宽约三尺，甚是整
齐，要铺成这样的大道，工程浩大之极，不知是何年何代何人所造。大道两旁
树立着些石人，皆面目狰狞，手持各色神器让人望之心惊。
LONG);
	 set("exits", ([
                "southeast" : __DIR__"ytbu",
		"west" : __DIR__"dadao3",
		"north" : __DIR__"dadao5",
        ]));       
	set("outdoors", "天山");
	setup();
}
