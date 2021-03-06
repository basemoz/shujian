// halt.c

int main(object me, string arg)
{
        int i, success = 0;
        object ob, *enemy;

        if( arg && wizardp(me) ) {
                ob = present(arg, environment(me));
                if (!ob) ob = LOGIN_D->find_body(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("没有这个生物。\n");
                if (ob->is_busy()) {
                        message_vision("\n$N用巫师的神力解除了$n的忙乱。\n", me, ob);
                        ob->interrupt_me();
                        ob->start_busy(-1);
                        ob->interrupt_me();
                        return 1;
                }
                if( !ob->is_fighting() ) return notify_fail(ob->name()+"现在不忙。\n");
                ob->remove_all_enemy();
                message_vision("\n$N用巫师的神力停止了$n的战斗。\n", me, ob);
                return 1;
        }
        if (!me->is_busy()) {
                if (me->is_fighting()) {
                        if (me->is_perform()) 
                                return notify_fail("你正在使用"+me->query_perform()+"，暂时无法停止战斗。\n");
                        enemy = me->query_enemy();
                        success = sizeof(enemy);
                        for (i=0;i<sizeof(enemy);i++)
                                if (random(me->query_dex()) < enemy[i]->query_dex() &&
                                    random(me->query("combat_exp")) < enemy[i]->query("combat_exp")/2 &&
                                    random(me->query_skill("dodge")) < enemy[i]->query_skill("dodge") &&
                                    (enemy[i]->query("fight_follow") || userp(enemy[i])))
                                        success -= 1;
                        if (success < sizeof(enemy) && !me->query_temp("always_escape")) {
                                me->start_busy(1);
                                message_vision("\n$N身行向后一跃，但对手立即便又跟了上来。\n", me); 
                                return 1;
                        } else {
                                me->remove_all_enemy();
                                message_vision("\n$N身行向后一跃，跳出战圈不打了。\n", me); 
                                return 1;
                        }
                }
                return notify_fail("你现在不忙。\n");
        }

        notify_fail("你现在很忙，停不下来。\n");
        me->interrupt_me();
        if (me->is_busy()) return 0;
        return 1;
}

