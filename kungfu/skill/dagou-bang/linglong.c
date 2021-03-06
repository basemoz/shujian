// linglong.c 玲珑棒诀

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBCYN"玲珑棒诀"NOR; }
int perform(object me, object target)
{
//       string msg;
       int ap, dp, damage, jl, i;
       object weapon;

       weapon = me->query_temp("weapon");
       if( !target ) target = offensive_target(me);

       if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
             return notify_fail("「玲珑棒诀」只能在战斗中使用。\n");

       if (!weapon 
        || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang")
             return notify_fail("你手里无棒，无法使用「玲珑棒诀」！\n");
       
       if((int)me->query_int() < 20)
             return notify_fail("你悟性不够,不能使用「玲珑棒诀」！\n");

       if( (int)me->query_skill("huntian-qigong", 1) < 200 )
             return notify_fail("你的混天气功修为不够，使不出「玲珑棒诀」绝技。\n");

       if (me->query_skill_mapped("force") != "huntian-qigong")
             return notify_fail("没有混天气功作为根基，是无法使出「玲珑棒诀」绝技的！\n"); 

       if((int)me->query_skill("dagou-bang",1) < 200)
             return notify_fail("你的打狗棒法修为不够,目前还不能使用「玲珑棒诀」！\n");

       if ((int)me->query_skill("bangjue",1) < 150)
             return notify_fail("「玲珑棒诀」是以打狗棒诀为基础的，你棒决不熟如何使用？\n");

       if((int)me->query("max_neili") < 2000)
             return notify_fail("你内力修为现在不够, 不能用「玲珑棒诀」！\n");

       if ((int)me->query("neili") < 800)
             return notify_fail("你内力用尽, 不能用「玲珑棒诀」！\n");

       if( target->query_temp("dgb_chan"))
             return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");

       message_vision( HIY"\n$N轻声一笑，潇洒已极，双目精光四射，口中念念有词。", me, target);
       message_vision(    "但见棒子化成了一团碧影，猛点$n后心\n“强间”、“风府”、", me, target);
       message_vision(    "“大椎”、“灵台”、“悬枢”各大要穴。只要被棒端点中，非死即伤。\n"NOR, me, target);
     //  message_vision(msg, me, target);  
ap= random(me->query_skill("dagou-bang",1))+me->query_skill("bangjue",1)/50*(1+random(me->query_int()/2));
dp= (int)target->query_skill("dodge",1);
       me->add("neili", -200);
       if( ap > dp ) {
       damage = me->query_skill("dagou-bang",1)*2+me->query_skill("bangjue",1)*(1+random(me->query("int")/3));
         if (damage > 2000) damage=2000+random(damage/5);
   message_vision(CYN"\n$n叫声不好，势在不及回身招架，只得向前窜跃趋避，岂知$N的点打连绵不断，一点不中，\n"+
                "又点一穴，棒影只在$n背后各穴上晃来晃去。$n一个疏神，连连中招!\n"NOR,me,target);
         target->receive_damage("qi",damage);
         target->receive_damage("jingli",damage/2);
         target->receive_wound("qi",damage/2);
 switch(random(3)) {
             	case 3: target->apply_condition("no_exert",3); message_vision(    HIR"$n被$N一棒点中了"+(random(2)?"「"HIC"强间穴"HIR"」":"「"HIW"灵台穴"HIR"」")+"，顿时头晕脑眩，体内真气无法运转自如。\n"NOR, me, target);
   
break;
 case 2:target->apply_condition("no_force",3); message_vision(    HIR"$n被$N一棒点中了"+(random(2)?"「"HIG"风府穴"HIR"」":"「"HIY"百会穴"HIR"」")+"，顿时脸色苍白，内息大乱。\n"NOR, me, target);
 
break;
 
case 1:target->apply_condition("no_perform",3);
message_vision(    HIR"$n被$N一棒点中了"+(random(2)?"「"HIM"大椎穴"HIR"」":"「"HIB"悬枢穴"HIR"」")+"，顿时行动迟缓，各种外功难以使用。\n"NOR, me, target);
break;default: target->apply_condition("no_exert",3); 
message_vision(    HIR"$n被$N一棒点中了"+(random(2)?"「"HIC"强间穴"HIR"」":"「"HIW"灵台穴"HIR"」")+"，顿时脸色苍白，体内真气无法运转自如。\n"NOR, me, target);
break;} COMBAT_D->report_status(target, 0);  me->add("neili", -300);
         me->start_busy(1);
  if(wizardp(me)) tell_object(me,sprintf("damage=%d\n",damage));
           //  message_vision(msg, me, target);
    
       me->start_perform(4,"「玲珑棒诀」");
   }
       else if(ap > dp/3*2){
        message_vision( HIG"$N朗声诵道：「狗急跳墙如何打？ 快击狗臀劈狗尾。」，随之向$n下盘接连攻出数招。\n" NOR,me,target);
        // message_vision(msg,me,target); 
         me->add("neili", -200);
  target->start_busy(1);
       for (jl=0; jl<4 ;jl++)
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
          //  me->start_busy(1);
   
       me->start_perform(4,"「玲珑棒诀」");
    }
       else if( ap > dp/2){
          message_vision( HIG"$N悄声念道：「棒回掠地施妙手 ，横打双犬莫回头。」, 随之棒影横掠而下，$n躲闪不及连中几下。\n"NOR, me, target);
       //  message_vision(msg, me, target);
         me->add("neili", -200);
 i = random(5) +3;
         target->add_busy(i);
         target->set_temp("dgb_chan", 1);
    
       me->start_perform(5,"「玲珑棒诀」");
     call_out("check_fight", 1, me, target, weapon, i);
       }
       else {
           message_vision(WHT"$n早识得丐帮打狗神技「玲珑棒诀」的厉害，料敌机先远远逃了开去。\n"NOR, me, target);
        me->start_busy(1+random(2));
       //   message_vision(msg, me, target);
    
       me->start_perform(3,"「玲珑棒诀」");
   }
       me->add("jingli", -100);
    return 1;
}

void check_fight(object me,object target,object weapon, int count)
{
       if( !target) return;
       if( !target->query_temp("dgb_chan")) return;
       if( ! me
        || !me->is_fighting()
        || weapon != me->query_temp("weapon")
        || count < 1){
         target->delete_temp("dgb_chan");
         if( target->is_busy())
          target->start_busy(1);
         return;
       }
       call_out("check_fight",1 ,me ,target ,weapon, count -1);
}

