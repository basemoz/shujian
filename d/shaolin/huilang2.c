// Room: /d/shaolin/huilang2.c
// Date: YZC 96/01/19
// by zqb

inherit ROOM;

void create()
{
        set("short", "回廊");
        set("long", @LONG
这里是法堂西侧的回廊。彩梁画栋，连顶棚也用彩漆绘满了各种飞天的
图形，每幅画似乎都在诉说一个娓娓动人的佛经故事。廊外两侧是翠绿的青
竹，在微风中沙沙做响。四周静悄悄的，只有你自己的脚步声在耳边回荡。
LONG
        );

        set("exits", ([
                "west" : __DIR__"huilang3",
                "north" : __FILE__,
                "south" : __DIR__"huilang1",
                "east" : __FILE__,
        ]));

        
        set("coor/x",40);
 set("coor/y",420);
   set("coor/z",130);
   setup();
}

