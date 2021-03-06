// Exert: LifeHeal.c
// Date : AHA 97/06/22

#include <ansi.h>

int exert(object me, object target)
{
  string he;

  if(!objectp(target) || 
     (environment(me)!=environment(target)) ||
     !living(target)
    )
    return notify_fail("这里没有这个人。\n");
   
  if(target == me )
     return notify_fail("你想替自己疗伤，可是运功的方法不对。\n");
  
  he = target->name();

  if( me->is_fighting() )
      return notify_fail("战斗中无法替别人疗伤！\n");
  if( target->is_fighting() )
      return notify_fail(he+"正在战斗中，无法疗伤！\n");
  if( target->is_busy() )
      return notify_fail(he+"正忙着呢。\n");
  if ((int)me->query_skill("emei-jiuyang", 1) < 30)
      return notify_fail("你的九阳功修为太低，还是好好练功吧。\n");
  if( (int)me->query("neili") < 50 ) 
      return notify_fail("你的真气不足。\n");

  if( (int)target->query("eff_qi") >= (int)target->query("max_qi") )
      return notify_fail(he+"现在并没有受伤呀！\n");

  if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 3 )
      return notify_fail(
               he+"受伤太重了，只怕一受到真气震荡便会有生命危险！\n");
 
  if(target->query("gender") != "中性" &&
     target->query("gender") != me->query("gender") &&
     me->query("class")=="bonze")
       command("say 阿弥陀佛！善哉！善哉！为了救人，"
               +RANK_D->query_self(me)+"也顾不得男女之防了。\n");

  write( HIW "你盘腿坐下，一手按在"+he+"的小腹，另一手按在"+he+"的后腰，\n"
             "气凝丹田，开始为"+he+"疗伤。\n" NOR);
  message("vision",
     me->name() + HIR"的脸越来越红，"+HIW"头顶开始出现白雾，白雾越来越浓，\n"
           "逐渐将"+me->name()+"和"+he+"围了起来。\n"NOR     
          + me->name() + "运功完毕，长长地吐了一口气。"
          +he+"脸色看起来好了许多。\n",
     environment(me), me);
  
  target->receive_curing("qi", 20 + (int)me->query_skill("force")/5 );
  me->add("neili", -50);
  return 1;
}

�
