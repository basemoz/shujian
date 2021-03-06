// douzhuan-xingyi 斗转星移
// 1997-2-14
// Modified by Darken@SJ
// rewrite by athoi@sj 2004.03.28

#define DAMAGE_TYPE 	""
#define LEVEL 		ADVANCED
#define LEARN_TYPE 	"parry"

#include <ansi.h>
inherit SKILL;

string *attack_action = ({
YEL"蓦地里一股力道飞来，将$n一引一带，$N身子轻轻越起，身行落在一旁"NOR,
BLU"$N当下一股内力冲向$n，$n击向$N招数莫名奇妙的溜滑向一旁"NOR,
HIW"$N双手前探，左臂搭上$n右臂，右臂使出$n的招数将$n此招化去"NOR,
HIY"$N星移斗转，$n这招莫名其妙的在中途转了方向，直奔自己袭来"NOR,
YEL"$N作壁上观，双手与对方相交数掌，竟使出$n成名技艺，使得$n不知如何是好"NOR,
BLU"$N凝神运气向$n猛攻快打，使出的招数好似$n的成名绝技，把$n的招数化于无行"NOR,
HIW"只见$N身如飘风，恰似漫天星移，诡异地一式，双掌动向无定不可捉摸地拍向$n"NOR,
HIY"$N身行飘忽不定，在星移斗转之间反用$n的招数击向$n，令$n百思不得其解"NOR,
});

string query_parry_msg(object weapon)
{
        return attack_action[random(sizeof(attack_action))] + "。\n";
}

string force = "shenyuan-gong";

#include <skills.h>

int valid_enable(string usage)
{
	if (usage == "force" || usage == "dodge" || usage == "unarmed")
		return 0;
	else
		return 1;
}

mapping query_action(object me, object weapon)
{
	int power = 0;
	string color = "";
	mapping action;
        
        action = get_action(me, weapon, power, color);
        action["parry"] = action["parry"]?action["parry"]:me->query_con("postnatal") / 2;
        return action;
}

int learn_check(object me, object weapon)
{
        return notify_fail("斗转星移只能通过领悟来提高。\n");
}
