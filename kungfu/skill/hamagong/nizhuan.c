
// nizhuan.c ��ת����
// by snowman@SJ
// Modify by server 2007.07 ������ת�������Quest ����
// Modify by server 2007.08 ������ת����Quest �ȼ�����
//by spiderii@ty hama�����ͺ��ѿ���88�ĺ�����Ҫ���ʵ������hama2������
//by yueying@TY ���Ӹ�wiz����Ϣ 6/7/2008
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

string exert_name()
{
        return HIW"��ת����"NOR;
}

int exert(object me, object target)
{
        int skill,sk;

        if( !target )
                target = me;

        if(!(int)me->query_skill("hamagong", 1) )
                return 0;
        if( me->query("oyf/hamagong") < 2 )
                return notify_fail("���˸�󡹦ʹ������ת����������\n");
        if((int)me->query("neili") < 300  )
                return notify_fail("�������������\n");
        if((int)me->query("jingli") < 200  )
                return notify_fail("��ľ���������\n");
        if((int)me->query_temp("hmg_nizhuan") )
                return notify_fail("���Ѿ������˾�����\n");

        if (me->query("oyf/hamagong") < 3 )          
           skill = me->query_skill("force",1) / 4 + me->query_skill("hamagong", 1) /2;
           sk = me->query_skill("force",1)/2 + me->query_skill("hamagong", 1);
           sk /= 2;
        if (me->query("oyf/hamagong") == 3 )  
           skill = me->query_skill("force",1)/2 + me->query_skill("hamagong", 1);
           skill /= 2;
        me->add("neili", -200);
        me->add("jingli", -20);
        
        if (me->query("oyf/hamagong") == 3 ){
        message_vision(HIW "\n$N˫�ֳŵأ����з���һ���ܵͺ�����һ�ɹ��ھ�����ʹ$N˫����أ���ͷ������֮�ơ�\n" NOR, me);
        tell_object(me, HIW "��о����ڸ�󡹦�������ת�������йɾ޴������Ҫ��������һ����\n" NOR);
        if( wizardp(me) || me->query("env/debug"))
                    tell_object(me, "��ġ�"HIW"��ת����"NOR"�����ӣ���"HIW"��Ч�� "NOR"��"+skill/3+"����"HIW"������"NOR"�� "+skill/4+"����"HIW"���� "NOR"��"+skill+"����"HIW"���� "NOR"��"+skill/3+" ����"HIW"����ʱ��"NOR"�� "+skill+"��\n"NOR);
        me->start_call_out( (: call_other, this_object(), "remove_effect", me :), skill);
        }
        if (me->query("oyf/hamagong") == 2 ){
        message_vision(HIW "\n$N���¶������ӣ������󡹦����ֻ��$Nʹ�û��Ž��أ����Ǻÿ���\n" NOR, me);
        tell_object(me, HIW "��о����ڸ�󡹦�������������������й��ھ���ֹ���˹���\n" NOR);
        if( wizardp(me) || me->query("env/debug"))
                    tell_object(me, "��ġ�"HIW"��ת����"NOR"�����ӣ���"HIW"��Ч�� "NOR"��"+skill/3+"����"HIW"������"NOR"�� "+skill/4+"����"HIW"���� "NOR"��"+skill+"����"HIW"���� "NOR"��"+skill/3+" ����"HIW"����ʱ��"NOR"�� "+skill+"��\n"NOR);
        if( wizardp(me) || me->query("env/debug"))
                    tell_object(me, "��"HIY"��ȫ��ת����"NOR"�����ӣ���"HIW"��Ч�� "NOR"��"+sk/3+"����"HIW"������"NOR"�� "+sk/4+"����"HIW"���� "NOR"��"+sk+"����"HIW"���� "NOR"��"+sk/3+" ����"HIW"����ʱ��"NOR"�� "+sk+"��\n"NOR);
        me->start_call_out( (: call_other, this_object(), "remove_effect", me :), skill);

        }
              if (me->query_skill("hamagong", 1) > 450)
        {
                me->add_temp("apply/parry", skill/4);
                me->add_temp("apply/dodge", skill/4);
                 if( wizardp(me) || me->query("env/debug"))
                             tell_object(me, "��ġ�"HIW"��ת��������450lvl"NOR"�����ӣ���"HIW"�м� "NOR"��"+skill/4+"����"HIW"�Ṧ"NOR"�� "+skill/4+"��\n"NOR);
        }
        me->add_temp("apply/constitution", skill/3);
        me->add_temp("apply/dexerity", skill/3);
        me->add_temp("apply/strength", skill);
        me->add_temp("apply/attack", skill/4);
        me->set_temp("hmg_nizhuan", skill);
        
        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

void remove_effect(object me)
{
        int amount;
        if(!me) return;

        if( !intp(amount = me->query_temp("hmg_nizhuan")) )
                return;

        if (me->query_skill("hamagong", 1) > 450)
        {
                me->add_temp("apply/parry", -amount/4);
                me->add_temp("apply/dodge", -amount/4);
        }
        me->add_temp("apply/strength", - amount);
        me->add_temp("apply/dexerity", - amount/3);
        me->add_temp("apply/constitution", - amount/3);
        me->add_temp("apply/attack", - amount/4);
        me->delete_temp("hmg_nizhuan");
        if (me->query("oyf/hamagong") == 3 ){
        tell_object(me, HIW "����ת�����˹����ã������ֽ�����ԭ��\n" NOR);
        }
        if (me->query("oyf/hamagong") == 2 ){
        tell_object(me, HIW "���󡹦�˹����ã�һ��ǿ����ھ���ֹ���˹���\n" NOR);      
        }
}

int help(object me)
{
write(WHT"\n��󡹦����ת��������"NOR"\n");
write(@HELP
ŷ����Ķ��ž�����󡹦����������ѧ�еľ��������Դ������������ɷ�
���ֶ�����µ�һ�ĳƺź����󡹦������Ѱ���书�����ӹ������ס���
��ת����֮�������ǵ�������������ľ�����

      Ҫ������ 300 ���ϣ�
            �⿪��󡹦�������
            ����ʩչ��ת������
            �⿪��󡹦��������
            �����ͷ���ת��������������
HELP
);
return 1;

}
