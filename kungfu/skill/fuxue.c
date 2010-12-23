// fuxue.c ������Ѩ
// Created by Numa 19990927

#include <ansi.h>

inherit F_SSERVER;

string *xue_name = ({
"����Ѩ","����Ѩ","����Ѩ","�׺�Ѩ","��̨Ѩ","�縮Ѩ","���Ѩ","����Ѩ",
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
}); 

void remove_effect(object me);

int perform(object me, object target)
{
	string msg,name;
	int p, ap, dp, damage;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("��������Ѩ��ֻ����ս���жԶ���ʹ�á�\n");

	if( me->query_temp("weapon") )
		return notify_fail("��������ʹ�á�������Ѩ����\n");

	if( me->query_skill("lanhua-shou",1) < 180 )
		return notify_fail("���������Ѩ�ֻ�������죬������������������Ѩ���ġ�׼���֡�\n");

	if( me->query_skill("suibo-zhuliu",1) < 180 )
		return notify_fail("����沨������������죬������������������Ѩ���ġ��졹�֡�\n");

	if( me->query_skill("qimen-bagua",1) < 180 )
		return notify_fail("������Ű��Ի�������죬������������������Ѩ���ġ��桹�֡�\n");

	if (me->query_skill_mapped("force") != "bihai-chaosheng")
		return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

	if( me->query("neili") < 700 )
		return notify_fail("�������̫���ˣ��޷�ʹ����������Ѩ����\n");

	if( me->query("jingli") < 500 )
		return notify_fail("��ľ���̫���ˣ��޷�ʹ����������Ѩ����\n");

	if (me->query_skill_prepared("hand") != "lanhua-shou"
	 || me->query_skill_mapped("hand") != "lanhua-shou"
	 || me->query_skill_mapped("parry") != "lanhua-shou" )
		return notify_fail("�������޷�ʹ�á�������Ѩ�����й�����\n");                                         

	name = xue_name[random(sizeof(xue_name))];

	ap = me->query("combat_exp") / 1000 * me->query_skill("hand");
	dp = target->query("combat_exp")/1000 * target->query_skill("parry");

	if ( target->is_busy())
		dp -= dp/4;

	if ( me->query_skill("lanhua-shou", 1) > 350 )
		ap += random(ap/2);

	damage = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("hand") + me->query_skill("qimen-bagua", 1);
	damage *= 2;

// ���� ��
	if (me->query("eff_qi") >= ( me->query("max_qi") + me->query_temp("apply/qi")) / 2){
		msg = HIC"\n$N���ֻӳ���Ĵָ��ʳָ����������ָ���ţ���ָ��һ֦���������������$n�����������Ѽ���\n" NOR;

                if( random(ap + dp ) > dp ) {
			msg += CYN"$nֻ�С�"RED + name + CYN"����һ�飬��$N����Ѩ����\n"NOR;
			damage += random(damage);
			if ( damage > 4500 )
				damage = 4500 + (damage - 4500)/10;
			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/3 + random(damage/3), me);
			if (random(2)) {
				p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += COMBAT_D->damage_msg(damage, "����");
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			}
			else {
				p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += COMBAT_D->damage_msg(damage, "����");
				msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
			}
			msg = replace_string( msg, "$w", "����ָ��");
			msg = replace_string( msg, "$l",  name);
			me->add("neili",- 400);
			me->add("jingli",- 150);
			target->add_busy(random(2)+2);
			me->start_perform(3, "������Ѩ");
		}
		else {
			msg += CYN"$nֻ�С�"RED + name + CYN"����һ�飬�ֱۼ������������Ѹ�٣�û��$N����Ѩ����\n"NOR;
			me->start_perform(2, "������Ѩ");
			me->add("neili",-100);
			me->add("jingli",-80);
		}
		message_vision(msg, me, target);
		me->start_busy(1);
		me->set_temp("lanhua-fuxue", 1);
		return 1;
	}
// ������ ��
	else {
		msg = HIC"\n$N���ֻӳ���Ĵָ��ʳָ����������ָ���ţ���ָ����бб�ط���$n��\n" NOR;
		if( random(ap + dp ) > dp ) {
			msg += CYN"$nֻ�С�"RED + name + CYN"����һ�飬��$N����Ѩ����\n"NOR;
			damage += random(damage/2);
			damage *= 2;

			if ( damage > 8000 )
				damage = 8000 + (damage - 8000)/10;

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/2 + random(damage/2), me);

			if (random(2)) {
				p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += COMBAT_D->damage_msg(damage, "����");
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			}
			else {
				p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
				msg += COMBAT_D->damage_msg(damage, "����");
				msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
			}
			msg = replace_string( msg, "$w", "����ָ��");
			msg = replace_string( msg, "$l",  name);
			me->add("neili",- 500);
			me->add("jingli",- 200);
			target->add_busy(random(2)+ 3);
			me->start_perform(4, "������Ѩ");
		}
		else {
			msg += CYN"$nֻ�С�"RED + name + CYN"����һ�飬�ֱۼ������������Ѹ�٣�û��$N����Ѩ����\n"NOR;
			me->start_perform(2, "������Ѩ");
			me->add("neili",-100);
			me->add("jingli",-80);
		}
		message_vision(msg, me, target);   
		me->start_busy(1);
		me->set_temp("lanhua-fuxue", 1);
		return 1;
	}
}

string perform_name(){ return HIC"������Ѩ"NOR; }

int help(object me)
{
	write(HIC"\n������Ѩ��֮��������Ѩ����"NOR"\n\n");
	write(@HELP
	Ҫ��	��ǰ���� 700 ���ϣ�
		��ǰ���� 500 ���ϣ�
		������Ѩ�ֵȼ� 180 ���ϣ�
		���Ű��Եȼ� 180 ���ϣ�
		�沨�����ȼ� 180 ���ϣ�
		�����ڹ�Ϊ�̺���������
		�����ַ�Ϊ������Ѩ�֣�
		�����м�Ϊ������Ѩ�֣�
		���ַ�Ϊ������Ѩ�����ޱ�����

HELP
	);
	return 1;
}
