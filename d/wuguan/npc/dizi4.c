//dizi4.c ��� by river

#include <ansi.h>
inherit NPC;
int ask_wuguan();
int ask_liguan();
int ask_xuexi1();

void create()
{
	set_name("���", ({ "sun jun","sun","jun", "man" }));
	set("title", "��������ĵ���");
	set("gender", "����");
	set("age", 21);
	set("long", "��������ɽ���ĵ��ӣ���ò�Ͱ���һ�쵽��Ц�Ǻǵġ�\n");
	set("combat_exp", 5000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("unique", 1);

	set_skill("force", 50);
	set_skill("strike", 50);
	set_skill("sword", 50);
	set_skill("shenzhao-jing",50);
	map_skill("force", "shenzhao-jing");

	set("inquiry", ([
		"����ɽ" : "�����˼����ҵĶ�ʦ����",
		"���" : (:ask_liguan:),
		"���" : (:ask_wuguan:),
		"�������" :(:ask_wuguan:),
		"ѧϰ" : (:ask_xuexi1:),
	]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ( ob ->query("combat_exp") < 500 && ob->query_temp("jobask") == 1){
		command("bow "+ob->query("id"));
		command("say ��λ" + RANK_D->query_respect(ob) +",����� "HIY HBCYN"ask sun about ѧϰ"CYN" �������˽���ݵ������"NOR);
		
	}
}

int ask_xuexi1()
{
	object ob = this_player();
	if( ob->query_temp("jobask") == 1 ) {
		command("say �㲻���Ĵ�����"HIY HBCYN"look"CYN"��������ʲô�����㶼���Լ�����"HIY HBCYN"get"CYN"���š�\n"+
		"������Ȳ��"HIY HBCYN"i or inventory"CYN"����������������Щʲô����Ҫ��ʱ�ز��"HIY HBCYN"hp\n"+
		CYN"�������״̬��Ҫ�Ƕ��˻���˾�ȥ��Щ�Եĺȵİɡ���Ҫ����ʲô�����\n"+
		"�����ҡ�"HIY HBCYN"ask sun about ������ݣ�ask sun about ���"CYN"��\n"+
		"���ڸ���ָ��ľ����÷����Բο� "HIY HBCYN"help commands"CYN"��"NOR);
		ob->delete_temp("jobask");
		if(ob->query_temp("jobover") != 1) {
			ob->set_temp("jobover", 1);
			command("say ��˵�����ֵ��е��������㣬�����ȥ��һ�¡�"NOR);
			if ( ob->query("combat_exp") < 100) {
				ob->add("potential", 20);
				ob->add("combat_exp",100);
				tell_object(ob,HIW"����������Ľ��⣬������һ�ٵ�ʵս����Ͷ�ʮ��Ǳ�ܣ��Խ����ֶ���һ���˽⡣\n"NOR);
			}
		}
		return 1;
	}
	if ( ob->query_temp("jobover") == 1) {
		command("say �Ҳ��Ƕ�����˵��ô�������ֵ��������㣬��ȥ���°ɡ�");
		return 1;
	}
}

int ask_wuguan()
{
	object ob = this_player();
	if (ob ->query("combat_exp") < 1000){
		command("say  �������������ʦ���������֡�����ɽ�����˼�һ�ֽ����ģ�����\n"+
		"������Ŀ�ľ����ڸ�һЩ���뽭��������һЩ������ʵ���Ļ��ᡣ����������\n"+
		"���� "HIY HBCYN"help wuguan"CYN" �� "HIY HBCYN"help map_wuguan"CYN"��"NOR);
		return 1;
	}
	else{
		command("kick "+ ob->query("id"));
		command("say �������ô��ʱ���ˣ����ڸ��𰡣��Լ���Ϥȥ�ɣ�\n");
		return 1;
	}
}

int ask_liguan()
{
	object book, ob = this_player();
	if (!ob->query("enter_wuguan")){
		command("congra "+ob->query("id"));
		command("say ��λ" + RANK_D->query_respect(ob)+"���Գ�ȥ���������ˣ������ն񣬿�ǧ��С�İ���������\n"+
		"�͵�����ݣ���������Գ˳����������ɣ�����ݾ��������ˡ�");
		ob->set_temp("marks/���", 1);
		if (!ob->query_temp("have_xymap") && ob->query("max_neili") < 100 ) {
			new("/d/xiangyang/obj/map_book")->move(ob);
			book = new(MEDICINE_D("neili/yujiwan"));
			book->set("owner", ob->query("id"));
			book->move(ob);
			ob->set_temp("have_xymap", 1);
			command("say �Ҷ�ʦ�����ߴ����������꣬�����п������һ��������ͼ�����������ã���ȥ�ɡ�");
			message_vision("$N�ݸ�$nһ��"+HIW+"����"+NOR+"��һ��"+HIC+"������ͼ��"+NOR+"��\n", this_object(), ob);
		}
		return 1;
	}
	else{
		command("hmm "+ob->query("id"));
		command("say ��λ" + RANK_D->query_respect(ob)+"û�й�����ͬ�⣬�ҿɲ������������뿪��ݡ�");
		return 1;
	}
}
