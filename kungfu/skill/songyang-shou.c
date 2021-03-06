// songyang-shou.c  嵩阳手
// Created by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ
// Modified by Looklove@SJ 2001.10.22

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N一掌高，一掌低，摆出了“嵩阳手”的起首式--「嵩阳拜首」",
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "嵩阳拜首"
]),
([
	"action" : "$N左掌一提，右掌一招便即劈出。但见他一掌出手，登时全身犹如渊停岳峙，气度凝重",
	"damage_type" : "内伤",
	"lvl" : 30,
	"skill_name" : "渊停岳峙"
]),
([
	"action" : "$N大喝一声道：“小心了！”随即双掌凌空推出，一股猛烈的掌风向着$n逼体而至",
	"damage_type" : "瘀伤",
	"lvl" : 60,
	"skill_name" : "中岳迎风"
]),
([
	"action" : "$N两手连续挥舞，双掌交错，一拍$n的面门，一拍$n的小腹",
	"damage_type" : "瘀伤",
	"lvl" : 80,
	"skill_name" : "松柏苍天",
]),
([
	"action" : "$N踏前一步，绕$n坻壁而行，双手快如风、迅如电，不停击向$n周身各大要穴",
	"lvl" : 100,
	"damage_type" : "瘀伤",
	"skill_name" : "坻壁而行"
]),
([
	"action" : "$N运气丹田，连续几个斜步围绕$n周身不断出掌，其迅捷令$n全身各大要穴均暴露无疑",
	"damage_type" : "内伤",
	"lvl" : 120,
	"skill_name" : "岳雾缭人"
]),
([
	"action" : "$N蹂身向前，身行猛的一窜，窜至半空又两手互抵，双掌竖直向$n的天门压去",
	"damage_type" : "内伤",
	"lvl" : 140,
	"skill_name" : "临渊下探"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("学习嵩阳手必须空手。\n");
	if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
		return notify_fail("你的寒冰真气火候不够，无法学嵩阳手。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练嵩阳手。\n");
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
	level = (int)me->query_skill("songyang-shou", 1);

	if (me->query_temp("yinyang") && random(level/10) > 12 && random(2)){
		switch(random(2)) {
			case(0) :
				return([
					"action": HIW "$N倏地欺近身来，远远发出一掌，掌力击在$n胸口，此掌寒气逼人，$n立时一个哆嗦"NOR,
					"force" : 350+ random(150),
					"dodge" : random(35),
					"parry": random(35),
					"damage_type" : "瘀伤",
				]);
				break;
			case(1) :
				return([
					"action": HIW "$N倏地欺近身来，远远发出一掌，掌力击在$n胸口，此掌炙热无比，$n浑身顿感难受"NOR,
					"force" : 350+random(150),
					"dodge" : random(35),
					"parry": random(35),
					"damage_type" : "瘀伤",
				]);
				break;
		}
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
                   if(me->query_temp("ss_lf") && (int)me->query_skill("songyang-shou",1)>=450){
                           return([
                           "action": HIW+action[j]["action"]+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 400 +random(400),
                           "dodge": 30+random(30),
                           "parry": 20+ random(30),
                   ]);
               }
                   if(me->query_temp("ss_lf") && (int)me->query_skill("songyang-shou",1)>=350){
                   return ([
                           "action":HIY+ action[j]["action"]+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 300 +random(300),
                           "dodge":20+random(30),
                           "parry":10+ random(30),
                   ]);
               }
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string msg;
	int focus, lvl, j;
	focus = me->query_temp("ss/focus");
	lvl= me->query_skill("songyang-shou", 1);
	j = (lvl - 100) / 5 + 1;

	if ( victim->query("job_npc")) return 0;

	if (me->query_temp("ss/hb") && !victim->is_busy()) {
		if ( !random(3))
			victim->add("neili",-me->query_skill("force"));
		if (victim->query("neili") < 0) victim->set("neili",0);
		msg = HIW"$n被$N这一掌击中，陡然一哆嗦，似乎全身的血液即将冻结一般！\n"NOR;
		victim->add_condition("cold_poison", 3 + random(3));
		message_vision(msg, me, victim);
	}
	if ( j > 6 ) j = 6;

	if ( me->query_temp("ss_lf") ) return 0;

	if ( random(me->query_con(1))>20
	&& lvl >= 100
	&& random(me->query_str(1))>20
	&& me->query_skill_prepared("hand") == "songyang-shou"
	&& me->query_skill_mapped("force") =="hanbing-zhenqi"
	&& me->query("neili") > 1000
	&& me->query("max_neili") > 1500
	&& me->query("jiali")
	&& random(2) ) {
		me->add("neili", -50);
		msg = HIB"$N运起寒冰真气，脸上升起一鼓若隐若现的白气，右掌猛力向$n击去。\n"NOR;
		victim->add_condition("cold_poison", 3+ random(3));
		msg +=HIW"$n只觉得$N这一掌夹着奇寒无比的真气，变幻百端，势如破竹般注入全身穴道, 不能动弹。\n"NOR;
		victim->add_busy(2+random(2));
		message_vision(msg, me, victim);
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("songyang-shou", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if (me->query("jingli") < 40)
		return notify_fail("你的精力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练嵩阳手。\n");
	me->receive_damage("jingli", 30);
	me->receive_damage("neili", 10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"songyang-shou/" + action;
}
