//�ε���
//lestat for daya-jian
//ȡ���ձ�����ά���ڼ䴫˵�е�ɱ������彣�ĵľ�ѧ
//��彣�ĵĽ������ڷ���������,ά���ڼ�ųưε���
//�����佣������,���аε�������,Ҳ�ǴºŰε��������
//����Ϊ�ձ�������һ����

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("�ε���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	message_vision(RED"$N�ս�����Ŀ��ת���ض���$n��׼����������һ����\n"NOR,me,target);
    me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), random(1)+1);
	me->start_busy(5);
	if (userp(target))
		target->start_busy(4);
	if (!userp(target))
		target->start_busy(6);
	return 1;
}
void kill_him(object me, object target)
{
	string msg,str;
	int damage, ap, dp,qixue,eff_qi,max_qi,qi_pcg,force;
	eff_qi=me->query("eff_qi");
	max_qi=me->query("max_qi");
	qi_pcg=eff_qi*100/max_qi;
	force=target->query("force");
	if(me->is_fighting() && target->is_fighting() &&
		environment(me) == environment(target))
	{
		msg = HIB "$N�ν����ʣ�һ������"NOR+HIC"����"NOR+HIB"������$n"NOR+HIB"ֻ��������һ��������" ;
		msg +=  "\nһ��Ѫ����ӿ��������$N��ָ���������վ�ţ�һ�ε���Ѫ���������е��ϵ��£���\n" NOR;

		message_vision(msg, me, target);
		if (!userp(target))
		      str=target->query("name")+"��"+me->query("name")+"�ô�˵�е�ɱ�˽���:"HIC"�ε���"NOR+HIM"ն�ˣ�ʬ���������ϣ�";
		if (userp(target))
		         str=target->query("name")+"��"+me->query("name")+"�ô�˵�е�ɱ�˽���:"HIC"�ε���"NOR+HIM"���ˣ�";
			message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
		if (userp(target))
		{
			target->set("qi", 0);
			target->set("jing",0);
			target->set("eff_qi",eff_qi*random(5)/10);
			target->set("force",1);
			target->set("eff_jing",me->query("eff_jing")*random(5)/10);
			call_out("huifu",5,target,force);
		}
		if (!userp(target))
		target->die();
	}
	return ;
}

void huifu(object target,int force)
{
	if (target)
		target->set("force",force);
}
