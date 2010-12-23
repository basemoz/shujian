#include <ansi.h>
inherit F_SSERVER;
void attack_1(object me);
void attack_2(object me);
void attack_3(object me);
void finish(object me);

int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("�۷�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("yinlong-bian",1) < 180
	|| me->query_skill("jiuyin-zhengong",1) < 180 )
		return  notify_fail("��Ĺ��򻹲�����죬����ʹ�÷�����\n");

	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "yinlong-bian" 
	|| me->query_skill_mapped("parry") != "yinlong-bian") 
		return  notify_fail("�������޷�ʹ�÷�����\n");

	if( me->query("neili") < 2000 )
		return notify_fail("�������������\n");

	if( me->query("jingli") < 1500 )
		return notify_fail("��ľ���������\n");

	me->start_perform(8, "����");
	msg = HIG"\n$Nʹ�����������޵ġ�����������һ������ʹ�ĵ�ˮ��©��\n"NOR;

	me->add("apply/parry",200);
// busy �ڸ��� callout ��������
	me->start_busy(random(2));
	message_vision(msg, me, target);
	call_out("attack_1",3);
	me->add("jingli", -200);
	me->add("neili", -300);
	return 1;
}

void attack_1(object me)
{
	object target;
	if(!me) return;	
	target = offensive_target(me);
	if(!target)
	{
		call_out("finish",1,me);
		return;
	}
		
	if (me->is_fighting()) {
		me->add_temp("apply/attack",me->query_skill("yinlong-bian",1));
		message_vision(HIY"$NͻȻ��ջӱ���$n��ȥ��\n"NOR, me, target);		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);		
		me->add_temp("apply/attack",-me->query_skill("yinlong-bian",1));
		call_out("attack_2",3,me);
	}
	else
		call_out("finish",1,me);
}

void attack_2(object me)
{
	object target;
	if(!me) return;	
	target = offensive_target(me);
	if(!target)
	{
		call_out("finish",1,me);
		return;
	}
	if (me->is_fighting()) {
		me->add_temp("apply/attack",me->query_skill("yinlong-bian",1));
		message_vision(HIY"$NͻȻ��ջӱ���$n��ȥ��\n"NOR, me, target);		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/attack",-me->query_skill("yinlong-bian",1));	
		call_out("attack_3",3,me);
	}
	else
		call_out("finish",1,me);
}

void attack_3(object me)
{
	object target;
	if(!me) return;	
	target = offensive_target(me);
	if(!target)
	{
		call_out("finish",1,me);
		return;
	}
	if (me->is_fighting()) {
		me->add_temp("apply/attack",me->query_skill("yinlong-bian",1));
		message_vision(HIY"$NͻȻ��ջӱ���$n��ȥ��\n"NOR, me, target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);		
		me->add_temp("apply/attack",-me->query_skill("yinlong-bian",1));
		call_out("finish",1,me);
	} 
	else
		call_out("finish",1,me);
}

void finish(object me)
{
	if(!me) return;
	message_vision(HIY"$N�������ã��޷�����������\n"NOR, me);
	me->start_perform(1, "����");
	me->add("apply/parry",-200);
}

string perform_name(){ return HIG"������"NOR; }

int help(object me)
{
        write(HIG"\n����������֮������������"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 2000 ���ϣ�
                ������� 1500 ���ϣ�
                ��ǰ���� 1500 ���ϣ�
                ���������޵ȼ� 180 ���ϣ�
                �����湦�ȼ� 180 ���ϣ�
                �����޷�Ϊ���������ޣ�
                �����м�Ϊ���������ޣ�
                ���ֱֳ�����

HELP
        );
        return 1;
}
