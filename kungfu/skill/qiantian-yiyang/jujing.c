// jujing.c �۾�����
// by augx@sj  6/11/2002

#include <ansi.h>

int exert(object me)
{
	int i;

	if ( me->query("tls"))
		return notify_fail("���Ѿ������ˣ���ô���ô����׼��书��\n");

	if ( me->query("family/master_name") != "һ�ƴ�ʦ" )
		return notify_fail("���һ�Ƶ��ӣ����������ܲ�����ô������������\n");

	if (me->query_skill("qiantian-yiyang",1) < 300 )
		return notify_fail("���Ǭ��һ����������죬�޷����۾���������\n");

	if( me->query_skill_mapped("force") != "qiantian-yiyang" )
		return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

	if ( me->query_skill("yiyang-zhi", 1) < 300 )
		return notify_fail("���һ��ָ�ȼ��������޷����۾���������\n");

	if ( me->query_skill_mapped("finger") != "yiyang-zhi"
	|| me->query_skill_prepared("finger") != "yiyang-zhi") 
		return notify_fail("�������һ��ָʹ�á��۾���������\n");

	if (me->query("max_neili") < 6000  )
		return notify_fail("����ھ���Ϊ������\n");

	if (me->query("neili") < 3000  )
		return notify_fail("�������������\n");

	if (me->query("max_jing") < 2000  )
		return notify_fail("��ľ�Ѫ���㡣\n");

	if (me->query("jing") < 2000  )
		return notify_fail("��ľ�Ѫ���㡣\n");

	if (me->query_temp("dali/jujing"))
		return notify_fail("���Ѿ�ʹ�á��۾��������ˡ�\n");

	message_vision(HIY"\n$N�����������ɫ���䣬ֻ�о�ͷ��һ���ӿհף���ɫ��������ࡣ\n"NOR, me);

	i = me->query_skill("qiantian-yiyang",1);
	i = i * i / 60;
	i = MIN(i,me->query("jing")-100);
	i = MIN(i,me->query("neili"));

	me->add("neili", -i);
	me->add("max_jing",-i);
	me->add("eff_jing",-i);
	me->add("jing",-i);
	me->add("max_qi",i);
	me->add("eff_qi",i);
	me->add("qi",i);

	me->set_temp("dali/jujing", i);
	me->set("dali/jujing", i);
	me->set_temp("dali/jujing1", 0);
	if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(3, "�۾�����");

	call_out("remove_effect", 6, me, 3+me->query_skill("qiantian-yiyang", 1)/50);
	return 1;
}

void remove_effect(object me, int tick)
{
	int i;

	if(!me) return;
	if( me->query_skill_mapped("force")!="qiantian-yiyang" || !tick ) {
		tell_object(me, HIY"\nʱ��һ������о�֧�ֲ�ס������ʼ��ɢ�ˡ�\n" NOR);
		i = me->query_temp("dali/jujing");
		me->delete_temp("dali/jujing");
		me->delete("dali/jujing");
		me->delete_temp("dali/jujing1");

		me->add("max_jing",i);
		me->add("eff_jing",i);
		if( me->query("jing") > me->query("eff_jing") )
			me->set("jing",me->query("eff_jing"));

		me->add("max_qi",-i);
		if( me->query("eff_qi") > me->query("max_qi") )
			me->set("eff_qi",me->query("max_qi"));
		if( me->query("qi") > me->query("eff_qi") )
			me->set("qi",me->query("eff_qi"));
		return;
	}
	call_out("remove_effect", 6, me, tick-1);
}

string exert_name(){ return HIY"�۾�����"NOR; }

int help(object me)
{
	write(HIY"\nǬ��һ����֮���۾���������"NOR"\n\n");
        write(@HELP
	�۾�������һ�ƴ�ʦ������������֮���칦������ѧ�в�������ģ�
	���ֻ���ڸ��׼ҵ��ӡ�

	Ҫ��	��ǰ���� 550 ���ϣ�
		Ǭ��һ�����ȼ� 300 ���ϣ�
		һ��ָ�ȼ� 300 ���ϣ�
		����ָ��Ϊһ��ָ����ָ��Ϊһ��ָ��
		����Ϊ�׼ҵ��ӡ�

HELP
        );
        return 1;
}
