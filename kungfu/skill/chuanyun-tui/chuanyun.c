 // chuanyun.c 
// By Daidai 2002/03/16
//by spiderii@ty 完善
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"穿云"NOR;}

#define TICKTIME 5

 void exam1(object me , object tartget );

 int perform(object me, object target)
 {
              int j, z, y;
              j = me->query_skill("chuanyun-tui",1)/2;
              z = me->query_skill("zhentian-quan",1)/2;
              y = me->query_skill("xuantian-wuji",1)/2;

         if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("「穿云」只能对战斗中的对手使用。\n");
         if (me->query_skill_prepared("leg") != "chuanyun-tui"
             || me->query_skill_mapped("leg") != "chuanyun-tui")
                return notify_fail("你现在无法使用「穿云」！\n");  

         if((int)me->query_skill("chuanyun-tui", 1) < 120 )
                 return notify_fail("你的穿云腿够娴熟，不会使用「穿云」。\n");

         if((int)me->query_skill("xuantian-wuji", 1) < 120 )
                 return notify_fail("你的玄天无极功不够深厚，无法使用「穿云」。\n");

         if((int)me->query("max_neili") < 1500)
                 return notify_fail("你现在内力太弱，不能使用「穿云」。\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("你拿着兵器无法使用神龙追命腿。\n");

         if(me->query_skill_mapped("force") != "xuantian-wuji")
                 return notify_fail("你现在所使用的内功同玄天无极功相抵触，不能使用「穿云」。\n");

	  if( target->is_busy() )
		   return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧!\n");

	  message_vision( HIG "\n$N霍地借力一弹，冲天而起，已经运穿云破日重轰而至。\n"NOR, me, target);
                 
	 if( random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 )
	     {
		message_vision(   HIR "$n避无可避，整个人被腿劲凝成的「穿云」气墙，罩得密不透风，一时缓不过气来! \n" NOR, me, target);
		target->start_busy( random(2) + 2);
		me->add("neili", -200);
              me->add("jingli", -50);
        if( (int)me->query_skill("chuanyun-tui", 1) > 140 && me->is_fighting(target) )
              call_out("perform2", random(3)+3, me, target); 
	      }

        else
             {
             message_vision(HIR "$n却身如旋风急速翻转，轻易避过$N汹涌的一招。\n"HIY"$N一招失手，并不惊慌，趁势拳腿齐出，如风似电向$n攻出踢出几脚！\n"NOR,me, target);
             me->add_temp("apply/strength", j);
             me->add_temp("apply/dexerity", y);
             me->add_temp("apply/dodge", y*2);
             me->add_temp("apply/cuff", z*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/cuff", -z*2);
             me->add_temp("apply/leg", j*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/leg", -j*2);
             me->prepare_skill("leg");
             me->prepare_skill("cuff","zhentian-quan");
             me->add_temp("apply/cuff", z*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/cuff", -z*2);
             me->add_temp("apply/strength", -j);
             me->add_temp("apply/dexerity", -y);  
             me->add_temp("apply/dodge", -y*2);
             me->prepare_skill("leg","chuanyun-tui");  
             me->prepare_skill("cuff","zhnetian-quan");
             me->start_busy(3);
             me->add("neili", -400);
             me->add("jingli", -200);
       }
             me->start_perform(5,"「穿云」");
	      return 1;
     }
int perform2(object me, object target)
   {  
              int j,y,z;
              j = me->query_skill("chuanyun-tui",1)/2;
              z = me->query_skill("zhentian-quan",1)/2;
              y = me->query_skill("xuantian-wuji",1)/2;
 
              if (!me->is_fighting(target))   
                  return notify_fail("对手已经不能再战斗了。\n");   
              if( !target || !target->is_character() || !me->is_fighting(target) )
                  tell_object(me, HIC"\n对方已经被打倒，你将内力缓缓手回丹田！\n"NOR);   
              if( !target ) target = offensive_target(me);

              if( !target || !target->is_character() || !me->is_fighting(target) )
                  return notify_fail("「穿云」只能对战斗中的对手使用。\n");
              if( (int)me->query("neili") < 500 )
                  return notify_fail("你的内力修为还不够高。\n");
              if( (int)me->query("jingli") < 200 )
                   return notify_fail("你的精力修为还不够高。\n");
          message_vision(HIY "\n过了一会，「穿云」气墙的窒息之力渐渐微弱，$n总算可以缓过气来。\n"HIG"$N看准此刻正是$n体内新旧内力交换之际，立即乘虚而上，闪电般的向$p扫出两脚！\n"NOR,me, target);
          me->add_temp("apply/strength", j);
          me->add_temp("apply/dexerity", y);
          me->add_temp("apply/leg", j*2);
          me->add_temp("apply/dodge", y*2);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          me->add_temp("apply/strength", -j);
          me->add_temp("apply/dexerity", -y);
          me->add_temp("apply/leg", -j*2);
          me->add_temp("apply/dodge", -y*2);
          me->start_perform(5,"「穿云」");
          me->add("neili", -400);
          me->add("jingli", -150);  
    }
int help(object me)
{
   write(WHT"\n穿云腿「"HIY"穿云"WHT"」："NOR"\n");
   write(@HELP
    要求： 最大内力 1500 以上；
           当前精力 700 以上；
           穿云腿等级 120 以上；
           玄天无极功等级 120 以上。
HELP
   );
   return 1;
}
