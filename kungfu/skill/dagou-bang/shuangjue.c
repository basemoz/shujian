// shuangjue.c It's a "pfm" .
// by Looklove@SJ 2001/2/14 ...情人节
// Modify by looklove 2001.4.4
// Mofify by looklove 2001.4.8
// Modify by looklove 2001.5.2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIW"棒掌双绝"NOR; }
int perform(object me, object target)
{
	int b, z, j;
	object weapon;
	b = me->query_skill("dagou-bang", 1);
	b += me->query_skill("xianglong-zhang", 1);
	weapon = me->query_temp("weapon");

	if (!target ) target = offensive_target(me);

	if (!objectp(target) || !me->is_fighting(target) || !necessary(target) )
		return notify_fail("「棒掌双绝」只能在战斗中对对手使用。\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "stick")
		return notify_fail("你手里没有棒，无法使用棒掌双绝！\n");

	if( (int)me->query_int(1) < 30)
		return notify_fail("你悟性不足，无法使用棒掌双绝。\n");

	if( (int)me->query_skill("dagou-bang", 1) < 300 )
		return notify_fail("你的打狗棒法还不够娴熟，使不出「棒掌双绝」绝技。\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 300 )
		return notify_fail("你的降龙十八掌还未练成，不能使用棒掌双绝！\n");

	if( me->query_skill_mapped("force") != "huntian-qigong"
	|| (int)me->query_skill("huntian-qigong", 1) < 300 )
		return notify_fail("你的混天气功还没有学成，无法使用棒掌双绝！\n");

	if( me->query_skill_mapped("parry") != "dagou-bang")
		return notify_fail("你的招架功夫不是打狗棒，无法使用棒掌双绝！\n");

	if( me->query_skill_mapped("strike") != "xianglong-zhang"
	|| me->query_skill_prepared("strike") != "xianglong-zhang")
		return notify_fail("你没有用降龙十八掌，无法使用棒掌双绝！\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你的内力根基太弱，使不出「棒掌双绝」。\n");

	if( (int)me->query("neili") < 2500 )
		return notify_fail("你现在真气太弱，使不出「棒掌双绝」。\n");

	if((int)me->query("jingli") < 1200 )
		return notify_fail("你的精力不足以让你使出此绝技。\n");

	z = b/2;
			
	j = to_int( z / 4.5);

	if( z > 450 )
		j = to_int( z/3.5 * z/450.0 );

	else if( z > 250 )
		j = to_int( z/4.5 * z/250.0 );
	

	message_vision(HIW"\n$N大喝一声「棒掌双绝」，挥舞"+weapon->name()+HIW+"向$n击来，只见棒中藏掌，势不可挡，当者披靡。\n"NOR, me, target);

	me->add_temp("apply/attack", j);
	me->set_temp("shuangjue/dgb", 3);
	me->set_temp("shuangjue/xlz", 2);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/3);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->add_temp("apply/strike", -j);

	weapon->wield();
	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->add_temp("apply/strike", -j);

	weapon->wield();
	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);

	me->add_temp("apply/attack", -j);
	me->add("neili", -500 );
	me->add("jingli", -200);
	me->delete_temp("shuangjue");
        me->start_perform(3+ random(2),"「棒掌双绝」");
	me->start_busy(random(2));
	return 1;
}

int help(object me)
{
	write(WHT"\n「棒掌双绝」："NOR"\n");
	write(@HELP
	集打狗棒与降龙十八掌精华于一身，棒中藏掌，势不可挡，当者披靡。

	要求：	后天悟性30以上；
		最大内力 5000 以上；
		当前内力 2500 以上；
		打狗棒等级 300 以上；
		混天气功等级 300 以上；
		降龙十八掌等级 300 以上；
		激发招架为打狗棒；
		空手武功为降龙十八掌。
HELP
	);
	return 1;
}
