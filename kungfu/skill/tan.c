// ��ͨ  shentong.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string *xue_name = ({ 
"��׶Ѩ","�ٻ�Ѩ","־��Ѩ","�羮Ѩ","�͹�Ѩ","�ڹ�Ѩ","���Ѩ","����Ѩ","����Ѩ",
"����Ѩ","����Ѩ","�׺�Ѩ","��̨Ѩ","�縮Ѩ","���Ѩ","����Ѩ","����Ѩ","����Ѩ",
"˿����Ѩ","����Ѩ","����Ѩ","��׵Ѩ","����Ѩ","����Ѩ",
});

string perform_name(){ return HIG"���־�"NOR; }

int perform(object me, object target)
{
	int ap, dp;
	object weapon;
	string msg, dodge_skill, xue_names;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || environment(target)!=environment(me))
		return notify_fail("��ָ��ֻͨ�ܶ�ս���еĶ���ʹ�á�\n");

	if(  me->query_skill("tanzhi-shentong", 1) < 150 )
		return notify_fail("��ĵ�ָ��ͨ��δ�����ʹ��������ָ��ͨ��\n");

	if(  me->query_skill("bihai-chaosheng", 1) < 150)
		return notify_fail("��ı̺���������δ�����\n");

	if(  me->query_skill("throwing", 1) < 150 )
		return notify_fail("��Ļ���������δ�����ʹ��������ָ��ͨ��\n");

	if(  me->query("max_neili", 1) < 1800 )
		return notify_fail("����ڹ���Ϊ������ʹ����ָ��ͨ������\n");

	if(  me->query("neili", 1) < 1000 )
		return notify_fail("�������������ʹ����ָ��ͨ������\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 && (int)me->query_skill("tanzhi-shentong", 1) < 150)
		return notify_fail("�������޷�ʹ�õ�ָ��ͨ��\n");

	if(weapon && (weapon->query("skill_type") != "throwing"
	 || me->query_skill_mapped("throwing") != "tanzhi-shentong"))
		return notify_fail("�����ڵ������޷�ʹ�õ�ָ��ͨ��\n");

	if( me->query_skill_mapped("parry") != "tanzhi-shentong"
	 || me->query_skill_prepared("finger") != "tanzhi-shentong")
	 	return notify_fail("�������޷�ʹ�õ�ָ��ͨ��\n");

	if ( target->is_busy())
		return notify_fail( target->name(1)+"���Թ˲�Ͼ������Էŵ������ˡ�\n");

	xue_names = xue_name[random(sizeof(xue_name))];

	if(!weapon)
		msg = HIG"\n$NԾ���ڰ�գ����ο�ʼ���ٻζ���ֻ�������͡�֮����һ������Ϯ��$n�ġ�"+xue_names+"����\n"NOR;
	else
		msg = HIG"\n$NԾ���ڰ�գ����ο�ʼ���ٻζ���ֻ�������͡�֮����һ"+ weapon->query("unit") + weapon->name()+HIG"Ϯ��$n�ġ�"+xue_names+"����\n"NOR;

	ap = me->query("combat_exp", 1) /1000 * me->query_skill("tanzhi-shentong", 1);
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("dodge", 1);

	if ( me->query_skill("tanzhi-shentong", 1) >= 400 )
		ap += random(ap/2);

	if ( random( ap + dp ) > dp || target->query_temp("tzst_tan") >= 2) {
		target->add_busy(4 + random(4));
		if ( !weapon)
			msg += HIR"$nֻ���á�"+xue_names+"���ѱ�$N��ָ����У����β��ɵĻ���������\n"NOR;
		else
			msg += HIR"$nֻ���á�"+xue_names+"���ѱ�$N��"+weapon->name()+HIR"���У����β��ɵĻ���������\n"NOR;

		target->delete_temp("tzst_tan");
		me->add("neili", -200);
		me->add("jingli", -100);
	}
	else {
		if ( !userp(target))
			target->add_temp("tzst_tan", 1);
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	}
	message_vision(msg, me, target);
	me->add("neili", -150);
	me->add("jingli", -80);
	me->start_busy(random(2));
	me->start_perform(2, "���־�");
	return 1;
}

int help(object me)
{
        write(HIG"\n��ָ��֮ͨ�����־�����"NOR"\n\n");
        write(@HELP
        Ҫ��  ������� 1800 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                �̺������� 150 �����ϣ�
                �������� 150 �����ϣ�
                ��ָ��ͨ 150 �����ϣ�
                ����ָ�� 120 �����ϣ�
                ����ָ��Ϊ��ָ��ͨ��
                �����м�Ϊ��ָ��ͨ��

HELP
        );
        return 1;
}
