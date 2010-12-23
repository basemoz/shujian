// full.c for apprentice
// written by snowman@SJ 29/10/1999
#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me,string arg)
{
        string kind;
        int amount;
        object n_money;

        if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
		return notify_fail("money <����Ǯ> <Ǯ������>\n");

        n_money = present(kind + "_money", me);
        if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
                return notify_fail("�����˰���ȴʲôҲû���ڳ�����\n");
        if( amount < 1 )
                return notify_fail("�����˰���ȴʲôҲû���ڳ�����\n");

        if( !n_money ) {
                n_money = new("/clone/money/" + kind);
        }
                
	tell_object(me,HIY"��ǰ�����ַ���ȡǮˬ�ɣ������������Ƕ��ݵģ�����������������Ϊ����\n"NOR);
	tell_object(me,HIY"�ٴ�������࿴help rules�������벻Ҫ�����齣��ʦ��Դ����¼������ľ��ġ�\n"NOR);
	/*message_vision( sprintf("$N�ó�һ��VISA������ATM��ȡ����%s%s%s��\n",
                        chinese_number(amount),
                        n_money->query("base_unit"),
                        n_money->query("name")),me);*/
        log_file("static/HOWG_BUG",
		sprintf("%s(%s)��ͼ��ȡ%s%s%s\n",
			me->name(1), geteuid(me),chinese_number(amount),
			n_money->query("base_unit"),n_money->query("name")
		), me
	);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: money <����Ǯ> <Ǯ������>
 
 ȡǮ��

HELP );
        return 1;
}
