// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>

string perform_name(){ return HBBLU"�� ɰ ��"NOR; }
int perform(object me, object target)
{
	string msg;
	int ap, dp;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 ||  !target->is_character()
	 ||  !me->is_fighting(target) )
		return notify_fail("����ɰ�ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( (int)me->query_skill("guiyuan-tunafa", 1) < 150 )
		return notify_fail("��Ĺ�Ԫ���ɷ���Ϊδ�����޷�ʹ����ɰ�ơ�\n");

	if( (int)me->query_skill("shuishangpiao", 1) < 150 )
		return notify_fail("���ˮ��Ư��Ϊδ�����޷�ʹ����ɰ�ơ�\n");

	if( me->query_skill_mapped("parry") != "tiezhang-zhangfa" 
	|| me->query_skill_prepared("strike") != "tiezhang-zhangfa")
		return notify_fail("�������޷�ʹ�á���ɰ�ơ���\n");

	if( me->query_temp("weapon") && !me->query_temp("tzzf") )
		return notify_fail("���ֳ����������ʹ�á���ɰ�ơ���\n");

	if( (int)me->query_skill("tiezhang-zhangfa", 1) < 150 )
		return notify_fail("���������Ϊδ�����޷�ʹ����ɰ�ơ�\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("����������̫�������ܳ���ɰ�ơ�\n");

	if( target->query_condition("no_force") )
		return notify_fail(target->name(1)+"�Ѿ���������ˣ�����Ҫ��ʹ�ú�ɰ�ơ�\n");
                

	msg = HBBLU"\n$N˫��һ��һ��һ����$n���ؿڼ����������\n"NOR;

	ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	if ( me->query_skill("tiezhang-zhangfa", 1) > 350 )
		ap += random(ap/3);

	if ( target->is_busy())
		dp -= dp/3;

	if (random(ap + dp ) > dp ) {
		msg += HIR"���$N˫˫���У�$n����һ�ϣ���Ϣ��Ҳ�޷�������ת��\n"NOR;
		target->add_condition("no_force", 4);
		me->add("neili",- 200);
		me->add("jingli",- 100);
	}
	else {
		msg += HIR"$n��ǿ�㿪����Ϣ���ء�\n"NOR;
		me->add("neili",-100 );
		me->add("jingli",- 50);
	}
	me->start_busy(random(2));
	me->start_perform(2, "��ɰ��");
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
        write(HBBLU"\n�����Ʒ�֮����ɰ�ơ���"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 1000 ���ϣ�
                ��Ԫ���ŷ��ȼ� 150 ���ϣ�
                ˮ��Ư�ȼ� 150 ���ϣ�
                �����Ʒ��ȼ� 150 ���ϣ�
                �����Ʒ�Ϊ�����Ʒ���
                �ұ������Ʒ���

HELP
        );
        return 1;
}
