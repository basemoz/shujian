#define FLOOR 10
#define SAVE_NPC "宗维侠"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔十层");
        set("long","这里是万安寺内宝塔的第十层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-9",
                "up" : __DIR__"baota-11"
        ]));
        setup();
}

#include "baota.h"