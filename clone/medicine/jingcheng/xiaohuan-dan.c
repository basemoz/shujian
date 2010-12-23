#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("小还丹", ({"xiaohuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("value", 3000);
                set("unit", "颗");
                set("long", "这是一颗小还丹，可以补满内力。\n");
        }
}

int do_eat(string arg)                             
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
        if (me->query("neili") >= me->query("max_neili"))
                return notify_fail("你现在不需要用小还丹。\n");
        me->set("neili", me->query("max_neili"));
        message_vision(HIY"$N吃下一颗小还丹，顿时感觉内力源源而生。\n"NOR, me);
        me->start_busy(1);
        destruct(this_object());
        return 1;
}