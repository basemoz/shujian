// xunlei-jian perform
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;
        j = me->query_skill("xunlei-jian", 1);
        weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("��Ѹ���Ƶء�ֻ����ս���жԶ���ʹ�á�\n");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "xunlei-jian"
               || me->query_skill_mapped("parry") != "xunlei-jian")
                return notify_fail("�������ʹ�ý�ʱ����ʹ����Ѹ���Ƶء�\n");
        if(me->query_skill("xunlei-jian", 1) < 100 )
                return notify_fail("���Ѹ�׽���������죬ʹ������Ѹ���Ƶء���\n");
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("����������̫����ʹ������Ѹ���Ƶء���\n");
        if( (int)me->query("neili") < 400 )
                return notify_fail("����������̫����ʹ������Ѹ���Ƶء���\n");
        me->add_temp("apply/attack", j * 2);
        me->add_temp("apply/damage", j / 2);
        msg = HIB"\n$N��Ȼ���أ�ʹ��Ѹ��ʮ����֮��Ѹ���Ƶء�����ʱһƬ�׹�ֱ��ǰ��ȥ��\n\n"NOR;
        message_vision(msg, me, target);
        me->set_temp("kl/podi",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);

        if(me->is_fighting(target) && (int)me->query_skill("xunlei-jian", 1) > 350 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    
else
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

        if(me->is_fighting(target) && (int)me->query_skill("xunlei-jian", 1) > 350 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
else
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
       me->add("neili",-j*2);
       me->add("jingli",-j);    
       me->add_temp("apply/attack", -j * 2);
       me->add_temp("apply/damage", -j / 2);
       me->delete_temp("kl/podi");
       me->start_perform(3+random(2),"��Ѹ���Ƶء�");
       return 1;
}
string perform_name(){ return MAG"Ѹ���Ƶ�"NOR; }
int help(object me)
{
write(MAG"\nѲ�׽���֮��Ѹ���Ƶء���"NOR"\n\n");
write(@HELP
          Ҫ��  ��ǰ���� 400 ���ϣ�
          ������� 1000 ���ϣ�
          Ѹ�׽����ȼ� 100 ���ϣ�
          ��������ΪѸ�׽�����
          �����м�ΪѸ�׽�����
          ��������������
          ע�⣺350�����Ծ���ռ��㷨��
HELP
);
return 1;
}
