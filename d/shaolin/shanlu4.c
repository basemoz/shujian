// Room: /d/shaolin/shanlu4.c
// Date: bren

inherit ROOM;


void create()
{
	set("short", "山路");
	set("long", @LONG
这是少室山五乳峰下的一条小路，路旁长满的青草。黄土铺就的小路看
起来很齐整，似乎有人经常打扫。不远处就是五乳峰，山势挺拔，景秀境幽
，峰上种满了松树，随着微风拂过，传来阵阵滔声。北面是初祖庵，南面可
至少林寺。
LONG
	);

	set("exits", ([
		"north" : __DIR__"czan",
		"south" : __DIR__"shanlu3",
	]));

	
	set("outdoors", "shaolin");

	set("coor/x",50);
  set("coor/y",470);
   set("coor/z",140);
   setup();
}




