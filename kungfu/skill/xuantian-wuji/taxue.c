// 玄天无极-踏雪无痕
// 脚踏白雪身无痕
// modify by cmkj 2003.8.19
// update增加飞跃后效果
#include <ansi.h>
void remove_effect(object me,int count);

string exert_name() {return HIY"踏雪"NOR;}

int exert(object me)
{                               
        int improve;
      
        if( !me->is_fighting() && (int)me->query_skill("xuantian-wuji",1)<350 )
                return notify_fail("你现在只能在战斗中使用「踏雪」！\n");

        if( (int)me->query_skill("xuantian-wuji",1) < 100 )
                return notify_fail("你的玄天无极功还不够娴熟，不会使用「踏雪」！\n");

        if (me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你的内功不对，不能使用「踏雪」。\n");
      
        if((int)me->query("max_neili")<1000)
                return notify_fail("你的内力修为太差，多多打坐吧。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");

        if( me->query_temp("kl/taxue")   )
                return notify_fail("你正在使用「踏雪」！\n");

        if( me->query_temp("kl/riyue")   )
                return notify_fail("你正在使用「日月无极」！\n");
      
        message_vision(CYN"$N双手虚按丹田，高纵上跃，矫若游龙，宛似凌空飞行，" +
        "飘然若仙！\n" NOR, me);
      
        improve = (int)me->query_dex();
        me->start_perform(1,"「踏雪」");
        me->add_temp("apply/dodge", improve);
        me->add_temp("apply/dexerity", improve);
        me->set_temp("kl/taxue",improve);  
        me->add("neili", -(350-(int)me->query_skill("xuantian-wuji",1)/10));            
        call_out("remove_effect", 1, me, improve);
        return 1;
}

void remove_effect(object me,int count)
{
         int improve;
         if( !me ) return;
         if( !intp(improve = me->query_temp("kl/taxue"))) return;
         if( count < 1){
          me->add_temp("apply/dodge", - improve);
          me->add_temp("apply/dexerity", -improve);
          me->delete_temp("kl/taxue");
          tell_object(me, HIY"你散去丹田聚集的内力，立定了脚步，身法回复了正常。\n"NOR);
          tell_room(environment(me), HIY + me->name()+"气回丹田，散去了周身的功力。\n"NOR,  ({ me })); 
          return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(WHT"\n玄天无极功「踏雪」字诀："NOR"\n");
        write(@HELP
        玄天无极功，传为昆仑派绝世内功心法。此「踏雪」练成后高纵上跃，矫若游龙，在腾起之势将竭之时，
        可以不借助任何物体，仅凭身形在空中打一回旋，便可立即拔高，如是者再，即可盘旋而上达二三十丈。
        此心法一经使出，可大幅度提升轻功身法，且在自身忙乱时能极大的消耗所受的伤害。

        要求：  踏雪无痕等级 120 以上；
                玄天无级等级 100 以上；
                最大内力 1000 以上；
                当前内力 600 以上；
                不可与 日月无极 同时使用。
HELP
        );
        return 1;
}
