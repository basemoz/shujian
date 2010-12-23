// bahuang-gong.c �˻�����Ψ�Ҷ���

inherit FORCE;

#include "force.h"

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{	
	if (me->query_skill("force", 1) < 10)	
		return notify_fail("��Ļ����ڹ�����Ҫ��һ����ߡ�\n");
	if ((int)me->query_skill("bahuang-gong", 1) > me->query_skill("force", 1) + 10	
	 && me->query_skill("bahuang-gong", 1) >= 200 )	
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
	return valid_public(me);
}

int practice_skill(object me)
{	
	return notify_fail("�˻�����Ψ�Ҷ���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{	
	return __DIR__"bahuang-gong/" + func;
}
