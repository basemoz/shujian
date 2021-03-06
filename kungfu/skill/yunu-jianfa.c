// yunu-jiafa 玉女素心剑
// by xdd and shang 97/6
// Modify By River 98/10
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N击高而下，一式「雁行斜击」，腾身下击，剑尖直点$n的$l",
	"lvl" : 0,
	"skill_name" : "雁行斜击",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N踏前数步，左手遥指，右手$w使一式「浪迹天涯」直劈$n的$l",
	"lvl" : 10,
	"skill_name" : "浪迹天涯",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「花前月下」，$w颤动如鲜花招展风中，来回挥削$n的$l",
	"lvl" : 20,
	"skill_name" : "花前月下",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N剑尖上翻，指向自己的樱唇，一招「清饮小酌」，宛若举杯自饮一般，横扫$n的$l",
	"lvl" : 30,
	"skill_name" : "清饮小酌",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N使出「抚琴按箫」，$w自横脐前，做抚琴状，随即剑出中宫，平削$n的$l",
	"lvl" : 40,
	"skill_name" : "抚琴按箫",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N右手一招「彩笔画眉」，构成帘下梳妆之状，一脸娇羞，$w却未有停留，逼向$n的$l",
	"lvl" : 50,
	"skill_name" : "彩笔画眉",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「举案齐眉」，双手齐握剑柄，举剑上挑，直划$n的$l",
	"lvl" : 70,
	"skill_name" : "举案齐眉",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N向前急进两步，一招「木兰回射」，蓦地里挺剑反手向背后刺出，直刺$n的$l",
	"lvl" : 90,
	"skill_name" : "木兰回射",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「分花拂柳」，$w似左实右，似右实左，虚实莫辩，点向$n的喉头",
	"lvl" : 110,
	"skill_name" : "分花拂柳",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N眼角尽是笑意，眉目含情，一招「如影相随」，影随$n周身，身形飘飘中剑光熠熠生辉，",
	"lvl" : 130,
	"skill_name" : "如影相随",
	"damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ( me->query_skill("yunu-xinjing", 1) < 20)
		return notify_fail("你的玉女心经功力不够。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);

	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	string msg;

	level =  me->query_skill("yunu-jianfa",1);

	for(i = sizeof(action); i > 0; i--){
		if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("hebi") && me->query_temp("double_attack") ) {
			 	if (random(2) && me->query_skill("quanzhen-jianfa", 1) > 0) {
					msg = SKILL_D("quanzhen-jianfa")->query_action(me, me->query_temp("weapon"))["action"];
					return ([  
						"action" :random(2)? HIW + msg +NOR : HIY + msg +NOR,
						"force" : 200 + random(350),
						"dodge": random(30),
						"damage": 80 +random(140),
						"lvl" : action[j]["lvl"],
						"parry": random(20),
						"weapon" : random(2)?"剑气":"剑锋",
						"damage_type" : random(2)?"刺伤":"割伤",
					]);
				}
				return ([  
					"action" :random(2)? HIC + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR
							: HIR + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"lvl" : action[j]["lvl"],
					"parry": random(20),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			if ( me->query_temp("hebi") && random(2) ){ 
				return ([  
					"action" :random(2)? HIC + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR
							: HIR + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"lvl" : action[j]["lvl"],
					"parry": random(20),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
			}
			if( me->query_temp("juan")){ 
				return ([  
					"action" : CYN + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"CYN)+NOR,
					"force" : 150 +random(300),
					"dodge": random(30),
					"damage": 60 + random(100),
					"lvl" : action[j]["lvl"],
					"parry": random(30),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
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
	|| weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if (me->query("jingli") < 30)
		return notify_fail("你的体力不够练玉女素心剑。\n");
	if (me->query("neili") < 20)
		return notify_fail("你的内力不够练玉女素心剑。\n");
	me->add("jingli", -20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunu-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int skill = me->query_skill("yunu-jianfa", 1);
	if(random(skill) > 60
	 && me->query_temp("hebi")
	 && me->query("combat_exp") > victim->query("combat_exp")/(3+random(2))) {
		victim->add_temp("lost_attack", random(skill/50) + 2);
		call_out("check_fight", 1, me, victim);
	}
}

void check_fight(object me,object victim)
{
	if(!victim) return;
	if( ! me 
	 || ! me->query_temp("hebi")) {
		victim->delete_temp("lost_attack");
		return;
        }
	call_out("check_fight", 1, me, victim);
}
