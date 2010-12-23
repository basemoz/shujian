// quanzhen-jianfa ȫ�潣��
// Modify By River 99.5.26
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N��Ӱ�ζ���̤���ţ���ƫ�棬һʽ���ֻ�������������$n��$l",
	"lvl" : 0,
	"skill_name" : "�ֻ�����",
	"damage_type" : "����"
]),
([
	"action" : "$N��ǰԾ��һ�������ֽ��������ֽ�ʹ��һʽ������Į����ֱ��$n��$l",
	"lvl" : 10,
	"skill_name" : "����Į��",
	"damage_type" : "����"
]),
([
	"action" : "$N�β�ͦ����һʽ����ɽ�����������н������ޱȣ������ӽ�ײ��$n��$l",
	"lvl" : 25,
	"skill_name" : "��ɽ����",
	"damage_type" : "����"
]),
([
	"action" : "$N����΢�࣬��������һ���һ���󻡣�һʽ��˳ˮ���ۡ���ƽƽ����$n��$l��ȥ",
	"lvl" : 30,
	"skill_name" : "˳ˮ����",
	"damage_type" : "����"
]),
([
	"action" : "$N����š���������鱧��Բ��һʽ�������仨�������й�ֱ��������$n��$l",
	"lvl" : 50,
	"skill_name" : "�����仨",
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ������ٵء�����������������������ֱ����Ю����֮����Ȼն��$n��$l",
	"lvl" : 70,
	"skill_name" : "����ٵ�",
	"damage_type" : "����"
]),
([
	"action" : "$N����ʩ�����׵罻�ӡ�������Ƴ�һ����â��������ƿ�����$n��$l",
	"lvl" : 90,
	"skill_name" : "�׵罻��",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�Ȱ�����ף�һʽ�����񹲷ߡ������⻮������ԲȦ����������������",
	"lvl" : 110,
	"skill_name" : "���񹲷�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry"); 
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if( ! me->query_skill("xiantian-gong"))
	if ((int)me->query_skill("yunu-xinjing", 1) < 20)
		return notify_fail("�����Ů�ľ����̫ǳ��\n");
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
	int i, j, level,xtg;
	level = me->query_skill("quanzhen-jianfa",1);
	xtg = me->query_skill("xiantian-gong", 1);

	for(i = sizeof(action); i > 0; i--){
		if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("hebi") && random(2)) { 
				return ([  
					"action" :random(2)? HIW+action[j]["action"]+NOR :HIY+action[j]["action"]+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"����":"����",
					"damage_type" : random(2)?"����":"����",
				]);
			}
			if( me->query_temp("sanqing")){
				return ([  
					"action" :HIW+action[j]["action"]+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
					"damage": 50 + random(100) + (level+xtg)/4,
					"parry": random(15)+xtg/15,
					"weapon" : random(2)?"����":"����",
					"damage_type" : random(2)?"����":"����",
				]);
			}
			return ([
				"action": action[j]["action"],
				"force" : 100 +random(250),
				"dodge": random(20)-10,
				"parry": random(10),
				"damage": 40 +random(100),
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
			]);
		}
	}
}

int practice_skill(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("�������������ȫ�潣����\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������������ȫ�潣����\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"quanzhen-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int skill= me->query_skill("quanzhen-jianfa", 1);
	if( random(me->query_skill("quanzhen-jianfa", 1)) > 60
	 && me->query_temp("hebi")
	 && me->query("combat_exp") > victim->query("combat_exp")/(3+random(2))){
		victim->add_temp("lost_attack", random(skill/50) + 2);
		call_out("check_fight", 1, me, victim);
	}
}

void check_fight(object me,object victim)
{
	if(!victim) return;
	if( ! me 
         || ! me->query_temp("hebi")){
		victim->delete_temp("lost_attack");
		return;
        }
	call_out("check_fight", 1, me, victim);
}
