// shijiushi.c 玉女十九式
// Update by lsxk@hsbbs 调整剑宗和气宗使用效果。

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
string perform_name() {return HIC"玉女十九式"NOR;}

int perform(object me, object target)
{
        string weapon;
        int i;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("玉女十九式只能对战斗中的对手使用。\n");
    
        if (me->query_skill_mapped("force") != "zixia-gong"
          &&me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("你的内功有误，无法使用「玉女十九式」。\n");

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用玉女十九式！\n");
        
        if( me->query_skill("zixia-gong", 1) < 300
         && me->query_skill("huashan-qigong", 1) < 300)
                return notify_fail("你的特殊内功火候未到，无法施展玉女十九式！\n");

        if( (int)me->query_skill("huashan-jianfa",1) < 300 )
                return notify_fail("你的华山剑法火候不足，无法使用精妙绝伦的玉女十九式！\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("玉女十九式需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用玉女十九式！\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("你的内力不够使用玉女十九式！\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("你的精力不够使用玉女十九式！\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("你正在运用玉女十九式！\n");

      if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("你手中无剑怎能使用玉女十九式？！\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N运剑如风，精妙非常的“玉女剑十九式”一式式施展开来。" + weapon + HIC"如银龙出海,幻起道道电光！\n" +
        "顷刻之间，$N将“玉女十九剑”中那十九式的数百招一气呵成的使了出来，这数百招便如一招，剑法之快，直是匪夷所思。\n" NOR, me, target);
        me->set_temp("hsj_19",1);
        if(me->query("quest/huashan")=="气宗")
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/5);
 
    for( i = 0; i < MAX_HITS; i ++ ) {
        if( random( MAX_HITS ) >= i ||(i<=4 && me->query("quest/huashan")=="剑宗")) {
          if (me->query("quest/huashan") == "剑宗"){
             me->add_temp("apply/damage",(int)me->query_skill("huashan-jianfa",1)/4);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->add_temp("apply/damage",-(int)me->query_skill("huashan-jianfa",1)/4);
          }
          else if(me->query("quest/huashan") == "气宗"){
             if(random(3)) target->set_temp("must_be_hit",1);
             if(!random(3)){
                 message_vision(HIW"$N更加浑厚内劲附于手中"+weapon+HIW+"上，$n只觉一股劲风袭来，"+
                     "竟吓得手脚不听使唤！\n"NOR,me,target);
                 target->add_busy(1);
             }
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
             target->delete_temp("must_be_hit");
          }
          else
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
          me->add("neili",-100);
          }
        else {
            break;
        }
    }
        me->add("neili", -300);
     if(me->query("quest/huashan")=="气宗")
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/5);
        me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(2+random(3));

        return 1;
}

int help(object me)
{
   write(WHT"\n华山剑法「"HIC"玉女十九式"WHT"」："NOR"\n");
   write(@HELP
    这招「玉女十九式」乃穷华山先辈心血而创，华山剑宗，气宗对其理
    解却各有所不同，剑宗讲究剑招轻盈灵巧，行云流水，而气宗却讲究
    以深厚内力驭剑，攻敌破绽，一招即出，绝无不中之理。因此，剑宗
    使用，出招数以及威力均强与气宗，而气宗使用，则命中率远高于剑
    宗，并有几率让敌人忙乱。
    指令：perform shijiushi

    要求：华山气功 或者 紫霞神功 300级
          后天身法大于60，
          华山剑法300级，
          基本剑法300级，
          基本轻功300级，
          当前内力5000以上，
          当前精力3000以上。
HELP
   );
  return 1;
}
