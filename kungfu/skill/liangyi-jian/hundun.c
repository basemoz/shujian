//by daidai 2005-12-26
//重新写，简化代码
//by spiderii@ty 完善
//by spiderii@ty 再次更新。修改判断命中条件
#include <ansi.h>
inherit F_SSERVER;
void finish();
int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用"HIG"混沌剑气"NOR"。\n");
        weapon = me->query_temp("weapon");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
              || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("你手里没有剑，无法使用"HIG"混沌剑气"NOR"！\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 200 )
                return notify_fail("你的正两仪剑法不够娴熟，无法施展出"HIG"混沌剑气"NOR"。\n");
        if( (int)me->query_skill("sword", 1) < 200 )
                return notify_fail("你的基本剑法不够娴熟，无法施展出"HIG"混沌剑气"NOR"。\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 200 )
                return notify_fail("你的玄天无极功不够娴熟，无法施展出"HIG"混沌剑气"NOR"。\n");
        if ( (int)me->query("max_neili") < 2500)
                return notify_fail("你的内力不够，无法施展出"HIG"混沌剑气"NOR"。\n");
        if ( (int)me->query("neili") < 1000)
                return notify_fail("你的真气不够，无法施展出"HIG"混沌剑气"NOR"。\n");
        if ((int)me->query("jingli") < 300)
                return notify_fail("你的精气不够，无法施展出"HIG"混沌剑气"NOR"。\n");

        message_vision(HIG"\n$N"HIG"剑走太极，招式连绵不绝，把$n完全淹没在一团混沌剑意之中。\n"NOR, me,target);
        me->set_temp("lianhuan", 5);
        me->add("neili", -100-random(100));
        me->add("jingli", -100);
        message_vision(HIG"$N手中的"+weapon->query("name")+HIG"如行云流水一般，向$n攻去,看似不重，却也蕴藏致命杀机！\n"NOR,me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2) {
                   message_vision(HIW"\n$n只觉得自己周身被$N剑气缠绕，体内真气难以运转自如！\n"NOR, me,target);
                   target->apply_condition("no_exert", 1);
                   me->start_perform(999,"「"HIG"混沌剑气"NOR"」");
                   call_out("check_fight", 1+random(3), me, 1+i/30);
} 
    else {
        message_vision(HIY"$n向后一跃，逃离了$N剑气笼罩的范围！\n"NOR, me,target);
        me->start_busy(1);
        me->start_perform(3,"「"HIG"混沌剑气"NOR"」");
        me->add("neili",-300);
}
    return 1;
}

void remove_effect(object me)
{
         int i=me->query_skill("liangyi-jian",1);
         object target = offensive_target(me);
         if(!me) return;
         me->delete_temp("lianhuan");
         if(!living(me)) return;
         if (me->is_fighting()) {
             message_vision(HIW"\n\n$N"HIW"剑势如网交织逼至，从四方八面涌入，重重把$n前后左右紧夹。\n$n只觉得四周压力骤增，$N的「"HIG"混沌剑网"HIW"」已将$n团团围住！\n"NOR, me,target);
             me->set_temp("lianhuan", 5);
             me->set_temp("lianhuan2", 1);
        if(me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        call_out("check_fight", 1, me, 1+i/30);
           }

         else {
       
           me->delete_temp("lianhuan"); 
           me->delete_temp("lianhuan2");
           me->start_perform(4,"「"HIG"混沌剑气"NOR"」");
           message_vision(HIY"\n$N"HIY"的「"HIG"混沌剑气"HIY"」绝技使完，$N神采飞扬气息均匀，动作优美潇洒非凡。\n"NOR, me);
      }
}
void finish()
{
       object me = this_player();
       me->delete_temp("kj");
       me->delete_temp("lianhuan"); 
       me->delete_temp("lianhuan2");
       me->start_perform(4,"「"HIG"混沌剑气"NOR"」");
       if(!me->is_busy())
       me->start_busy(1+random(2));
       message_vision(HIW"$N轻轻舒了一口气，剑法恢复了自然。\n"NOR, me);
}

void check_fight(object me, int i)
{
    object weapon, target;
    int jl;

    if (!me ) return;
    
    target = offensive_target(me);
     
    if( !living(me) 
        || !target 
        || !me->is_fighting(target) 
        || !living(target)
        || environment(target)!=environment(me)
        || !me->query_temp("lianhuan"))
              call_out("finish",1);

    else if(me->query_skill_mapped("sword") != "liangyi-jian"){
                tell_object(me, HIR"你临时改换剑法，决定不再使用「"HIG"混沌剑气"NOR"」绝技。\n");
                call_out("finish",1);
                }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"你临时改换武器，决定不再使用「"HIG"混沌剑气"NOR"」绝技。\n");
                call_out("finish",1);
                }
    else if ((int)me->query("neili") < 200 ){
                tell_object(me, HIR"你内力不济，只得缓缓收回「"HIG"混沌剑气"NOR"」。\n");
                call_out("finish",1);
                }
    else if ((int)me->query("jingli") < 100 ){
                tell_object(me, HIR"你体力不支，只得缓缓收回「"HIG"混沌剑气"NOR"」。\n");
                call_out("finish",1);
                }
    else if(me->is_busy()) 
                call_out("check_fight", 1, me, i);
    
    else{
           me->add("neili", -80);
           jl= me->query_skill("sword")/2;
           me->add("jingli", -30);
           message_vision(HIG"\n$N的剑气交织成网，层层叠叠，$n喘气如牛，行动迟缓，举步艰难。\n"NOR, me,target);
           if (random(me->query_skill("force")) > target->query_skill("force") /2 
               && me->query_skill("liangyi-jian",1)> 240 ){ 
               message_vision(HIC"$n只觉得自己周身被$N剑气缠绕，体内真气难以运转自如！\n"NOR, me,target);
               target->apply_condition("no_exert", 1);
        }  
           if(me->is_fighting(target) )
                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                   target->start_busy(1+random(2));
                   target->add("jingli", -(jl+random(200)));
                   target->add("neili", -(jl+random(200))); 
                   me->add_temp("lianhuan",-1);                       
                   i--;
          if (me->query_temp("lianhuan")==1 && me->query_skill("liangyi-jian", 1) >250 && !me->query_temp("lianhuan2")) remove_effect(me);  
     else  
         call_out("check_fight",2+random(2), me, i);
           }
}



string perform_name(){ return HIW"混沌剑气"NOR; }
int help(object me)
{
write(HIW"\n两仪剑法之「混沌剑气」："NOR"\n\n");
write(@HELP
要求      最大内力 2500 点以上；
          当前内力 1000 点以上；
          当前精力 400 点以上；
          两仪剑法等级 200 以上；
          玄天无极功等级 200 以上；
          激发剑法为两仪剑法；
          激发招架为两仪剑法；
          激发内功为玄天无极功；
          手拿兵器。
HELP
);
return 1;
}

