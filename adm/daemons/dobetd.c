/**********************************************************************************
//
//      dobetd.c
//      Created by mychat 12/05/2004
//      保留我的签名情况下 free of use.
//      当然更欢迎修改、优化等。
//
//      Email & MSN: codemake@163.com
//      文件位于/adm/deamons下
// 		处理赌局的进程

-- 赌局设置库
if(select count(*) from sysobjects where name = 'dobet_main') > 0
  drop table dobet_main
go
不考虑加最低投注额和最高投注额，没什么意义吧，还麻烦
create table dobet_main
(
	U_Site  char(10)		not null,	--站点
	code	char(10)		not null,	--赌局代码
	context	char(80)		not null,	--赌局内容：如谁对谁
	setup_id		char(8)			not null , -- 赌局设置人
	flag			int			not null , -- 状态0设置1开始投注2投注截止3结果输入4派彩结束10暂停使用
	max_bet			int			not null , -- 最大下注金额
	begin_time		int			not null , -- 起始时刻
	stop_time		int			not null , -- 截止时刻
	end_time		int		not null , -- 派彩时刻,也是本赌局的结束时间
	deposit 		int		not null , -- 设赌押金（若wiz设的则为0）
	bet_result		int		not null , -- 赌局结果，对应dobet_odds中的odds_id,另外0表示取消,-1表示尚无结果
	remark			varchar(100), -- 赌局变动记录	--以后再用
)
go
-- 赌局赔率库
if(select count(*) from sysobjects where name = 'dobet_odds') > 0
  drop table dobet_odds
go
create table dobet_odds
(
	U_Site  char(10)		not null,	--站点
	code	char(10)		not null,	--赌局代码
	odds_id	int		not null,	--赔率代码:不能设置为0，因为设置结果时0表示比赛没进行或赌局取消,
	odds_remark	char(20)		not null,	--赔率说明最简单的就是1主赢2平3客赢
	odds		int			not null , -- 赔率，不含本金，如果是0.8返回的时候就是1.8,存储为赔率*100
)
go
-- 赌局下注库
if(select count(*) from sysobjects where name = 'dobet_chip') > 0
  drop table dobet_chip
go
create table dobet_chip
(
	U_Site  char(10)		not null,	--站点
	code	char(10)		not null,	--赌局代码
	chip_id	char(8)		not null,	--投注人id
	odds_remark	char(20)		not null,	--赔率说明最简单的就是1主赢2平3客赢;冗余字段，以免查两个表
	odds_id	int			not null , -- 赔率代码
	odds	int			not null , -- 下注赔率，因为赌局的赔率可能在变，所以记录下注时的赔率,存储为赔率*100
	chip	int			not null , -- 投注金
	chip_time	int			not null , -- 下注时间
)
go
http://shaer.mymud.com/bbs/showthread.php?threadid=24238
备注：
只要赌局没有结束，允许在任何时刻都输入结果，这时候flag自动变为3
***********************************************************************************/
#include <ansi.h>
#include <mudlib.h>
#include  <database.h>

void init_dobet();
void do_dobet();
void check_dobet();
void clear_dobet();

int delete_odds(string valcode, int valodds_id);
int delete_chip(string valcode);

mixed leasedb(string sql);
string pay_all(string valcode,string valcontext, int bet_result);
string money_str(int amount);
int givemoney_removeflag(string valuserid,int money,string valreason,string valflag);
string Ctime(string ts);

int ilaststatistic;
int iifstop;

int iifpublicrepay=1;

#define DB_DOBET_NAME "dobet_main"
#define DB_ODDS_NAME "dobet_odds"
#define DB_CHIP_NAME "dobet_chip"


#define MSG_CMDS "/cmds/std/msg"
//#define MYLOG_TIME 600
//callouts 时间定义
#define MYLOG_TIME 60
//用来定义平均每多少次MYLOG_TIME提醒一次(现在为平均6小时)
#define MYSHOUT_TIME 360
//#define MYSHOUT_TIME 360
//删除过期赌局使用，表示过期多少天用
#define MYDEL_TIME 86400
//#define MYDEL_TIME 60

string longtime(int t)
{
	string ts = ctime(t);
	ts = " "+ts[19..23]+"年"+ts[4..6]+ts[8..9]+ts[10..15];
	return Ctime(ts);
}

string shorttime(int t)
{
	string ts = ctime(t);
	ts = ts[4..6]+ts[8..9]+ts[10..15];
	return Ctime(ts);
}

string Ctime(string ts)
{

	ts = replace_string(ts, "Jan", "一月");
	ts = replace_string(ts, "Feb", "二月");
	ts = replace_string(ts, "Mar", "三月");
	ts = replace_string(ts, "Apr", "四月");
	ts = replace_string(ts, "May", "五月");
	ts = replace_string(ts, "Jun", "六月");
	ts = replace_string(ts, "Jul", "七月");
	ts = replace_string(ts, "Aug", "八月");
	ts = replace_string(ts, "Sep", "九月");
	ts = replace_string(ts, "Oct", "十月");
	ts = replace_string(ts, "Nov", "十一月");
	ts = replace_string(ts, "Dec", "十二月");
	return ts;
}

int set_bet(string valcode,string valcontext, string valsetup_id, int valmax_bet,
		int valbegin_time, int valstop_time, int valend_time, int valdeposit)
{
	string sql;
	mixed ret = leasedb("select code from "+DB_DOBET_NAME+" WHERE code='"+valcode+"' AND U_Site='"+INTERMUD_MUD_NAME+"'");
	if(!ret) return 0;
	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	//如果有这个赌局，就修改它,否则创建
	if(sizeof(ret)>0)
	sql = "UPDATE "
	+DB_DOBET_NAME+" SET "	
	+"context='"+valcontext+ "',"
	+"max_bet='"+valmax_bet+ "',"
	+"begin_time='"+valbegin_time+ "',"
	+"stop_time='"+valstop_time+ "',"
	+"end_time='"+valend_time+ "'"
	+" WHERE code='"+valcode+"' AND U_Site='"+INTERMUD_MUD_NAME+"'";
	else sql = "REPLACE "+DB_DOBET_NAME+" SET "
	+"U_Site='" + INTERMUD_MUD_NAME + "',"
	+"flag='0',"
	+"code='"+valcode+ "',"
	+"context='"+valcontext+ "',"
	+"setup_id='"+valsetup_id+ "',"
	+"max_bet='"+valmax_bet+ "',"
	+"begin_time='"+valbegin_time+ "',"
	+"stop_time='"+valstop_time+ "',"
	+"end_time='"+valend_time+ "',"
	+"bet_result='-1',"
	+"deposit='"+valdeposit+ "'";

	if(leasedb(sql)) return 1;
	return 0;
}

int delete_bet(string valcode)
{
	//如果赌局没有结束就不能删除
	mixed ret = leasedb("select code,context,setup_id,flag,begin_time,stop_time,end_time,deposit,bet_result,remark from "+DB_DOBET_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"'");

	if(!ret || sizeof(ret)<1) 
		return 0;

	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	if( ret[0][3] != 4 ){
		write("赌局没结束前不能删除!\n请先修改赌局结束时间，然后等待标志变了再删,以便退投注者的钱\n");
		return 0;
	};
//先删除投注记录
	delete_chip(valcode);
//然后删除投注选项
	delete_odds(valcode,-1);
//然后删除赌局
	if(!leasedb("DELETE FROM "+DB_DOBET_NAME+" WHERE code='"+valcode+"' AND U_Site='"+INTERMUD_MUD_NAME+"'"))
		return 0;
//	write("删除赌局成功！\n");
	return 1;
}

int set_odds(string valcode, int valodds_id, string valodds_remark, int valodds)
{
	string sql;
	mixed ret = leasedb("select code,odds_id  from "+DB_ODDS_NAME+" WHERE code='"+valcode+"' AND odds_id='"+valodds_id+"' AND U_Site='"+INTERMUD_MUD_NAME+"'");
	if(!ret) return 0;
	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	if( (valodds_id == -1)||(valodds_id == 0) ){
		write("赌局选项代码不能为0或-1,这是内部专业代码\n");
		return 0;
	};
	//如果有这个投注选项，就修改它,否则创建
	if(sizeof(ret)>0)
	sql = "UPDATE "+DB_ODDS_NAME+" SET "	
	+"odds_remark='"+valodds_remark+ "',"
	+"odds='"+valodds+ "'"
	+" WHERE code='"+valcode+"' AND odds_id='"+valodds_id+"' AND U_Site='"+INTERMUD_MUD_NAME+"'";
	else sql = "REPLACE "+DB_ODDS_NAME+" SET "
	+"U_Site='" + INTERMUD_MUD_NAME + "',"
	+"code='"+valcode+ "',"
	+"odds_id='"+valodds_id+ "',"
	+"odds_remark='"+valodds_remark+ "',"
	+"odds='"+valodds+ "'";
	if(leasedb(sql)) return 1;
	return 0;
}

//如果valodds_id=-1表示该赌局的全部选项都删除
int delete_odds(string valcode, int valodds_id)
{
	if( valodds_id == -1 ){
		if(!leasedb("DELETE FROM "+DB_ODDS_NAME+" WHERE code='"+valcode+"' AND U_Site='"+INTERMUD_MUD_NAME+"'"))
			return 0;
	}else{
		if(!leasedb("DELETE FROM "+DB_ODDS_NAME+" WHERE code='"+valcode+"' AND odds_id='"+valodds_id+"' AND U_Site='"+INTERMUD_MUD_NAME+"'"))
			return 0;
	};
//	write("删除投注选项成功！\n");
	return 1;
}

//赌注下就不能修改
int set_chip(string valcode, string valchip_id, int valodds_id, string valodds_remark, int valodds, int valchip)
{
	string sql;
	sql = "REPLACE "+DB_CHIP_NAME+" SET code='" + valcode + "',"
	+"U_Site='" + INTERMUD_MUD_NAME + "',"
	+"chip_id='"+valchip_id+ "',"
	+"odds_id='"+valodds_id+ "',"
	+"odds_remark='"+valodds_remark+ "',"
	+"odds='"+valodds+ "',"
	+"chip='"+valchip+ "',"
	+"chip_time='"+time()+"'";
	if(leasedb(sql)) return 1;
	return 0;
}

//删除投注记录只有在整个赌局被删除时才用，所以就不判断别的了
int delete_chip(string valcode)
{
	if(!leasedb("DELETE FROM "+DB_CHIP_NAME+" WHERE code='"+valcode+"' AND U_Site='"+INTERMUD_MUD_NAME+"'"))
		return 0;
//	write("删除投注记录成功！\n");
	return 1;
}

//按局查
//查赌局
//按投注人查

//设置结果
//接受投注

int start_dobet()
{
	if(!iifstop) return 0;
	call_out("do_dobet", 2);
	iifstop=0;
	return 1;
}

void create()
{
	seteuid(getuid());

	init_dobet();
	iifstop=0;
}

void remove()
{
}

void init_dobet()
{
	call_out("do_dobet", MYLOG_TIME);
}

void do_dobet()
{
	//检查赌局设置
	check_dobet();
	clear_dobet();
	
	remove_call_out("do_dobet");
	if(!iifstop)
		call_out("do_dobet", MYLOG_TIME);
}

void stop_dobet()
{
	iifstop=1;
	remove_call_out("do_dobet");
}

void check_dobet()
{
	int i,ichangflag,inewval;
	string csoutstr;
	string tempstr;
	string sql="select code,context,setup_id,flag,begin_time,stop_time,end_time,deposit,bet_result,remark from "+DB_DOBET_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND flag!='10' AND flag!='4'";
	string sql2;
	int ipos,iIfshout;
	int inowtime = time();
	mixed op;		
	mixed ret = leasedb(sql);
	
	ipos=0;
	while(1){
		if(!ret || !sizeof(ret)) return;
		if(iifstop==1) return;
		for(i=0;i<sizeof(ret);i++)
		{
			ichangflag=0;
			op = ret[i];
			//flag==0 and begin_time<inowtime
			if( (op[3] == 0) && (op[4]<inowtime) ){
				//将状态改为开始投注
				inewval=1;
				ichangflag=1;
			};

			//flag<2 and stop_time<inowtime
			if( op[3] < 2 && op[5]<inowtime){
				//将状态改为停止投注
				inewval=2;
				ichangflag=1;
			};
		
			//只有结果已经输入了，才能将派彩flag==3 and end_time<inowtime
			if( op[3] == 3 && op[8] != -1 && op[6]<inowtime){
				//将状态改为停止投注
				inewval=4;
				tempstr=pay_all(op[0],op[1],op[8]);
				ichangflag=1;
			};
		
			if( ichangflag==1 ){
				if(!leasedb("UPDATE "+DB_DOBET_NAME+" SET "
					+"flag='"+inewval+ "'"
					+" WHERE code='" + op[0] + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))
					log_file("dobetlog","check_dobet上步数据库操作失败。");
				if(inewval==1)
					csoutstr=HIY"【"
						+op[1]
						+"】可以开始下注了，请各位踊跃参与\n"NOR;
				else if(inewval==2)
					csoutstr=HIY"【"
						+op[1]
						+"】现在停止下注，请各位等待结果揭晓\n"NOR;
				else if(inewval==4){
					csoutstr=HIY"【"
						+op[1]
						+"】现在开始派彩了，请各投注者注意信息\n"NOR
						+tempstr;
				}else 
					csoutstr=HIY"【"
						+op[1]
						+"】见鬼了，"
						+inewval
						+"请wiz注意信息\n"NOR;
				message("channel:chat", 
					HIW"\n【赌局信息】"HIY
					+csoutstr,
					users());
			}else{
				//用来多长时间提醒一次
				iIfshout=0;
				if( op[3] == 1 ){
				//如果大于一天，就一天喊一次
					if( (op[5]-inowtime)>86400 ){
						if( random(1440)==0 )
							iIfshout=1;
						}else{
				//如果大于四个小时，就两小时喊一次
							if( (op[5]-inowtime)>14400 ){
								if( random(120)==0 )
									iIfshout=1;
							}else
				//如果小于四个小时，就半小时喊一次
								if( random(30)==0 )
									iIfshout=1;
						}
					}

					if( iIfshout==1)
							message("channel:chat", 
									HIW"\n【赌局信息】"HIY
									+"【"
									+op[1]
									+"】正在接受下注，请各位踊跃参与。帮助请help gamblers\n"NOR,
									users());
			}; //
		}
		ipos+=sizeof(ret);
		sql2 = sql+sprintf(" LIMIT %d,%d",ipos,ROW_LIMIT);
		ret = leasedb(sql2);

	}
	return;
}

//删除过期三天的赌局
void clear_dobet()
{
	int i;
	string sql1,sql;
	mixed ret;
	
	sql1="select code from "+DB_DOBET_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND flag='4' and end_time<%d";
	sql=sprintf(sql1,time()-MYDEL_TIME);
	ret = leasedb(sql);
	if(!ret || !sizeof(ret)) return;
	if(iifstop==1) return;
	for(i=0;i<sizeof(ret);i++)
		delete_bet(ret[i][0]);
	return;
}

//给大家分派采金,bet_result==0的时候，是退回原来的筹码
string pay_all(string valcode,string valcontext, int bet_result)
{
	int i;
	int itotalwin,itotallost;
	string result_context;
	string logstr,flagstr;
	string sql="select chip_id,odds_id,odds_remark,odds,chip from "+DB_CHIP_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"'";
	string sql2;
	int ipos;
	mixed op;
	mixed ret = leasedb(sql);
	
	//无人下注
	if(!ret || !sizeof(ret)) return "\n";
	
	if(iifstop==1) return "\n";
	
	if( bet_result!=0 ){
		op = leasedb("select odds_remark from "+DB_ODDS_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"' AND odds_id='"+bet_result+"'");
		if(!op || sizeof(op)<1){
			log_file("dobetlog","见鬼了，"+valcode+"派彩时找不到"+bet_result+"。");
			return "error3,报告wiz";
		};
		result_context=op[0][0];
	};

	itotalwin=0;
	itotallost=0;
	flagstr="bet/"+valcode;
	while( ret && sizeof(ret) ){
		for(i=0;i<sizeof(ret);i++)
		{
			if( bet_result==0 ){
				itotallost+=ret[i][4]*10000;
				givemoney_removeflag(ret[i][0],ret[i][4]*10000,
					HIY"【"+valcontext+"】的赌局已经被取消了，你原来下的投注"
					+money_str(ret[i][4]*10000)
					+"已退回你的存款，请查收\n"NOR,
					flagstr);
			}else{
				if( ret[i][1] == bet_result ){
					itotallost+=ret[i][4]*10000;
					itotalwin+=ret[i][4]*ret[i][3]*100;
					givemoney_removeflag(ret[i][0],ret[i][4]*ret[i][3]*100,
						HIY"【"+valcontext+"】赌局的结果是："
						+result_context
						+"。恭喜你中奖了，奖金含原投注金"
						+money_str(ret[i][4]*ret[i][3]*100)
						+"已恭送到你的钱庄存款，请查收\n"NOR,
						flagstr);
				}else{
					itotallost+=ret[i][4]*10000;
					givemoney_removeflag(ret[i][0],0,
						HIY"【"+valcontext+"】赌局的结果是："
						+result_context
						+"。你猜的是："
						+ret[i][2]
						+"，可惜你没有猜中\n"NOR,
						flagstr);
				};
			};
		};
		ipos+=sizeof(ret);
		sql2 = sql+sprintf(" LIMIT %d,%d",ipos,ROW_LIMIT);
		ret = leasedb(sql2);
	};
	
	if( bet_result!=0 )
		logstr=sprintf("收到赌注为:%s，分配彩金%s,赌场%s：%s",
			money_str(itotallost),money_str(itotalwin),
			((itotalwin>itotallost)?"亏损":"盈利"),
			((itotalwin>itotallost)?money_str(itotalwin-itotallost):money_str(itotallost-itotalwin))
			);
	else
		logstr=sprintf("已退回彩金%s",money_str(itotallost));

	log_file("betlog",sprintf("%s 赌局派彩：%s",
			valcontext,
			logstr));
	return HIW"【赌局信息】"HIY
			+"【"+valcontext+"】赌局的结果是："
					+result_context
					+"，"
					+logstr
					+"\n"NOR;
}

mixed leasedb(string sql)
{
	mixed ret = dbquery(sql);	
	if(!ret){
		error("roomlease db error!"+sql);
		return 0;
	}
	return ret;	
}

string money_str(int amount)
{
	// returns a chinese string of `amount` of money
	string output;
		
	if(amount==0)
		return "零两白银";

	if (amount / 10000) {
		output = chinese_number(amount / 10000) + "锭黄金";
		amount %= 10000;
	}
	else
		output = "";
	if (amount / 100) {
		output = output + chinese_number(amount / 100) + "两白银";
		amount %= 100;
	}
	if (amount)
		return output + chinese_number(amount) + "文铜钱";
	return output;
}

//这个givemoney
int givemoney_removeflag(string valuserid,int money,string valreason,string valflag)
{
	object body,ob;

	if(objectp(body = LOGIN_D->find_body(valuserid))) {
		body->add("balance",money);
		body->delete(valflag);
		if( money!=0 )
			valreason += sprintf(HIY"现在的存款余额为%s\n"NOR,
				money_str(body->query("balance")));
		tell_object(body, valreason);
//		destruct(body);
	}else{
		ob = new(LOGIN_OB);
		ob->set("id", valuserid);
		
		if( !ob->restore() ) {destruct(ob); return 1;}
		body = LOGIN_D->make_body(ob);
		if( body->restore() ) {
			body->add("balance",money);
			body->delete(valflag);
			if( money!=0 )
				valreason += sprintf(HIY"现在的存款余额为%s\n"NOR,
					money_str(body->query("balance")));
			valreason = sprintf(HIW"【离线期间信息】"HIY"你在离线后，于%s系统通知你\n",
				 longtime(time()))+valreason;
//			MSG_CMDS->system_send(this_object(),({valuserid}),"赌局信息",valreason);
			//add
			body->set_temp("db_quit",1);
			body->save();
		}
		destruct(ob);
		destruct(body);
	}
	return 1;
}


string getflag(int valflag)
{
//	string outstr;
//	mixed ret;
//	int i;

	//状态0设置1开始投注2投注截止3结果输入4派彩结束10暂停使用
	if( valflag==0 )
		return CYN"将要投注"NOR;
	if( valflag==1 )
		return HIG"正在投注"NOR;
	if( valflag==2 )
		return HIB"投注截止"NOR;
	if( valflag==4 )
		return HIR"派彩结束"NOR;
	if( valflag==10 )
		return HIR"暂停投注"NOR;
	if( valflag!=3 )
		return HIR"状态不明"NOR;
	if( valflag==3 )
		return HIY"等待派彩"NOR;
/*
	if( valresult!=0){
		ret = leasedb("select odds_id,odds_remark,odds from "+DB_ODDS_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"' AND odds_id='"+valresult+"'");
		if(!ret || sizeof(ret)!=1) 
			return "赔率设置有问题，请报告wiz\n";
		return ret[0][1];
	}else
*/
		return HIR"已被取消"NOR;
}

string getresult(string valcode, int valflag,int valresult)
{
	mixed ret;

	//状态0设置1开始投注2投注截止3结果输入4派彩结束10暂停使用
	switch(valflag){
		case 0:
		case 1:
		case 2:
			return "";
		};

	if( valresult!=0){
		ret = leasedb("select odds_id,odds_remark,odds from "+DB_ODDS_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"' AND odds_id='"+valresult+"'");
		if(!ret || sizeof(ret)!=1) 
			return "赔率设置有问题，请报告wiz\n";
		return ret[0][1];
	}else
		return "已被取消";
}

string getmytime(int valflag, int valbegin_time, int valstop_time, int valend_time)
{
	if( valflag==0 )
		return sprintf("开局:%s",DOBET_D->shorttime(valbegin_time));
	if( valflag==1 )
		return sprintf("截止:%s",DOBET_D->shorttime(valstop_time));
	if( valflag==2 )
		return sprintf("派彩:%s",DOBET_D->shorttime(valend_time));
	if( valflag==3 )
		return sprintf("派彩:%s",DOBET_D->shorttime(valend_time));
	if( valflag==4 )
		return "派彩结束";
	if( valflag==10 )
		return "暂停投注";
	return "不明";
}

string getoddsstr(string valcode,string valpre,string valsuffix)
{
	string outstr,sql,sql2;
	mixed ret;
	int i,ipos;

	sql = "select odds_id,odds_remark,odds from "+DB_ODDS_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND code='"+valcode+"' order by odds_id";
	ret = leasedb(sql);
	if(!ret || sizeof(ret)<1) 
		return valpre+HIR"尚未设置任何赔率                                       "NOR+valsuffix;
	outstr="";
	
	ipos=0;
	while(1){
		if(!ret || !sizeof(ret)) return outstr;
		for(i=0;i<sizeof(ret);i++)
			outstr+= valpre+sprintf("赌注代码:"HIW"%2i"NOR" 赌注内容："CYN"%-20s"NOR" 赔率："HIW"%3d.%-2d"NOR,
				ret[i][0],ret[i][1],ret[i][2]/100,ret[i][2]%100)+valsuffix;
		ipos+=sizeof(ret);
		sql2 = sql+sprintf(" LIMIT %d,%d",ipos,ROW_LIMIT);
		ret = leasedb(sql2);
	}
	return outstr;
}
