// hero Ӣ������
// 19991002001
// Update By lsxk@hsbbs 2007/6/5

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIR"Ӣ������"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("��Ӣ�����С�ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("��Ӣ�����С�ֻ�а��˽���������ã�\n");

        if( objectp(weapon=me->query_temp("weapon")) ) {
                string *ids = weapon->parse_command_id_list();
                if (member_array("bishou", ids) == -1)                          
                        return notify_fail("���������ذ�ײ����á�Ӣ�����С���\n");
        }
        else {
                return notify_fail("���������ذ�ײ����á�Ӣ�����С���\n");
        }
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 250 )
                return notify_fail("��Ļ������ƻ���������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("ֻ��ʹ�û�������ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 250 )
                return notify_fail("��������ȷ�����������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("ֻ��ʹ�������ȷ�ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 250 )
                return notify_fail("��Ĳ��˹�������������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("ֻ��ʹ�ò��˹���ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("��Ķ����󷨹������㣬�����á�Ӣ�����С���\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 250 )
                return notify_fail("�������ذ������������������ʹ�á�Ӣ�����С���\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�Ӣ�����С���\n");

        if( (int)me->query_skill("dagger", 1) < 250 )
                return notify_fail("��Ļ���ذ������������������ʹ�á�Ӣ�����С���\n");

        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("������������Ϊ�еͣ�����ʹ�á�Ӣ�����С���\n"); 

        if((int)me->query("eff_jingli", 1) < 2500) 
                return notify_fail("�����ھ�����Ϊ�еͣ�����ʹ�á�Ӣ�����С���\n"); 

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�Ӣ�����С���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á�Ӣ�����С���\n");      

        if(me->query("gender")!= "����") 
                return notify_fail("ֻ�����˲���ʹ�á�Ӣ�����С���\n");      

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á�Ӣ�����С���\n");

        me->add("jingli",-100);
        me->add("neili",-200);

        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ�����������֮����������Ӣ�����С�\n"NOR;

        if(random((int)me->query_skill("canglang-goufa",1))*8/5 > (int)target->query_skill("parry",1)
          ||random((int)me->query("combat_exp"))*8/5 > (int)target->query("combat_exp")
          ||target->is_busy() ){
                me->start_busy(1);
                me->add("neili",- random(400)-400 );
                me->add("jingli",-random(200)- 200);
                total = 0;
                msg += HIR "\n$Nʹ��һ�С�"HIY"����ٶ�"HIR"����һ����ɦ$nҸ�׼�ȪѨ���������֮�ʣ���һ��ͬ\n"+
                           "ʱ����$n���С��Ѩ������ˤ����ϡ�\n"NOR;
                i = calc_damage((int)me->query_skill("huagu-mianzhang",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��Ѩ" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIR "\n$Nʹ��һ�С�"HIW"³�����"HIR"�������ȼ�װ��$nߵͷ��ͻȻһ��������������$n����\n"+
                         "�������ֻһ���ƣ�����ץ��$n�ҽ����ף����ֱ��������$nС����һ��������$nͷ��\n"+
                         "���ϣ�����������\n"NOR;

                i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "С��" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIR "\n$Nʹ��һ�С�"HIC"���ཱུ��"HIR"����������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�\n"+
                         "ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n\n"+
                         "̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"����");
                result = replace_string( result, "$l", "ͷ��" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(5,"��Ӣ�����С�");
        }
        else {
                msg += HIR "\n$Nʹ��һ�С�"HIY"����ٶ�"HIR"����һ����ɦ$nҸ�׼�ȪѨ���������֮�ʣ���һ��ͬ\nʱ����$n���С��Ѩ������ˤ����ϡ�\n"NOR;
                msg += "����$n������$N����ͼ��û���ϵ�������ææ���Ա�һ�������˹�ȥ��\n";
                msg +=HIR "\n$Nʹ��һ�С�"HIW"³�����"HIR"�������ȼ�װ��$nߵͷ��ͻȻһ��������������$n����\n"+
                          "�������ֻһ���ƣ�����ץ��$n�ҽ����ף����ֱ��������$nС����һ��������$nͷ��\n"+
                          "���ϣ�����������\n"NOR;
                msg += "$n����һ�������漴�侲�������ڿ�����һ��������$N���ţ�$Nֻ���ɿ����֡�\n";
                msg += HIR "\n$Nʹ��һ�С�"HIC"���ཱུ��"HIR"����������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�\n"+
                           "ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n\n"+
                           "̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR;
                msg += "$n��$N��ס������Σ���ң���������סҪ����ͬʱ�߸�Ծ�𣬷�����ͷײ�أ���$Nײ�˳�ȥ��\n";

                message_vision(msg,me,target);

                me->start_busy(1+random(3));
                me->start_perform(3,"��Ӣ�����С�");
        }

        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);
            if( i < (skill2*5)) i = (int)target->query("max_qi",1)/3;

            if(!userp(me)) i = i/2;

        return i*4/5;
}

int help(object me)
{
   write(WHT"\n���˹�����"HIR"Ӣ������"WHT"����"NOR"\n");
   write(@HELP

    Ҫ��������� 4000 ���ϣ�
          ����� 2500 ���ϣ�
          ��ǰ���� 1500 ���ϣ�
          ��ǰ���� 800 ���ϣ�
          �������Ƶȼ� 250 ���ϣ�
          �����ȷ��ȼ� 250 ���ϣ�
          ���˹����ȼ� 250 ���ϣ�
          �����󷨵ȼ� 250 ���ϣ�
          ����ذ���ȼ� 250 ���ϣ�
          ����ذ���ȼ� 250 ���ϣ�
          �Ա����� ���ԡ�
HELP
   );
   return 1;
}
