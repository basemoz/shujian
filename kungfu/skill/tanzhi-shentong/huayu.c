// huayu.c 漫天花雨

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return CYN"漫天花雨"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
        int damage, num, lvl, p;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("漫天花雨只能对战斗中的对手使用。\n");

	if (!(me->query("thd/perform") & 16))
		return notify_fail("你虽然听说过“漫天花雨”这一招，可是却未获传授。\n");

	lvl = me->query_skill("tanzhi-shentong", 1);

	if (lvl < 120)
		return notify_fail("你的弹指神通不够娴熟，无法使用漫天花雨。\n");

	if (me->query_skill("throwing", 1) < 120)
		return notify_fail("你的基本暗器不够娴熟，无法使用漫天花雨。\n");

   if ( me->query_skill_mapped("throwing") != "tanzhi-shentong")
		return notify_fail("你现在的情况，无法使用漫天花雨。\n");

	if ( me->query_skill("bihai-chaosheng", 1) < 120 )
		return notify_fail("你的碧海潮生功等级不够，无法使用漫天花雨。\n");

	weapon = me->query_temp("weapon");

	if (!weapon)
		return notify_fail("漫天花雨必须装备暗器才能使用。\n");

	if ((num = weapon->query_amount()) < lvl / 20)
		return notify_fail("你掏了掏背囊，发现里面的暗器已经不够使用漫天花雨的要求了！\n");

	if (me->query("neili") < 1000)
		return notify_fail("你的内力不够，无法使用漫天花雨。\n");

	if (me->query("jingli") < 900)
		return notify_fail("你的精力不够，无法使用漫天花雨。\n");

	msg = HIW"\n$N双手在背囊里一抓，抓出" + CHINESE_D->chinese_number(lvl / 20) + weapon->query("base_unit") + weapon->query("name") + HIW"来，运用指力漫天地弹了出去，$n只觉眼前似乎在下一场暗器雨！\n"NOR;

       damage = (int)me->query_skill("force") + (int)me->query_skill("finger") + me->query_temp("thd/is_fast");
       if (random(me->query_dex()) > (int)target->query_dex() / 2) {
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		msg += "$n躲闪不及，“噗噗”地几声，被几道暗器击中！\n";
		target->receive_damage("qi", damage, me);
           target->receive_wound("qi", damage, me);
		me->add("neili", -400);
		me->add("jingli", -100);
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg += COMBAT_D->damage_msg(damage, "刺伤");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
	}
	else {
		me->add("neili", -150);
		me->add("jingli", -50);
		msg += "$n吓得赶忙抱头团身，万分狼狈地向旁边一滚，方才堪堪地躲了过去。\n" NOR;
		target->add_busy(1);
	}
	message_vision(msg, me, target);
	me->start_perform(2, "「漫天花雨」");
	me->start_busy(random(2));
	if (num == lvl / 20) {
		weapon->unequip();
		tell_object(me, "\n你的" + weapon->query("name") + "用完了！\n");
	}
	weapon->add_amount(-(lvl/20));
	return 1;
}

int help(object me)
{
        write(HIG"\n「漫天花雨」："NOR"\n");
        write(@HELP

        一次同时弹出许多的暗器，让对手防不胜防，避无可避。同时，由於使用暗
        器数量极多，若是连续使用必须注意，以免战中发现暗器不够了。

        要求：  碧海潮生等级 150 以上；
                弹指神通等级 150 以上；
                最大内力 500 以上；
                配合奇门五转使用攻击伤害增加；
                必须准备暗器。
HELP
        );
        return 1;
}
