// maze.c ���Ű�������

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, object target, int count, int skill);

int exert(object me, object target)
{
	string msg;
	int skill, ap, dp;
//<Added by mxzhao 2005/02/10>
	int count = 3;
//</Added by mxzhao 2005/02/10>

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_temp("thd/mazed")) 
		return notify_fail("������������˲��������С�\n");

	if(me->query("neili") < 600  ) 
		return notify_fail("�������������\n");

	if(me->query("jingli") < 400  )
		return notify_fail("��ľ���������\n");

	if(me->query_skill("bihai-chaosheng", 1) < 120)
		return notify_fail("��ı̺��������ȼ�������\n");

	if( me->query_skill_mapped("force") != "bihai-chaosheng")
		return notify_fail("����뼤���̺���������\n");

	if(me->query_skill("qimen-bagua", 1) < 120 )
		return notify_fail("������Ű��Եȼ�������\n");

	if(me->query_temp("thd/maze")) 
		return notify_fail("���Ѿ�����һ�������ˡ�\n");

	skill = me->query_skill("qimen-bagua", 1);

	me->add("neili", -150);
	me->add("jingli",- 50);

	me->start_exert(2, "�����Ի���");
	me->start_busy(random(2));

	if ( !me->is_perform())
		me->start_perform(2, "�����Ի���");

	msg = HIY"\n$NͻȻԾ������һ�ƣ�����һ�ȣ�����Χ��ʯ�顢��֦�ƶ���λ�ã�";

	me->add_temp("apply/armor", skill/4);
	me->set_temp("thd/maze", skill/4);

	ap = me->query("combat_exp", 1);
	dp = target->query("combat_exp", 1);

	if( random( ap + dp ) > dp ) {
		msg += "$n���������У���ʱ�����޴롣\n"NOR;
		target->add_temp("apply/dexerity", -(skill/10));
		target->add_temp("apply/damage", -(skill/10));
		target->add_temp("apply/dodge", -(skill/10));
		target->set_temp("thd/mazed", 1);
		target->add_busy(3 + random(2));
		me->add("neili", -100);
		me->add("jingli",-100);
		me->set_temp("thd/maze_target", target);
//<Added by mxzhao 2005/02/10>
		count = skill/2;
//</Added by mxzhao 2005/02/10>
	}
	msg += "\n"NOR;
	message_vision(msg, me, target);
//<Modified by mxzhao 2005/02/10>
//	call_out("remove_effect", 1, me, target, skill / 2, skill);
	call_out("remove_effect", 1, me, target, count, skill);
//</Modified by mxzhao 2005/02/10>
	return 1;
}

void remove_effect(object me, object target, int count, int skill)
{
	if (objectp(me) && me->query_temp("thd/maze")){
		if (count-- > 0 && me->is_fighting(target)) {
			call_out("remove_effect", 1, me, target, count, skill);
			return;
		}
		me->add_temp("apply/armor", - (skill/4));
		me->delete_temp("thd/maze");
		if (!target || target->is_ghost(1)) return;
		me->delete_temp("thd/maze");
		me->delete_temp("thd/maze_target");
		if (target && me->is_fighting(target)) {
			tell_object(me, "�㲼�������Ѿ���" + target->name(1) + "�ƻ��ˡ�\n");
			if (userp(target) && living(target))
				tell_object(target, me->name(1) + "���㲼�������Ѿ�����ʶ���ˡ�\n");
		}
		else {
			tell_object(me, "�㲼�������Ѿ�ʧЧ�ˡ�\n");
		}
	}
	if (objectp(target) && target->query_temp("thd/mazed")){
		target->delete_temp("thd/mazed");
		target->add_temp("apply/dexerity", skill/10);
		target->add_temp("apply/dodge", skill/10);
		target->add_temp("apply/damage", skill/10);
	}
}

string exert_name(){ return HIY"����"NOR; }

int help(object me)
{
        write(HIY"\n�̺�������֮�����󡹣�"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 600 ���ϣ�
                ��ǰ���� 400 ���ϣ�
                �̺��������ȼ� 120 ���ϣ�
                ���Ű��Եȼ� 120 ���ϣ�
                �����ڹ�Ϊ�̺���������

HELP
        );
        return 1;
}
