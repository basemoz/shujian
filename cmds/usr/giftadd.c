//Create by lsxk@hsbbs 2008/3/17
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int gifts, max_gifts;
    string gifts_name;

    max_gifts = me->query("relife/gift/now");

    if(!arg){
        tell_object(me,"�밴�ա�"+HIG+"giftadd �츳���� to �츳��������"+NOR+"���ĸ�ʽ��������츳!\n\n"NOR);
        write("��ǰ���õ��츳�������£�\n\n");
        write(HIR"       ����ϵ"+HIY+"    ����ϵ"+HIC+"    ��ѧϵ"+HIM+"    ����ϵ"+HIG+"    �ָ�ϵ\n"NOR);
        write(HIR"      ��������"+HIY+"  �����м�"+HIC+"  �������"+HIM+"  ̽������"+HIG+"  �������\n"NOR);
        write(HIR"      ����ɱ¾"+HIY+"  ��Ʒ����"+HIC+"  ��ͯ����"+HIM+"  ̽��ר��"+HIG+"  ��������\n"NOR);
        write(HIR"      ��ѪԪ��"+HIY+"  ͭǽ����"+HIC+"  ��ѧ���"+HIM+"  �����ʦ"+HIG+"  ǧ������\n\n"NOR);
        return 1;
    }

    if(!sscanf(arg, "%d to %s", gifts, gifts_name)){
        tell_object(me,"�밴�ա�"+HIG+"giftadd �츳���� to �츳��������"+NOR+"���ĸ�ʽ��������츳!\n"NOR);
        return 1;
    }
    else{
        if(gifts<1)
            return notify_fail("������ת��ת�����ˣ�\n");

        if(gifts > max_gifts)
            return notify_fail("������û��ô���츳�������Է��䣡\n����"+HIR+" mygift "+NOR+"ָ�����鿴������ӵ�ж��ٵ��츳!\n");
        //����ϵ
        if(gifts_name == "��������"){
            if((int)me->query("relife/attack/jsmz",1)>15 - gifts)
               return notify_fail("���������С��츳���ֻ�����15���츳������������ѡ��\n"NOR);
            else{
               me->add("relife/attack/jsmz",gifts);
               me->add("relife/gift/now",-gifts);
               me->add("relife/gift/used",gifts);
               tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIR+"��������"+NOR+"����\n");
            }
            return 1;
        }

        if(gifts_name == "����ɱ¾"){
            if((int)me->query("relife/attack/jsmz",1)<5)
               return notify_fail("������ڡ��������С��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/attack/jdsl",1)>10 - gifts)
               return notify_fail("������ɱ¾���츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/attack/jdsl",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIR+"����ɱ¾"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "��ѪԪ��"){
            if((int)me->query("relife/attack/jdsl",1)<5)
               return notify_fail("������ڡ�����ɱ¾���츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/attack/sxys",1)>5 - gifts)
               return notify_fail("����ѪԪ���츳���ֻ�����5���츳������������ѡ��\n"NOR);
            me->add("relife/attack/sxys",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIR+"��ѪԪ��"+NOR+"����\n");
            return 1;
        }
        //����ϵ
        if(gifts_name == "�����м�"){
            if((int)me->query("relife/defend/jszj",1)>15 - gifts)
               return notify_fail("�������мܡ��츳���ֻ�����15���츳������������ѡ��\n"NOR);
            me->add("relife/defend/jszj",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIY+"�����м�"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "��Ʒ����"){
            if((int)me->query("relife/defend/jszj",1)<5)
               return notify_fail("������ڡ������мܡ��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/defend/jptz",1)>10 - gifts)
               return notify_fail("����Ʒ���ʡ��츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/defend/jptz",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIY+"��Ʒ����"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "ͭǽ����"){
            if((int)me->query("relife/defend/jptz",1)<5)
               return notify_fail("������ڡ���Ʒ���ʡ��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/defend/tqtb",1)>5 - gifts)
               return notify_fail("��ͭǽ���ڡ��츳���ֻ�����5���츳������������ѡ��\n"NOR);
            me->add("relife/defend/tqtb",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIY+"ͭǽ����"+NOR+"����\n");
            return 1;
        }
        //��ѧϵ
        if(gifts_name == "�������"){
            if((int)me->query("relife/study/jsqc",1)>10 - gifts)
               return notify_fail("��������š��츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/study/jsqc",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIC+"�������"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "��ͯ����"){
            if((int)me->query("relife/study/jsqc",1)<5)
               return notify_fail("������ڡ�������š��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/study/stzs",1)>15 - gifts)
               return notify_fail("����ͯ�������츳���ֻ�����15���츳������������ѡ��\n"NOR);
            me->add("relife/study/stzs",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIC+"��ͯ����"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "��ѧ���"){
            if((int)me->query("relife/study/stzs",1)<5)
               return notify_fail("������ڡ���ͯ�������츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/study/bxtc",1)>5 - gifts)
               return notify_fail("����ͯ�������츳���ֻ�����5���츳������������ѡ��\n"NOR);
            me->add("relife/study/bxtc",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIC+"��ѧ���"+NOR+"����\n");
            return 1;
        }

        //����ϵ
        if(gifts_name == "̽������"){
            if((int)me->query("relife/quest/txqr",1)>15 - gifts)
               return notify_fail("��̽�����ˡ��츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/quest/txqr",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIM+"̽������"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "̽��ר��"){
            if((int)me->query("relife/quest/txqr",1)<5)
               return notify_fail("������ڡ�̽�����ˡ��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/quest/txzj",1)>10 - gifts)
               return notify_fail("��̽��ר�ҡ��츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/quest/txzj",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIM+"̽��ר��"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "�����ʦ"){
            if((int)me->query("relife/quest/txzj",1)<5)
               return notify_fail("������ڡ�̽��ר�ҡ��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/quest/lwds",1)>5 - gifts)
               return notify_fail("�������ʦ���츳���ֻ�����5���츳������������ѡ��\n"NOR);
            me->add("relife/quest/lwds",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIM+"�����ʦ"+NOR+"����\n");
            return 1;
        }
        //�ָ�ϵ
        if(gifts_name == "�������"){
            if((int)me->query("relife/recover/jsjg",1)>10 - gifts)
               return notify_fail("��������ǡ��츳���ֻ�����10���츳������������ѡ��\n"NOR);
            me->add("relife/recover/jsjg",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIG+"�������"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "��������"){
            if((int)me->query("relife/recover/jsjg",1)<5)
               return notify_fail("������ڡ�������ǡ��츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/recover/sehs",1)>15 - gifts)
               return notify_fail("�������������츳���ֻ�����15���츳������������ѡ��\n"NOR);
            me->add("relife/recover/sehs",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIG+"��������"+NOR+"����\n");
            return 1;
        }

        if(gifts_name == "ǧ������"){
            if((int)me->query("relife/recover/sehs",1)<5)
               return notify_fail("������ڡ������������츳�ϻ�������5���츳�󣬷��ɷ�����츳��\n"NOR);
            if((int)me->query("relife/recover/qgqr",1)>5 - gifts)
               return notify_fail("��ǧ�����ˡ��츳���ֻ�����5���츳������������ѡ��\n"NOR);
            me->add("relife/recover/qgqr",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"��ɹ��������"+HIW+chinese_number(gifts)+NOR+"���츳����"+HIG+"ǧ������"+NOR+"����\n");
            return 1;
        }

        //������
        return notify_fail("��ѡ����ȷ���츳����������츳������ָ���ʽ��"+HIR+"giftadd �츳���� to �츳�������� "+NOR+"!\n");
    }

    return 1;
}
