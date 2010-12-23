/*
�������ת���齣ͨ��Ϊ��Ʒ

SJ_Credit 	�齣ͨ��
SJ_Credit_Used 	�ۼ�ʹ�û���
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
        "gold"  	:      	 "һ��"HIY"�ƽ�"NOR,
        "wulong gao"	:   	"����������",
        "dumang dan":	MAG"������"NOR,
        "wucai laba"	:	MAG"��"HIY"��"HIB"��"HIM"��"NOR,
        "zhengqi dan": 	HIR"����������"NOR,
        "puti zi"	:	"������",
        "shouwu"	:	YEL"ǧ������"NOR
]);

mapping valid_special = ([
        "death"  	:      	1800,
        "per"	:	3800,
        "recover"	:	4000,
]);
mapping special_to_chinese = ([
        "death"  	:       	"һ��"HIY"��Ч����"NOR,
        "per"  	:      	"һ��"HIG"������ò"NOR,
        "recover"	:	"�ָ�һ��"HIB"������ʧ"NOR,
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

// ��ȡ����
//this function is useless now
int GetMyCredit()
{
	object me = this_player();
	mixed ret = dbquery("SELECT U_Credit FROM Users WHERE U_Username=\""+me->query("id")+"\"");

	if (!ret)
	{
		write("���ݿ�����ʧ�ܡ�\n");
		return 0;
	}

	if (sizeof(ret) != 1)
	{
		write("���ݿ����������⣬���������Ա��ϵ��\n");
		return 0;
	}
	if (ret[0][0] > 0)
	{
		me->add("SJ_Credit",ret[0][0]);
		dbquery("UPDATE Users U_Credit = 0 WHERE U_Username=\""+me->query("id")+"\"");
		write(HIY"�齣ͨ����ֵ�ɹ���ͨ������"+chinese_number(ret[0][0])+"����\n"NOR);	
	}
	return 1;

}
//�����齣ͨ��
int Update_Credit(object me)
{
	string uname = me->query("id");
	mixed ret = dbquery("SELECT U_Credit FROM Users WHERE U_Username=" + save_variable(uname));
	int credit = ret[0][0];
	if (sizeof(ret) == 1 && credit > 0)
	{

		me->add("SJ_Credit",credit);
		write(HIY BYEL+"�齣ͨ����ֵ�ɹ���ͨ������"+chinese_number(credit)+"����\n"NOR);	
		
		dbquery("UPDATE Users SET U_Credit = 0 WHERE U_Username=" + save_variable(uname));

		log_file("static/SJ_Credit", sprintf(" %s(%s) �����齣ͨ�� %d ����", 
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
        write("�㽫"+chinese_number(chg)+"���齣ͨ���һ�Ϊ"+chinese_number(count)+myobj->query("base_unit")+myobj->query("name") + "��\n");
        }
        else
        {
        myobj->set("exchange", 1);
        myobj->move(me,1);
        if (myobj->query("id") != "wucai laba")
        myobj->set("owner",me->query("id"));
        write("�㽫"+chinese_number(chg)+"���齣ͨ���һ�Ϊ"+chinese_number(count)+myobj->query("unit")+myobj->query("name") + "��\n");
        }
        return 1;
}

// �һ���Ʒ
int ExchangeObj(int SJ_Credit, int chg, string obj)
{
	object me = this_player();
//	mixed ret;
	
	if(chg/valid_obj[obj]>1 && member_array(obj,valid_combined)==-1) return notify_fail("����Ʒֻ����һ�λ�һ����\n");
	
/*	ret = dbquery("UPDATE Users SET U_Credit = U_Credit - "+chg+" WHERE U_Username=\""+me->query("id")+"\"");
	if (!ret)
	{
		write("���ݿ�����ʧ�ܡ�\n");
		return 0;
	}
*/
	me->add("SJ_Credit",-chg); //�۳�ͨ������
	log_file("static/EXCHANGE", 
		sprintf("%s(%s) use %d credit(%d/%d) to exchange %s, ", 
		 me->name(1), geteuid(me), chg, SJ_Credit, me->query("SJ_Credit_Used"), obj));

	//credit -= chg;

	me->add("SJ_Credit_Used",chg); //�Ѿ����ѵ��齣ͨ��
	me->start_busy(1+random(2));

	if (CloneObj(obj, chg/valid_obj[obj], chg))
	{
		return notify_fail(HIG BGRN+"��Ŀǰʣ����齣ͨ��Ϊ��" 
		 	+ chinese_number(me->query("SJ_Credit"))+"�����ۼ�ʹ���齣ͨ��Ϊ��" 
			+ chinese_number(me->query("SJ_Credit_Used")) + "����\n"+NOR);
	}
	else
	{
		return notify_fail("�齣ͨ������ʧ�ܣ�������ʦ��ϵ��\n");
	}

}

int main(object me, string arg)
{
        int SJ_Credit, chg;
        string obj;
        string obj2;
        
        if( me != this_player(1) ) return 0;
        
        if (me->is_busy())
		return notify_fail("����æ���ء�\n");
		
        Update_Credit(me);
        SJ_Credit = me->query("SJ_Credit");
        if (!arg || arg=="") {
                return notify_fail(HIG BGRN+"��Ŀǰ�����齣ͨ��Ϊ��"+chinese_number(SJ_Credit)+"�����ۼ�ʹ���齣ͨ��Ϊ��"+chinese_number(me->query("SJ_Credit_Used")) +"����\n"+NOR);
        }
        
        if (sscanf(arg, "%s %d", obj, chg)!=2 ){
		if (sscanf(arg, "%s %s %d", obj,obj2, chg)!=3 ) return notify_fail("ָ���ʽ�� <��Ʒ> <�齣ͨ��>\n");
		obj = obj+" "+obj2;
	}
        
        if (valid_obj[obj] == 0)
                return notify_fail("Ŀǰ�齣���ṩ����Ʒ�Ķһ���\n");

        if (chg > SJ_Credit) 
                return notify_fail("�����齣ͨ��������\n");
        
        if (chg%valid_obj[obj] != 0)
                return notify_fail("�һ� "+obj+" ��Ҫ "+valid_obj[obj]+" ���������齣ͨ����\n");
                
        return ExchangeObj(SJ_Credit, chg, obj);
}

int help(object me)
{
        string *p;
        int i;
        
        write(@HELP
ָ���ʽ : exchange [Ҫת������Ʒ] [Ҫת�����齣ͨ��]

���ָ�����ת���齣ͨ��Ϊ��Ʒ��
�����κβ������鿴�Լ����齣ͨ����

HELP
);
        p = sort_array(keys(valid_obj), 1);
        write("��ǰ����ת����Ʒ���£�("HIG"���ǽ�����������µ���Ʒ"NOR")\n");
        write("��������������������������������������������������������\n");
        write(sprintf("   %-15s��  %-20s  %-12s\n", "��ƷID","��Ʒ��", "��Ҫ����"));
        write("��������������������������������������������������������\n");
        for (i=0;i<sizeof(p);i++) {
                write(sprintf("   %-15s��  %-20s  %-12s\n", p[i],obj_to_chinese[p[i]], chinese_number(valid_obj[p[i]])+"��"));
        }
        write("��������������������������������������������������������\n");
        
        p = sort_array(keys(valid_special), 1);
        write("��ǰ��ת�������������£�("HIG"���ǽ�����������µ���������"NOR")\n");
        write("��������������������������������������������������������\n");
        write(sprintf("   %-15s��  %-20s  %-12s\n", "��������ID","������������", "��Ҫ����"));
        write("��������������������������������������������������������\n");
        for (i=0;i<sizeof(p);i++) {
                write(sprintf("   %-15s��  %-20s  %-12s\n", p[i],special_to_chinese[p[i]], chinese_number(valid_special[p[i]])+"��"));
        }
        write("��������������������������������������������������������\n");
        write("��������ת�����뵽������������(exchange)����ת��\n");
        return 1;
}
