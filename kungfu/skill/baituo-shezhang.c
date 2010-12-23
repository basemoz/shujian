// baituo-shezhang.c ��������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N�߸�Ծ�𣬻��������е�$wһ�С�һ�����졹����һ����������$n��ͷֱ�����",
	"lvl" : 0,
	"damage_type": "����"
]),
([
	"action": "$Nһ�����ȡ���ɨǧ��������$w��������һ�ã�˫����ס$wβ��ת���͵ú�ɨ����$n��$l",
	"lvl" : 10,
	"damage_type": "����"
]),
([
	"action": "$N��Ȼ����һ�䣬ʹ�������߳��������ȷ��Ե�����֮��������$w����������Ӱ����$n",
	"lvl" : 20,
	"damage_type": "����"
]),
([
	"action": "$N���ȴ�����$w�й�ֱ��������һ����̳�������$n��$l�������С����߻�����",
	"lvl" : 40,
	"damage_type": "����"
]),
([
	"action": "$Nһʽ��һ�ȶ���������ͷһ$w������������ͷδ����һ�ɷ��ѽ�$n�Ƶ����Դ���",
	"lvl" : 60,
	"damage_type": "����"
]),
([
	"action": "$N���С�Ⱥ�߿��衹��$wɨ��һ������Ӱ������˷�Χ��$n��Ҫ��$n��û��ʳ",
	"lvl" : 80,
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="staff" || usage=="parry"; }

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me)
{
	object target, weapon; 
	int i, level, lvl, j;

	target = offensive_target(me);
	if (target->query_temp("weapon"))
		weapon = target->query_temp("weapon");
    
	lvl = random((int)me->query_skill("baituo-shezhang",1));
      
	if (me->query_skill("baituo-shezhang",1) > 100
	&& me->query("neili") > 1000 
	&& random(5) > 3 
	&& random(me->query("combat_exp")) > target->query("combat_exp")/2){
		me->add("neili", -20);            
		return ([
			"action":	HIC"������ʽ���ϣ�$N������$w˳��һ�Σ��ȼ�ֱ�����£�����һ����������$n��"NOR,
			"force":	400+random(250),
			"dodge":	30,
			"parry":	30,
			"damage":	180 +random(100),
			"damage_type":	"����"
		]);
	}
	if (objectp(weapon) 
	&& weapon->query("skill_type") == "stick" 
	&& target->query_skill_mapped("stick") == "dagou-bang"
	&& lvl > target->query_skill("bagou-bang",1)/2 
	&& me->query("neili") > 100 
	&& lvl >= 140 
	&& me->query("oyf_hamagong") > 2) {                                                    
		me->add("neili", -100);
		return ([
			"action":	HIC"$N��������ֱͦ�����۹��������ϣ��������Ʈ�ڣ����ȼ�������籩��Ҳ���ƶ���\n"+
					"����ֱָ$n�Ŀڣ����Ǵ򹷰�����ʮ��·�����������޹����ĵ�����İ������ڣ�"NOR,
			"force" :	600,
			"dodge" :	random(30),
			"parry":	random(35),
			"damage":	180 +random(150),
			"damage_type":	"����",
		]);
	}
	level   = (int) me->query_skill("baituo-shezhang",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"parry":	random(30),
				"dodge":	random(30),
				"force":	300 + random(350),
				"damage":	100 + random(180),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 60)
		return notify_fail("������������ˡ�\n");
	if ((int)me->query("neili") < 30)
		return notify_fail("������������ˡ�\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

int valid_learn(object me)
{
	object weapon;

	if( (int)me->query("max_neili") < 500 )
		return notify_fail("����������㣬û�а취����������, ����Щ���������ɡ�\n");

	if (!me->query_skill("hamagong", 1) || me->query_skill("hamagong", 1) < 50)
		return notify_fail("��ĸ�󡹦���̫ǳ��\n");

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "staff" )
		return notify_fail("�����ʹ�����������ȷ���\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"baituo-shezhang/" + action;
}
