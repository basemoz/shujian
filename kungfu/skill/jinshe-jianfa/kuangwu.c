//by yueying
 
#include <ansi.h>
#include <combat.h>
 
 inherit F_SSERVER;
 
 int perform(object me, object target)
 {
         string msg;
          int j, z, bt,st,dexs,armor,skills,n;
          int a, b, c;
         object weapon;
         j = me->query_skill("jinshe-jianfa", 1)/8;
         z = me->query_skill("jinshe-zhang", 1)/8;
         bt = me->query_skill("wudu-yanluobu", 1)/100;
         n = me->query_skill("jinshe-jianfa",1)/120;
         dexs = me->query("str",1)*n;
         armor = me->query("dex",1)*n;
         skills = me->query_skill("sword",1)/5 + me->query_skill("jinshe-jianfa",1)/5;  
         
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
 
         if( !target || !me->is_fighting(target) )
                 return notify_fail("�����߿��衹ֻ����ս���жԶ���ʹ�á�\n");
 
        if((int)me->query_temp("hmg_nizhuan") )
        return notify_fail("�������˾���������ʲô��,�����߻���ħ��!\n");
         if (!weapon || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("�������ʹ�ý�ʱ����ʹ�������߿��衹��\n");
 
         if(me->query_skill("jinshe-jianfa", 1) < 120 )
                 return notify_fail("��Ľ��߽�����������죬ʹ���������߿��衹������\n");

         if( (int)me->query_skill("force") < 170 )
                 return notify_fail("����ڹ��ȼ�������ʹ���������߿��衹������\n");
 
         if( (int)me->query_str() < 27)
                 return notify_fail("�������������ǿ����ʹ���������߿��衹������\n");
 
         if( (int)me->query_dex() < 27)
                 return notify_fail("�����������Ѹ�ͣ�ʹ���������߿��衹������\n");
//���Ӷ��������Ե�Ҫ��
         if( (int)me->query("dex") < 20 || (int)me->query("str") > 20 || (int)me->query("int") < 20)
                 return notify_fail(HIG"��ɵͷɵ��,���ֱ��ŵ�,�����ʲô��.\n"NOR);
//��ǿ���߿����÷�,���Ե�������                 
//         if((int)me->query_temp("jinshe_kuangwu")) 
//                 return notify_fail("����������ʹ�á����߿��衹������\n"); 
               
         if( (int)me->query("max_neili") < 800 )
                 return notify_fail("����������̫����ʹ���������߿��衹��\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("�������������㣬ʹ���������߿��衹��\n");
 
         msg = HIC"\nͻȻ$N����$n���ٱ��ߣ���Ȼ��������һ�ƣ�����ָ��$n��\n\n"NOR;
//��⣬��ֹ�ظ���������         
         if (!me->query_temp("jinshe_kuangwu",1))
                  {
                                                                if( me->query_skill("wudu-yanluobu", 1) > 120 && me->query_skill_mapped("dodge") == "wudu-yanluobu")
                                                                                     {
                                                                                                      a = (int)me->query_skill("wudu-yanluobu",1)/3;
                                                                                                      me->add_temp("apply/dexerity",a);
                                                                                                      me->add_temp("apply/attack",a);
                                                                                                      me->add_temp("dodge/power",1);
                                 if( wizardp(me) || me->query("env/debug"))
                                                                                                              tell_object(me, "���Ṧ��"HIW"�嶾���ܲ�"NOR"�����ӣ���"HIW"���� "NOR"��"+a+"����"HIW"��"NOR"�� "+a+"��\n"NOR);
       
                            }
                                                                if( me->query_skill("jinshe-zhangfa", 1) > 120 
                                                                            && me->query_skill_mapped("strike") == "jinshe-zhangfa"
                                                                            && me->query_skill_prepared("strike") == "jinshe-zhangfa")
                            {
                                 b = (int)me->query_skill("jinshe-zhangfa",1);
                                                                                                      me->add_temp("apply/strength", b/7);
                                                                                                      me->add_temp("apply/damage", b/4);
                                                                                                      me->add_temp("strike/power",1);
                                                                                                      
                                                                                              if( wizardp(me) || me->query("env/debug"))
                                                                                                              tell_object(me, "���Ʒ���"HIW"�����Ʒ�"NOR"�����ӣ���"HIW"���� "NOR"��"+b/7+"����"HIW"�˺�"NOR"�� "+b/4+"��\n"NOR);
                
                                                                                     }       
                                                                
                                                                if( me->query_skill("jinshe-jianfa",  1) > 120 && me->query_skill_mapped("sword") == "jinshe-jianfa")
                                                                                {   
                                                                                       c = (int)me->query_skill("jinshe-jianfa",1);
                                                                                             me->add_temp("apply/sword", c/5);
                                                                                             me->add_temp("apply/parry", c/4);
                                                                                             me->add_temp("sword/power",1);
                                                                                             if( wizardp(me) || me->query("env/debug"))
                                                                                                     tell_object(me, "�㽣����"HIW"���߽���"NOR"�����ӣ���"HIW"���� "NOR"��"+c/5+"����"HIW"�м�"NOR"�� "+c/5+"��\n"NOR);
           
                                                                                     }        
           }
//����������ϣ��жϽ��߽�������

         if(weapon->query("id") == "jinshe sword" || !userp(me)){
    
                    me->set_temp("jsj", 1);
                                        msg = HIR"\n$N���н��߽������������Ƴ�������⣬������$N����Ϊ�������������ֱָ$n��\n\n"NOR;
                                                        
                                                        }
//�ж������Ʒ�������׼��������        
         if(  me->query_skill("wudu-yanluobu", 1) > 120 
                                           && me->query_skill_mapped("dodge") == "wudu-yanluobu"
                                         && me->query_skill("jinshe-zhangfa",1) > 120
                                     && me->query_skill_mapped("strike") == "jinshe-zhangfa"
                                     && me->query_skill_prepared("strike") == "jinshe-zhangfa")
              {  
                    msg = HIY"\n$Nһ������"+weapon->name()+HIR",���ų�������,$n��ʱ�����ۻ�����,��$N���˸����ֲ�����\n\n"NOR; 
//��������NPC����busyЧ��Ϊ���ܵȼ�/100,�������busyЧ��,���н��߽�ʱǿ�����busy+1           
                                        bt = me->query_skill("wudu-yanluobu",1)/100;
                                        target->start_busy( bt + random(2));
                                        if(userp(target)) target->start_busy(0);
                                        if(userp(target) && me->query_temp("jsj")) target->start_busy(1);
           
                                        if( wizardp(me) || me->query("env/debug"))
                                                        tell_object(me, "��ġ�"HIW"��"HIR"��"HIW"��"HIY"���߿���"NOR"�����ӣ���"HIW"���� "NOR"��"+me->query_skill("jinshe-zhangfa", 1)/7+"����"HIW"����"NOR"�� "+me->query_skill("jinshe-jianfa", 1)+"��\n"NOR);
       
              me->start_perform(4,"�����߿��衹");
              me->add("neili", -300);
              me->add("jingli", -200);
              me->add_temp("apply/attack",  me->query_skill("jinshe-jianfa", 1));
              me->add_temp("apply/strength",  me->query_skill("jinshe-zhangfa", 1)/7);
              
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
                          message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
   
        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
                          message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       

        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
                          message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
        if (me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
                          message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
                          message_vision(HIY"                                                                     ��������������\n"NOR,me);       
            me->add_temp("apply/attack", - me->query_skill("jinshe-jianfa", 1));
            me->add_temp("apply/strength", - me->query_skill("jinshe-zhangfa", 1)/7);

            me->start_busy(1);
            me->add_temp("apply/sword", -c/5);
                        me->add_temp("apply/parry", -c/4);
                        me->add_temp("apply/strength", -b/7);
                        me->add_temp("apply/damage", -b/4);
                        me->add_temp("apply/dexerity",-a);
                        me->add_temp("apply/attack",-a);
            return 1;
           }  
           
//dodge strike sword ����,����busyЧ��,��npc busyЧ����ǿ,��jinshe swordЧ����ǿ
              
       if( me->query_skill("wudu-yanluobu", 1) < 120 || me->query_skill_mapped("dodge") != "wudu-yanluobu")
             {
               if ( me->query_skill("jinshe-zhangfa", 1) < 120 || me->query_skill_mapped("strike") != "jinshe-zhangfa"
                      || me->query_skill_prepared("strike") != "jinshe-zhangfa" )
                        {
                                  if ( weapon->query("id") != "jinshe sword" && userp(me))
//�����ж�powerupЧ�������Ƿ��������                                                                                   
                                                                                         { 
                                        
                                                                                                                     me->add("neili", -300);
                                                                                                             me->add("jingli", -150);
//��������powerup                                                                                                            
                                                                                                             if (!me->query_temp("jinshe_kuangwu",1)){  
                                                                                                                                                     
                                                                                                                                             
                                                                                                         me->add_temp("apply/dexerity", armor*2);
                                                                                                     me->add_temp("apply/strength",dexs/2);
                                                                                                     me->set_temp("jinshe_kuangwu", 1); 
//�Ƴ�Ч���������ö���Ƴ�����                                                                                                   
                                                                                                     call_out("check_fight", 1, me, dexs, armor, skills);
                                                                                                     }
           
                                                                                                             if( wizardp(me) || me->query("env/debug"))
                                                                                                                     tell_object(me, "��ġ�"HIW"��"HIR"һ"HIW"��"HIY"���߿���"NOR"�����ӣ���"HIW"���� "NOR"��"+dexs/2+"����"HIW"��"NOR"�� "+armor*2+"��\n"NOR);
//����Ϊ������о��������Ϊ������pfm����ͷţ�����powerupЧ��ֻ��һ��
                                                                        me->add_temp("apply/strength", z);
                                                                                                             me->add_temp("apply/attack", j); 
                                                                        message_vision(HIC"\n$Nһ������"+weapon->name()+HIC"ʹ�����߽�������֮�أ���"HIW"һ"HIC"�ؽ��߿���֮"HIY"������о"HIC"����Ȼ�ӿ죬�û�������������$n�糸��ȥ��\n"NOR,me,target);
                                                                                     me->add_temp("apply/damage", 100);
                                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                                                                                                             me->add_temp("apply/damage", -100);
                                                                                                             me->add_temp("apply/strength", -z);
                                                                                                             me->add_temp("apply/attack", -j);
                                                                                                              
                                                                                                             me->add_temp("apply/sword", -c/5);
                                                me->add_temp("apply/parry", -c/4);
                                                
                                                me->start_perform(3,"��������о��");
           
                                    return 1;
                                                                                 }
                  
                        
                                                                                }
           
               } 
//�ж�ɸѡ3�غ�1�غ�ȫ��Ϊ2��2��1��3Hit���������н��߽�����Ϊ3��2��5Hit������         
                  
         message_vision(msg, me, target);
         
         me->add_temp("apply/strength", z);
         me->add_temp("apply/attack", j); 
         
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);
         me->add("jingli", -10); 
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       
 
         weapon->unequip(); 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);  
         me->add("jingli", -10);
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);
 
         weapon->wield();
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
         me->add("neili", -100);  
         me->add("jingli", -10);
         if(me->query_temp("jsj"))
            message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);
 
         if(me->query_temp("jsj"))
         {          
            weapon->unequip(); 
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
            me->add("neili", -50);  
            me->add("jingli", -5);
            message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);        
            weapon->wield();               
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
            me->delete_temp("jsj");
            me->add("neili", -50);
            me->add("jingli", -5);
            me->add_temp("apply/damage", -50);
         }
 
        
         
         me->add_temp("apply/sword", -c/5);
         me->add_temp("apply/parry", -c/4);
         me->add_temp("apply/strength", -b/7);
         me->add_temp("apply/damage", -b/4);
         me->add_temp("apply/strength", -z);
         me->add_temp("apply/attack", -j); 
         if ( me->query_temp("dodge/power",1))
         {
                    me->add_temp("apply/dexerity",-a);
                                me->add_temp("apply/attack",-a);
                                
                }
         me->start_busy(1+random(2));
         target->start_busy(1);
         return 1;
 }

void remove_effect(object me, int dexs, int armor, object weapon)
{      
       me->add_temp("apply/dexerity", -armor*2);
       me->add_temp("apply/strength",-dexs/2);
       
       me->delete_temp("jinshe_kuangwu");
       tell_object(me, HIW"��ġ�������о��ʩչ��ϣ�����������������\n" NOR); 
}

void check_fight(object me, int dexs, int armor, int skills)
{
       object weapon;
       if (!me) return;
      
       if( skills < 1 || !me->is_fighting()) {
           remove_effect(me, dexs, armor, weapon);
           return;
       }
       call_out("check_fight", 1, me, dexs, armor, skills-1);
}
int help(object me)
{
        write(HIY"\n�����ؼ�֮�����߿��衹��"NOR"\n\n");
        write(@HELP
        �����ɾ���ѩ�������������ĵľ����书. ��ϧ�������н����ؼ���
        �ָ�ɺü�����, ���߿��������Ҳ����ǰ. �ഫ�ڴ�������ؼ�
        �еĽ���, ��, �Ʒ�����ܷ��ӽ��߿�������������. ������ҿ�
        �Ի�ý��߽�, ��ʹ���������ϲ�¥.

        Ҫ��  ��ǰ���� 1500 ���ϣ���������� 2800 ���ϣ�
                ������,���Բ���С��20,����������ܴ���20,
                ��������������27
                ��һ�׶Σ����߽����ȼ� 120 ���ϣ������ڹ��ȼ� 170 ���ϣ�
                ������������������Ϊ���߽�����
                �ڶ��׶Σ������Ʒ��ȼ� 120 ���ϣ�����׼���Ʒ�Ϊ�����Ʒ���
                �����׶Σ��嶾���޲��ȼ� 120 ���ϣ������ṦΪ�嶾���޲���
                
                ���⣬���װ���˽��߽��������ɸ���һ��¥��

HELP
        );
        return 1;
}

