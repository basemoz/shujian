// Modified by Darken@SJ
// Modify by server@sjty 2007.7.27 ����ʧ��������

#include <ansi.h>
inherit F_SSERVER;

void remove_effect(object me, object target, int count, int skill);

string exert_name() { return HIG"�����Ի���"NOR; }

int exert(object me, object target)
{
        int skill;

        if( !target ) target = offensive_target(me);
        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (me->query_temp("thd/mazed")) 
                return notify_fail("������������˲��������С�\n");
        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
        if( (int)me->query("neili") < 300  ) 
                return notify_fail("�������������\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
        if( (int)me->query_temp("thd/maze") ) 
                return notify_fail("���Ѿ�����һ�������ˡ�\n");

        skill = me->query_skill("qimen-bagua", 1);
        me->add("neili", -200+random(300));
        me->add("jingli",-100);
        me->start_exert(5,"�����Ի���");
        message_vision(HIY"$NͻȻԾ������һ�ƣ�����һ�ȣ�����Χ��ʯ�顢��֦�ƶ���λ�ã�\n"NOR, me, target);
        if(random(me->query_dex()) > target->query_dex()/2){
        message_vision(HBYEL"$n���������У���ʱ�����޴롣\n" NOR, me, target);
                target->add_temp("apply/dexerity", -(skill/10));
                target->add_temp("apply/damage", -(skill/10));
                target->add_temp("apply/dodge", -(skill/10));
                target->set_temp("thd/mazed", 1);
                target->start_busy(3);
                me->add_temp("apply/defense", skill/5);
                me->set_temp("thd/maze", skill/5);
                me->set_temp("thd/maze_target", target);
                call_out("remove_effect", 1, me, target, skill / 2, skill);
        }
        else {
		message_vision(HBGRN"$nѸ����ǰ�ˣ�������������������֮�⡣\n" NOR, me, target);
                me->delete_temp("thd/maze");
                me->delete_temp("thd/maze_target");
                me->start_exert(3,"�����Ի���");                        
        }
         return 1;
        }
void remove_effect(object me, object target, int count, int skill)
{
        if (objectp(me) && me->query_temp("thd/maze")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count, skill);
                        return;
                }
                me->add_temp("apply/defense", - (skill/5));
                me->delete_temp("thd/maze");
                if (!target) return;
                me->delete_temp("thd/maze");
                me->delete_temp("thd/maze_target");
                if (target && me->is_fighting(target)) {
                        tell_object(me, "�㲼�������Ѿ���" + target->name() + "�ƻ��ˡ�\n");
                        if (userp(target) && living(target))
                                tell_object(target, me->name() + "���㲼�������Ѿ�����ʶ���ˡ�\n");
                }
                else {
                        tell_object(me, "�㲼�������Ѿ�ʧЧ�ˡ�\n");
                }
        }
        if (objectp(target) && target->query_temp("thd/mazed")){
                target->delete_temp("thd/mazed");
                target->add_temp("apply/dexerity", skill/10);
                target->add_temp("apply/dodge", skill/10);
                target->add_temp("apply/damage", skill/10);
        }
}

int help(object me)
{
        write(HIG"\n�������Ի��󡹣�"NOR"\n");
        write(@HELP

        ʹ�����Ű���֮�����������Ա̺�����֮�ھ�Ѹ��������֦����ʯ������
        ����һ���ر�Ϊ�̱������׼����������������Ķ��ֲ�������æ�ң�ͬ
        ʱս������Ҳ�ή�ͣ�����ķ�����Ե���ߡ�

        Ҫ��  �̺������ȼ� 50 ���ϣ�
                ���Ű��Եȼ� 50 ���ϣ�
                ������� 300 ���ϣ�
                ��������������ֵ��������޷�ʹ�á�
HELP
        );
        return 1;
}

