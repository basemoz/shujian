 // chuanyun.c 
// By Daidai 2002/03/16
//by spiderii@ty ����
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"����"NOR;}

#define TICKTIME 5

 void exam1(object me , object tartget );

 int perform(object me, object target)
 {
              int j, z, y;
              j = me->query_skill("chuanyun-tui",1)/2;
              z = me->query_skill("zhentian-quan",1)/2;
              y = me->query_skill("xuantian-wuji",1)/2;

         if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("�����ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
         if (me->query_skill_prepared("leg") != "chuanyun-tui"
             || me->query_skill_mapped("leg") != "chuanyun-tui")
                return notify_fail("�������޷�ʹ�á����ơ���\n");  

         if((int)me->query_skill("chuanyun-tui", 1) < 120 )
                 return notify_fail("��Ĵ����ȹ���죬����ʹ�á����ơ���\n");

         if((int)me->query_skill("xuantian-wuji", 1) < 120 )
                 return notify_fail("��������޼�����������޷�ʹ�á����ơ���\n");

         if((int)me->query("max_neili") < 1500)
                 return notify_fail("����������̫��������ʹ�á����ơ���\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("�����ű����޷�ʹ������׷���ȡ�\n");

         if(me->query_skill_mapped("force") != "xuantian-wuji")
                 return notify_fail("��������ʹ�õ��ڹ�ͬ�����޼�����ִ�������ʹ�á����ơ���\n");

	  if( target->is_busy() )
		   return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ�������!\n");

	  message_vision( HIG "\n$N���ؽ���һ������������Ѿ��˴��������غ������\n"NOR, me, target);
                 
	 if( random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 )
	     {
		message_vision(   HIR "$n���޿ɱܣ������˱��Ⱦ����ɵġ����ơ���ǽ���ֵ��ܲ�͸�磬һʱ����������! \n" NOR, me, target);
		target->start_busy( random(2) + 2);
		me->add("neili", -200);
              me->add("jingli", -50);
        if( (int)me->query_skill("chuanyun-tui", 1) > 140 && me->is_fighting(target) )
              call_out("perform2", random(3)+3, me, target); 
	      }

        else
             {
             message_vision(HIR "$nȴ�������缱�ٷ�ת�����ױܹ�$N��ӿ��һ�С�\n"HIY"$Nһ��ʧ�֣��������ţ�����ȭ�����������Ƶ���$n�����߳����ţ�\n"NOR,me, target);
             me->add_temp("apply/strength", j);
             me->add_temp("apply/dexerity", y);
             me->add_temp("apply/dodge", y*2);
             me->add_temp("apply/cuff", z*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/cuff", -z*2);
             me->add_temp("apply/leg", j*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/leg", -j*2);
             me->prepare_skill("leg");
             me->prepare_skill("cuff","zhentian-quan");
             me->add_temp("apply/cuff", z*2);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
             me->add_temp("apply/cuff", -z*2);
             me->add_temp("apply/strength", -j);
             me->add_temp("apply/dexerity", -y);  
             me->add_temp("apply/dodge", -y*2);
             me->prepare_skill("leg","chuanyun-tui");  
             me->prepare_skill("cuff","zhnetian-quan");
             me->start_busy(3);
             me->add("neili", -400);
             me->add("jingli", -200);
       }
             me->start_perform(5,"�����ơ�");
	      return 1;
     }
int perform2(object me, object target)
   {  
              int j,y,z;
              j = me->query_skill("chuanyun-tui",1)/2;
              z = me->query_skill("zhentian-quan",1)/2;
              y = me->query_skill("xuantian-wuji",1)/2;
 
              if (!me->is_fighting(target))   
                  return notify_fail("�����Ѿ�������ս���ˡ�\n");   
              if( !target || !target->is_character() || !me->is_fighting(target) )
                  tell_object(me, HIC"\n�Է��Ѿ����򵹣��㽫���������ֻص��\n"NOR);   
              if( !target ) target = offensive_target(me);

              if( !target || !target->is_character() || !me->is_fighting(target) )
                  return notify_fail("�����ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
              if( (int)me->query("neili") < 500 )
                  return notify_fail("���������Ϊ�������ߡ�\n");
              if( (int)me->query("jingli") < 200 )
                   return notify_fail("��ľ�����Ϊ�������ߡ�\n");
          message_vision(HIY "\n����һ�ᣬ�����ơ���ǽ����Ϣ֮������΢����$n������Ի���������\n"HIG"$N��׼�˿�����$n�����¾���������֮�ʣ�����������ϣ���������$pɨ�����ţ�\n"NOR,me, target);
          me->add_temp("apply/strength", j);
          me->add_temp("apply/dexerity", y);
          me->add_temp("apply/leg", j*2);
          me->add_temp("apply/dodge", y*2);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          me->add_temp("apply/strength", -j);
          me->add_temp("apply/dexerity", -y);
          me->add_temp("apply/leg", -j*2);
          me->add_temp("apply/dodge", -y*2);
          me->start_perform(5,"�����ơ�");
          me->add("neili", -400);
          me->add("jingli", -150);  
    }
int help(object me)
{
   write(WHT"\n�����ȡ�"HIY"����"WHT"����"NOR"\n");
   write(@HELP
    Ҫ�� ������� 1500 ���ϣ�
           ��ǰ���� 700 ���ϣ�
           �����ȵȼ� 120 ���ϣ�
           �����޼����ȼ� 120 ���ϡ�
HELP
   );
   return 1;
}
