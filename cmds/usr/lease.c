/**********************************************************************************
//
//      lease.c
//      Created by mychat 31/04/2004
//      �����ҵ�ǩ������� free of use.
//      ��Ȼ����ӭ�޸ġ��Ż��ȡ�
//
//      Email & MSN: codemake@163.com
//      �ļ�λ��/cmds/usr��
// 		
***********************************************************************************/
#include <ansi.h>
//#include <roomlease.h>

int main(object me, string arg)
{
	mapping leasemap;	
	string *indexval, outstr,roomset,leasestr,bidstr;
	string myid;
	string valroomname;
	int i;
	int irunflag;

	if (!wizardp(me) && me->query_temp("command_busy"))
                return notify_fail("����æ���ء�\n");
        me->set_temp("command_busy",1);
        call_out("remove_busy", 3, me);
	indexval=ROOMLEASE_D->query_keys();	
	if( sizeof(indexval)==0 )
		return notify_fail("û���κγ�����̵���Ϣ\n");
	
	myid=me->query("id");
	roomset="";
	leasestr="";
	bidstr="";
	irunflag=0;
	for(i=0;i<sizeof(indexval);i++)
	{
		leasemap=ROOMLEASE_D->query_amap(indexval[i]);
		if( (leasemap["leaser"]!=myid) && (leasemap["bider"]!=myid) )
			continue;

		irunflag+=1;
		//����������
		valroomname=ROOMLEASE_D->get_myregions(leasemap["roomwhere"])+leasemap["originshortname"];

		roomset+=sprintf("��%-20s %-8s %8d������ %8d������%14s ���֮%-8s��\n",
			valroomname+"("+indexval[i]+")",
			( (leasemap["bidtype"]==0)?RED"ֹͣͶ��"NOR:((leasemap["bidtype"]==1)?BLU"ʵ��Ͷ��"NOR:CYN"����Ͷ��"NOR) ),
			leasemap["minirent"]/100,
			leasemap["minirentadd"]/100,
			ROOMLEASE_D->chinese_time(leasemap["leasetime"]),
			CHINESE_D->chinese_number(leasemap["discount"])
			);

		//�ѳ�������
		if( leasemap["leaser"]==myid )
			leasestr+=sprintf("��%-20s %4s %8d������ %-14s %8d������ %8d������   ��\n",
				valroomname+"("+indexval[i]+")",
				((leasemap["leasertype"]==2)?"����":"ʵ��"),
				leasemap["leaser_bidmoney"]/100,
				(leasemap["endtime"]==0)?"��":ROOMLEASE_D->shorttime(leasemap["endtime"] ),
				ROOMLEASE_D->sum_by_discount(leasemap["repayamount"],leasemap["discount"])/100,
				leasemap["payamount"]/100
				);

		//Ͷ�����
		if( leasemap["bider"]==myid )
			bidstr+=sprintf("��%-20s %4s %8d������ %14s  %-14s   %8s      ��\n",
				valroomname+"("+indexval[i]+")",
				(leasemap["bidertype"]==2)?"����":"ʵ��",
				leasemap["bidamount"]/100,
				(leasemap["bidtime"]==0)?"��":ROOMLEASE_D->shorttime(leasemap["bidtime"]),
				(leasemap["bidendtime"]==0)?"��":ROOMLEASE_D->shorttime(leasemap["bidendtime"]),
				(leasemap["bidendtime"]>time())?HIG"����Ͷ��"NOR:HIY"Ͷ���ֹ"NOR
				);
/**/
	};
	if( irunflag==0 )
		return notify_fail("��û��Ͷ�������κε���\n");
	outstr="";
	outstr+=sprintf("������������Ͷ������ĵ�����%4d����������������������������������������������������������\n",irunflag);
//	outstr+="���������������                                                                          ��\n";
	outstr+="��   ����              Ͷ������     ���Ͷ���      ��ͼӼ�        ����     ��ɱ���     ��\n";
	outstr+=roomset;
	outstr += "�������������������������������������������������������������������������������������������\n";
//	outstr+="�������̵�ǰ�������                                                                      ��\n";
	outstr+="��   ����              ����       �б��       ���ڽ�ֹ          ����           Ԥ֧      ��\n";
	outstr+=leasestr;
	outstr += "����������Ͷ�������������������������������������������������������������������������������\n";
//	outstr+="�������̵�ǰͶ�����                                                                      ��\n";
	outstr+="��   ����              ����     Ͷ���       Ͷ��ʱ��         ����ʱ��      Ͷ��״̬      ��\n";
	outstr+=bidstr;
	outstr += "��������������������������������������������������������������������������������������������\n";

	write( outstr );
	return 1;
}

void remove_busy(object me)
{
        if (me) me->delete_temp("command_busy");
}

int help(object me)
{
  write(@HELP
--------------------------------------------------
ָ���ʽ��lease
--------------------------------------------------
 ���Լ�����Ͷ�꼰�ѳ�������

write by mychat@ln(codemake@163.com)
--------------------------------------------------

HELP
    );
    return 1;
}
