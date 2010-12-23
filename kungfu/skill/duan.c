#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
	string msg; 
	int lvl, j;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("���ϡ��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( me->query("neili") < 1500 || me->query("max_neili") < 2000 )
		return notify_fail("�������������\n");

	if( me->query_skill("wuhu-duanmendao") < 150 )
		return notify_fail("��ġ��廢���ŵ����������ң��޷�ʹ�á��ϡ��־���\n");

	if( me->query_skill_mapped("blade") != "wuhu-duanmendao" )
		return notify_fail("�����ʹ�á��廢���ŵ���������ʹ�á��ϡ��־���\n");

	msg = HIY"\n$N��Ȼ���أ�ʹ�����õ���"HIR"��"HIY"���־�����ʱһƬ�׹�ֱ��$n��ȥ��\n"NOR;
	message_vision(msg, me, target);

	lvl = me->query_skill("wuhu-duanmendao", 1);
	j = lvl/3;

	if( lvl > 200 )
		j = to_int( lvl/3.0 * lvl/200.0);


	if( wizardp(me) ) {
		tell_object(me,HIW"�廢���ŵ�����Ч�ȼ�Ϊ: "+j+" \n"NOR);
	}

	me->add_temp("apply/blade", j);
	me->add_temp("apply/attack", j);
	me->add_temp("apply/damage", j/2);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/blade", -j);
	me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j/2);

	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(2, "���־�");
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HIY"���־�"NOR; }

int help(object me)
{
	write(HIY"\n�廢���ŵ�֮�����־�����"NOR"\n\n");
	write(@HELP
	Ҫ��	��ǰ���� 1500 ���ϣ�
		������� 2000 ���ϣ�
		�廢���ŵ��ȼ� 150 ���ϣ�
		�����м�Ϊ�廢���ŵ���
		�ֱֳ�����

HELP
        );
        return 1;
}
