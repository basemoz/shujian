//jinshe-zhangfa.c
// 增加auto 解密成功后才能使用 by daidai
#include <ansi.h>

inherit SKILL;
#include <combat_msg.h>
#include <combat.h>

mapping *action = ({
([
	"action": "$N使一招「金蛇出洞」，双手轻摆，宛如灵蛇出洞飘移不定击向$n$l",
        "lvl" : 0,
        "damage_type": "瘀伤"
]),
([
	"action": "$N使一招「金蛇游水」，双臂微弯如蛇行，手掌立起拍向$n的$l",
        "lvl" : 20,
        "damage_type": "瘀伤"
]),
([
	"action": "$N突然微一弓身，一招「金蛇挺身」，双掌划向$n的$l",
        "lvl" : 40, 
        "damage_type": "瘀伤"
]),
([
	"action": "$N倏忽欺至$n身前，一招「金蛇过涧」直拍$n的$l",
        "lvl" : 60,
        "damage_type": "瘀伤"
]),
([
	"action": "$N身形绕$n一转，一招「金蛇缠身」向$n$l接连出掌",
        "lvl" : 70, 
        "damage_type": "瘀伤"
]),
([
	"action": "$N身形拔起，在半空一招「升天入地」右掌猛击$n的$l",
        "lvl" : 80, 
        "damage_type": "瘀伤"
]),
([
	"action": "$N使一招「金蛇翻腾」，纵起丈余双掌交错直击$n的$l",
        "lvl" : 90,
        "damage_type": "瘀伤"
]),
([
	"action": "$N一声大喝使出「蛇跨彩虹」，幻出满天掌影，掌掌不离$n的$l",
        "lvl" : 100,
	"damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练金蛇游身掌必须空手。\n");
	if ((int)me->query_skill("strike", 1) < 60)
		return notify_fail("你的基本功不够，不能学习金蛇游身掌。\n");
	if( !me->query("jinshe/zhangfa"))
		return notify_fail("你无法修习金蛇游身掌。\n");
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("你的内力太弱，无法练金蛇游身掌。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("jinshe-zhangfa",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
    if ( me->query("quest/金蛇剑法/pass") ){  
    if (me->query_temp("jsj"))  
                        return ([
                             "action":       YEL+action[j]["action"]+NOR,
                             "lvl":          action[j]["lvl"],
                            "damage_type":  action[j]["damage_type"],
                             "force":        350 + random(250),
                            "dodge":        10+random(30),
                           "parry":        10+random(30),
                    ]);
 else                         return ([ 
                               "action":       CYN+action[j]["action"]+NOR,
                              "lvl":          action[j]["lvl"],
                           "damage_type":  action[j]["damage_type"],
                             "force":        300 + random(200),
                            "dodge":        10+random(20),
                          "parry":        10+random(20),
                     ]);
                  }
else  
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	150 + random(300),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
	}
}
void lianji(object me, object victim)
{
     if (!me || !victim || !me->is_fighting(victim))
           return;

   if( me->query("quest/金蛇剑法/pass")
    && me->query("neili") > 500 
   && !me->query_temp("weapon")
    && !me->is_busy()
   && !me->query_temp("jsj")){
            message_vision(HIW"\n但见$N倏进倏退，忽东忽西，双手轻摆，宛如灵蛇出洞般的飘移！"NOR, me);
           me->set_temp("jsj", 1);
           me->add_temp("apply/strike", me->query_skill("jinshe-zhangfa", 1)/4);
          COMBAT_D->do_attack(me, victim, 0, random(3)?1:3);
           if (me->is_fighting(victim)) 
                COMBAT_D->do_attack(me, victim, 0, random(2)?1:3);
            me->add_temp("apply/strike", -me->query_skill("jinshe-zhangfa", 1)/4);
          me->delete_temp("jsj");
  }
  }

  mixed hit_ob(object me, object victim, int damage_bonus, int factor)
 {
           int ap, dp, pp, exp1, exp2;
      if(!me->query("quest/金蛇剑法/pass"))            return 0;

      if(me->query("neili") < 600
      || me->query("max_neili") < 2500
      || me->query_skill("jinshe-zhangfa", 1) < 200 
      || me->query_temp("jsj")) 
                return 0; 
                ap = COMBAT_D->skill_power(me,"strike",SKILL_USAGE_ATTACK);
                dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
                pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
                    exp1 = (int)me->query("combat_exp",1);
                    exp2 = (int)victim->query("combat_exp",1); 
        if(random(ap+dp)>dp/3 && random(ap+pp)>pp/3 && random(exp1) > exp2/3){
         if(random(2)) {
         message_vision(HIY"$N双臂微弯，双掌交错，身形犹如蛇行般绕着$p游走不定！\n"NOR, me, victim);
        if( !victim->is_busy() )    
           victim->start_busy(2 + random(2));
          }
          else           call_out((: lianji :), 1, me, victim);
 }
 }

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 40)
		return notify_fail("你太累了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练金蛇游身掌。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}
