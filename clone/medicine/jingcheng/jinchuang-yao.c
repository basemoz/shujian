#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("金创药", ({"jinchuang yao", "jinchuang", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("value", 3000);
                set("unit", "包");
                set("long", "这是一包特效金创药，可以补满气血。\n");
        }
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
        if (me->query("eff_qi") >= me->query("max_qi"))
                return notify_fail("你现在不需要用金创药。\n");
        me->receive_curing("qi", me->query("max_qi"));
        me->receive_heal("qi", me->query("max_qi"));
        message_vision(HIY"$N吃下一包金创药，身上外伤已然无碍。\n"NOR, me);
        me->start_busy(1);
        destruct(this_object());
        return 1;
}