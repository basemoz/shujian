// passwd.c

// Modified by mxzhao 2004/02/18
// Modified by LinuX  2004/02/19

inherit F_CLEAN_UP;

#include <database.h>
#include <ansi.h>
#include <mudlib.h>
#include <login.h>

string seed = "1AaBb2CcDd3EeFf4GgHh5IiJj6KkLl7MmNn8OoPp9QqRr0SsTtUuVvWwXxYyZz";

string make_password()
{
	int i = 8, j;
	string id = "";

	while (i--)
	{
		j = random(62);
		id += seed[j..j];
	}

	return id;
}

string change_passwd(object ob)
{
	string new_pass;

	if( !ob )
	{
		return 0;
	}

	new_pass = make_password();

	if ( !ob->set("confirm_passwd", crypt(new_pass, "$1$ShuJian")))
	{
		return 0;
	}

	write(HIW"\n���" + ob->query("name") 
		+ "(" + ob->query("id") + ")��ȷ�������Ѿ����ġ�\n"NOR);
	
	return new_pass;
}

private void del_question(object me, string arg)
{
	mixed ret = dbquery("SELECT Question,Answer FROM Users "
		"WHERE U_Username="+save_variable(arg));
	
	if (!ret)
	{
		write("���ݿ�����ʧ�ܡ�\n");
		return;
	}
	
	if (sizeof(ret) == 0)
	{
		write("���ݿ���û�з��� "+arg+" �����ҡ�\n");
		return;
	}
	
	if (ret[0][0]=="")
	{
		write("��� "+arg +" û����������ʹ���,���ʲô��?!\n");
		return;
	}
	
	if (!dbquery("update Users set Question = \"" + "" 
		+ "\",Answer = \""+""+"\" where U_username=\""+arg+"\""))
	{
		write(HIY"���ݿ�����ʧ�ܡ�\n"NOR);
	}
	else
	{
		write("\n��� "+HIY+arg+NOR+" ����Ϸ�е�����ʹ��Ѿ���ա�\n");
	}	
}

private void get_question(object me, string arg)
{
	mixed ret = dbquery("SELECT Question,Answer FROM Users "
		"WHERE U_Username="+save_variable(arg));
	
	if (!ret)
	{
		write(HIY"���ݿ�����ʧ�ܡ�\n"NOR);
		return;
	}
	
	if (sizeof(ret) == 0)
	{
		write("���ݿ���û�з��� " + arg + " �����ҡ�\n");
		return;
	}
	
	if (ret[0][0]=="")
	{
		write("��� " + arg + " û����������ʹ���!\n");
	}
	else
	{		
		write ("��� " + arg + " ��Ϸ�е����⣺" + ret[0][0] + "\n");	
		write ("��� " + arg + " ��Ϸ�еĴ𰸣�" + ret[0][1] + "\n");	
	}
}

int main(object me, string arg)
{
	if (me != this_player(1))
	{
		return 0;
	}

/*	if (me->id("linux"))
	{
		string who;

		if (sscanf(arg, "%s -d", who) == 1)
		{
			del_question(me, who);
			return 1;
		}
		
		if (sscanf(arg, "%s -g", who) == 1)
		{
			get_question(me, who);
			return 1;
		}
	}
*/	
	if ( arg == "-change" )
	{
		write("E-mail��ַ�ı����\n");
		write(HBRED+HIY"ע�⣬�趨������ʹ����ò��ܸ��ģ���С�����ã�\n"NOR);
		write(HBRED+HIY"��ʦ�Ժ󲻻������Ҵ��Լ��������䣬����ؼ�ס���趨������ʹ𰸣�\n"NOR);
		write("Ϊ�˰�ȫ����������������ĵ�½���룺");

		input_to("get_pass", me, me->name(1) );
	}
	else 
	{
		if (arg == "-c")
		{
			write("��������ԭ����ȷ������(��δ������ֱ�Ӱ��س���)��");
		}
		else 
		{
			write("Ϊ�˰�ȫ����������������ĵ�½���룺");
		}
		
		input_to("get_old_pass", 1, me, arg);
	}

	return 1;
}

private void get_old_pass(string pass, object ob, string arg)
{
	mixed ret;
	if (arg == "-c")
	{
		string confirm_pass = ob->query("confirm_passwd");
		
		if (strlen(confirm_pass) == 0
			&& strlen(pass) > 0
			|| strlen(confirm_pass) > 0
			&& crypt(pass, confirm_pass) != confirm_pass)
		{
			write("��Ϸȷ���������\n");
			return;
		}
		
		write("�������µ�ȷ�����룺");

		input_to("get_new_pass", 1, ob, arg);
	}
	else
	{
		string old_pass = PASSWD_D->get_passwd(ob->query("id"));
		
		if (crypt(pass, old_pass)!=old_pass)
		{
			write("��Ϸ��½�������\n");
			return;
		}
		if ( arg == "-g")
		{
			string msg;
			string name = getuid(ob);
			
			seteuid(getuid());
			
			ret = dbquery("select U_Email, Question, Answer from Users "
				"where U_username=\""+ob->query("id")+"\"");
			
			if (!ret)
			{
				write("���ݿ�����ʧ�ܡ�\n");
				return;
			}
			
			if (sizeof(ret) != 1)
			{
				write("���ݿ����������⣬���������Ա��ϵ��\n");
				return;
			}
			msg =   "" + ob->query("name") + "(" + ob->query("id")+")" + "���ã�\n"
				"��ӭ����" + CHINESE_MUD_NAME + "��\n"
				"�����ʺ��޸��������ʾ�����ǣ�" + ret[0][1] + "\n"
				"���ǣ�" + ret[0][2] +"\n"
				"�޸�����󣬽��������Ʊ������Լ�����ʾ����ʹ𰸣����������������롣\n"
				"�������ڽ�����Ϸ���ʹ�á�help passwd��ָ��,��������Ϣ��\n"
				 + ctime(time()) + "\n";
			write("��ʼ���������޸���ʾ����ʹ��ż���" + ob->query("name") + "(" + ob->query("id") + ")��ǰ���䡣\n");
			SMTP_D->send_mail(ob, name, "" + CHINESE_MUD_NAME + "�����޸���ʾ����ʹ��ż�", msg);
			log_file("static/PASSWD", 
				sprintf("%s get the question from IP: %s ", 
				ob->query("id"),query_ip_number(this_player())));
			return;
				
		}	
		if ( arg == "-send" )
		{
			string new_pass;
			string msg;
			string name = getuid(ob);
			
			seteuid(getuid());
			
			if (!(new_pass = change_passwd(ob)))
			{
				write("ȡ���뷢��������֪ͨ������Ա����ʱ�޷������޸ġ�\n");
				return;
			}
			
			msg =   "" + ob->query("name") + "(" + ob->query("id")+")" + "���ã�\n"
				"��ӭ����" + CHINESE_MUD_NAME + "��\n"
				"����ȷ�������Ѿ�����Ϊ��\n\n" + new_pass + "\n\n"
				"��¼�ɹ��󣬽������� passwd -c ָ���������ȷ�����롣\n"
				"�������ڽ�����Ϸ���ʹ�á�help passwd��ָ��,��������Ϣ��\n"
				 + ctime(time()) + "\n";
			
			write("��ʼ����֪ͨ�ż���" + ob->query("name") + "(" + ob->query("id") + ")��ǰ���䡣\n");
			SMTP_D->send_mail(ob, name, "" + CHINESE_MUD_NAME + "����ȷ�������ż�", msg);
			return;
		}
		else
		{
			write("�������µ����룺");

			input_to("get_new_pass", 1, ob, arg);
		}
	}
}

private void get_new_pass(string pass, object ob, string arg)
{
	int i = strlen(pass);
	int j = 0;
	int k = 0;

	write("\n");

	if (pass == "")
	{
		write("�����޸ģ�����ʹ��ԭ���룡\n");
		return;
	}
	
	if (i < 5)
	{
		write("����ĳ��ȱ��벻С�������ĸ��\n�������������룺");
		input_to("get_new_pass", 1, ob, arg);
		return;
	}

	if (!LOGIN_D->query("md5") && i > 8)
	{
		write("����ĳ��ȱ��벻���ڰ˸���ĸ��\n�������������룺");
		input_to("get_new_pass", 1, ob, arg);
		return;
	}

	if (!wizardp(ob))
	{
		while(i--)
		{
			if( pass[i]>='0' && pass[i]<='9' )
			{
				j++;
			}
			
			if( pass[i]>='A' && pass[i]<='Z' )
			{
				k++;
			}
		}
		
		if (j < 1 || k < 1)
		{
			write("�Բ��������������������ֺ�Ӣ�Ĵ�д��ĸ��\n");
			write("�������������룺");
			input_to("get_new_pass", 1, ob, arg);
			return;
		}
	}

	if (arg == "-c")
	{
		write("��������һ���µ�ȷ�����룺");
	}
	else
	{
		write("��������һ���µ����룺");
	}

	input_to("confirm_new_pass", 1, ob, crypt(pass, "$1$ShuJian"), arg);
}

private void confirm_new_pass(string pass, object ob, string new_pass, string arg)
{
	if( crypt(pass, new_pass) != new_pass )
	{
		write("����������������벢����ͬ������ʹ��ԭ�������롣\n");
		return;
	}

	if ( arg == "-c")
	{
		ob->set("confirm_passwd", new_pass);
		write("ȷ���������ɹ���\n");
		ob->save();
		return;
	}

	if (!PASSWD_D->set_passwd(ob->query("id"), new_pass))
	{
		write("������ʧ�ܡ�����ʹ��ԭ���룡\n");
		return;
	}

	write("�������ɹ���\n");
}

private void get_pass(string pass, object ob, string name)
{
	string old_pass;
	mixed ret;
	
	old_pass = PASSWD_D->get_passwd(ob->query("id"));
	if( crypt(pass, old_pass)!=old_pass ) 
	{
		write("�������\n");
		return;
	}

	ret = dbquery("select U_Email, Question, Answer from Users "
		"where U_username=\""+ob->query("id")+"\"");
	
	if (!ret)
	{
		write("���ݿ�����ʧ�ܡ�\n");
		return;
	}
	
	if (sizeof(ret) != 1)
	{
		write("���ݿ����������⣬���������Ա��ϵ��\n");
		return;
	}
	
	ob->set("mail",ret[0][0]);
	
	write(HIG"\nE-mail�����������Լ��趨����ʹ𰸣�һ����Ҫ�Ķ��Լ���ע���ʼ���ַ��\n"
		"ϵͳ��ѯ�����趨�����⡣ֻ���������Ĵ𰸺��趨�Ĵ���ȫ��ͬ���ſ���\n"
		"��������ע���ʼ���ַ��\n");

	if( ret[0][1] != "" )
	{
		write(HIW"\n��ش�" YEL + ret[0][1] + NOR);
		write(HIW"\n��  ����"NOR);
		
		input_to("get_answer", ob ,ret[0]);
	} 
	else 
	{
		write(BLINK HIR"�ٴ����ѣ�ӵ�а�ȫ����𰸿�����ʱ�������ע�����䣡��\n"NOR 
			HIG"���磬��ȫ��������ǣ��Լ������֤�����Ƕ��٣�\n"
			"���趨���������֤���롣\n"
			"������Ҫ����Email��ַʱ��ϵͳ�ͻ�������ʾ��\n"
			HIW"��ش�ȫ�趨���⣺"YEL"�Լ������֤�����Ƕ��٣�\n"
			HIW"�𰸣�\n"
			HIG"��ʱ��������ȷ�Ĵ𰸡�һ������ȷ���Ϳ��Ը����Լ���ע��Email�ˡ�\n\n"NOR);
		
		write("�㻹û���趨�Լ���E-mail������ȫ���⣬\n��������Ҫ�趨�����⣺");

		input_to("new_question", ob );
	}
}

private void get_answer(string answer, object ob, mixed *res)
{
	string e_answer = res[2];
	if (answer != e_answer )
	{
		write("\n�𰸴�������������ٸ��ġ�\n");
		return;
	}

	write(HIG"\n����ȷ��\n"NOR"��Ŀǰ��ע���ַ�ǣ�"+ res[0] +"\n");
	write("����������������Email��ַ��");
	
	input_to("new_email", ob);
}

private void new_email(string email, object ob)
{
	string b_mail;
	int i;
	
	//string *forbid_email = ({
	//      "shujian.com","mymud.com","shujian.net"});
	
	if( !email || email == "" || email == " ")
	{
		write("�����趨���´���������Ч��"+HIG+"�����ַ"+NOR+"��\n");
		return;
	}

	if ( strlen(email) > 30 )
	{
		write("�Բ����ʼ���ַ���ܳ�����ʮ���ַ���\n");
		return;
	}
	
	if( !email || sscanf(email, "%*s@%*s.%*s") != 3 )
	{
		write("��������ĵ����ʼ���ַ��ʽ����\n");
		return;
	}

	sscanf(email,"%*s@%s",b_mail);

/*	if (member_array(b_mail,forbid_email) != -1 )
 {
		write("�Բ��𣬴������ֹ��Ϊע�����䡣\n");
		return;
	}
*/	
	for(i = 0;i < sizeof(email);i++)
	{
		if (email[i] == '\"') 
		{
			write("������󣬲��ܺ���\"�ַ���\n");
			return;
		}
	}
	
	write(HIW"ȷ����ȷ��[Y|N]"NOR);

	input_to("confirm_email", ob, email);
}

private void confirm_email(string arg, object ob, string email)
{
// Modified by mxzhao 2004/02/18
	string old_mail = ob->query("email");

	if( arg[0] != 'y' && arg[0] != 'Y' )
	{
		write("�ðɣ����´�������ٸ��ġ�\n");
		return;
	}
	
	seteuid(getuid());
	
	if (!dbquery("update Users set U_Email= \"" + email 
		+"\" where U_username=\""+ob->query("id")+"\""))
	{
		write(HIY"���ݿ���ϵ���ϣ���ʱ�޷��޸����䣬����������ʦ��ϵ��\n"NOR);
	}
	else
	{
		object link_ob;

		if( !ob->set("email", email) ) 
		{
			write("Email�趨ʧ�ܣ���֪ͨ��ʦ��\n");
			return;
		}
		
		if ( old_mail != email ) 
		{
			log_file("static/PASSWD", 
				sprintf("%s change email from %s to %s IP: %s ", 
				ob->query("id"),old_mail,email,query_ip_number(this_player())));
		}
		
		ob->save();

		link_ob = new(LOGIN_OB);

		if (link_ob)
		{
			link_ob->set("id", ob->query("id"));
			link_ob->restore();
			link_ob->set("email", email);
			link_ob->save();

			destruct(link_ob);
		}
		
		write(HIG"\n�ɹ��������ʼ���ַ�Ѿ�����Ϊ��"+ email +" \n"NOR);
	}
// End
}

private void new_question(string question, object ob)
{
	int i;
	
	if( !question || question == "" || question == " ")
	{
		write("�����趨���´���������Ч��"HIG"����"NOR"��\n");
		return;
	}
	
	if ( strlen(question) < 10 )
	{
		write("�Բ�������ĳ��Ȳ�������ʮ����ĸ��\n");
		return;
	}
	
	if ( strlen(question) > 40 )
	{
		write("�Բ�������ĳ��Ȳ��ܳ�����ʮ����ĸ��\n");
		return;
	}
	
	for(i = 0;i < sizeof(question);i++)
	{
		if (question[i] == '\"') 
		{
			write("������󣬲��ܺ���\"�ַ���\n");
			return;
		}
	}
	
	write("����������𰸣�ֱ�ӻس��������趨����");
	
	input_to("new_answer", ob, question);
}

private void new_answer(string answer, object ob, string question)
{
	int i;
	
	if( !answer || answer == "" || answer == " " )
	{
		write("�����޸ģ��´���������Ч��"HIG"��"NOR"��\n");
		return;
	}
	
	if ( strlen(answer) < 6 )
	{
		write("�Բ��𣬴𰸵ĳ��Ȳ�������������ĸ��\n");
		return;
	}
	
	if ( strlen(answer) > 40 )
	{
		write("�Բ��𣬴𰸵ĳ��Ȳ��ܳ�����ʮ����ĸ��\n");
		return;
	}
	
	for(i = 0;i < sizeof(answer);i++)
	{
		if (answer[i] == '\"')
		{
			write("������󣬲��ܺ���\"�ַ���\n");
			return;
		}
	}
	
	write("\n���趨�����ǣ�" YEL + question + NOR 
		"\n���ǣ�" YEL + answer + HIW "\n��ȷ��[Y|N]"NOR);

	input_to("confirm_change", ob, question, answer);
}

private void confirm_change(string arg, object ob, string question, string answer)
{
// Modified by mxzhao 2004/02/18
	if( arg[0] != 'y' && arg[0] != 'Y' )
	{
		write("����ȡ����\n");
		return;
	}

	seteuid(getuid());

	if (!dbquery("update Users set Question = \"" + question 
		+ "\",Answer = \""+answer+"\" where U_username=\""+ob->query("id")+"\""))
	{
		write(HIY"���ݿ���ϵ���ϣ���ʱ�޷��޸ģ�����������ʦ��ϵ��\n"NOR);
	}
	else
	{
		write(HIG"\n������ʺʹ𰸶��趨�ɹ���\n");
		log_file("static/PASSWD", 
			sprintf("%s set question and answer at %s  IP: %s ", 
			ob->query("id"),ctime(time()),query_ip_number(this_player())));

		write("��Ŀǰ��ע���ַ�ǣ�"+ ob->query("email") +"\n"NOR);
		write("����������������Email��ַ��ֱ�ӻس������趨����");
		input_to("new_email", ob);
	}
// End
}

int help(object me)
{
	write(@HELP
ָ���ʽ : passwd [-change]

���ָ������޸�����������롣

-change  ������ʾ��Ҫ�޸�ע�����䡣
-c       ���û��޸����ȷ�����롣
-send    �����µ�ȷ�����뵽���ע�����䡣
-g       ���������޸���ʾ����ʹ��ż������ע�����䡣

HELP

);
	return 1;
}

