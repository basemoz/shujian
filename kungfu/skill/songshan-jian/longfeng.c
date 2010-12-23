// longxiang.c ��������
// by xiaoyao 4/19/2k

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl, j, focus;
        object weapon;

	lvl = me->query_skill("songshan-jian", 1);
	focus = me->query_temp("ss/focus") + 1;
	weapon = me->query_temp("weapon");

	if (!target ) target = offensive_target(me);

	if (!objectp(target) 
	|| !me->is_fighting(target) )
		return notify_fail("���������衹ֻ����ս���жԶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("�����ʹ�ý�����ʹ�á��������衹��\n");

	if (me->query_skill("songshan-jian", 1) < 300 )
		return notify_fail("�����ɽ������������죬ʹ�������������衹������\n");

	if (me->query_skill("hanbing-zhenqi", 1) < 300 )
		return notify_fail("��ĺ������������ߣ��޷�ʹ�á��������衹��\n");

	if (me->query_skill("songyang-shou", 1) < 300 )
		return notify_fail("��Դ���������ʶ��������\n");

	if ( me->query_skill("force") < 400 )
		return notify_fail("����ڹ��ȼ�������ʹ�������������衹������\n");

	if ( me->query_str(1) < 35)
		return notify_fail("�������������ǿ����ʹ�������������衹������\n");

	if (me->query_skill_prepared("hand") != "songyang-shou"
	|| me->query_skill_mapped("hand") != "songyang-shou")
		return notify_fail("���������衹��Ҫ�ô������ָ�����\n");

	if ( me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian")
		return notify_fail("�����ڵ�״̬ʹ�������������衹������\n");

	if ( me->query_temp("ss_lf"))
		return notify_fail("������ʹ�á��������衹�أ�\n");

	if ( me->query("max_neili") < 2500 )
		return notify_fail("����������̫����ʹ�������������衹��\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("����������̫����ʹ�������������衹��\n");

	if ( me->query("jingli") < 1000 )
		return notify_fail("�����ھ���̫����ʹ�������������衹��\n");

	msg = HIR"\n$N�������Ĵָ��ʳָ����ָ������ָ����ס�˽��⣬����һ�ɣ�"+weapon->name()+HIR"ͻȻ���𣬽�����ǰ����ס�ػζ���\nͻȻ$N����$n���ٹ������˽���һ������һ�������ڿն����԰���к��������������ֱ��ٿ������$n��\n\n"NOR;
	message_vision(msg, me, target);
	if(me->query_temp("ss/hb"))
			message_vision(HIB"\n$N�����������������ӵ����쾡�£����ܺ����ʢ��\n" NOR,me,target);

	me->set_temp("ss_lf", 1);

	if ( focus > 15) focus = 15;

	j = lvl/ 5;

	if ( lvl > 200 )
		j = to_int( lvl/5.0 * lvl/ 200.0);

	j += focus * 5;
	
	if(target->is_busy()) j += j / 2;
	
	me->add_temp("apply/attack", j * 2);
	if(me->query_temp("ss/hb"))
		me->add_temp("apply/damage", j);

	me->add_temp("apply/damage", j/3);
   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/damage", -j/3);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->unequip();
   COMBAT_D->do_attack(me, target, 0, 3);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->wield();
	me->add_temp("apply/damage", j/2);
   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lvl<350)?1:3);
	me->add_temp("apply/damage", -j/2);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->unequip();
   COMBAT_D->do_attack(me, target, 0, 3);
	message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

	weapon->wield();

	if ( lvl > 350 ){
		me->add_temp("apply/damage", j/2);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lvl<450)?1:3);
		me->add_temp("apply/damage", -j/2);
	}
	if(me->query_temp("ss/hb"))
		me->add_temp("apply/damage", -j);
	me->add_temp("apply/attack", -j * 2);
	me->delete_temp("ss_lf");
	me->add("neili", -500);
	me->add("jingli", -200);
	me->start_busy(random(2));
   me->start_perform(4+random(2),HIR"���������衹"NOR);
	return 1;
}

string perform_name(){ return HIR"��������"NOR; }

int help(object me)
{
        write(HIR"\n��ɽ����֮���������衹��"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 1500 ���ϣ�
                ������� 2500 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                ��ɽ�����ȼ� 300 ���ϣ�
                ���������ȼ� 300 ���ϣ�
                �������ֵȼ� 300 ���ϣ�
                ��Ч�ڹ��ȼ� 400 ���ϣ�
                ��������Ϊ��ɽ������
                �����м�Ϊ��ɽ������
                �����ַ�Ϊ�������֣�
                ���ַ�Ϊ�������֣�
                ���ֱֳ�����

HELP
        );
        return 1;
}
