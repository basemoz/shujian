inherit NPC;
#include <ansi.h>
#include <job_skill.h>
void create()
{
        set_name("元兵守卫", ({ "yuanbing shouwei", "shouwei"}));
        set("gender", "男性");
        set("age", 20 + random(60));
        set("long", "这是一名看守万安寺宝塔的元兵守卫。\n");
        if (random(20) < 5)
                set("double_attack",1);
        set("attitude", "peaceful");
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("combat_exp", 2000000);
        set("no_get",1);
        set_basic();
        setup();
}
void init(object me)
{
        object ob;
        me = this_player();
        ob=this_object();
        ::init();

        if (!me->query_temp("was_job/asked"))
                return;

        command("say 快来人！有人劫狱！\n");
        if (!this_object()->query_temp("do_clone"))
                ob->do_clone(me, environment()->query_floor());
        if (!random(3))
                ob->do_clone(me, environment()->query_floor());
        kill_ob(me);
        me->kill_ob(this_object());
}

void die()
{
        switch (random(15))
        {
                case 0:
                        new(MEDICINE_D("jingcheng/shen-wan"))->move(this_object());
                        break;
                case 5:
                        new(MEDICINE_D("jingcheng/jinchuang-yao"))->move(this_object());
                        break;
                case 10:
                        new(MEDICINE_D("jingcheng/xiaohuan-dan"))->move(this_object());
                        break;
                case 15:
                        new(MEDICINE_D("jingcheng/jiedu-wan"))->move(this_object());
                        break;

        }
        ::die();
}
