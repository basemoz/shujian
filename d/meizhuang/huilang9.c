// Room: /d/meizhuang/huilang9.c
// By Lklv

inherit ROOM;

void create()
{
	set("short", "回廊");
	set("long", @LONG
这是庄内的一条回廊，地面上整齐地铺着细碎的青石，头上是精美的画梁
，回廊外四周的空地上种着一排排整齐的梅树。
LONG
	);

	set("exits", ([
		"east" : __DIR__"huilang11",
		"north" : __DIR__"huilang7",
		]));
	setup();
}