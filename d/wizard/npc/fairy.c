// By Spiderii ����tb������������1m
inherit NPC;
#include <ansi.h>
#include <mudlib.h>

int ask_clear_divorce();
int ask_gender();
int ask_divorce();
int ask_new_gift();
int ask_new_pks();
int ask_gift();
mixed change_gift(string gift);

void create()
{
        set_name("��ʦ����", ({"fairy"}));
        set("long","һ���ɰ���С���飬��˵���������˿���ʵ�����ĵ�һЩԸ����\n");

        set("gender", "Ů��");
        set("attitude", "friendly");
        set("age", 18);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 30);
        set("no_quest", 1);
        set("combat_exp", 100000);
        set("inquiry", ([

		  "��������" : (: ask_gift :),
                "������Ե" : (: ask_clear_divorce :),
                "�ָ��Ա�" : (: ask_gender :),
                "���"     : (: ask_divorce :),
                "��վ����" : (: ask_new_gift :),
                "ʮ����" : (: ask_new_pks :),
        ]));
        carry_object("/clone/misc/cloth")->wear();
        setup();
}
void init()
{
	object me = this_player();
	me->set_temp("exp",me->query("combat_exp"));
	add_action("do_change", "change");
}

int ask_gift()
{
	object me, ob;
	me = this_player(1);
	ob = me->query_temp("link_ob");

	if( !ob )
		return 0;
	while( ob && ob->is_character() )
		ob = ob->query_temp("link_ob");

	if (me->query("gift_changed"))
	{
		command("say ���Ѿ�������һ�������ˣ���Ҫ̰�������\n");
		return 1;
	}
	if (me->query_temp("gift_change"))
	{
		command("say �����ˣ��뻻�Ϳ�㻻�ɡ�\n");
		return 1;
	}
        if (! me->query("relife/times") )
    	{
	        command("say ������ת�����޵���ң������Ե������ԡ�\n");
	        return 1;
    	}
	command("say ���������ѽ�����ǲ��ѣ�ת��һ��ֻ��һ�ζ���Ļ���Ŷ��һ��Ҫ���ذ���\n");
	write("ȷ���Ļ����������ĵ�½���룺");

	input_to("check_answer", 1, me, 1);
	return 1;
}

private int check_answer(string passwd, object me)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("password");
	if( crypt(passwd, old_pass)!=old_pass )
	{
		tell_object(me, "���������������޸����ԣ�\n");
		return;
	}
	command("say ��Ȼ������ˣ�����ת��������԰ɡ�\n");
       command("say ָ���ʽ��change <��ֵ> <��������> to <��������>\n");
	me->set_temp("gift_change",1);
	return 1;
}

int do_change(string arg)
{
	object me = this_player();
	int i;
	string old_gift, new_gift;

	if (!arg || arg == "" || (sscanf(arg, "%d %s to %s", i, old_gift, new_gift) != 3))
		return notify_fail("ָ���ʽ��change <��ֵ> <��������> to <��������>\n");
	if (!me->query_temp("gift_change"))
		return notify_fail("���������������ԣ�\n");
	if (!change_gift(old_gift) || !change_gift(new_gift))
		return notify_fail("��Ҫ����ʲô���ԣ�\n");
	if (i < 1)
		return notify_fail("��Ҫ�����������ԣ�\n");
	if (me->query(change_gift(old_gift)) - i < 10 || me->query(change_gift(new_gift)) + i >30)
		return notify_fail("��ô���ˣ�̫���˵�ѣ�\n");
	me->add(change_gift(old_gift),-i);
    	me->add(change_gift(new_gift),i);
    	me->set("gift_changed",1);
    	if (INTERMUD_MUD_NAME == "SHTX")
                return notify_fail(HIR"���Ե�����ϣ��˴ε�����ת��" + chinese_number(i) + "��"
                      + old_gift + "Ϊ" + new_gift + "��\n"NOR);
	me->setup();
	log_file("quest/gift_change", sprintf("[%s] %sת��%d��%sΪ%s.\n",
           	ctime(time())[0..15], geteuid(this_player(1)), i, old_gift, new_gift));
	return notify_fail(HIR"���Ե�����ϣ��˴ε�����ת��" + chinese_number(i) + "��" + old_gift + "Ϊ" + new_gift +
	"��\n"NOR);
}

mixed change_gift(string gift)
{
	if (gift == "����")
		return "str";
	if (gift == "����")
		return "con";
	if (gift == "��")
		return "dex";
	if (gift == "����")
		return "int";
	return 0;
}



int ask_clear_divorce()
{
        int exp;
        object me = this_player();
        if (!me->query("divorce"))
        {
                command("say �����û�������ɣ�\n");
                return 1;
        }
        exp = me->query("combat_exp") * me->query("divorce") * 5 / 1000;
        if (exp > 300000)
                exp = 300000;
        command("say ������������¼���㽫Ҫ���ͷ�" + chinese_number(exp) + "�㾭�顣\n");
        command("say ��ȷ��Ҫ�������¼��(yes or no)?");
        input_to("confirm_clear_divorce", 1, me, exp);
        return 1;
}

int confirm_clear_divorce(string arg, object me, int exp)
{
        if (arg != "yes")
        {
                write("��������������¼���뷨��\n");
                return 1;
        }
        command("say �ðɣ���Ȼ������ˣ��ҾͰ���������ɣ��Ժ�ǵ�Ҫרһ����\n");
        command("sigh " + me->query("id"));
        command("lover fairy");
        log_file("quest/clear_divorce", sprintf("[%s] %s�������¼%d�Σ����پ���%d��.\n",
                ctime(time())[0..15], geteuid(this_player(1)), me->query("divorce"), exp));
        me->delete("divorce");
        me->add("combat_exp", -exp);
        me->setup();
        write(HIR"����¼�����ϣ������پ���" + chinese_number(exp) + "�㡣\n"NOR);
        return 1;
}

int ask_gender()
{
        int exp;
        object me = this_player();
        if (me->query("gender") != "����")
        {
                command("say ������ʮ�ֽ�ȫ���ѵ������ӳ������⣿\n");
                return 1;
        }
        exp = me->query("combat_exp");
        if (exp < 100000)
        {
                command("say �㾭��̫���ˣ��ߵ������ɡ�\n");
                return 1;
        }
        exp = exp * 5 / 100;
        if (exp > 300000)
                exp = 300000;
        command("say �����ָ��Ա��㽫Ҫ���ͷ�" + chinese_number(exp) + "�㾭�顣\n");
        command("say ��ȷ��Ҫ�ָ��Ա���(yes or no)?");
        input_to("confirm_gender", 1, me, exp);
        return 1;
}

int confirm_gender(string arg, object me, int exp)
{
        if (arg != "yes")
        {
                write("������˻ָ��Ա���뷨��\n");
                return 1;
        }
        command("say �ðɣ���Ȼ������ˣ��ҾͰ���ָ��ɣ����ַ����Ѷ��Ƿǳ���ģ�����\n");
        command("poor fairy");
        command("sweat fairy");
        me->delete_skill("pixie-jian");
        me->set("class", me->query("class_old"));
        me->set("gender", "����");
        me->add("combat_exp", -exp);
        me->setup();
        log_file("quest/clear_divorce", sprintf("[%s] %s�ָ��Ա�Ϊ���ԣ����پ���%d��.\n",
                ctime(time())[0..15], geteuid(this_player(1)), exp));
        write(HIR"�Ա�ָ���ϣ������پ���" + chinese_number(exp) + "�㡣\n"NOR);
        return 1;
}

int ask_divorce()
{
        object me = this_player();
        string id = me->query("marry/id");
        int last_on = FINGER_D->get_last_on(id);

        if (!me->query("marry"))
        {
                command("say ��û�н�飬����ʲô��\n");
                return 1;
        }
        if (!last_on)
        {
                command("say ���" + (me->query("gender") == "����"?"����":"���") + "�أ�\n");
                return 1;
        }
        if ((time() - last_on) / 86400 < 30)
        {
                command("say ���" + (me->query("gender") == "����"?"����":"���") + "����ŵ�½�����������ðɣ�\n");
                return 1;
        }
        command("say ������������(yes or no)?");
        input_to("confirm_divorce", 1, me);
        return 1;
}

int confirm_divorce(string arg, object me)
{
        if (arg != "yes")
        {
                write("������������뷨��\n");
                return 1;
        }
        command("say �ðɣ���Ȼ������ˣ��Ҿͳ�ȫ��ɡ�\n");
        command("sigh " + me->query("id"));
        command("lover fairy");
        me->delete("marry");
        me->add("divorce", 1);
        return 1;
}

int ask_new_gift()
{
        object me = this_player();
        

        if (me->query("ty_gift") )
        {
                command("say �㲻��������\n");
                return 1;
        }
        if (me->query("combat_exp") < 1500000 )
        {
                command("say �㻹�ǵȾ���ߵ������ɡ�\n");
                command("addoil " + me->query("id"));
                return 1;
        }

        if ( me->query("combat_exp") >= 1500000 )
        {
                me->add("balance", 5000000);
                me->set("ty_gift", 1);
        }
        command("say �ðɣ��͸���һ����ʦ��ף���ɡ�\n");
        command("addoil " + me->query("id"));
        return 1;
}
int ask_new_pks()
{
        object me = this_player();
        

        if (me->query("ty_pks") )
        {
                command("say �㲻�Ѿ��Ƕ�����ô��\n");
                return 1;
        }
            if ((int)me->query_skill("jiuyin-baiguzhua",1) < 1)
        {
                command("say �㻹û�о������澭�¾���ѧ��\n");
                command("addoil " + me->query("id"));
                return 1;
        }

            if ((int)me->query_skill("jiuyin-baiguzhua",1) > 1 )
        {
                me->add("PKS", 50);
                me->set("ty_pks", 1);
        }
        command("say �ðɣ���ȥ������ȥ�ɡ�\n");
        command("sigh " + me->query("id"));
        return 1;
}
