// Modified by Lane@SJ 2005/4/14

#include <ansi.h>
int exert(object me)
{
if( !me->is_fighting() )
return notify_fail("你现在这么闲，慢慢打坐疗伤吧。\n");

if( (int)me->query_skill("linji-zhuang", 1) < 60 )
return notify_fail("你的内功修为还不够。\n");

if( (int)me->query_skill("medicine", 1) < 60 )
return notify_fail("你的本草术理修为还不够。\n");

if( (int)me->query("neili") < 200 )
return notify_fail("你的真气不够。\n");

if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
return notify_fail("没受伤，疗什么伤啊？\n");

if( (int)me->query("eff_qi") < (int)me->query("max_qi")*3/10 ) // 改为30%上限
return notify_fail("你已经受伤过重，经受不起真气震荡！\n");

if( me->query_temp("ljz/wuwo") )// 改成 不能和 wuwo 同时使用
return notify_fail("你正在运用临济十二庄的「无我」字决！\n");

message_vision(HIW"$N深深的吸了口气，脸色看来好多了。\n"NOR,me);
me->receive_curing("qi", (int)me->query_skill("force")/3);
me->add("neili", -100);
me->start_exert(1,"天地");
me->start_busy(random(2));
return 1;
}
string exert_name(){ return HIW"天地字决"NOR; }

int help(object me)
{
        write(HIW"\n临济十二庄「天地字诀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 200 以上；
                临济十二庄等级 60 以上；
                本草术理 60 以上；
                不能和「无我」字诀同时使用。
HELP
        );
        return 1;
}
