//by yueying@SJTY 6/7/2008
//����Ų�ƴ�
#include <ansi.h>
void remove_effect(object me, int amount);
inherit F_SSERVER;
int exert(object me, object target)
{
    int skill,sk,dex,wx;
    if( target != me ) 
        return notify_fail("����Ų�ƴ�ֻ�ܶ��Լ�ʹ�á�\n");
    if( (int)me->query("neili") < 1000  ) 
        return notify_fail("�������������\n");
    if ((int)me->query_temp("apply/shade_vision"))
        return notify_fail("���Ѿ����˹����ˡ�\n");
    skill = me->query_skill("kuihua-shengong",1);
        if (skill<90) return notify_fail("��Ŀ����ķ���������졣\n");
    skill = skill + me->query_skill("dodge") / 2;
    sk = skill;
    skill = skill / 3;
    if (me->query("gender") == "Ů��") skill = skill*2/3;
    dex = (int)me->query_skill("kuihua-shengong",1);
    wx = me->query_int();
    dex = to_int(dex/100*wx);
     
    message_vision( HIW "$N΢һ������������ķ�����������ͬ����������һ�㣬Ʈ��������\n"
        HIB"  ��������\n" NOR, me);
    me->add("neili",-300);
    me->set_temp("apply/shade_vision",1);
    me->add_temp("apply/dexerity",skill*3/2);
    me->add_temp("apply/parry",skill);
    me->add_temp("apply/attack",skill);
    me->add_temp("apply/armor",dex);
    me->add_temp("apply/constitution",skill);
    if( wizardp(me) || me->query("env/debug"))
                tell_object(me, "��ġ�"HIW"����Ų�ƴ�"NOR"�����ӣ���"HIW"��Ч�� "NOR"��"+skill*3/2+"����"HIW"������"NOR"�� "+skill+"����"HIW"�м� "NOR"��"+skill+"����"HIW"���� "NOR"��"+skill+"����"HIW"���� "NOR"��"+dex+" ����"HIW"����ʱ��"NOR"�� "+sk/2+"��\n"NOR);
    if( me->query("gender") == "Ů��" )
    tell_object(me, "���Եġ�"HIW"����Ų�ƴ�"NOR"�����ӣ���"HIW"��Ч�� "NOR"��"+sk*3/6+"����"HIW"������"NOR"�� "+sk/3+"����"HIW"�м� "NOR"��"+sk/3+"����"HIW"���� "NOR"��"+skill+"����"HIW"���� "NOR"��"+dex+" ����"HIW"����ʱ��"NOR"�� "+sk/2+"��\n"NOR);
    me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), sk/2);
    if( me->is_fighting() ) me->start_busy(1);
    return 1;
}
void remove_effect(object me, int amount)
{
    if (!me)    return;
    me->delete_temp("apply/shade_vision");
    me->add_temp("apply/dodge",-amount);
    me->add_temp("apply/parry",-amount);
    me->add_temp("apply/attack",-amount);
    me->add_temp("apply/armor",-amount);
    me->add_temp("apply/constitution",-amount);
    message_vision( BOLD "$N�Ŀ����ķ�������ϣ�ȫ�����һ�٣��ֳ��������Ρ�\n" NOR, me);
}
void reset() { }
int clean_up() { return 1; }


