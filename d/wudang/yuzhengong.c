// /d/wudang/yuzhengong.c 遇真宫
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW"遇真宫"NOR);
        set("long", @LONG
这里是进香客进香还愿的遇真宫，乃武当山的第一道宫宇。宽敞
无比，香火鼎盛。宫中供着张三丰真人像。由于张真人闭关已久，外
人不知其是否尚在人间，民间传说他已得道仙逝，因此立像膜拜。旁
边是专供香客游人休息的茶亭。
LONG
        );
        set("exits", ([
                "westup" : __DIR__"wdbolin",
                "north" :__DIR__"sldadao",
        ]));

        set("objects",([
                "/kungfu/class/wudang/zhike" : 1,
                __DIR__"obj/gdxiang" : 1,
        ]));
        
        set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",30);
   setup();

}
