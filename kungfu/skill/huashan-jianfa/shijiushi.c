// shijiushi.c ��Ůʮ��ʽ
// Update by lsxk@hsbbs �������ں�����ʹ��Ч����

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
string perform_name() {return HIC"��Ůʮ��ʽ"NOR;}

int perform(object me, object target)
{
        string weapon;
        int i;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��Ůʮ��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");
    
        if (me->query_skill_mapped("force") != "zixia-gong"
          &&me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("����ڹ������޷�ʹ�á���Ůʮ��ʽ����\n");

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ����Ůʮ��ʽ��\n");
        
        if( me->query_skill("zixia-gong", 1) < 300
         && me->query_skill("huashan-qigong", 1) < 300)
                return notify_fail("��������ڹ����δ�����޷�ʩչ��Ůʮ��ʽ��\n");

        if( (int)me->query_skill("huashan-jianfa",1) < 300 )
                return notify_fail("��Ļ�ɽ��������㣬�޷�ʹ�þ�����׵���Ůʮ��ʽ��\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("��Ůʮ��ʽ��Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("�����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("��ľ�������ʹ����Ůʮ��ʽ��\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("������������Ůʮ��ʽ��\n");

      if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("�������޽�����ʹ����Ůʮ��ʽ����\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N�˽���磬����ǳ��ġ���Ů��ʮ��ʽ��һʽʽʩչ������" + weapon + HIC"����������,���������⣡\n" +
        "���֮�䣬$N������Ůʮ�Ž�������ʮ��ʽ��������һ���ǳɵ�ʹ�˳������������б���һ�У�����֮�죬ֱ�Ƿ�����˼��\n" NOR, me, target);
        me->set_temp("hsj_19",1);
        if(me->query("quest/huashan")=="����")
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/5);
 
    for( i = 0; i < MAX_HITS; i ++ ) {
        if( random( MAX_HITS ) >= i ||(i<=4 && me->query("quest/huashan")=="����")) {
          if (me->query("quest/huashan") == "����"){
             me->add_temp("apply/damage",(int)me->query_skill("huashan-jianfa",1)/4);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->add_temp("apply/damage",-(int)me->query_skill("huashan-jianfa",1)/4);
          }
          else if(me->query("quest/huashan") == "����"){
             if(random(3)) target->set_temp("must_be_hit",1);
             if(!random(3)){
                 message_vision(HIW"$N���ӻ���ھ���������"+weapon+HIW+"�ϣ�$nֻ��һ�ɾ���Ϯ����"+
                     "���ŵ��ֽŲ���ʹ����\n"NOR,me,target);
                 target->add_busy(1);
             }
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
             target->delete_temp("must_be_hit");
          }
          else
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
          me->add("neili",-100);
          }
        else {
            break;
        }
    }
        me->add("neili", -300);
     if(me->query("quest/huashan")=="����")
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/5);
        me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(2+random(3));

        return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"HIC"��Ůʮ��ʽ"WHT"����"NOR"\n");
   write(@HELP
    ���С���Ůʮ��ʽ�����ɽ�ȱ���Ѫ��������ɽ���ڣ����ڶ�����
    ��ȴ��������ͬ�����ڽ���������ӯ���ɣ�������ˮ��������ȴ����
    ���������Ԧ��������������һ�м��������޲���֮����ˣ�����
    ʹ�ã��������Լ�������ǿ�����ڣ�������ʹ�ã���������Զ���ڽ�
    �ڣ����м����õ���æ�ҡ�
    ָ�perform shijiushi

    Ҫ�󣺻�ɽ���� ���� ��ϼ�� 300��
          ����������60��
          ��ɽ����300����
          ��������300����
          �����Ṧ300����
          ��ǰ����5000���ϣ�
          ��ǰ����3000���ϡ�
HELP
   );
  return 1;
}
