//xunlei-jian by cool
//��Ѹ��������ɫ�������auto��ͻ-----by daidai 2007-06-26
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N�������ң�����һ�ܣ�һʽ������ָ·����$wͻȻ��$n��$l��ȥ",
        "lvl" : 0,
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ��һʽ�����ӷ�����������ղ෭��һ�������´̳�",
        "lvl" : 5,
	"damage_type" : "����"
]),
([
	"action" : "$N���ֽ�ָѪָ������$wʹ��һ�С�����Ѱ�롹��������������$n��$l����",
        "lvl" : 10,
	"damage_type" : "����"
]),
([
	"action" : "$N��������$w�����ڱ��£�һ�С���Գ̽������������������$n��$l",
        "lvl" : 15,
	"damage_type" : "����"
]),
([
	"action" : "$N̤����ǰ��һʽ������Ѱ�ߡ������г����ڶ����������$n��$l",
        "lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С�б����֦�������屳ת������$w���Ҽ��Ϸ��������´̳�",
        "lvl" : 25,
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ�������׶����������з棬�������ϣ���$n���������ؽ���֮��",
        "lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : "$N��ǰ����һ�С�����Ҿ�֡���$w��Ȼ�����´̳���������������",
        "lvl" : 35,
	"damage_type" : "����"
]),
([
	"action" : "$N����$w�����һζ���һ�С����������������ֱ��$n������Ҫ��",
        "lvl" : 45,
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ֳֽ�����$w������ʹ��һ�С��ٻ����졹���������$n��ǰ�Ϸ���ȥ",
        "lvl" : 55,
	"damage_type" : "����"
]),
([
	"action" : "$N������$n��ʹ��һ�С�����ն�㡹���Ӷ�����$w��ֱ��$n������·",
        "lvl" : 65,
	"damage_type" : "����"
]),
([
	"action" : "$N����$w��������һ�С���Ů���롹��$wͻȻ���ִ���$n��$l",
        "lvl" : 75,
	"damage_type" : "����"
]),
([
	"action" : "$N������ǰ��������ָ��һ�С���Գ��֦����$w����$n��ͷ��Ҫ��",
        "lvl" : 85,
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С�����ӱޡ���$w�����ߣ�����һ����������$nȫ����������",
        "lvl" : 95,
	"damage_type" : "����"
]),
([
	"action" : "$N�������£�һ�С����ƿ�������$w��Ȼ��תֱ�ϣ�������$n������Ҫ������Χס",
        "lvl" : 110,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 30)
		return notify_fail("��������޼������̫ǳ��\n");
	if ((int)me->query_skill("sword", 1) < 20)
		return notify_fail("��Ļ����������̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("xunlei-jian",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
if( random(level) >= 100 && random(10) > 5 && !me->query_temp("kl/podi") ) {
				return ([
"action" : HIB+replace_string(replace_string(action[NewRandom(i, 20, level/5)]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR,
					"damage": 90 + random(100),
					"damage_type": "����",
					"dodge":  random(30) + 10,
					"force":  300 + random(180),
					"parry": random(35),
				]);
			}
                        if ( me->query_temp("kl/podi")){
if(level>350)
				return ([
//                                         "action": action[j]["action"],
"action" :RED+replace_string(replace_string(action[NewRandom(i, 20, level/5)]["action"], "$w", "$W"), "$W", "$w"RED)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
                                        "force": 350 +random(200),
                                        "dodge": 20+random(20),
                                        "parry": 20+random(10),
                                        "damage": 140 +random(60),
 ]);
else
return ([
"action" : HIC+replace_string(replace_string(action[NewRandom(i, 20, level/5)]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR,
                                        "lvl": action[j]["lvl"],
                                        "damage_type": action[j]["damage_type"],
                                        "force": 350 +random(200),
                                      "dodge": 20+random(20),
                                        "parry": 20+random(10),
                                       "damage": 140 +random(60),
                                ]);
			}
			else {
				return ([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 150 +random(300),
					"dodge": random(30),
					"parry": random(30),
					"damage": 60 +random(100),
				]);
			}
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xunlei-jian", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("�������������Ѹ�׽�����\n");
	if ( me->query("neili") < 20)
		return notify_fail("�������������Ѹ�׽�����\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xunlei-jian/" + action;
}
