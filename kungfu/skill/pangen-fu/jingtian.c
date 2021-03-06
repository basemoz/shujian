//  jingtian.c 惊天断云斧 
//  by Leontt 2000.6.11

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("pangen-fu", 1)/3;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
        return notify_fail("「惊天断云斧」只能在战斗中对对手使用。\n");
    
      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "pangen-fu")
        return notify_fail("你使用的兵刃不对，无法使用「惊天断云斧」！\n");             

      if( (int)me->query_skill("pangen-fu",1) < 120 )
        return notify_fail("你的盘根斧法不够娴熟，不能使用「惊天断云斧」！\n"); 
      
      if( (int)me->query_skill("axe",1) < 100 )
        return notify_fail("你的基本斧法等级不够，不能使用「惊天断云斧」！\n");  
     
      if( (int)me->query_skill("qiantian-yiyang", 1) < 100 )
        return notify_fail("你的乾天一阳功等级不够，不能使用「惊天断云斧」！\n");

      if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力太弱，不能使用「惊天断云斧」！\n");
      
      if( (int)me->query("neili") < ( me->query_skill("force")+ lvl ))
        return notify_fail("你的内力太少了，无法使用出「惊天断云斧」！\n");   
      
      message_vision(HIY"\n$N突然突然大喝一声犹如惊雷一般，将手中"+weapon->query("name") +HIY"斜向上举起，然后在半空中划出一"+
                          "道圆弧，随即径直斜下斩向$n！这一瞬间，$n只觉得呼吸困难！\n"NOR, me,target);
      me->add("neili", - (300+random(200)));
      me->add("jingli", -80);      
      lvl= lvl/3 + me->query("con")/2 + me->query("str");
      me->add_temp("apply/axe", lvl);
      me->add_temp("apply/attack", lvl);
      me->set_temp("jingtian", 1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      if (present(target,environment(me)) && me->is_fighting(target))
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("pangen-fu", 1) > 150){
       if(random(me->query("combat_exp")) > target->query("combat_exp")/2)     
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       else 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      }
      me->add_temp("apply/axe", -lvl);
      me->add_temp("apply/attack", -lvl);
      me->delete_temp("jingtian");
      me->start_busy(random(2));
      me->start_perform(5,"「惊天断云斧」");
      return 1;
}
