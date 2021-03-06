/*
允许玩家转换书剑通宝为物品

SJ_Credit 	书剑通宝
SJ_Credit_Used 	累计使用积分
*/

inherit F_CLEAN_UP;
inherit F_DBASE;

#include <ansi.h>
#include <mudlib.h>
private int mysql = 0;
int help(object);

mapping valid_obj = ([
        "gold"  	:       	10,
        "wulong gao"	:       	30,  
        "dumang dan":	100,
        "wucai laba"	:	100,
        "zhengqi dan":	110,
        "puti zi"	:	150,
        "shouwu"	:	200,
]);

mapping obj_to_chinese = ([
        "gold"  	:      	 "一锭"HIY"黄金"NOR,
        "wulong gao"	:   	"回阳五龙膏",
        "dumang dan":	MAG"毒蟒胆"NOR,
        "wucai laba"	:	MAG"五"HIY"彩"HIB"喇"HIM"叭"NOR,
        "zhengqi dan": 	HIR"六阳正气丹"NOR,
        "puti zi"	:	"菩提子",
        "shouwu"	:	YEL"千年首乌"NOR
]);

mapping valid_special = ([
        "death"  	:      	1800,
        "per"	:	3800,
        "recover"	:	4000,
]);
mapping special_to_chinese = ([
        "death"  	:       	"一次"HIY"有效死亡"NOR,
        "per"  	:      	"一个"HIG"先天容貌"NOR,
        "recover"	:	"恢复一次"HIB"死亡损失"NOR,
]);

string *valid_combined  = ({"gold"});//means some item inherit combined

mapping obj_file = ([
        "gold"  	:       	"/clone/money/gold.c",
        "wulong gao"	:   	"/clone/medicine/huiyang",
        "dumang dan":	"/clone/medicine/neili/gshedan",
        "wucai laba"	:	"/clone/credit/laba",
        "zhengqi dan":	"/clone/medicine/neili/liuyang-dan",
        "puti zi"	:	"/clone/medicine/neili/puti-zi",
        "shouwu"	:	"/clone/medicine/neili/qnshouwu",
]);

void create()
{
        seteuid(getuid());
}

// 获取积分
//this function is useless now
int GetMyCredit()
{
	object me = this_player();
	mixed ret = dbquery("SELECT U_Credit FROM Users WHERE U_Username=\""+me->query("id")+"\"");

	if (!ret)
	{
		write("数据库连接失败。\n");
		return 0;
	}

	if (sizeof(ret) != 1)
	{
		write("数据库数据有问题，请与管理人员联系。\n");
		return 0;
	}
	if (ret[0][0] > 0)
	{
		me->add("SJ_Credit",ret[0][0]);
		dbquery("UPDATE Users U_Credit = 0 WHERE U_Username=\""+me->query("id")+"\"");
		write(HIY"书剑通宝充值成功，通宝增加"+chinese_number(ret[0][0])+"个。\n"NOR);	
	}
	return 1;

}
//更新书剑通宝
int Update_Credit(object me)
{
	string uname = me->query("id");
	mixed ret = dbquery("SELECT U_Credit FROM Users WHERE U_Username=" + save_variable(uname));
	int credit = ret[0][0];
	if (sizeof(ret) == 1 && credit > 0)
	{

		me->add("SJ_Credit",credit);
		write(HIY BYEL+"书剑通宝充值成功，通宝增加"+chinese_number(credit)+"个。\n"NOR);	
		
		dbquery("UPDATE Users SET U_Credit = 0 WHERE U_Username=" + save_variable(uname));

		log_file("static/SJ_Credit", sprintf(" %s(%s) 增加书剑通宝 %d 个。", 
			me->name(1), uname, credit));

		return 1;
	}

	return 0;
}


// Clone obj
int CloneObj(string obj, int count, int chg)
{
        object myobj, me = this_player();
        string err;
        
        if (!load_object(obj_file[obj]))
                return 0;
        err = catch(myobj = new(obj_file[obj]));
        if (err)
                return 0;        
 	if (obj_file[obj] == "/clone/money/gold.c"){       
        myobj->set("exchange", 1);
        myobj->set_amount(count);
        myobj->move(me,1);
        write("你将"+chinese_number(chg)+"个书剑通宝兑换为"+chinese_number(count)+myobj->query("base_unit")+myobj->query("name") + "。\n");
        }
        else
        {
        myobj->set("exchange", 1);
        myobj->move(me,1);
        if (myobj->query("id") != "wucai laba")
        myobj->set("owner",me->query("id"));
        write("你将"+chinese_number(chg)+"个书剑通宝兑换为"+chinese_number(count)+myobj->query("unit")+myobj->query("name") + "。\n");
        }
        return 1;
}

// 兑换物品
int ExchangeObj(int SJ_Credit, int chg, string obj)
{
	object me = this_player();
//	mixed ret;
	
	if(chg/valid_obj[obj]>1 && member_array(obj,valid_combined)==-1) return notify_fail("该物品只允许一次换一件。\n");
	
/*	ret = dbquery("UPDATE Users SET U_Credit = U_Credit - "+chg+" WHERE U_Username=\""+me->query("id")+"\"");
	if (!ret)
	{
		write("数据库连接失败。\n");
		return 0;
	}
*/
	me->add("SJ_Credit",-chg); //扣除通宝个数
	log_file("static/EXCHANGE", 
		sprintf("%s(%s) use %d credit(%d/%d) to exchange %s, ", 
		 me->name(1), geteuid(me), chg, SJ_Credit, me->query("SJ_Credit_Used"), obj));

	//credit -= chg;

	me->add("SJ_Credit_Used",chg); //已经消费的书剑通宝
	me->start_busy(1+random(2));

	if (CloneObj(obj, chg/valid_obj[obj], chg))
	{
		return notify_fail(HIG BGRN+"您目前剩余的书剑通宝为：" 
		 	+ chinese_number(me->query("SJ_Credit"))+"个，累计使用书剑通宝为：" 
			+ chinese_number(me->query("SJ_Credit_Used")) + "个。\n"+NOR);
	}
	else
	{
		return notify_fail("书剑通宝交易失败，请与巫师联系。\n");
	}

}

int main(object me, string arg)
{
        int SJ_Credit, chg;
        string obj;
        string obj2;
        
        if( me != this_player(1) ) return 0;
        
        if (me->is_busy())
		return notify_fail("你正忙着呢。\n");
		
        Update_Credit(me);
        SJ_Credit = me->query("SJ_Credit");
        if (!arg || arg=="") {
                return notify_fail(HIG BGRN+"您目前可用书剑通宝为："+chinese_number(SJ_Credit)+"个，累计使用书剑通宝为："+chinese_number(me->query("SJ_Credit_Used")) +"个。\n"+NOR);
        }
        
        if (sscanf(arg, "%s %d", obj, chg)!=2 ){
		if (sscanf(arg, "%s %s %d", obj,obj2, chg)!=3 ) return notify_fail("指令格式： <物品> <书剑通宝>\n");
		obj = obj+" "+obj2;
	}
        
        if (valid_obj[obj] == 0)
                return notify_fail("目前书剑不提供该物品的兑换。\n");

        if (chg > SJ_Credit) 
                return notify_fail("您的书剑通宝不够。\n");
        
        if (chg%valid_obj[obj] != 0)
                return notify_fail("兑换 "+obj+" 需要 "+valid_obj[obj]+" 的整数倍书剑通宝。\n");
                
        return ExchangeObj(SJ_Credit, chg, obj);
}

int help(object me)
{
        string *p;
        int i;
        
        write(@HELP
指令格式 : exchange [要转换的物品] [要转换的书剑通宝]

这个指令可以转换书剑通宝为物品。
不带任何参数将查看自己的书剑通宝。

HELP
);
        p = sort_array(keys(valid_obj), 1);
        write("当前可用转换物品如下：("HIG"我们将不定期添加新的物品"NOR")\n");
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        write(sprintf("   %-15s：  %-20s  %-12s\n", "物品ID","物品名", "需要积分"));
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        for (i=0;i<sizeof(p);i++) {
                write(sprintf("   %-15s：  %-20s  %-12s\n", p[i],obj_to_chinese[p[i]], chinese_number(valid_obj[p[i]])+"个"));
        }
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        
        p = sort_array(keys(valid_special), 1);
        write("当前可转换特殊内容如下：("HIG"我们将不定期添加新的特殊内容"NOR")\n");
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        write(sprintf("   %-15s：  %-20s  %-12s\n", "特殊内容ID","特殊内容名字", "需要积分"));
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        for (i=0;i<sizeof(p);i++) {
                write(sprintf("   %-15s：  %-20s  %-12s\n", p[i],special_to_chinese[p[i]], chinese_number(valid_special[p[i]])+"个"));
        }
        write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");
        write("特殊内容转换，请到大理定安府输入(exchange)进行转换\n");
        return 1;
}
