// 此去彼来perform?

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
    string msg, *limbs;
	int a,b,p,count, damage = 0;
	int arg=(int)(me->query_skill("liumai-shenjian", 1) / 30);
	
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「此去彼来」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「此去彼来」！\n");

        if( (int)me->query_skill("liumai-shenjian", 1) < 120 )
                return notify_fail("你的六脉神剑不够娴熟，不会使用「此去彼来」。\n");

        if( (int)me->query_skill("force") < 160 )
                return notify_fail("你的内功等级不够，不能使用「此去彼来」。\n");

        if( (int)me->query_str() < 26 )
                return notify_fail("你的膂力不够强，不能使用「此去彼来」。\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian"
        || me->query_skill_mapped("finger") != "liumai-shenjian")
                return notify_fail("你现在无法使用「此去彼来」进行攻击。\n");                                                                                 
        
	if( (int)me->query("neili", 1) < 150 * arg )
		return notify_fail("你现在的内力不够使用「此去彼来」进行攻击。\n");
     
	 a=me->query("max_neili",1);
	 b=target->query("max_neili",1);
        
     	message_vision(MAG "$N十指连动，忽伸忽缩，或点或按，空中气流激荡，剑气自$N指中汹涌而出，此去彼来，连绵无尽。\n" NOR, me, target);

       if( random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	{
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++)
        {
	  message_vision(
		replace_string(
	  SKILL_D("liumai-shenjian")->query_action(me, me->query_temp("weapon"))["action"],
		"$l", limbs[random(sizeof(limbs))]) + "！\n\n", me, target);
	  damage = damage+200+random(100);
        }    
	damage = (1 + me->query("jiali")/300) * damage*a/b ;
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage);
	   p = (int)target->query("qi")*100/(int)target->query("max_qi");
       msg = damage_msg(damage, "内伤");
       msg += "( $n"+eff_status_msg(p)+" )\n";  

	me->add("neili", -150 * arg);
	me->start_busy(2);
	}
    else {
	me->start_busy(arg/2+1);
    me->add("neili", -200);
    target->add("neili", -100);
    msg =RED"\n$n就地一滚，躲开了攻击，吓的脸色惨白。\n" NOR;
       	}
 message_vision(msg, me, target);

	return 1;
}