//lwc18.c

inherit ROOM;

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是少林寺的练武场。由无数块巨大的花岗岩石板铺就。上千年的踩
踏已使得这些石板如同镜子般平整光滑。十来个僧人正在练习武技。东西北
三面各有一练武场。
LONG
	);

	set("exits", ([
		"north" : __DIR__"lwc15",
		"east" : __DIR__"lwc19",
		"west" : __DIR__"lwc17",
		]));
         set("objects",([
		__DIR__"obj/zhuang" : 1,
	]));

	set("outdoors", "shaolin");
	set("coor/x",90);
  set("coor/y",260);
   set("coor/z",110);
   setup();

}

