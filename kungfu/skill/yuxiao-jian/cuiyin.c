// By Darken@SJ

#include <ansi.h>
inherit F_SSERVER;
string perform_name() { return HIG"��©������"NOR; }

int perform(object me, object target)
{
        object weapon, *arm;
        int i, lvl = (me->query_skill("sword") + me->query_skill("throwing"))/2;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ����©��������\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽����޷�ʩչ��©��������\n");

        if( (int)me->query_skill("yuxiao-jian", 1) < 250 )
                return notify_fail("������｣��������죬�޷�ʩչ����©��������\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 250)
                return notify_fail("��ı̺���������򲻹����޷�ʩչ����©��������\n");
        if ((int)me->query_skill("tanzhi-shentong", 1) < 250)
                return notify_fail("��ĵ�ָ��ͨ��򲻹����޷�ʩչ����©��������\n");
        if ((int)me->query_skill("throwing", 1) < 250)
                return notify_fail("��İ������ɲ������޷�ʩչ����©��������\n");
        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("������Ե�ָ��ͨ��Ϊ���ֵ�׼���似��\n");
        if ( (int)me->query("max_neili") < 4500)
                return notify_fail("��������������޷�ʩչ����©��������\n");
        if ( (int)me->query("neili") < 2000)
                return notify_fail("��������������޷�ʩչ����©��������\n");
        if ((int)me->query("jingli") < 2000)
                return notify_fail("��ľ����������޷�ʩչ����©��������\n");

        message_vision(HBGRN"$N�˾���ָ���Ե�ָ��ͨ����"+weapon->query("name")+HBGRN+HIW"��\n"NOR, me, target);
        message_vision(HBGRN"$Nһʽ��©��������"+weapon->query("name")+HBGRN+HIW"���ַɳ�����۵糸������$n��\n"NOR,me,target);
        me->add_temp("apply/attack",lvl/2);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("apply/attack",-lvl/2);
        weapon->move(environment(me));
        lvl += weapon->query("sharpness")*5;

        me->add("neili", -(300 +random(200)) );
        me->add("jingli", -250);
        me->add("max_neili", -2-random(4));

        if (random(me->query_dex()) > target->query_dex()/2) {
                weapon = target->query_temp("weapon");
                arm = all_inventory(target); 
                for (i=0;i<sizeof(arm);i++) {
                        if (arm[i]->query("equipped")
                         && arm[i]->query("armor_prop/armor") < lvl /5
                         && arm[i]->query("rigidity") < lvl /50) {
                                message_vision(HIR"$N��"+arm[i]->query("name")+HIR"��������һ�������ˣ�\n"NOR, target);
                                destruct(arm[i]);
                        }
                }
                if (weapon 
                && weapon->query("armor_prop/armor") < lvl /5 
                && weapon->query("rigidity") < lvl /50) {
                        message_vision(HIR"$N��"+weapon->query("name")+HIR"��������һ�������ˣ�\n"NOR, target);
                        destruct(arm[i]);
                }
                target->reset_action();
        }
        me->start_perform(2,"����©��������");
        return 1;
}

int help(object me)
{
        write(HIG"\n����©����������"NOR"\n");
        write(@HELP

        ��ϵ�ָ��ͨ�����Ľ�����������֮����Ϊ������Ю���̺��������Ļ����
        �������ٶ������ϵķ����Լ�������

        Ҫ��  �̺������ȼ� 250 ���ϣ�
                ��ָ��ͨ�ȼ� 250 ���ϣ�
                ���������ȼ� 250 ���ϣ�
                ���｣���ȼ� 250 ���ϣ�
                ������� 4500 ���ϣ�
                ���Ķ���������������
HELP
        );
        return 1;
}

