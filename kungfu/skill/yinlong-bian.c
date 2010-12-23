#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action": HIG"$N��$w������Բ��һʽ��Բת���⡹��$w�ѽ�$n$l��ס"NOR,
	"lvl" : 0,
	"skill_name" : "Բת����",
	"damage_type":  "����"
]),
([
	"action": HIW"$N��$w��$n����������������Ȼһ�С��������ס���$n$l����������"NOR,
	"lvl" : 60,
	"skill_name" : "��������",
	"damage_type":  "����"
]),
([
	"action": HIM"$N�������������$w��Ȼ��ɱ�ֱ��һʽ����������������$nֱ�̹�ȥ"NOR,
	"lvl" : 90,
	"skill_name" : "��������",
	"damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if( !me->query("quest/jiuyin2/pass") && !me->query("quest/jiuyin1/pass"))
		return notify_fail("�㲻����ϰ���������ޡ�\n");
	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("���������Ϊ���㣬û�а취�����������ޡ�\n");
	if ( me->query_skill("yinlong-bian", 1) < 150 )
		return notify_fail("��ľ��������޵ȼ���������\n");
//	if ((int)me->query_skill("jiuyin-zhengong", 1) <= (int)me->query_skill("yinlong-bian", 1))
//		return notify_fail("��ľ����湦���̫ǳ��\n");
	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ������޷���\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me)
{
	int i, level, j;
	level   = (int) me->query_skill("yinlong-bian",1);
	for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"damage":	100 + random(180),
				"force":	300 + random(350),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 60)
		return notify_fail("����������������������ޡ�\n");
	if ((int)me->query("neili") < 30 )
		return notify_fail("����������������������ޡ�\n");
	me->receive_damage("jingli", 50);
	me->add("neili",-20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yinlong-bian/" + action;
}
