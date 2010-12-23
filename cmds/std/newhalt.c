// halt.c

int main(object me, string arg)
{
        int i, success = 0;
        object ob, *enemy;

        if( arg && wizardp(me) ) {
                ob = present(arg, environment(me));
                if (!ob) ob = LOGIN_D->find_body(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("û��������\n");
                if (ob->is_busy()) {
                        message_vision("\n$N����ʦ�����������$n��æ�ҡ�\n", me, ob);
                        ob->interrupt_me();
                        ob->start_busy(-1);
                        ob->interrupt_me();
                        return 1;
                }
                if( !ob->is_fighting() ) return notify_fail(ob->name()+"���ڲ�æ��\n");
                ob->remove_all_enemy();
                message_vision("\n$N����ʦ������ֹͣ��$n��ս����\n", me, ob);
                return 1;
        }
        if (!me->is_busy()) {
                if (me->is_fighting()) {
                        if (me->is_perform()) 
                                return notify_fail("������ʹ��"+me->query_perform()+"����ʱ�޷�ֹͣս����\n");
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
                                message_vision("\n$N�������һԾ���������������ָ���������\n", me); 
                                return 1;
                        } else {
                                me->remove_all_enemy();
                                message_vision("\n$N�������һԾ������սȦ�����ˡ�\n", me); 
                                return 1;
                        }
                }
                return notify_fail("�����ڲ�æ��\n");
        }

        notify_fail("�����ں�æ��ͣ��������\n");
        me->interrupt_me();
        if (me->is_busy()) return 0;
        return 1;
}

