// �����޼�-̤ѩ�޺�
// ��̤��ѩ���޺�
// modify by cmkj 2003.8.19
// update���ӷ�Ծ��Ч��
#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;

        if ((int)me->query_skill("taxue-wuhen", 1) < 100)
                return notify_fail("���̤ѩ�޺���Ϊ��������\n");
        if((int)me->query("max_neili")<1000)
                return notify_fail("���������Ϊ̫��������ɡ�\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");
        if (me->query_temp("kl/taxue"))
                return notify_fail("���Ѿ���ʹ��̤ѩ�޺��ˡ�\n");
        

        skill = me->query_skill("taxue-wuhen",1) / 3;

        message_vision(CYN "$N˫���鰴���չ���Ṧ��������ƮƮ�ģ�������շ��У�\n" NOR, me);
        
        me->add_temp("apply/dodge", skill);
        me->set_temp("kl/taxue", skill);
        me->add("neili", -150);
          me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/2 );
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
void remove_effect(object me)
{
        int amount;
        
        if ( me && (int)me->query_temp("kl/taxue") ) {
                amount = me->query_temp("kl/taxue");
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("kl/taxue");
               message_vision(CYN "$Nɢȥ����ۼ��������������˽Ų������ظ���������\n" NOR, me);
        }
}
