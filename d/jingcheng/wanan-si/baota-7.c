#define FLOOR 7
#define SAVE_NPC "空智大师"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔七层");
        set("long","这里是万安寺内宝塔的第七层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-6",
                "up" : __DIR__"baota-8"
        ]));
        setup();
}

#include "baota.h"