// qianzhu-wandushou千蛛万毒手
// Update By River@SJ 2002.11
// Modified by mxzhao 2005/02/11 修改成150以上可以练
// Update by lsxk@hsbbs  修改颜色
// Update by server 修改没标记可以jifa 可以通过marry 来学习

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N深吸口气，身体急纵而上，右手食指疾伸，直戳$n的$l",
	"lvl" : 0,
	"poison": 80,
	"damage_type": "瘀伤"
]),
([
	"action": "$N身形微曲，踢出右腿横扫$n的下盘, 突然间又飞起双掌拍向$n的$l",
	"lvl" : 40,
	"poison": 60,
	"damage_type": "瘀伤"
]),
([
	"action": "$N阴喝一声，双手向前舞动，突然一股内劲顺指尖破空而出，疾射$n的$l",
	"lvl" : 80,
	"poison": 40,
	"damage_type": "瘀伤"
]),
([
	"action": "$N身形纵起，十指轻弹，只见缕缕内劲犹如飞瀑般向$n的$l射去",
	"lvl" : 120,
	"poison": 80,
	"damage_type": "内伤"
]),
([
	"action": "$N脸上阴气大盛，一股黑气顺双手蔓延到两臂，一招「万蛛吸血」连连戳向$n的$l",
	"lvl" : 160,
	"poison": 100,
	"damage_type": "瘀伤"
]),
});

string *rcolor = ({HIR,HIB,HIC,HIW,HIM,HIG,HIY,BLU,RED,YEL,CYN,MAG,WHT});

int valid_enable(string usage)
{
   if ( this_player()->query("quest/qianzhu/pass"))
	return usage=="hand" || usage=="parry"; 
}

string query_skill_name(int level)
{
	int i = sizeof(action);

	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

//	HIR"$N眉间黑气笼罩，牙关紧咬，突然喷出一股香气，十指又快如鬼魅般点向$n膻中穴"NOR,

mapping query_action(object me)
{
	int i, j, level;
	level = me->query_skill("qianzhu-wandushou",1);

	for(i = sizeof(action); i > 0; i--){
		if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("qzwd_pfm")) {
				return ([
					"action" :	HIR+action[j]["action"]+NOR,
					"poison":	action[j]["poison"],
					"damage_type":	"内伤",
					"dodge":	random(35),
					"parry":	random(35),
					"force":	350 + random(300),
					"damage":	50 + random(50),
				]);
			}
                   if( me->query_temp("qzwd_pfm2")) {
                           return ([
                                   "action" :      rcolor[random(sizeof(rcolor))]+action[j]["action"]+NOR,
                                   "poison":       action[j]["poison"],
                                   "damage_type":  "内伤",
                                   "dodge":        random(55),
                                   "parry":        random(55),
                                   "force":        400 + random(350),
                                   "damage":       50 + random(50),
                           ]);
                   }
			return ([
				"action":	action[j]["action"],
				"damage_type":	action[j]["damage_type"],
				"poison":	action[j]["poison"],
				"lvl":		action[j]["lvl"],
				"force":	300 + random(250),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	if (me->query_skill("qianzhu-wandushou", 1) < 150)
	{
		return notify_fail("千蛛万毒手只能通过修炼来提高。\n");
	}

	if (me->query("jingli") < 50)
	{
		return notify_fail("你的体力不够练习千蛛万毒手。\n");
	}
	
	if (me->query("neili") < 20)
	{
		return notify_fail("你的内力不够练习千蛛万毒手。\n");
	}

	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

int valid_learn(object me)
{
	if (me->query_skill("qianzhu-wandushou", 1) < 150)
	{
		return notify_fail("千蛛万毒手只能通过修炼来提高。\n");
	}

	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int i = me->query_skill("qianzhu-wandushou", 1);

	if ( victim->query("job_npc")) return 0;

	if( (random(i) > 150 || me->query_temp("qzwd_pfm")) && me->query("env/千蛛万毒手")) {
		message_vision(HIR"$N身体一经接触，只觉浑身一震，脸露潮红之色，看来已经中毒了！\n"NOR, victim);
		victim->set_temp("qianzhu", 1);
		victim->add_condition("qzhu_poison", random(6)+ i/30);
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && ! me->query_temp("revenge/"+victim->query("id"))
               && (!me->query_temp("special_die") || !victim->query_temp("special_die")))
			me->add_condition("killer", 5);
	}
}

string perform_action_file(string action)
{
	return __DIR__"qianzhu-wandushou/" + action;
}
