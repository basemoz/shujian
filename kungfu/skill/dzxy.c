// douzhuan-xingyi ��ת����
// 1997-2-14
// Modified by Darken@SJ
// rewrite by athoi@sj 2004.03.28

#define DAMAGE_TYPE 	""
#define LEVEL 		ADVANCED
#define LEARN_TYPE 	"parry"

#include <ansi.h>
inherit SKILL;

string *attack_action = ({
YEL"�����һ��������������$nһ��һ����$N��������Խ����������һ��"NOR,
BLU"$N����һ����������$n��$n����$N����Ī��������ﻬ��һ��"NOR,
HIW"$N˫��ǰ̽����۴���$n�ұۣ��ұ�ʹ��$n��������$n���л�ȥ"NOR,
HIY"$N���ƶ�ת��$n����Ī�����������;ת�˷���ֱ���Լ�Ϯ��"NOR,
YEL"$N�����Ϲۣ�˫����Է��ཻ���ƣ���ʹ��$n�������գ�ʹ��$n��֪����Ǻ�"NOR,
BLU"$N����������$n�͹����ʹ������������$n�ĳ�����������$n��������������"NOR,
HIW"ֻ��$N����Ʈ�磬ǡ���������ƣ������һʽ��˫�ƶ����޶�����׽��������$n"NOR,
HIY"$N����Ʈ�������������ƶ�ת֮�䷴��$n����������$n����$n��˼�������"NOR,
});

string query_parry_msg(object weapon)
{
        return attack_action[random(sizeof(attack_action))] + "��\n";
}

string force = "shenyuan-gong";

#include <skills.h>

int valid_enable(string usage)
{
	if (usage == "force" || usage == "dodge" || usage == "unarmed")
		return 0;
	else
		return 1;
}

mapping query_action(object me, object weapon)
{
	int power = 0;
	string color = "";
	mapping action;
        
        action = get_action(me, weapon, power, color);
        action["parry"] = action["parry"]?action["parry"]:me->query_con("postnatal") / 2;
        return action;
}

int learn_check(object me, object weapon)
{
        return notify_fail("��ת����ֻ��ͨ����������ߡ�\n");
}
