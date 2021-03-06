// Code Of ShenZhou
// 琴剑双绝   (perform jue)
// 要求：     玄天无极 300 级，两仪剑 300 级。 (需解 Quest)
// 说明：     琴剑合一的昆仑派绝学。       

#include <ansi.h>
#include <combat.h> 

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
mapping prepare_status; 
string weapon, op_weapon, op_skill, *pname; 
int my_power, op_power, my_li, op_li, my_jing, my_nei, op_jing, op_nei;
if( !target ) target = offensive_target(me); 

if( !target
||      !target->is_character() 
||      !me->is_fighting(target) ) 
        return notify_fail("「剑琴两绝」只能对战斗中的对手使用。\n"); 

if( me->query_skill_mapped("force") != "xuantian-wuji" ) 
return notify_fail("你所使用并非玄天无极功，所以无法施展其绝技！\n"); 

if( me->query_skill("force") < 350 )
return notify_fail("你的玄天无极功火候未到，无法运劲施展「剑琴两绝」！\n"); 

if( me->query_skill("sword") < 400 ) 
return notify_fail("你两仪剑法修为不足，还不会使用「剑琴两绝」！\n");

if( me->query_skill("qinqi-shuhua",1) < 250 )
return notify_fail("你琴棋书画修为不足，还不会使用「剑琴两绝」！\n");

if( me->query("neili") <= 500 ) 
return notify_fail("你的内力不够使用「剑琴两绝」！\n");  

if( me->query("jingli") <= 500 ) 
return notify_fail("你的精力不够使用「剑琴两绝」！\n"); 


my_jing = me->query("jingli") *7/10; 
my_nei = me->query("neili") *7/10;
  if ( target->query("neili") < me->query("neili")*3/2 ) { 
op_nei = target->query("neili")*8/10;
}
else op_nei = my_nei;

if ( target->query("jingli") < me->query("jingli")*3/2 ) { 
op_jing = target->query("jingli") *8/10; 
}
else op_jing = my_jing;

message_vision(HIY"\n$N突然间停于战阵外，掏出一个古琴，弹起一阵阵的琴声。\n\n"
               HIG"琴音变化无常，如同仙境中的琴声淘醉，琴音尽，$N持著剑大喝刺上正淘醉于琴声中的$n \n" NOR, me, target);

  my_power = me->query_skill("sword") + me->query_skill("dodge") + me->query_skill("force") + me->query_skill("parry") + me->query("combat_exp") / 900; 
  op_power = target->query_skill(op_skill) + target->query_skill("dodge") + target->query_skill("force") + target->query_skill("parry") + target->query("combat_exp") / 950; 

my_li = me->query("jingli") + me->query("neili"); 
op_li = target->query("jingli") + target->query("neili"); 

  if ( target->query("qi") < me->query("qi")*3/2 ) {
message_vision(RED"$N从淘醉中惊醒过来，发出一声凄历的叫声，人影带同剑刺中了$N的心房！\n\n" NOR, target);
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
target->receive_wound("qi", target->query("max_qi")*7/10, me);
}

else if ( me->query_str() > target->query_str() ) { 
message_vision(RED"$N及时惊醒过来，但却难以躲过这一击，发出一声凄历的惨嚎，剑已刺中心房！\n\n" NOR, target); 
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
target->receive_wound("qi", target->query("max_qi")/3, me); 
}

else if ( target->query("neili") < me->query("neili") ) { 
message_vision(RED"$N惊醒过来，但剑已刺入$N的心房，令$N发出一声凄历的惨嚎。\n\n" NOR, target); 
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
target->receive_wound("qi", target->query("max_qi")/4, me); 
}


else {
message_vision(HIY"$N从惊吓中回神，化尽力气才躲过了这绝技！\n" NOR, target);
}

me->add("neili", -1*1000);
me->add("jingli", -700); 
  target->start_busy(3);
  me->start_busy(5);
target->kill_ob(me); 
return 1;
}
