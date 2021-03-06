// leiting 雷霆万钧
// Created by Numa@Sj 19991118

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	//string msg;
	//int damage, p, ap, dp;
	int focus = me->query_temp("ss/focus");
	int j;
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「雷霆万钧」只能在战斗中使用。\n");
        
	if( (int)me->query_skill("songshan-jian", 1) < 160 )
		return notify_fail("你的嵩山剑法还不够娴熟，无法使出「雷霆万钧」。\n");

	if( (int)me->query_skill("hanbing-zhenqi", 1) < 160 )
		return notify_fail("你的寒冰真气等级还不够，无法使出「雷霆万钧」。\n");

	if (me->query_skill_mapped("force") != "hanbing-zhenqi")
		return notify_fail("你目前的内功无法使出「雷霆万钧」。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("你无法使出「雷霆万钧」。\n");

	if (me->query_temp("ss/leiting"))
		return notify_fail("你刚使用完「雷霆万钧」，休息一下吧。\n"); 
                
	if( (int)me->query("max_neili") < 2500)
		return notify_fail("你的内力修为太差，无法使出「雷霆万钧」。\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("你现在真气太弱，使不出「雷霆万钧」。\n");
	
	j = me->query_skill("songshan-jian", 1);
	
	if ( me->query_skill("songshan-jian", 1) > 200 )
		j = to_int( j* j/ 200.0);

	j += focus * 5;
			
	me->set_temp("ssj/leiting",1);
	me->add_temp("apply/attack",focus * 10 );
	me->add_temp("apply/damage", j / 2);
	target->set_temp("combat_msg/dodge",CYN"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR );
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	target->delete_temp("combat_msg/dodge");
	me->add_temp("apply/damage", -j / 2);
	me->add_temp("apply/attack",-focus * 10 );
	me->delete_temp("ssj/leiting");
	/*	
	msg = YEL"\n$N右手衣袖鼓了起来，犹似吃饱了风的帆篷一般，全身劲力都集中到了右臂之上，全力向着$n刺出。\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * (me->query_skill("sword") + focus * 10);
	dp = target->query("combat_exp",1 ) / 1000 * target->query_skill("dodge");

	if ( target->is_busy())
		dp -= dp/3;

	if( random( ap + dp) > dp ) {
		msg += HIR"$n被这招乾坤一掷的猛击当胸一撞，立时口中鲜血狂喷而出！\n"NOR;
		damage = me->query_skill("sword") + me->query_skill("force");
		damage = damage * (focus+1);
		damage += random(damage);

		if( damage > 4500) 
			damage = 4500 + (damage- 4500)/5;

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2 + random(damage/2), me);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
        else {
		msg += CYN"突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	message_vision(msg, me, target);
	*/
	me->add("neili", -100);
	me->add("jingli", -80);
	me->start_perform(2, "雷霆万钧");
	me->start_busy(random(2));
        return 1;
}

string perform_name(){ return YEL"雷霆万钧"NOR; }

int help(object me)
{
        write(YEL"\n嵩山剑法之「雷霆万钧」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 1000 以上；
                最大内力 2500 以上；
                当前精力 1000 以上；
                嵩山剑法等级 160 以上；
                寒冰真气等级 160 以上；
                有效内功等级 250 以上；
                激发剑法为嵩山剑法；
                激发招架为嵩山剑法；
                激发内功为寒冰真气；
                且手持兵器。

HELP
        );
        return 1;
}
