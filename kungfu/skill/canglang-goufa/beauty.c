// beauty 美人三招
// 19991002001
// Update By lsxk@hsbbs 2007/6/5

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return MAG"美人三招"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「美人三招」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「美人三招」只有拜了教主后才能用！\n");

        if( objectp(weapon=me->query_temp("weapon")) ) {
                string *ids = weapon->parse_command_id_list();
                if (member_array("bishou", ids) == -1)                          
                        return notify_fail("你必须拿着匕首才能用「美人三招」！\n");
        }
        else {
                return notify_fail("你必须拿着匕首才能用「美人三招」！\n");
        }
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 150 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("只有使用化骨绵掌时才能使用「美人三招」！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 150 )
                return notify_fail("你的神龙腿法还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("只有使用神龙腿法时才能使用「美人三招」！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 150 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("只有使用沧浪钩法时才能使用「美人三招」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("你的毒龙大法功力不足，不能用「美人三招」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「美人三招」！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用「美人三招」！\n");      

        if(me->query("gender") == "男性" ) 
                return notify_fail("不是女人怎么能使用「美人三招」呢！\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用「美人三招」。\n");


        me->add("jingli",-100);
        me->add("neili",-400);

        msg = MAG"$N乘$n稍稍走神之机，拼尽全力使出苏夫人不传之绝技－－「美人三招」"NOR;

        if(random((int)me->query_skill("canglang-goufa",1))*8/5 > (int)target->query_skill("parry",1)
          ||random((int)me->query("combat_exp"))*8/5 > (int)target->query("combat_exp")
          ||target->is_busy() ){
                me->start_busy(1);
                total = 0;
                msg +=MAG "\n\n$N使出一招「"HIM"贵妃回眸"MAG"」，身子微曲，纤腰轻扭，左足反踢，向$n小腹踢去，\n"+
                          "而后顺势反身，左手搂住$n头颈，右手兵刃对准$n后心击去。\n"NOR;
                i = calc_damage((int)me->query_skill("huagu-mianzhang",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "头颈" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 

                msg =MAG "\n$N使出一招「"HIG"小怜横陈"MAG"」，脑袋蓦地向自己胸口钻落，顺势在地上一个斛斗，\n"+
                         "从$n胯下钻过，握着兵器的右手成拳击向$n后心。\n"NOR;

                i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "后心" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =MAG "\n$N使出一招「"HIB"飞燕回翔"MAG"」，右足顺势一勾，在兵器上一点，兵器陡地向$N咽喉\n"+
                         "射过去，$N身子向下一缩，那兵器急射$n胸口。\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"内伤");
                result = replace_string( result, "$l", "胸口" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(5,"「美人三招」");
        }
        else {
                msg += MAG "\n\n$N使出一招「"HIM"贵妃回眸"MAG"」，身子微曲，纤腰轻扭，左足反踢，向$n小腹踢去，\n"+
                           "而后顺势反身，左手搂住$n头颈，右手兵刃对准$n后心击去。\n"NOR;
                msg += "但是$n看破了$N的企图，没有上当，急急忙忙向旁边一闪，躲了过去。\n";
                msg +=MAG "\n$N使出一招「"HIG"小怜横陈"MAG"」，脑袋蓦地向自己胸口钻落，顺势在地上一个斛斗，\n"+
                          "从$n胯下钻过，握着兵器的右手成拳击向$n后心。\n"NOR;
                msg += "$n吃了一惊，但随即冷静下来，在空中猛一蹬腿踢向$N面门，$N只得松开了手。\n";
                msg +=MAG "\n$N使出一招「"HIB"飞燕回翔"MAG"」，右足顺势一勾，在兵器上一点，兵器陡地向$N咽喉\n"+
                          "射过去，$N身子向下一缩，那兵器急射$n胸口。\n"NOR;
                msg += "$n被$N制住，但临危不乱，以内力护住要害，同时高高跃起，翻身以头撞地，把$N撞了出去！\n";
                message_vision(msg,me,target);
                me->start_busy(1+random(3));
                me->start_perform(3,"「美人三招」");
        }
        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);
//            if( i < (skill2*5)) i = (int)target->query("qi",1)/3;    //By lsxk 取消sld女弟子该效果

            if(!userp(me)) i = i/2;

       return i/3; //再次降低女弟子使用效果 by lsxk@hsbbs 2007/6/5/
}

int help(object me)
{
   write(WHT"\n沧浪钩法「"MAG"美女三招"WHT"」："NOR"\n");
   write(@HELP

    要求：当前内力 1500 以上；
          当前精力 800 以上；
          化骨绵掌等级 150 以上；
          神龙腿法等级 150 以上；
          沧浪钩法等级 150 以上；
          毒龙大法等级 150 以上；
          性别需求 女性。
HELP
   );
   return 1;
}
