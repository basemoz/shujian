// juli.c 真气聚力  By lsxk@hsbbs 2007/7/22
// 作用为：增加后天身法和躲闪。  By lsxk@hsbbs

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIW"真气聚力"NOR;}

private int remove_effect(object me, int amount);
int exert(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「真气聚力」只能在战斗中使用。\n");

        if((int)me->query_skill("huashan-qigong", 1) < 150 )
                return notify_fail("你的华山气功等级不够，不能使用「真气聚力」。\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 150 )
                return notify_fail("你的华山剑法不够娴熟，不能真正发挥「真气聚力」的威力。\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         ||( me->query_skill_mapped("parry") != "huashan-jianfa" &&  me->query_skill_mapped("parry") != "dugu-jiujian")
         ||( me->query_skill_mapped("sword") != "huashan-jianfa" &&  me->query_skill_mapped("sword") != "dugu-jiujian") )
                return notify_fail("你现在无法使用「真气聚力」！\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能使用「真气聚力」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「真气聚力」。\n");

        if(me->query_temp("hsqg/juli"))
                return notify_fail("你现正在使用「真气聚力」。\n");

        if(me->query_temp("hsqg/yjs"))
                return notify_fail("你现正在使用「驭剑式」。\n");                

/*
        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("你正在使用「君子剑法」绝技。\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("你正在使用「淑女剑法」绝技。\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("你正在使用「淑女剑法」。\n");

        if ( me->query_temp("zxg/jianyi") ) 
                return notify_fail("你正在使用「紫霞剑意」。\n");
*/
        if (me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("你的内功有误，无法使用「真气聚力」。\n");

    message_vision(HIW"$N暗运一口真气，内力竟全部流转于握剑之手，顿时$N的剑招变得无法琢磨!\n"NOR, me);
        me->start_exert(3+random(2),"「真气聚力」");
//        me->start_perform(2+random(2),"「真气聚力」");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/5;
        me->add_temp("apply/dexerity",  skill);
//        me->add_temp("apply/dodge",skill*5/4);
        if(me->query("quest/huashan")=="剑宗"){
            me->add_busy(1);
            me->add_temp("apply/damage",skill);
        }
        me->set_temp("hsqg/juli", skill);

        call_out("check_fight", 1, me, weapon);
        return 1;
}

void check_fight(object me, object weapon)
{  
        object wep;
        int i;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("force") != "huashan-qigong"
         || !wep
         || weapon != wep ){
       i = me->query_temp("hsqg/juli");
           me->add_temp("apply/dexerity", -i);
//           me->add_temp("apply/dodge",-i*5/4);
           if(me->query("quest/huashan")=="剑宗")
               me->add_temp("apply/damage",-i);
           me->delete_temp("hsqg/juli");
           if(living(me) && !me->is_ghost())
              message_vision(HIW"$N渐感内力不支，长长地呼了口气，招数又恢复了平常。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon);
}

int help(object me)
{
    write(YEL"\n华山气功「"HIW"真气聚力"YEL"」："NOR"\n");
   write(@HELP
   华山气功乃华山一派基础内功，虽不及本门紫霞神功精妙，但若练到
   深处，也绝非同小可！此「真气聚力」绝技乃运内劲于四肢，大幅度
   提高自身实战身法和躲闪，配合华山剑法以显轻盈灵巧。若华山派剑
   宗使用，则剑招威力更甚！
   指令：exert juli

   要求：华山气功150级，
         华山剑法150级，
         当前内力 500 以上，
         当前精力 500 以上，
         激发华山剑法为招架。
HELP
   );
   return 1;
}
