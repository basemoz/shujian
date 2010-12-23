// huayu.c ���컨��

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return CYN"���컨��"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
	int damage, num, lvl, p, ap, dp;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("���컨��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!(me->query("thd/perform") & 16))
		return notify_fail("����Ȼ��˵�������컨�ꡱ��һ�У�����ȴδ���ڡ�\n");

	lvl = me->query_skill("tanzhi-shentong", 1);

	if (lvl < 120)
		return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʹ�����컨�ꡣ\n");

	if (me->query_skill("throwing", 1) < 120)
		return notify_fail("��Ļ�������������죬�޷�ʹ�����컨�ꡣ\n");

	if ( me->query_skill_mapped("parry") != "tanzhi-shentong"
	|| me->query_skill_mapped("throwing") != "tanzhi-shentong")
		return notify_fail("�����ڵ�������޷�ʹ�����컨�ꡣ\n");

	if ( me->query_skill("bihai-chaosheng", 1) < 120 )
		return notify_fail("��ı̺��������ȼ��������޷�ʹ�����컨�ꡣ\n");

	weapon = me->query_temp("weapon");

	if (!weapon)
		return notify_fail("���컨�����װ����������ʹ�á�\n");

	if ((num = weapon->query_amount()) < lvl / 20)
		return notify_fail("�������ͱ��ң���������İ����Ѿ�����ʹ�����컨���Ҫ���ˣ�\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷�ʹ�����컨�ꡣ\n");

	if (me->query("jingli") < 900)
		return notify_fail("��ľ����������޷�ʹ�����컨�ꡣ\n");

	msg = HIW"\n$N˫���ڱ�����һץ��ץ��" + CHINESE_D->chinese_number(lvl / 20) + weapon->query("base_unit") + weapon->query("name") + HIW"��������ָ������ص��˳�ȥ��$nֻ����ǰ�ƺ�����һ�������꣡\n"NOR;

	damage = lvl * 2 + (int)me->query_skill("bihai-chaosheng", 1);
	damage *= 3;
	damage += random(damage);
	if ( damage > 4000 )
		damage = 4000 + (damage -4000 )/10;

	ap = me->query("combat_exp")/1000 * me->query_str(1);
	dp = target->query("combat_exp")/1000 * target->query_dex(1);

	if (target->is_busy())
		dp -= dp/3;

	if (random(ap + dp ) > dp ) {
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		msg += "$n���������������ۡ��ؼ������������������У�\n";
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3+random(damage/3), me);
		me->add("neili", -400);
		me->add("jingli", -100);
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg += COMBAT_D->damage_msg(damage, "����");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
	}
	else {
		me->add("neili", -150);
		me->add("jingli", -50);
		msg += "$n�ŵø�æ��ͷ��������Ǳ������Ա�һ�������ſ����ض��˹�ȥ��\n" NOR;
		target->add_busy(random(2));
	}
	message_vision(msg, me, target);
	me->start_perform(2, "�����컨�꡹");
	me->start_busy(random(2));
	if (num == lvl / 20) {
		weapon->unequip();
		tell_object(me, "\n���" + weapon->query("name") + "�����ˣ�\n");
	}
	weapon->add_amount(-(lvl/20));
	return 1;
}

int help(object me)
{
        write(CYN"\n��ָ��֮ͨ�����컨�꡹��"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 1000 ���ϣ�
                ��ǰ���� 900 ���ϣ�
                ��ָ��ͨ 120 �����ϣ�
                �̺������� 120 �����ϣ�
                ��������Ϊ��ָ��ͨ��
                �����м�Ϊ��ָ��ͨ��
                װ��һ�������İ������辭�û�ҩʦ��ָ�㡣

HELP
        );
        return 1;
}
