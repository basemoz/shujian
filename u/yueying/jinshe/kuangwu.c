//by yueying
 
#include <ansi.h>
#include <combat.h>
 
 inherit F_SSERVER;
 
 int perform(object me, object target)
 {
         string msg;
          int j, z, bt,st,dexs,armor,skills;
         object weapon;
         j = me->query_skill("jinshe-jianfa", 1)/8;
         z = me->query_skill("jinshe-zhang", 1)/8;
         bt = me->query_skill("wudu-yanluobu", 1)/100;
         dexs = me->query_dex()*2;
         armor = me->query_int()*3;
         skills = me->query_skill("sword",1)/5 + me->query_skill("jinshe-jianfa",1)/5;  
         
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
 
         if( !target || !me->is_fighting(target) )
                 return notify_fail("「金蛇狂舞」只能在战斗中对对手使用。\n");
 
         if (!weapon || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("你必须在使用剑时才能使出「金蛇狂舞」！\n");
 
         if(me->query_skill("jinshe-jianfa", 1) < 120 )
                 return notify_fail("你的金蛇剑法还不够娴熟，使不出「金蛇狂舞」绝技。\n");

         if( (int)me->query_skill("force") < 170 )
                 return notify_fail("你的内功等级不够，使不出「金蛇狂舞」绝技。\n");
 
         if( (int)me->query_str() < 27)
                 return notify_fail("你的膂力还不够强劲，使不出「金蛇狂舞」绝技。\n");
 
         if( (int)me->query_dex() < 27)
                 return notify_fail("你的身法还不够迅猛，使不出「金蛇狂舞」绝技。\n");
//增加对先天属性的要求
         if( (int)me->query("dex") < 20 || (int)me->query("str") > 20 || (int)me->query("int") < 20)
                 return notify_fail("你傻头傻脑,笨手笨脚的,乱舞个什么劲.\n");
         if((int)me->query_temp("jinshe_kuangwu")) 
                 return notify_fail("你现在正在使用「金蛇狂舞」绝技。\n"); 
                 

         if( (int)me->query("max_neili") < 800 )
                 return notify_fail("你现在内力太弱，使不出「金蛇狂舞」。\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("你现在真气不足，使不出「金蛇狂舞」。\n");
 
         msg = HIC"\n突然$N绕着$n快速奔走，猛然击出两剑一掌，齐齐指向$n！\n\n"NOR;
 
          
         if(weapon->query("id") == "jinshe sword" || !userp(me)){
            me->set_temp("jsj", 1);
            msg = HIR"\n$N手中金蛇剑连划数剑，逼出道道金光，剑光中$N化身为二，掌剑齐出，直指$n！\n\n"NOR;
         }
         if(  me->query_skill("wudu-yanluobu", 1) > 120 
           && me->query_skill_mapped("dodge") == "wudu-yanluobu"
           && me->query_skill("jinshe-zhangfa",1) > 120
           && me->query_skill_mapped("strike") == "jinshe-zhangfa"
           && me->query_skill_prepared("strike") == "jinshe-zhangfa")
         {  
         	   msg = HIY"\n$N一抖手中"+weapon->name()+HIR",绽放出万道金光,$n顿时觉得眼花缭乱,被$N攻了个措手不及！\n\n"NOR; 
         	   if(userp(target) && me->query_temp("jsj")) target->start_busy(1);
         else if ( !userp(target)){
        	    bt = me->query_skill("wudu-yanluobu",1)/100;
            	target->start_busy( bt + random(2));
           }
              
              me->start_perform(4,"「金蛇狂舞」");
              me->add("neili", -300);
              me->add("jingli", -200);
              me->add_temp("apply/attack",  me->query_skill("jinshe-jianfa", 1));
              me->add_temp("apply/strength",  me->query_skill("jinshe-zhangfa", 1)/7);
              
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※  金  ※※\n"NOR,me);
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
   
        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※  蛇  ※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       

        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※  狂  ※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※  舞  ※※\n"NOR,me);       
                          message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
        me->add_temp("apply/attack", - me->query_skill("jinshe-jianfa", 1));
        me->add_temp("apply/strength", - me->query_skill("jinshe-zhangfa", 1)/10);

            me->start_busy(1);
            target->start_busy(1);
            return 1;
           }  
           
//dodge strike sword 三种,增加busy效果,对npc busy效果加强,有jinshe sword效果加强              
       if( me->query_skill("wudu-yanluobu", 1) < 120 || me->query_skill_mapped("dodge") != "wudu-yanluobu")
         	{
            if ( me->query_skill("jinshe-zhangfa", 1) < 120 || me->query_skill_mapped("strike") != "jinshe-zhangfa"
          || me->query_skill_prepared("strike") != "jinshe-zhangfa" ){
              if ( weapon->query("id") != "jinshe sword" && userp(me))
         {    
           me->add_temp("apply/strength", z);
           me->add_temp("apply/attack", j); 
           me->add("neili", -300);
           me->add("jingli", -150);
           me->add_temp("apply/armor", armor);
           me->add_temp("apply/dexerity",dexs);
           me->set_temp("jinshe_kuangwu", 1); 
           message_vision(HIW"\n$N手中"+weapon->name()+HIW"信手一召,幻化出无数金芒，向$n电掣攻去。\n"NOR,me,target);
           me->add_temp("apply/damage", 100);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           me->add_temp("apply/damage", -100);
           me->start_perform(3,"「金蛇狂舞」");
           call_out("check_fight", 1, me, dexs, armor, skills);
           return 1;
                  }
                  
                        
          }
           
         } 
         if( me->query_skill("wudu-yanluobu", 1) > 120 && me->query_skill_mapped("dodge") == "wudu-yanluobu")
         
         {
         me->add_temp("apply/dexerity",(int)me->query_skill("wudu-yanluobu",1)/3);
         me->add_temp("apply/attack",(int)me->query_skill("wudu-yanluobu",1)/3);
         
         }
         if( me->query_skill("jinshe-zhangfa", 1) > 120 && me->query_skill_mapped("strike") == "jinshe-zhangfa"
         	  && me->query_skill_prepared("strike") == "jinshe-zhangfa")
         {
         me->add_temp("apply/strength", (int)me->query_skill("jinshe-zhangfa",1)/7);
         me->add_temp("apply/damage", (int)me->query_skill("jinshe-zhangfa",1)/4);
         
         }
         if( me->query_skill("jinshe-jianfa",  1) > 120 && me->query_skill_mapped("sword") == "jinshe-jianfa")
         {
         me->add_temp("apply/sword", (int)me->query_skill("jinshe-jianfa",1)/5);
         me->add_temp("apply/parry", (int)me->query_skill("jinshe-jianfa",1)/4);
         
        }	 
                  
         message_vision(msg, me, target);
          
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);
         me->add("jingli", -10); 
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ※※  金  ※※\n"NOR,me);       
 
         weapon->unequip(); 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);  
         me->add("jingli", -10);
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ※※  蛇  ※※\n"NOR,me);
 
         weapon->wield();
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);  
         me->add("jingli", -10);
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ※※  狂  ※※\n"NOR,me);
 
         if(me->query_temp("jsj"))
         {          
            weapon->unequip(); 
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
            me->add("neili", -50);  
            me->add("jingli", -5);
            message_vision(HIY"                                                                     ※※  舞  ※※\n"NOR,me);        
            weapon->wield();               
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
            me->delete_temp("jsj");
            me->add("neili", -50);
            me->add("jingli", -5);
            me->add_temp("apply/damage", -50);
         }
 
        
         me->delete_temp("apply");
 
         me->start_busy(1+random(2));
         target->start_busy(1);
         return 1;
 }

void remove_effect(object me, int dexs, int armor, object weapon)
{      
       me->add_temp("apply/armor", -armor);
       me->add_temp("apply/dexerity",-dexs);
       me->delete_temp("jinshe_kuangwu");
       tell_object(me, HIW"你「金蛇狂舞」施展完毕，身法渐渐慢了下来。\n" NOR); 
}

void check_fight(object me, int dexs, int armor, int skills)
{
       object weapon;
       if (!me) return;
       if(!objectp(weapon = me->query_temp("weapon"))
         || me->query_skill_mapped("sword") != "jinshe-jianfa"
         || weapon->query("skill_type") != "sword"){
           remove_effect(me, dexs, armor, weapon);
           return;
       }
       if( skills < 1 || !me->is_fighting()) {
           remove_effect(me, dexs, armor, weapon);
           return;
       }
       call_out("check_fight", 1, me, dexs, armor, skills-1);
}
int help(object me)
{
        write(HIY"\n金蛇秘籍之「金蛇狂舞」："NOR"\n\n");
        write(@HELP
        金蛇郎君夏雪宜所流传下来的的绝世武功. 可惜在争夺中金蛇秘籍被
        分割成好几部分, 金蛇狂舞的威力也大不如前. 相传在凑齐金蛇秘籍
        中的剑法, 身法, 掌法后才能发挥金蛇狂舞真正的威力. 如果有幸可
        以获得金蛇剑, 可使其威力更上层楼.

        要求：  当前内力 1500 以上；　最大内力 2800 以上；
                先天身法,悟性不能小于20,先天臂力不能大于20,
                后天身法臂力大于27
                第一阶段：金蛇剑法等级 120 以上；基本内功等级 170 以上；
                　　　　　激发剑法为金蛇剑法；
                第二阶段：金蛇掌法等级 120 以上；激发准备掌法为金蛇掌法；
                第三阶段：五毒阎罗步等级 120 以上；激发轻功为五毒阎罗步；
                
                另外，如果装备了金蛇剑，威力可更上一层楼．

HELP
        );
        return 1;
}
