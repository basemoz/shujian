// lianhuan.c  ����������
// Create by lsxk@hsbbs 2007/5/15

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return CYN"����������"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
         lev = ((int)me->query_skill("tiezhang-zhangfa", 1) + (int)me->query_skill("strike", 1))/2;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�����������ơ�����ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
/*            if( me->query_temp("tzzf") ){
                if ( (int)me->query_skill("tiezhang-zhangfa",1) < 400 ) 
                    return notify_fail("�������ֲ���ʹ�á����������ơ���\n");
                 }
            else   */
                return notify_fail("������������ô��ʹ�á����������ơ�����?\n");   
//        }

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 250 )
                return notify_fail("��������Ʒ���������죬ʹ���������������ơ�������\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á����������ơ��������й�����\n");  

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 250 )
                return notify_fail("��Ĺ�Ԫ���ŷ��ȼ���������ʹ���������������ơ�������\n");

        if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("��Ļ����ڹ��ȼ���������ʹ���������������ơ�������\n");

        if( me->query("max_neili") < 3500 )
                return notify_fail("������������Ϊ̫�ʹ���������������ơ���\n"); 

        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫����ʹ���������������ơ���\n"); 

        if( (int)me->query("max_jingli") < 2500 )
                return notify_fail("�����ھ�����Ϊ̫�ʹ���������������ơ���\n"); 

        if( (int)me->query("jingli") < 600 )
                return notify_fail("�����ھ���̫�ʹ���������������ơ���\n"); 

        message_vision(CYN"\n$NͻȻ���һ����˫������������������$n�����������Ʒ�֮���衸���������ơ�������\n"NOR,me,target);
        me->add_temp("apply/strike", lev/6);
        me->add_temp("apply/attack", lev/8);
        me->add_temp("apply/strength",(int)me->query("str"));
        me->add_temp("apply/dodge", -lev/6);
        me->set_temp("tiezhang", 1);
//        me->set_temp("action_flag", member_array("strike", keys(me->query_skill_prepare())));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("apply/strike", -lev/6);
        me->add_temp("apply/attack", -lev/8);
        me->add_temp("apply/strength",-(int)me->query("str"));
        me->add_temp("apply/dodge", lev/6);
        me->start_busy(1+random(2));
        me->start_perform(5,"�����������ơ�");
        me->add("neili", -500);
        me->delete_temp("tiezhang");
        return 1;
}
