

inherit ROOM;
#include <ansi.h>
string *dir=({"up","left","right"});

int     do_next(string arg);
int     do_cry();
void create()
{

                                        
        set("short", HIW"华山之巅"NOR);
        set("long", @LONG
终于爬上了一个稍微平坦之处，但四周白雪茫茫，除了向下，似乎再
也无路可走,你忽觉天地虽大，却无可去之处，不禁有种想哭的冲动。
LONG
        );

        set("objects", ([
//                "/d/huashan/hamasuperquest/hong" : 1,
        ]));

        set("outdoors", "huashan");
        set("cost", 5);
        setup();
}
void init()
{
        add_action("do_next","climb");
        add_action("do_cry","cry");
}
int do_next(string arg)
{
        object me = this_player();
        int cost,dodge;
         object hong = this_object();
        dodge = me->query_skill("dodge",1)/20+1;
        cost = dodge / 2 ;
        cost = random(cost) + 100;
        
        if(me->is_busy())
                return notify_fail("你还在忙着呢。\n");

        me->start_busy(2+random(2));
        
        if (!arg)
        {
                tell_object(me,"你想向哪个方向爬?\n"NOR);

                return 1;

        }
        if (me->query("jingli")<500)
        {
                tell_object(me,HIY"你的体力透支，昏了过去。\n"NOR);
                me->add("jingli",-500);
                return 1;
        }
        
        if (arg == "down")
        {
                message_vision("$N小心翼翼的爬了下去。\n"NOR,me);
                me->move("/d/huashan/sheshen");
                me->add("jingli",-cost);
                 destruct(hong);
        }
        else
        {
                tell_object(me,"这个方向不能爬。\n");
                
        }
        
        
        return 1;
}

int do_cry()
{
        object me=this_player();

        message_vision(HIR"$N觉得天地之大，却无可去之处，忍不住放声大哭。\n"NOR,me);

        return 1;

}
