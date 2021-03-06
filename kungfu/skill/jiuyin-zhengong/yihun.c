#include <ansi.h>
inherit F_SSERVER;

int exert(object me, object target)
{       
	int skill, ap, dp;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
        || !me->is_fighting(target)
        || !necessary(target) )
		return notify_fail("移魂大法只能对战斗中的对手使用。\n");

	if ((int)me->query_skill("jiuyin-zhengong", 1) < 200)
		return notify_fail("你的九阴真功修为还不够。\n");

	if( (int)me->query_int(1) < 45 )
                return notify_fail("你的悟性不够。\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("你的真气不够。\n");

	skill = me->query_skill("jiuyin-zhengong",1);

        ap = me->query_skill("force");
        dp = target->query_skill("force")/5;

	ap += random(ap/2);

	message_vision(HIW"$N脸上突然开始做出各样奇怪的表情。\n"NOR, me, target);

        if ( random( ap + dp ) > dp ) {
        	int qi2 = target->query("qi");
                message_vision(HIW"$n看了准备取笑$N，却不知不觉的学起$N的表情。\n"NOR, me, target);
		message_vision(HIW"$N猛然做出向自己攻击的动作，$n立刻向自己发疯似的攻击起来，出手越来越重！\n"NOR, me, target);
		target->add_temp("apply/attack",skill);
		target->add_temp("apply/damage",skill);
		target->add_temp("apply/dodge",-skill);
		target->add_temp("apply/parry",-skill);
		target->add_temp("apply/defence",-skill);
                COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 1);
                if( me->is_fighting(target)&& random(2)) COMBAT_D->do_attack(target, target, target->query_temp("weapon"),3);
                if( me->is_fighting(target)) COMBAT_D->do_attack(target, target, target->query_temp("weapon"),random(2)?1:3);
                if(target)
                {
			target->add_temp("apply/attack",-skill);
			target->add_temp("apply/damage",-skill);
			target->add_temp("apply/dodge",skill);
			target->add_temp("apply/parry",skill);
			target->add_temp("apply/defence",skill);
			if(qi2 > target->query("qi")) target->set_temp("last_damage_from", me);
                }
	        me->add("neili", - 350);
	        me->add("jingli", -100);
	}
	else {
		message_vision(HIW"不管$N怎么变化表情，$n总是冷冷的无动于衷。\n"NOR, me, target); 
	        me->add("neili", - 150);
	        me->add("jingli", -50);
	}
        me->start_exert(3, "「移魂大法」");
	if ( !me->is_perform())
		me->start_perform(2, "「移魂大法」");
	return 1;
}

string exert_name(){ return HIW"移魂大法"NOR; }

int help(object me)
{
        write(HIW"\n九阴真功之「移魂大法」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 2000 以上；
        	后天悟性 45 以上；
                九阴真功等级 200 以上。

HELP
        );
        return 1;
}
