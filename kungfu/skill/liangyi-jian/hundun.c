//by daidai 2005-12-26
//����д���򻯴���
//by spiderii@ty ����
//by spiderii@ty �ٴθ��¡��޸��ж���������
#include <ansi.h>
inherit F_SSERVER;
void finish();
int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��"HIG"���罣��"NOR"��\n");
        weapon = me->query_temp("weapon");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
              || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("������û�н����޷�ʹ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 200 )
                return notify_fail("��������ǽ���������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("sword", 1) < 200 )
                return notify_fail("��Ļ�������������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 200 )
                return notify_fail("��������޼���������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if ( (int)me->query("max_neili") < 2500)
                return notify_fail("��������������޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if ( (int)me->query("neili") < 1000)
                return notify_fail("��������������޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if ((int)me->query("jingli") < 300)
                return notify_fail("��ľ����������޷�ʩչ��"HIG"���罣��"NOR"��\n");

        message_vision(HIG"\n$N"HIG"����̫������ʽ���಻������$n��ȫ��û��һ�Ż��罣��֮�С�\n"NOR, me,target);
        me->set_temp("lianhuan", 5);
        me->add("neili", -100-random(100));
        me->add("jingli", -100);
        message_vision(HIG"$N���е�"+weapon->query("name")+HIG"��������ˮһ�㣬��$n��ȥ,���Ʋ��أ�ȴҲ�̲�����ɱ����\n"NOR,me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2) {
                   message_vision(HIW"\n$nֻ�����Լ�����$N�������ƣ���������������ת���磡\n"NOR, me,target);
                   target->apply_condition("no_exert", 1);
                   me->start_perform(999,"��"HIG"���罣��"NOR"��");
                   call_out("check_fight", 1+random(3), me, 1+i/30);
} 
    else {
        message_vision(HIY"$n���һԾ��������$N�������ֵķ�Χ��\n"NOR, me,target);
        me->start_busy(1);
        me->start_perform(3,"��"HIG"���罣��"NOR"��");
        me->add("neili",-300);
}
    return 1;
}

void remove_effect(object me)
{
         int i=me->query_skill("liangyi-jian",1);
         object target = offensive_target(me);
         if(!me) return;
         me->delete_temp("lianhuan");
         if(!living(me)) return;
         if (me->is_fighting()) {
             message_vision(HIW"\n\n$N"HIW"����������֯���������ķ�����ӿ�룬���ذ�$nǰ�����ҽ��С�\n$nֻ��������ѹ��������$N�ġ�"HIG"���罣��"HIW"���ѽ�$n����Χס��\n"NOR, me,target);
             me->set_temp("lianhuan", 5);
             me->set_temp("lianhuan2", 1);
        if(me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        call_out("check_fight", 1, me, 1+i/30);
           }

         else {
       
           me->delete_temp("lianhuan"); 
           me->delete_temp("lianhuan2");
           me->start_perform(4,"��"HIG"���罣��"NOR"��");
           message_vision(HIY"\n$N"HIY"�ġ�"HIG"���罣��"HIY"������ʹ�꣬$N��ɷ�����Ϣ���ȣ��������������Ƿ���\n"NOR, me);
      }
}
void finish()
{
       object me = this_player();
       me->delete_temp("kj");
       me->delete_temp("lianhuan"); 
       me->delete_temp("lianhuan2");
       me->start_perform(4,"��"HIG"���罣��"NOR"��");
       if(!me->is_busy())
       me->start_busy(1+random(2));
       message_vision(HIW"$N��������һ�����������ָ�����Ȼ��\n"NOR, me);
}

void check_fight(object me, int i)
{
    object weapon, target;
    int jl;

    if (!me ) return;
    
    target = offensive_target(me);
     
    if( !living(me) 
        || !target 
        || !me->is_fighting(target) 
        || !living(target)
        || environment(target)!=environment(me)
        || !me->query_temp("lianhuan"))
              call_out("finish",1);

    else if(me->query_skill_mapped("sword") != "liangyi-jian"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á�"HIG"���罣��"NOR"��������\n");
                call_out("finish",1);
                }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á�"HIG"���罣��"NOR"��������\n");
                call_out("finish",1);
                }
    else if ((int)me->query("neili") < 200 ){
                tell_object(me, HIR"���������ã�ֻ�û����ջء�"HIG"���罣��"NOR"����\n");
                call_out("finish",1);
                }
    else if ((int)me->query("jingli") < 100 ){
                tell_object(me, HIR"��������֧��ֻ�û����ջء�"HIG"���罣��"NOR"����\n");
                call_out("finish",1);
                }
    else if(me->is_busy()) 
                call_out("check_fight", 1, me, i);
    
    else{
           me->add("neili", -80);
           jl= me->query_skill("sword")/2;
           me->add("jingli", -30);
           message_vision(HIG"\n$N�Ľ�����֯��������������$n������ţ���ж��ٻ����ٲ����ѡ�\n"NOR, me,target);
           if (random(me->query_skill("force")) > target->query_skill("force") /2 
               && me->query_skill("liangyi-jian",1)> 240 ){ 
               message_vision(HIC"$nֻ�����Լ�����$N�������ƣ���������������ת���磡\n"NOR, me,target);
               target->apply_condition("no_exert", 1);
        }  
           if(me->is_fighting(target) )
                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                   target->start_busy(1+random(2));
                   target->add("jingli", -(jl+random(200)));
                   target->add("neili", -(jl+random(200))); 
                   me->add_temp("lianhuan",-1);                       
                   i--;
          if (me->query_temp("lianhuan")==1 && me->query_skill("liangyi-jian", 1) >250 && !me->query_temp("lianhuan2")) remove_effect(me);  
     else  
         call_out("check_fight",2+random(2), me, i);
           }
}



string perform_name(){ return HIW"���罣��"NOR; }
int help(object me)
{
write(HIW"\n���ǽ���֮�����罣������"NOR"\n\n");
write(@HELP
Ҫ��      ������� 2500 �����ϣ�
          ��ǰ���� 1000 �����ϣ�
          ��ǰ���� 400 �����ϣ�
          ���ǽ����ȼ� 200 ���ϣ�
          �����޼����ȼ� 200 ���ϣ�
          ��������Ϊ���ǽ�����
          �����м�Ϊ���ǽ�����
          �����ڹ�Ϊ�����޼�����
          ���ñ�����
HELP
);
return 1;
}

