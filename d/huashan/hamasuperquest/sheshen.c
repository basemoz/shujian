

#include <ansi.h>

inherit ROOM;
int do_climb(string arg);
void create()
{
        set("short", "舍身崖");
         set("long", @LONG
这是一段极窄极险的山崖，四周云雾飞绕，下面渊深无底。如不小心，一
失足掉下去，只怕连骨头都找不到。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
          "eastdown" : __DIR__"canglong",
         ]));
        
        set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "华山" );

        set("coor/x",60);
        set("coor/y",50);
        set("coor/z",70);
         setup();
}

void init()
{
        add_action("do_climb","climb");

}
int do_climb(string arg)
{
        object me = this_player();

        if (arg!="up") 
        return notify_fail(HIG"这个方向没办法爬。\n"NOR);
                
        if (me->query_skill("dodge",1) < 360)
        return notify_fail(HIG"你爬了半天毫无进展，还是回去练练轻功在来吧。\n"NOR);
        
        if (me->query_skill("hamagong",1) < 200)
        return notify_fail(HIG"你爬了半天感觉无聊到死。\n"NOR);
        
        if (me->query("oyf/hamagong") < 2)
        return notify_fail(HIG"你还是死了这条心吧。\n"NOR);	

        if (me->query("oyf/hamagong") == 3)
        return notify_fail(HIG"你已经见过你义父最后一面了。\n"NOR);     

        if (me->query("quest/hama/super") > 3)
        return notify_fail(HIG"你义父都死了多年了，不要来这伤心地了。\n"NOR);	
        
        if (me->query("jingli") < 1500)
        return notify_fail(HIG"你精神不好，还是歇歇再爬吧，小心送了小命！\n"NOR);

        me->add("jingli",-500);

        message_vision(HIG"$N手脚并用，使出了吃奶的力气终于爬了上来。\n"NOR,me);
        me->move("/d/huashan/hamasuperquest/jueding1");
}
                
