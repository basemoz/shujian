// mygift  by lsxk@hsbbs 2008/3/15 
// רΪת�����ã��鿴�����츳���������δת������޷�ʹ�ã�  by lsxk@hsbbs 2008/3/15

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int AP,DP,SP,QP,RP,A1,A2,A3,D1,D2,D3,S1,S2,S3,Q1,Q2,Q3,R1,R2,R3;
    string str_attack,str_defend,str_study,str_quest,str_recover,str_help;

    if(arg && objectp(find_player(arg)) && wizardp(me)) me = find_player(arg);

    A1 = (int)me->query("relife/attack/jsmz",1);
    A2 = (int)me->query("relife/attack/jdsl",1);
    A3 = (int)me->query("relife/attack/sxys",1);
    D1 = (int)me->query("relife/defend/jszj",1);
    D2 = (int)me->query("relife/defend/jptz",1);
    D3 = (int)me->query("relife/defend/tqtb",1);
    S1 = (int)me->query("relife/study/jsqc",1);
    S2 = (int)me->query("relife/study/stzs",1);
    S3 = (int)me->query("relife/study/bxtc",1);
    Q1 = (int)me->query("relife/quest/txqr",1);
    Q2 = (int)me->query("relife/quest/txzj",1);
    Q3 = (int)me->query("relife/quest/lwds",1);
    R1 = (int)me->query("relife/recover/jsjg",1);
    R2 = (int)me->query("relife/recover/sehs",1);
    R3 = (int)me->query("relife/recover/qgqr",1);

    AP = A1 + A2 + A3;
    DP = D1 + D2 + D3;
    SP = S1 + S2 + S3;
    QP = Q1 + Q2 + Q3;
    RP = R1 + R2 + R3;

    if(!me->query("relife/times")){
        write(me->query("name")+"��Ȼ�����츳���..... -____________________-!\n");
        return 1;
    }

    str_help =sprintf(HIY"������������������������������������������������������������������������������������������������"NOR);
    str_help += sprintf(HIY"\n%s%92s%s"NOR,"��"," ","��");
    str_help += sprintf(HIY+"\n��"HIC"%35s��ǰ������츳�������£�"HIY"%35s\n%s%94s\n"NOR,me->query("name"),"��","��","��");
    str_help += sprintf(HIY"��"HIR"%4s����ϵ("+HIW+"%2d"+HIR+"/30)%5s"+HIY+"����ϵ("+HIW+"%2d"+HIY+"/30)%5s"+HIC+"��ѧϵ("+HIW+"%2d"+HIC+"/30)%5s"+HIM+"����ϵ("+HIW+"%2d"+HIM+"/30)%5s"+HIG+"�ָ�ϵ("+HIW+"%2d"+HIG+"/30)"HIY"%5s\n"NOR," ",AP," ",DP," ",SP," ",QP," ",RP,"��");
    str_help += sprintf(HIY"��"HIR"%3s��������("+HIW+"%2d"+HIR+"/15)%3s"+HIY+"�����м�("+HIW+"%2d"+HIY+"/15)%3s"+HIC+"�������("+HIW+"%2d"+HIC+"/10)%3s"+HIM+"̽������("+HIW+"%2d"+HIM+"/15)%3s"+HIG+"�������("+HIW+"%2d"+HIG+"/10)"HIY"%4s\n"NOR," ",A1," ",D1," ",S1," ",Q1," ",R1,"��");
    str_help += sprintf(HIY"��"HIR"%3s����ɱ¾("+HIW+"%2d"+HIR+"/10)%3s"+HIY+"��Ʒ����("+HIW+"%2d"+HIY+"/10)%3s"+HIC+"��ͯ����("+HIW+"%2d"+HIC+"/15)%3s"+HIM+"̽��ר��("+HIW+"%2d"+HIM+"/10)%3s"+HIG+"��������("+HIW+"%2d"+HIG+"/15)"HIY"%4s\n"NOR," ",A2," ",D2," ",S2," ",Q2," ",R2,"��");
    str_help += sprintf(HIY"��"HIR"%3s��ѪԪ��("+HIW+"%2d"+HIR+"/ 5)%3s"+HIY+"ͭǽ����("+HIW+"%2d"+HIY+"/ 5)%3s"+HIC+"��ѧ���("+HIW+"%2d"+HIC+"/ 5)%3s"+HIM+"�����ʦ("+HIW+"%2d"+HIM+"/ 5)%3s"+HIG+"ǧ������("+HIW+"%2d"+HIG+"/ 5)"HIY"%4s\n"NOR," ",A3," ",D3," ",S3," ",Q3," ",R3,"��");
    str_help += sprintf(HIY"%s%92s%s\n"NOR,"��"," ","��");
    str_help += sprintf(HIY"��"HIW"%61sĿǰ"+((me->query("relife/gift/now")>=1)?("����"+HIR+"%2d"+HIW+"���츳�������Է���!"):"�����κ��츳�������Է���!")+HIY"%4s\n"NOR,me->query("name"),me->query("relife/gift/now")>=1?(int)me->query("relife/gift/now",1):"  ��","��");
    str_help += sprintf(HIY"%s%92s%s\n"NOR,"��"," ","��");
    str_help +=sprintf(HIY"������������������������������������������������������������������������������������������������"NOR);
    str_help += HIC"\n�����Ҫ�鿴��ϸ���ݣ���ʹ��"+HIR+" mygift ["+HIW+"�츳ϵ"+HIR+"] "+HIC+"�ĸ�ʽ���鿴��\n\n"NOR;

    if(AP > 0){
        str_attack = "�q���Щ��������������������������������������������������r\n";
        str_attack +="��  ��        ���ڽ���ϵ���ѵ��츳����Ϊ��"+sprintf(((AP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,AP)+"         ��\n";
        str_attack +="���������������Щ�����������������������������������������\n";
        str_attack +="��  ���츳���Ʃ�          ��    ǰ    Ч    ��          ��\n";
        str_attack +="��  �����������੤����������������������������������������\n";
        str_attack +="��  ���������Щ����ͶԷ���������������"+sprintf(HIR"%2d",A1)+"%"+NOR+"�Ķ������ʣ� ��\n";
        str_attack +="������("+sprintf(HIY"%2d"NOR,A1)+"/15) ����һ�ȼ�Ч����"+((A1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,A1+1))+"                       ��\n";
        str_attack +="��  �����������੤����������������������������������������\n";
        str_attack +="��  ������ɱ¾�������Լ�����������"+sprintf(HIR"%2d",A2)+"%"+NOR+"�˺���           ��\n";
        str_attack +="��  ��("+sprintf(HIY"%2d"NOR,A2)+"/10) ����һ�ȼ�Ч����"+((A2>9)?"N/A":sprintf(HIC"%2d%%"NOR,A2+1))+"                       ��\n";
        str_attack +="��ϵ�����������੤����������������������������������������\n";
        str_attack +="��  ����ѪԪ������"+sprintf(HIR"%2d",A3)+"%"+NOR+"�ļ���,�ڻ��жԷ��������һ�ζ\n";
        str_attack +="��  �� ("+sprintf(HIY"%1d"NOR,A3)+"/5)  ��������������                          ��\n";
        str_attack +="��  ��        ����һ�ȼ�Ч����"+((A3>4)?"N/A":sprintf(HIC"%2d%%"NOR,A3+1))+"                       ��\n";
        str_attack +="�t���ة��������ة����������������������������������������s\n";

    }

    if(DP > 0){
        str_defend = "�q���Щ��������������������������������������������������r\n";
        str_defend +="��  ��        ���ڷ���ϵ���ѵ��츳����Ϊ��"+sprintf(((DP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,DP)+"         ��\n";
        str_defend +="���������������Щ�����������������������������������������\n";
        str_defend +="��  ���츳���Ʃ�          ��    ǰ    Ч    ��          ��\n";
        str_defend +="��  �����������੤����������������������������������������\n";
        str_defend +="��  �������мܩ������Լ�������������"+sprintf(HIR"%2d",D1)+"%"+NOR+"���мܼ��ʣ�   ��\n";
        str_defend +="������("+sprintf(HIY"%2d"NOR,D1)+"/15) ����һ�ȼ�Ч����"+((D1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,D1+1))+"                       ��\n";
        str_defend +="��  �����������੤����������������������������������������\n";
        str_defend +="��  ����Ʒ���ʩ�����"+sprintf(HIR"%2d",D2)+"%"+NOR+"��������������������˺���     ��\n";
        str_defend +="��  ��("+sprintf(HIY"%2d"NOR,D2)+"/10) ����һ�ȼ�Ч����"+((D2>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,D2+1))+"                       ��\n";
        str_defend +="��ϵ�����������੤����������������������������������������\n";
        str_defend +="��  ��ͭǽ���ک�����"+sprintf(HIR"%2d",D3)+"%"+NOR+"�ļ���,�ڱ����к�Ե��˽���һ�αة�\n";
        str_defend +="��  �� ("+sprintf(HIY"%1d"NOR,D3)+"/5)  ���е�����������                        ��\n";
        str_defend +="��  ��        ����һ�ȼ�Ч����"+((D3>4)?"N/A":sprintf(HIC"%2d%%"NOR,D3+1))+"                       ��\n";
        str_defend +="�t���ة��������ة����������������������������������������s\n";

    }

    if(SP > 0){
        str_study = "�q���Щ��������������������������������������������������r\n";
        str_study +="��  ��        ������ѧϵ���ѵ��츳����Ϊ��"+sprintf(((SP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,SP)+"         ��\n";
        str_study +="���ĩ����������Щ�����������������������������������������\n";
        str_study +="��  ���츳���Ʃ�          ��    ǰ    Ч    ��          ��\n";
        str_study +="��  �����������੤����������������������������������������\n";
        str_study +="��  ��������ũ������Ķ����ѧϰЧ��"+sprintf(HIR"%2d",S1*5)+"%"+NOR+"��             ��\n";
        str_study +="��ѧ��("+sprintf(HIY"%2d"NOR,S1)+"/10) ����һ�ȼ�Ч����"+((S1>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S1+1)*5))+"                       ��\n";
        str_study +="��  �����������੤����������������������������������������\n";
        str_study +="��  ����ͯ��������������ϰ������Ч��"+sprintf(HIR"%2d",S2*2)+"%"+NOR+"��             ��\n";
        str_study +="��  ��("+sprintf(HIY"%2d"NOR,S2)+"/15) ����һ�ȼ�Ч����"+((S2>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S2+1)*2))+"                       ��\n";
        str_study +="��ϵ�����������੤����������������������������������������\n";
        str_study +="��  ����ѧ��ũ�����"+sprintf(HIR"%2d",S3*2)+"%"+NOR+"�ļ���,�ڼ�������ʱ��ʹ��������ܩ�\n";
        str_study +="��  �� ("+sprintf(HIY"%1d"NOR,S3)+"/5)  ����������һ����                          ��\n";
        str_study +="��  ��        ����һ�ȼ�Ч����"+((S3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S3+1)*2))+"                       ��\n";
        str_study +="�t���ة��������ة����������������������������������������s\n";

    }

    if(QP > 0){
        str_quest = "�q���Щ��������������������������������������������������r\n";
        str_quest +="��  ��        ���ڽ���ϵ���ѵ��츳����Ϊ��"+sprintf(((QP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,QP)+"         ��\n";
        str_quest +="��������������Щ�����������������������������������������\n";
        str_quest +="��  ���츳���Ʃ�          ��    ǰ    Ч    ��          ��\n";
        str_quest +="��  �����������੤����������������������������������������\n";
        str_quest +="��  ��̽�����˩������"+sprintf(HIR"%2d",Q1)+"%"+NOR+"�Ľ��ճɹ��ʣ�                 ��\n";
        str_quest +="���թ�("+sprintf(HIY"%2d"NOR,Q1)+"/15) ����һ�ȼ�Ч����"+((Q1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,Q1+1))+"                       ��\n";
        str_quest +="��  �����������੤����������������������������������������\n";
        str_quest +="��  ��̽��ר�ҩ�����"+sprintf(HIR"%2d",Q2)+"%"+NOR+"�����ڽ���ʧ��ʱ,�ٻ��һ�λ��ᣡ��\n";
        str_quest +="��  ��("+sprintf(HIY"%2d"NOR,Q2)+"/10) ����һ�ȼ�Ч����"+((Q2>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,Q2+1))+"                       ��\n";
        str_quest +="��ϵ�����������੤����������������������������������������\n";
        str_quest +="��  �������ʦ������"+sprintf(HIR"%2d",Q3*10)+"%"+NOR+"�ļ��ʣ����ջ���¼���ʱ��ֱ���� ��\n";
        str_quest +="��  �� ("+sprintf(HIY"%1d"NOR,Q3)+"/5)  ����ü��ܵ��㼼�����ޣ�                  ��\n";
        str_quest +="��  ��        ����һ�ȼ�Ч����"+((Q3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(Q3+1)*10))+"                       ��\n";
        str_quest +="�t���ة��������ة����������������������������������������s\n";

    }

    if(RP > 0){
        str_recover = "�q���Щ��������������������������������������������������r\n";
        str_recover +="��  ��        ���ڻָ�ϵ���ѵ��츳����Ϊ��"+sprintf(((RP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,RP)+"         ��\n";
        str_recover +="���֩����������Щ�����������������������������������������\n";
        str_recover +="��  ���츳���Ʃ�          ��    ǰ    Ч    ��          ��\n";
        str_recover +="��  �����������੤����������������������������������������\n";
        str_recover +="��  ��������ǩ��������˹����˹�Ч"+sprintf(HIR"%2d",R1*8)+"%"+NOR+"��               ��\n";
        str_recover +="������("+sprintf(HIY"%2d"NOR,R1)+"/10) ����һ�ȼ�Ч����"+((R1>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R1+1)*8))+"                       ��\n";
        str_recover +="��  �����������੤����������������������������������������\n";
        str_recover +="��  ��������������������ս�����Զ�����Ч��"+sprintf(HIR"%2d",R2*2)+"%"+NOR+"��         ��\n";
        str_recover +="��  ��("+sprintf(HIY"%2d"NOR,R2)+"/15) ����һ�ȼ�Ч����"+((R2>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R2+1)*2))+"                       ��\n";
        str_recover +="��ϵ�����������੤����������������������������������������\n";
        str_recover +="��  ��ǧ�����˩�ս���б����У��Զ��ָ�����Ѫ��"+sprintf(HIR"%2d",R3*2)+"%"+NOR+"������ ��\n";
        str_recover +="��  �� ("+sprintf(HIY"%1d"NOR,R3)+"/5)  �����͸��඾�Է���ʱ�䡣                  ��\n";
        str_recover +="��  ��        ����һ�ȼ�Ч����"+((R3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R3+1)*2))+"                       ��\n";
        str_recover +="�t���ة��������ة����������������������������������������s\n";

    }


    if(arg == "����ϵ"){
        write(str_attack);
        return 1;
    }
    else if(arg == "����ϵ"){
        write(str_defend);
        return 1;
    }
    else if(arg == "��ѧϵ"){
        write(str_study);
        return 1;
    }
    else if(arg == "����ϵ"){
        write(str_quest);
        return 1;
    }
    else if(arg == "�ָ�ϵ"){
        write(str_recover);
        return 1;
    }
    else{
        write(str_help);
        return 1;
    }

    return 1;
}
