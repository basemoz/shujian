// �ȱ���(cibei-fofa.c)

inherit SKILL;

int valid_learn(object me)
{
	if (!me->query("reborn\fofa"))
		return notify_fail("��ҵ��δ�������ϰ�𷨣�\n");
	return 1;
}
