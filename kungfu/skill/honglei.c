// by darken@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HBBLU"����˫��"NOR; }
int perform(object me, object target)
{
        int p, j, ap, dp;
        string msg;

        j = me->query_skill("tiezhang-zhangfa", 1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("������˫�ơ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) && !me->query_temp("tzzf") )
                return notify_fail("�������ֲ���ʹ�á�����˫�ơ���\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 220 )
                return notify_fail("������Ʋ�����죬ʹ����������˫�ơ�������\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 220 )
                return notify_fail("���Ԫ���ɷ�������ʹ��������˫�ƾ�����\n");

        if( (int)me->query("jiali") < 120 )
                return notify_fail("�����������ʹ����������˫�ơ�������\n");

        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if( (int)me->query_skill("force") < 320 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�����˫�ơ���\n");

        if( (int)me->query_str(1) < 50 )
                return notify_fail("�������������ǿ����ʹ����������˫�ơ�����\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á�����˫�ơ���\n");

        if( (int)me->query("max_neili") < 4000)
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");

	msg = HBBLU "\n$N�����ת��ʹ�������Ʒ��еġ�����˫�ơ���$n�ؿ�˫���Ƴ���\n"NOR;
	

	ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	if ( me->query_skill("tiezhang-zhangfa", 1) > 350 )
		ap += random(ap/3);

	if ( target->is_busy())
		dp -= dp/3;

	if (random( ap + dp) > dp ) {
		msg += HIR"���һ�����У�$n���ɳ�����������Զ��������Ѫ���磡\n"NOR;
		j *= 5;
		j += me->query("jiali") * 5;
		j *= 2;
		j += random(j/2);
		j -= target->query_con(1)* 20;

		j = j/2 + random(j/2);

		tell_object(me, sprintf("damage: %d", j));

		if ( j > 6000 )
			j = 6000 + (j - 6000)/10;

		target->receive_damage("qi", j, me);
		target->receive_wound("qi",j/3+random(j/3), me);
		me->add("neili", -400);
		me->add("jingli", -150);
		me->start_perform(3, "������˫�ơ�");
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(j, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(j, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	}
	else {
		msg += CYN"$n�������Ͷ񣬼�æԶԶ�ܿ���\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
		me->start_perform(2, "������˫�ơ�");
	}
	me->start_busy(random(2));
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
        write(HBBLU"\n�����Ʒ�֮������˫�ơ���"NOR"\n\n");
        write(@HELP
        Ҫ��  ���� 3000 ���ϣ�
                ������� 4000 ���ϣ�
                �������� 50 ���ϣ�
                �����Ʒ��ȼ� 220 ���ϣ�
                ��Ԫ���ɷ��ȼ� 220 ���ϣ�
                ��Ч�ڹ��ȼ� 320 ���ϣ�
                ���� 120 ���ϣ�
                �����ڹ�Ϊ��Ԫ���ɷ���
                �����Ʒ�Ϊ�����Ʒ���
                �����м�Ϊ�����Ʒ���
                �����ޱ�����

HELP
        );
        return 1;
}
