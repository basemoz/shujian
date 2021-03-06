/**********************************************************************************
//
//      lease.c
//      Created by mychat 31/04/2004
//      保留我的签名情况下 free of use.
//      当然更欢迎修改、优化等。
//
//      Email & MSN: codemake@163.com
//      文件位于/cmds/usr下
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
                return notify_fail("你正忙着呢。\n");
        me->set_temp("command_busy",1);
        call_out("remove_busy", 3, me);
	indexval=ROOMLEASE_D->query_keys();	
	if( sizeof(indexval)==0 )
		return notify_fail("没有任何出租店铺的信息\n");
	
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
		//房间基本情况
		valroomname=ROOMLEASE_D->get_myregions(leasemap["roomwhere"])+leasemap["originshortname"];

		roomset+=sprintf("│%-20s %-8s %8d两白银 %8d两白银%14s 万分之%-8s│\n",
			valroomname+"("+indexval[i]+")",
			( (leasemap["bidtype"]==0)?RED"停止投标"NOR:((leasemap["bidtype"]==1)?BLU"实名投标"NOR:CYN"匿名投标"NOR) ),
			leasemap["minirent"]/100,
			leasemap["minirentadd"]/100,
			ROOMLEASE_D->chinese_time(leasemap["leasetime"]),
			CHINESE_D->chinese_number(leasemap["discount"])
			);

		//已出租的情况
		if( leasemap["leaser"]==myid )
			leasestr+=sprintf("│%-20s %4s %8d两白银 %-14s %8d两白银 %8d两白银   │\n",
				valroomname+"("+indexval[i]+")",
				((leasemap["leasertype"]==2)?"匿名":"实名"),
				leasemap["leaser_bidmoney"]/100,
				(leasemap["endtime"]==0)?"无":ROOMLEASE_D->shorttime(leasemap["endtime"] ),
				ROOMLEASE_D->sum_by_discount(leasemap["repayamount"],leasemap["discount"])/100,
				leasemap["payamount"]/100
				);

		//投标情况
		if( leasemap["bider"]==myid )
			bidstr+=sprintf("│%-20s %4s %8d两白银 %14s  %-14s   %8s      │\n",
				valroomname+"("+indexval[i]+")",
				(leasemap["bidertype"]==2)?"匿名":"实名",
				leasemap["bidamount"]/100,
				(leasemap["bidtime"]==0)?"无":ROOMLEASE_D->shorttime(leasemap["bidtime"]),
				(leasemap["bidendtime"]==0)?"无":ROOMLEASE_D->shorttime(leasemap["bidendtime"]),
				(leasemap["bidendtime"]>time())?HIG"正在投标"NOR:HIY"投标截止"NOR
				);
/**/
	};
	if( irunflag==0 )
		return notify_fail("你没有投标或承租任何店铺\n");
	outstr="";
	outstr+=sprintf("┌───『你投标或承租的店铺有%4d个』──────────────────────────┐\n",irunflag);
//	outstr+="│各店铺情况介绍                                                                          │\n";
	outstr+="│   店铺              投标类型     最低投标价      最低加价        租期     提成比例     │\n";
	outstr+=roomset;
	outstr += "├───『承租情况』───────────────────────────────────┤\n";
//	outstr+="│各店铺当前承租情况                                                                      │\n";
	outstr+="│   店铺              类型       中标价       租期截止          收益           预支      │\n";
	outstr+=leasestr;
	outstr += "├───『投标情况』───────────────────────────────────┤\n";
//	outstr+="│各店铺当前投标情况                                                                      │\n";
	outstr+="│   店铺              类型     投标价       投标时间         结束时间      投标状态      │\n";
	outstr+=bidstr;
	outstr += "└────────────────────────────────────────────┘\n";

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
指令格式：lease
--------------------------------------------------
 看自己参与投标及已承租的情况

write by mychat@ln(codemake@163.com)
--------------------------------------------------

HELP
    );
    return 1;
}
