// liuyang-zhang.c ��ɽ������
// cck 10/8/97

inherit SKILL;

mapping *action = ({
([
	"action":"$Nһ�š�������������˫��ƮƮ���������裬���Ž��ȣ���$n��$lֱ���˹�ȥ",
	"lvl" : 0,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([
	"action":"$Nʹһʽ��������ѩ����˫���������ޣ������������������ʵĻ���$n��$l",
	"lvl" : 20,
	"skill_name" : "������ѩ",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ��ɽ��ҹ�ѡ�������б�����������ԲȦ���������ص������������",
	"lvl" : 40,
	"skill_name" : "ɽ��ҹ��",
	"damage_type":"����"
]),
([
	"action":"$N˫���������⣬�����ת��ʹ��һʽ������ɽ������˫��������֯��һƬ����",
	"lvl" : 60,
	"skill_name" : "����ɽ��",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ��������̩����˫������������Բ�������˳������綬ȥ�������������",
	"lvl" : 75,
	"skill_name" : "������̩",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ���������ա���������΢��ʵ�������������飬��ʵ����������$n��$l",
	"lvl" : 90,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ��������������˫����£���������磬�������Ѳ��������·��ɣ��������",
	"lvl" : 105,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ�������������˫��һ����ȴ����£��������ʹ�������������ޣ�����Ĩ��",
	"lvl" : 120,
	"skill_name" : "�������",
	"damage_type":"����"
]),
([
	"action":"$Nһ�š����������������������У���������ʵ��Զ������ֱ�����������������ˣ�����������",
	"lvl" : 135,
	"skill_name" : "��������",
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return (usage == "strike") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="zhemei-shou"; }

int valid_learn(object me)
{
	if(!me->query("tonglao/ok"))
		return notify_fail("���޷�ѧϰ��ɽ�����ơ�\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ɽ�����Ʊ�����֡�\n");
	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������������\n");
//	if ((int)me->query_skill("weiwo-duzun", 1) < 100)
//		return notify_fail("��İ˻�����Ψ�Ҷ��𹦻��̫ǳ��\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("liuyang-zhang",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	300+random(350),
				"dodge":	random(30),
				"parry":	random(30),
				"damage":	50 + random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("neili") < 30)
		return notify_fail("���������������ɽ�����ơ�\n");
	if ((int)me->query("jingli") < 60)
		return notify_fail("���������������ɽ�����ơ�\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liuyang-zhang/" + action;
}
