// ��ͨ  shentong.c

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIW"��ָ��ͨ"NOR; }

int perform(object me, object target)
{
	int damage, p, ap, dp;
	object weapon, weapon1;
	string msg, dodge_skill, *limbs, limb;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || environment(target)!=environment(me))
		return notify_fail("��ָ��ֻͨ�ܶ�ս���еĶ���ʹ�á�\n");

	if(  me->query_skill("tanzhi-shentong", 1) < 120 )
		return notify_fail("��ĵ�ָ��ͨ��δ�����ʹ��������ָ��ͨ��\n");

	if(  me->query_skill("bihai-chaosheng", 1) < 120)
		return notify_fail("��ı̺���������δ�����\n");

	if(  me->query_skill("throwing", 1) < 120 )
		return notify_fail("��Ļ���������δ�����ʹ��������ָ��ͨ��\n");

	if(  me->query("max_neili", 1) < 1600 )
		return notify_fail("����ڹ���Ϊ������ʹ����ָ��ͨ������\n");

	if(  me->query("neili", 1) < 500 )
		return notify_fail("�������������ʹ����ָ��ͨ������\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 && (int)me->query_skill("tanzhi-shentong", 1) < 160)
		return notify_fail("�������޷�ʹ�õ�ָ��ͨ��\n");

	if(weapon && (weapon->query("skill_type") != "throwing"
	 || me->query_skill_mapped("throwing") != "tanzhi-shentong"))
		return notify_fail("�����ڵ������޷�ʹ�õ�ָ��ͨ��\n");

	if( me->query_skill_mapped("parry") != "tanzhi-shentong"
	 || me->query_skill_prepared("finger") != "tanzhi-shentong")
	 	return notify_fail("�������޷�ʹ�õ�ָ��ͨ��\n");

	if(weapon)
		msg = HIW"\nֻ��$N˫��΢�Σ�������ָ����"+weapon->name()+HIW+"����һ�������$P���������ֱ��$n��ȥ��\n"NOR;
	else
		msg = GRN"\n$N�����ھ���ָ����׼�������$nһ����һ˿�����������������$p��ǰ��Ѩ��\n"NOR;

	limbs = target->query("limbs");
	limb = limbs[random(sizeof(limbs))];
	weapon1 = target->query_temp("weapon");

	ap = me->query("combat_exp", 1) /1000 * me->query_skill("tanzhi-shentong", 1);
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("dodge", 1);

	if ( random( ap + dp ) > dp ) {
		if( weapon && weapon1 ) {
			weapon1->unequip();
			weapon1->move(environment(target));
			target->reset_action();
			me->add("neili", -150);
			target->add_busy(2);
			msg += HIR"$nֻ�����ֱ�һ�飬�ѱ�$N��"+weapon->name()+HIR+"������Ѩ�������������ذ����е�"+weapon1->name()+HIR+"׹�أ�\n"NOR;
			me->start_perform(2, "��ָ��ͨ");
		}
		else {
			damage = me->query_skill("tanzhi-shentong", 1) * 3;
			damage += me->query_skill("throwing",1) * 2;
			damage += random(damage);

			if(me->query("neili") > target->query("neili")*2)
				damage *= 2;

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/3, me);

			if(weapon)
				target->receive_wound("qi", random(damage/2), me);

			target->add_busy(1 + random(2));

			p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
			msg = replace_string(msg, "$l", limb);
			msg = replace_string(msg, "$w", weapon?weapon->name():"��ָ����");
			me->add("neili", -200);
			me->add("jingli", -100);
			me->start_perform(3, "��ָ��ͨ");
		}
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->start_perform(2, "��ָ��ͨ");
	}
	message_vision(msg, me, target);
	me->add("neili", -150);
	me->add("jingli", -80);
	me->start_busy(random(2));
	return 1;
}

int help(object me)
{
        write(HIW"\n��ָ��֮ͨ����ָ��ͨ����"NOR"\n\n");
        write(@HELP
        Ҫ��  ������� 1600 ���ϣ�
                ��ǰ���� 500 ���ϣ�
                �̺������� 120 �����ϣ�
                �������� 120 �����ϣ�
                ����ʹ����Ҫ��ָ��ͨ 160 �����ϣ�
                �ֱ���ʹ���赯ָ��ͨ 120 �����ϡ�
                ����ָ�� 120 �����ϡ�
                ����ָ��Ϊ��ָ��ͨ��
                �����м�Ϊ��ָ��ͨ��

HELP
        );
        return 1;
}
