
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":"$N����һ��$w��һ�С�"+HIY"ʨ��ҡͷ"NOR+"����ǹ�Ϻ�ӧ�������������һ��ǹ������$n$lֱ����ȥ",
	"force" :random(40)+ 125,
	"dodge" : -0,
	"damage": 25,
	"lvl" : 0,
	"skill_name" : "ʨ��ҡͷ",
	"damage_type":  "����"
]),
([      "action":"$N��ת$w��һ�С�"+HIY"�׺羭��"NOR+"����б���Ʋ���ǹ���𴦣�ԲԲһ�ź�Ӱ��ǹ����һ�㺮�⼲��$n����",
	"force" :random(40)+ 160,
	"dodge" : -0,
	"damage": 45,
	"lvl" : 10,
	"skill_name" : "�׺羭��",
	"damage_type":  "����"
]),
([      "action":"$N�߶���������ɣ�����$wһ����ʹ��һ�С�"+HIY"����һ����"NOR+"����$wͦ�ñ�ֱ��Ѹ�����׵ش���$n��$l",
	"force" :random(40)+ 200,
	"dodge" : 10,
	"damage": 55,
	"lvl" : 20,
	"skill_name" : "����һ����",
	"damage_type":  "����"
]),
([      "action":"$Nͦ��$w��һ�С�"+HIY"���ͷ"NOR+"������ӧ������$w�ó����ǹӰ��ǹ����˸��������$n$l�㵽",
	"force" :random(40)+ 250,
	"dodge" : 10,
	"damage": 65,
	"lvl" : 30,
	"skill_name" : "���ͷ",
	"damage_type":  "����"
]),
([      "action":"$Nһ�С�"+HIY"������ŭ"NOR+"����ˢˢˢ������ǹ�����̶�������ӧ�Ұڣ�$w�������죬����һ�����Ȧ�ӣ���ס��$n���¸�·",
	"force" :random(40)+ 300,
	"dodge" : 5,
	"damage": 75,
	"lvl" : 40,
	"skill_name" : "������ŭ",
	"damage_type":  "����"
]),
([      "action":"$NͻȻ���һ����˫��ץסǹ������������$w��ɹ��Σ�ͻȻһ���֣����һ�����մ���$n����һ�С�"+HIY"���ߵ���"NOR+"��",
	"force" :random(40)+ 340,
	"dodge" : 5,
	"damage": 85,
	"lvl" : 50,
	"skill_name" : "���ߵ���",
	"damage_type":  "����"
]),
([      "action":"$NͻȻ̤��һ����$wͦ�ñ�ֱ��ʹ��һ�С�"+HIY"�����Ⱥ"NOR+"����$w������磬������ƥ����$n��$l��ȥ",
	"force" :random(40)+ 380,
	"dodge" : 10,
	"damage": 95,
	"lvl" : 60,
	"skill_name" : "�����Ⱥ",
	"damage_type":  "����"
]),
});

int valid_enable(string usage) { return usage == "spear" || usage == "parry"; }
int valid_learn(object me) { return 1; }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("yangjia-qiangfa",1);

        if ( me->query_temp("yqjf/huimaqiang")){
			return ([
				"action": HIW"$N���һ����˫��ץסǹ������Ȼ��š���ݱۣ������ǹ��ֱ��$n���ţ���һǹ�������ǹ���ġ�����ǹ��" NOR,
                "damage": 150,
                "dodge" : 100,
                "damage_type": "����"]);
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "spear")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("����������������ǹ��\n");
        me->receive_damage("jingli", 20);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yangjia-qiangfa/" + action;
}




