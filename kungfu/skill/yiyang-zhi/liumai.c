// Created by lsxk@hsbbs 2007/6/13

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIW"������"NOR;}

int perform(object me, object target)
{
        int lev;


        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
                return notify_fail("�������񽣡�ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á������񽣡���\n");   

        if( (int)me->query_skill("liumai-shenjian", 1) < 30 )
                return notify_fail("�㻹��δ��ͨ�������񽣡�֮һ�������ʹ�ó��þ���?\n");

        if((int)me->query_skill("force") < 250 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ�����������񽣡�������\n");

        if( (int)me->query("jiali")< 50 )
                return notify_fail("��ʹ�ù��ٵ������˵У��޷����������񽣡����������ֳ�����\n");

        if( me->query_temp("pf_rong"))
                return notify_fail("���������á��١��ִ󷨣�\n"); 

        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ�����������񽣡���\n");  

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á������񽣡���\n"); 

        if (me->query_skill_mapped("force") != "kurong-changong" )
        if (me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
                
        if( (int)me->query("max_neili") < 4500 )
                return notify_fail("����������̫����ʹ�����������񽣡���\n"); 

        if( (int)me->query("neili") < 2000) 
                return notify_fail("����������̫����ʹ�����������񽣡���\n");

        if( (int)me->query("jingli") < 1000)
                return notify_fail("�����ھ���̫�٣�ʹ�����������񽣡���\n");

        if( me->query_temp("yyz/6mai/6mai"))
                return notify_fail("������ʹ�á������񽣡��ء�\n");

	lev = (int)me->query_skill("yiyang-zhi", 1);

        message_vision(HIW"\n$N����һ��"HIY"��������"HIW"��������ת��ָ�⣬˲�����ܿ�������ӿ��������������ʢ��\n"NOR,me,target);

        me->add("neili",-500);
        me->add("jingli",-300);
        me->add_temp("apply/attack",lev/4);
        me->add_temp("apply/dodge",lev/4);

        me->set_temp("yyz/6mai/6mai",1);
        me->start_perform(3,"�������񽣡�");
      call_out("check",1,me,target,lev);
        return 1;
}

int check(object me,object target, int lev)
{
    if (!me) return 1;
    if( !me->is_fighting()
      || !living(me)
      || me->is_ghost()
      || (int)me->query("jiali")<50
      || me->query("weapon")){
        message_vision(HIG"\n$N��������������ϣ����鵤�������ȣ�\n"NOR,me,target);
        me->add_temp("apply/attack",-lev/4);
        me->add_temp("apply/dodge",-lev/4);
        me->delete_temp("yyz/6mai/6mai");
        return 1;
    }
      call_out("check",1,me,target,lev);
      return 1;
}

int help(object me)
{
   write(WHT"\nһ��ָ֮��"HIW"������"WHT"����"NOR"\n\n");
   write(@HELP

     Ҫ��: ������� 4500 ���ϣ�
           ��ǰ���� 2000 ���ϣ�
           ��ǰ���� 1000 ���ϣ�
           �����񽣵ȼ� 30 ���ϣ�
           �����ڹ��ȼ� 250 ���ϣ�
           �����ڹ��ȼ� 250 ���ϣ�
           ���� 50 ���ϣ�
           ����ָ��Ϊһ��ָ����һ��ָ��

HELP
   );
   return 1;
}
