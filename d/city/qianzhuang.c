// Room: /city/qianzhuang.c

inherit ROOM;

void create()
{
        set("short", "天阁斋");
        set("long", @LONG
这是一家老字号的钱庄，已有几百年的历史，在全国各地都有分店。它发
行的银票信誉非常好，通行全国。
LONG
        );

        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));

        set("objects", ([
                __DIR__"npc/qian" : 1,
                __DIR__"npc/dashou" : 1,
          
        ]));

        set("coor/x",110);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",10);
   set("coor/z",0);
   set("incity",1);
	setup();
}
