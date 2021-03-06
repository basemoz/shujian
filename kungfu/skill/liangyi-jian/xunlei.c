// Code of ShenZhou
//Revised by earl
//Sep 6 9
//xunlei.c 迅雷剑

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
          int speed, attack, lv, damage;

           lv = (int)me->query_skill("liangyi-jian", 1); 
           damage = lv + random(lv/2) + (int)me->query_skill("sword",1);
                      attack = lv + random(lv/2);
                         speed = me->query_skill("sword")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
	     return notify_fail("「迅雷剑」只能对战斗中的对手使用。\n");

        if( me->query_temp("xunlei_yushi"))
	     return notify_fail("你剑势未尽，不能再施展「迅雷剑」！\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
	     return notify_fail("你使用的武器不对。\n");

          if( (int)me->query("neili") < 300 )
	     return notify_fail("你的内力不够！\n");

        if( me->query_skill("liangyi-jian", 1) < 100 )
	     return notify_fail("你的「两仪剑法」未臻高妙境界，无法使用「迅雷剑」！\n");
        if( me->query_skill("xuantian-wuji", 1) < 100 )
             return notify_fail("你的玄天无极修为不够，无法使用「迅雷剑」！\n");

        msg = HIR "\n$N手中"+weapon->query("name")+HIR"剑尖指向自己胸口，剑柄斜斜向外，怪异之极，竟似回剑自戕一般！\n\n" NOR;
        message_vision(msg, me,target);
        me->start_busy(1);
        ob = me->select_opponent();
        me->delete_temp("xunlei");
        me->set_temp("xunlei",4);
          me->add("neili", -5);
        me->set_temp("xunlei_yushi");
        call_out("checking", 1, me, target);
        return 1;
}


  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
	if ( !objectp( me ) ) return;
        weapon = me->query_temp("weapon");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword") {
		tell_object(me, "\n你手中无剑，当下停止了迅雷剑的架势。\n" NOR);
		me->delete_temp("xunlei");
		return;
	}
	else if ( weapon->query("weapon_prop") == 0 ) {
		tell_object(me, "\n你的"+weapon->name()+"已毁，无法持续迅雷剑的攻势！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
          else if ( (int)me->query("neili") < 300  ) {
                  message_vision(HIR"$N的内劲後继无力，不得不停止迅雷剑的攻势！\n" NOR, me,target);
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
	else if ( me->query_skill_mapped("sword") != "liangyi-jian" ) {
		tell_object(me, HIR "\n你转而施展其他剑法，无法再以迅雷剑攻敌！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
	else if ( me->is_busy() ) {
		tell_object(me, HIR "\n你现在动作受制，无法继续维持迅雷剑攻势！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
        else if (!me->is_fighting() || !objectp(target)) {
		tell_object(me,  "\n你现在没有和人过招，当下收回了迅雷剑的攻势。\n" NOR);
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
	if( environment(target) != environment(me) ) {
		tell_object(me, "你见对方已经不在这里，当下停止了迅雷剑的攻势。\n");
                    call_out("xunlei_end", 6, me);
		me->delete_temp("xunlei");
		return;
	}
         if ( me->query_temp("xunlei") ==4)message_vision(HIY"\n$N纵身近前，"+weapon->name()+HIY"陡然弯弯弹出，剑尖直刺$n，出招之快真乃为任何剑法所不及！\n" NOR, me,target);
	{
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		 me->add("neili", -5);
		 me->start_busy(1);
		target->start_busy(random(3));
		}
	
        if ( me->query_temp("xunlei") !=3 )message_vision(HIW"\n$N伸指在"+weapon->name()+HIW"上一弹，剑声嗡嗡，有若龙吟，"+weapon->name()+HIW"颤处，剑锋来势神妙无方！\n" NOR, me,target);
        {        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        	 me->add("neili", -5);
        	 me->start_busy(1);
		target->start_busy(random(3));
		}
	        
	if ( me->query_temp("xunlei") ==4 )message_vision(HIG"\n$N陡然间大喝一声，"+weapon->name()+HIG"上寒光闪动，喝道：「"+target->name()+HIG"，可小心了！」\n" NOR, me,target);
	    message_vision(HIR"\n见$N随手挥剑，"+weapon->name()+HIR"颤处，前后左右，瞬息之间已攻出了四四一十六招！\n" NOR, me,target);
            damage = (int)me->query_skill("liangyi-jian", 1)+ (int)me->query_skill("sword", 1);
           damage = random(damage)*2 + random(damage);
        {       me->start_busy(1+random(2));
                me->delete_temp("xunlei");
                call_out("xunlei_end", 12, me);
                me->start_busy(2);        	  
		target->start_busy(random(3));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));		
		target->receive_damage("qi", damage*2);
		target->receive_wound("qi", damage*3/2);
		target->add("neili", -damage/10);
		me->add("neili", -100);
        if ( damage < 300 ) message_vision(HIG"\n结果$n被剑招所逼，踉踉跄跄退了好几步！\n"NOR,me,target);
        else if(damage < 400 ) message_vision(RED"\n结果，$n已被长剑已刺入额头，深入寸许！\n"NOR,me,target);
	else if( damage < 500 ) message_vision(HIR"\n结果$n已被刺中数剑，口中鲜血狂喷而出！\n"NOR,me,target);        
        else message_vision(HIR"\n$n只觉身体一凉，长剑已穿胸而过！\n"NOR,me,target);
        }			    
 }
void xunlei_end(object me)
{
        object weapon;
	if ( !objectp( me ) )
		return;
        weapon = me->query_temp("weapon");

        tell_object(me, HIR "\n你暗自调息，渐渐平复腾涌的真气。\n\n" NOR);

        me->delete_temp("xunlei");
        me->delete_temp("xunlei_yushi");

}
