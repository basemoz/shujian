
inherit SKILL;

int valid_enable(string usage) { return usage=="cuff" ||  usage=="parry";}

mapping query_action(object me, object weapon)
{
	return ([
		"action" : "$Nһȭ����$n����Ȼ������Ϣ���������Ƕ㲻���ˡ�",
		//"force" : me->query("gender")=="����"?600:450,
		"force": 100,
		"dodge": 300,
		"parry": 300,
		"attack": 999,
		"damage_type" : "����",
	]);
}

string perform_action_file(string action)
{
	return __DIR__"ciwei-quan/" + action;
}