#define FLOOR 2
#define SAVE_NPC "高老者"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔二层");
        set("long","这里是万安寺内宝塔的第二层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-1",
                "up" : __DIR__"baota-3"
        ]));
        setup();
}

#include "baota.h"