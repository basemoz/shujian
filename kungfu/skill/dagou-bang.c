// dagou-bang.c 打狗棒法
// Code By Looklove@SJ 2001/4/1
// Modify By Looklove 2001.4.8
// Looklove modified at 2001.5.5
// Looklove modified at 2001.5.18
// Lane@SJ modified at 2005.7.26
// Update by lsxk@hsbbs 2007/7/3

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N一声轻吟，挥起$w，使出一式「打草惊蛇」，猛扫向$n的$l",
	"lvl" : 0,
	"skill_name": "打草惊蛇",
	"damage_type": "挫伤"
]),
([
	"action": "$N步伐跳跃，手中$w左右晃动，一招「拨草寻蛇」向$n的$l攻去",
	"lvl":10,
	"skill_name": "拨草寻蛇",
	"damage_type": "内伤"
]),
([
	"action": "$N手中$w一圈，使出一招「关门打狗」将$n四面八方围个密不透风",
	"lvl" : 20,
	"skill_name": "关门打狗",
	"damage_type": "瘀伤"
]),
([
	"action": "$N步踏坤位，施出「拨狗朝天」，反手将$w由下往上向$n撩去",
	"lvl" : 30,
	"skill_name": "拨狗朝天",
	"damage_type": "挫伤"
]),
([
	"action": "$N大喝一声「狗急跳墙」！抢上一步，将$w劈头抡向$n的$l",
	"lvl" : 50,
	"skill_name": "狗急跳墙",
	"damage_type": "挫伤"
]),
([
	"action": "$N使出一招「棒打双犬」，手中$w化作两道青光砸向$n的$l",
	"lvl" : 80,
	"skill_name": "棒打双犬",
	"damage_type": "挫伤"
]),
([
	"action": "$N手腕一翻，一招「恶犬拦路」，将手中$w向$n的去势封了过去",
	"lvl" : 100,
	"skill_name": "恶犬拦路",
	"damage_type": "挫伤"
]),
([
	"action": "$N一招「棒打狗头」，只见$w突然飞起，直击$n的顶门",
	"lvl" : 120,
	"skill_name": "棒打狗头",
	"damage_type": "挫伤"
]),
([
	"action": "只见$N使出一招「斜打狗背」，侧身拧腰，$w斜劈向$n的$l",
	"lvl" : 140,
	"skill_name": "斜打狗背",
	"damage_type": "挫伤"
]),
([
	"action": "$N灵机一动，使出一招「反截狗臀」，反手将$w戳向$n的$l",
	"lvl" : 160,
	"skill_name": "反截狗臀",
	"damage_type": "挫伤"
]),
([
	"action": "$N一招「打狗入洞」，将$w舞了个棒花，横扫$n的$l",
	"lvl" : 180,
	"skill_name": "打狗入洞",
	"damage_type": "挫伤"
]),
([
	"action": "$N反身错步，手中$w一幌，使一招「压肩狗背」，夹头夹脸打向$n的$l",
	"lvl" : 200,
	"skill_name": "压肩狗背",
	"damage_type": "内伤"
]),
});

string *wugou_action=({
HIC"忽然$N急走数步，回身举棒斜劈，使出「天下无狗」第一变，戳向$n的肩头。"NOR,
HIW"$N闪身后跳，使出「天下无狗」第二变，挥棒猛扫$n的脚踝。"NOR,
HIG"$N使出「天下无狗」第三变，将手中棒抡圆了，突然直捅$n的眼睛！"NOR,
HIB"只见漫天棒影一停，$N将「天下无狗」第四变使出，脚在手中棒上一端一踢,斜斜飞向$n的小腹。"NOR,
HIR"$N使出「天下无狗」第五变，披天盖地般打来。但见棒影招招不离$n的脑门。"NOR,
HIY"$N棒走偏峰，舞出满天棒影，竟然使的是「天下无狗」第六变。刹那间漫天棒影罩住$n全身!"NOR
});

int valid_enable(string usage) { return (usage == "stick") || (usage == "parry"); }

int valid_learn(object me)
{
	if( me->query("family/master_name") != "洪七公" )
		return notify_fail("打狗棒法只能从洪七公处学到。\n");
	if( me->query_skill("stick", 1) < 20 )
		return notify_fail("你的基本棒法太差, 还领会不了打狗棒法。\n");
	if( me->query("gender") == "无性" )
		return notify_fail("你一个不男不女之人如何能学打狗棒？\n");
	if( me->query("max_neili") < 100 )
		return notify_fail("你的内力不够。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if( level > action[i]["lvl"] )
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, j, m, level,wx,deads;
	string msg;

	deads = (int)me->query("death_times") - 100;
	deads = deads/2 + random(deads/2);

	if( me->query("combat_exp") < 1000000 ) m = 50;
	else if( me->query("combat_exp") < 3000000 ) m = 100;
	else if( me->query("combat_exp") < 5000000 ) m = 150;
	else if( me->query("combat_exp") < 7000000 ) m = 200;
	else if( me->query("combat_exp") < 9000000 ) m = 250;
	else m = 300;

	if( deads < 0 ) deads = 0;
	if( deads > m ) deads = m;

	wx = (int)me->query_int(1)/3+random(me->query_skill("bangjue",1)/10);
	wx += me->query("gender") == "女性"?deads/8:deads/10;
//   if( wizardp(me) ) tell_object(me, HIY"打狗"YEL"("BLK"野菊"YEL")"HIY"棒法威力加成(累计死亡)指数为："+wx+"点。\n"NOR);

 	weapon = me->query_temp("weapon");
	level  = (int)me->query_skill("dagou-bang", 1);

   if( me->query_temp("dgb/wugou") ) {
           msg = wugou_action[(int)me->query_temp("dgb/wugou")-1];
           return ([
                   "action":       msg,
                   "dodge":        random(20)+wx,
                   "parry":        random(20)+wx,
                   "damage":       140+random(160),
                   "force":        260+random(360),
                   "damage_type":  "挫伤"
           ]);
   }

	if( me->query_temp("shuangjue/dgb") ) {
		switch((int)me->query_temp("shuangjue/dgb") ) {
			case 3: msg = HIW"$N晃身错步，猛然一声长啸，舞起漫天棒影攻向$n的$l"NOR; break;
			case 2: msg = HIG"$N忽然斜挪一步，眼中灵光一闪，手中$w"HIG"横扫向$n的$l"NOR; break;
			case 1: msg =  HIC"$N招数突变，忽然跃起，只见$w"HIC"化作一团棒影直向$n的$l打去"NOR;break;
			default: msg = HIW"$N晃身错步，猛然一声长啸，舞起漫天棒影攻向$n的$l"NOR; break;
		}
		me->add_temp("shuangjue/dgb", -1);
		return ([
			"action":	msg,
			"dodge":	random(20)+wx,
			"parry":	random(20)+wx,
			"damage":	130+random(140),
			"force":	250+random(350),
			"damage_type":	"挫伤"
		]);
	}
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action" : action[j]["action"],
				"dodge": me->query("gender")=="女性"?random(20)-10+wx:random(20)-15+wx,
				"parry": me->query("gender")=="女性"?random(30)+wx/2:random(20)+wx/2,
				"damage": me->query("gender")=="女性"?80+random(140):70+random(130),
				"force" : me->query("gender")=="女性"?200+random(350):180+random(320),
				"attack": random(wx/4)+wx/4,
				"lvl" : action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
			]);
		}
}

int practice_skill(object me)
{
	object weapon;
	int lvl = me->query_skill("dagou-bang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if( !objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "stick" )
		return notify_fail("你使用的武器不对。\n");

	if( me->query("jingli") < 50 )
		return notify_fail("你的精力不够练打狗棒法。\n");

	if( me->query("neili") < 20 )
		return notify_fail("你的内力不够练打狗棒。\n");

	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dagou-bang/" + action;
}


int ob_hit(object ob, object me, int damage)
{
	object weapon,twp;
	string msg;
	int j, p, level;

	weapon = me->query_temp("weapon");
	twp = ob->query_temp("weapon");
	level = me->query_skill("dagou-bang",1);

	if( me->query_temp("fanzhen") ) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if( me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang"
	 || ! weapon
	 || weapon->query("skill_type") != "stick"
	 || ob->query("env/invisibility"))
		return 0;

	if( random(level) > 100
	 && random(me->query_skill("bangjue", 1)) > 100
	 && me->query("neili") > 500
	 && random(level) > ob->query_skill("parry", 1)/2
	 && random(20) > 7) {
		me->add("neili", -50);
		if( twp ) {
			msg = HIM"$n"+ twp->name() +HIM"一招甫出，但见$N使个「封」字诀，棒影飘飘，登时将自己\n"NOR;
			msg += HIM"身前数尺之地尽数封住了。$n无奈之下，只有后退一步，静观变化。\n"NOR;
			ob->add_busy(1+random(2));
			me->add("neili",-70);
			j = -damage;
		}
		else {
			msg = HIM"$n的手指刚要碰到$N手腕，突然只见青影闪动，"NOR;
			msg += HIM""+weapon->name() +HIM "一势「封」字诀，来势神妙无方，\n"NOR;
			msg += HIM"$n手腕已被重重地敲了一下，慌忙后退两步，变色斜睨，背上惊出了一阵冷汗。\n"NOR;
			ob->receive_damage("qi", damage/3 > 0?damage/3:20, me);
			ob->receive_wound("qi", damage/5 > 0?damage/5:10, me);
			p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "劈伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			me->add("neili",-100);
			j = -damage;
		}
		me->set_temp("fanzhen", 1);
		message_vision(msg, me, ob);
		return j;
	}
}

int help(object me)
{
        write(HIG"\n打狗棒："NOR"\n");
        write(@HELP
        打狗棒共有绊、劈、缠、戳、挑、引、封、转八诀，是闻名天下的
        丐帮镇帮绝技。以轻、灵、奇、巧诸称，舞将起来是四处只见棒影
        不见人影。武学中有言道：“四两拨千斤”，乃打狗棒法的精妙招
        数精髓体现。修习时如不同时学习棒诀，终将无法大成。

HELP
        );
        return 1;
}

                                                                                      
