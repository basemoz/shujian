// cailian.c 「彩莲」
// creat by Caiji@SJ
// Modified by Lklv 2001.10.21
// Modified by Lane@SJ 2005.7.19

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIM"彩莲"NOR; }

string *color = ({ RED+"",GRN+"",YEL+"",BLU+"",MAG+"",CYN+"",
HIR+"",HIG+"",HIY+"",HIB+"",HIM+"",});

int perform(object me, object target)
{
	int tbusy, i, j;
	string msg;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 ||!target->is_character()
	 ||!me->is_fighting(target) )
		return notify_fail("「彩莲」只能对战斗中的对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("「彩莲」只能空手使用。\n");

	if( me->query_skill_prepared("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("parry") != "lianhua-zhang" )
		return notify_fail("你必须用莲花掌才能出此奇功。 \n");

	if( me->query_skill("huntian-qigong",1) < 100 )
		return notify_fail("你的混天气功功力还不足以使用「彩莲」!\n");

	if( me->query_skill("lianhua-zhang",1) < 100 )
		return notify_fail("你的莲花掌修为不够，还不能使出「彩莲」绝技!\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("你的内功不对。\n");

	if( me->query("max_neili") < 800 )
		return notify_fail("你的内力修为尚欠火候。\n");

	if( me->query("neili") < 500 )
		return notify_fail("你现在内力不够, 不能使用「彩莲」! \n");

	if( me->query("jingli") < 500 )
		return notify_fail("你现在精力不够, 不能使用「彩莲」! \n");

	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

	if( me->query_temp("lhz/cailian") )
		return notify_fail("你现在气血翻涌，现在还不能使用「彩莲」，! \n");

	msg = HIM "\n但见$N脚下后退一步，左手一记“千叶莲花”，朝前劈出，在$n身前像火树银花般爆发开来，\n"+
		"刹那间光芒四射，大如车轮，有如一朵盛开的彩色莲花，奇亮的闪光，照得人睁不开眼睛。\n"NOR;

	me->start_perform(3, "彩莲");
	me->set_temp("lhz/cailian",1);
	tbusy = (int)me->query_skill("lianhua-zhang",1) / 50 - random(3);
	if( tbusy < 3 ) tbusy = 3;
	if( tbusy > 5 ) tbusy = 5+random(2);

	i = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK) + me->query("combat_exp");
	j = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE) + target->query("combat_exp");

	if( random(i + j) > j ) {
		if( tbusy > 3 ) msg += BLINK+"";
		target->start_busy(tbusy);
		if( !userp(target) ) target->add_busy(random(2));
		msg+=color[tbusy]+
		"              /\\/\\/\\/\\/\\/\\ \n"+
		"            </\\/\\/\\/\\/\\/\\/\\>\n"+
		"           </\\/\\/\\/\\/\\/\\/\\/\\>\n"+
		"           \\_<>_\\_\\<>/_/_<>_/\n"+
		"           / <> / /<>\\ \\ <> \\ \n"+NOR;
		msg += HIY"结果$n被$N的彩色莲花罩住，瞬间便失去了攻击的能力! \n" NOR;
		me->add("neili",-200);
		me->add("jingli",-50);
		me->start_perform(tbusy-random(2), "彩莲");
		message_vision(msg, me, target);
	}
	else {
		msg += HIM"$n虽被这精妙的一招震得连退了数步，但招式章法却丝毫不乱，竟也勉强接了下来。\n" NOR;
		if( me->is_fighting(target) && random(i) > j/2 ) {
			msg+=HIG"只是被莲花掌风所伤，$N立即一吸真气，朝前逼进，右手起处连劈双掌………\n" NOR;
			message_vision(msg, me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?0:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
			me->start_busy(random(2));
			me->start_perform(3, "彩莲");
		}
		else if( me->is_fighting(target) && random(i) > random(j)/2 ) {
			msg+=HIB"只是被莲花掌风扫到了下盘，$n便略见窒碍，守护也立见松懈。\n" NOR;
			message_vision(msg, me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?0:1);
			me->start_busy(random(2));
			me->start_perform(2+random(2), "彩莲");
		}
		else message_vision(msg, me, target);
		me->add("neili",-200);
		me->add("jingli",-50);
	}
	me->delete_temp("lhz/cailian");
	return 1;
}

int help(object me)
{
        write(HIM"\n莲花掌「彩莲」："NOR"\n");
        write(@HELP
        彩莲为莲花掌绝技之一。功力达到者可用自身内力发出莲花状的掌锋。
        对手往往被掌风所迷惑，攻守不能自如。
        要求：  最大内力 800 以上；
                当前内力 500 以上；
                当前精力 500 以上；
                莲花掌等级 100 以上；
                混天气功等级 100 以上；
                激发招架为莲花掌。
HELP
        );
        return 1;
}
