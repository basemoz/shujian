// tianlei.c ����--�۶�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIB"��    ��"NOR; }
int perform(object me, object target)
{
	int damage, p, ap, dp;
	string msg,dodge_skill;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
	      return notify_fail("���۶���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")))
	      return notify_fail("�������ֲ���ʹ�á��۶�����\n");

	if((int)me->query_skill("guiyuan-tunafa", 1) < 120 )
	      return notify_fail("��Ĺ�Ԫ���ɷ���δ���ɣ�����ʹ�á��۶�����\n");
		
	if((int)me->query("neili", 1) < 800 )
	      return notify_fail("�������������㣬����ʹ�á��۶�����\n");       

	if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
	 || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
	 || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
		return notify_fail("�������޷�ʹ�á��۶�����\n");

	if(me->query_temp("tzzf"))
	      return notify_fail("������ʹ���Ƶ���\n");

	if((int)me->query_skill("tiezhang-zhangfa", 1) < 120 )
	      return notify_fail("��������Ʒ�������죬����ʹ�á��۶�����\n");

	msg = HIB"\n$N΢΢������$n�������Ƴ�һ��,ֻ��һ��������ǰ��ȥ��\n"NOR;

	ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	if ( me->query_skill("tiezhang-zhangfa", 1) > 350 )
		ap += random(ap/3);

	if ( target->is_busy())
		dp -= dp/3;

	if ( random(ap + dp ) > dp ){
		damage = me->query_skill("tiezhang-zhangfa",1);
		damage *= 3;
		if (damage > 1000) damage = 1000 + (damage - 1000)/10;
		target->receive_damage("jing", damage, me);
		target->receive_wound("jing", damage/2, me);
		target->receive_damage("jingli", damage+me->query_skill("poison",1), me);
		msg += BLU"$n����ʧ��֮�䣬���㲻����һ�ɺ���ֱ��$n��ü��֮��Ϯȥ��\n"NOR;
		p = (int)target->query("eff_jing")*100/(int)target->query("max_jing");
		msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		me->add("neili", -300);
		me->add("jingli", -120);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision(msg, me, target);
	me->start_busy(random(2));
	me->start_perform(2,"���۶���");
	return 1;
}

int help(object me)
{
	write(HIB"\n�����Ʒ�֮���۶�����"NOR"\n");
	write(@HELP
	������ǧ�����ƹ��ľ���֮һ���������۶�����ʹ�����Ƶ����ж�����Ϯ���Է���

	Ҫ��  ���� 800 ���ϣ�      
		���� 50 ���ϣ�  
		�����Ʒ��ȼ� 120 ���ϣ�
		��Ԫ���ɷ��ȼ� 120 ���ϣ�
		�����Ʒ�Ϊ�����Ʒ���
		�����м�Ϊ�����Ʒ���
		�����ޱ�����
HELP
	);
	return 1;
}
