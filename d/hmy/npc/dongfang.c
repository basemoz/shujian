// dongfang.c ��������
// By River@SJ For kuihua-baodian Quest 2003.1.11

inherit NPC;

inherit F_MASTER;

#include <ansi.h>

string ask_me();
void create()
{
	object ob;
	set_name("��������", ({ "dongfang bubai", "dongfang", "bubai"}));
	set("long", "����������֮��һλ���춯�أ��������Ĺֽܡ�\n"+
		"�˿�������˺��룬���Ͼ�Ȼʩ��֬�ۣ������Ǽ�����ʽ���в��У�Ů��Ů��\n"+
		"��ɫ֮�����㴩����Ů���ϣ�Ҳ�Ե�̫���ޡ�̫������Щ��\n");

	set("title",HIY"������̽���"NOR);         
	set("nickname", HIR"�ճ����� Ψ�Ҳ���"NOR);
	set("gender", "����");
	set("age", 54);
	set("attitude", "friendly");
	set("str", 35);
	set("int", 45);
	set("con", 45);
	set("dex", 45);
	set("per", 28);
	set("class", "eunuch");
	set("unique", 1);

	set("max_qi", 15000);
	set("max_jing", 10500);
	set("eff_jingli", 8000);
	set("max_neili", 23000);
	set("neili", 23000);
	set("jiali", 200);
	set("combat_exp", 5600000);
	set("shen", -50000);

	set_skill("sword", 380); 
	set_skill("parry", 380);
	set_skill("dodge", 380);
	set_skill("claw", 380);
	set_skill("force", 380);
	set_skill("pixie-jian", 380);        
	set_skill("youming-zhao", 380);
	set_skill("literate", 280);
	set_skill("kuihua-shengong", 380);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("dodge", "pixie-jian");
	map_skill("claw", "youming-zhao");
	map_skill("force", "kuihua-shengong");
	prepare_skill("claw", "youming-zhao");

	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
//		(: exert_function, "yinyun" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.feiying" :),
	}));

	set_temp("apply/damage", 50);
	set_temp("apply/dodge", 120);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 170);
	set_temp("��ڤ", 1);

	set("inquiry", ([
		"��������": (: ask_me :),
	]));

	setup();

	if (clonep()) {
		ob = unew(BOOK_D("kuihua"));
		if (!ob) ob = new("/clone/money/gold");
		ob->move(this_object());
		carry_object(BINGQI_D("xiuhua"))->wield();
		carry_object(ARMOR_D("xiupao2"))->wear();
	}
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BOOK_D("kuihua"))))
		ob->move(this_object());
}

string ask_me()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( is_busy() || is_fighting())
	 	return "��û��������æ��ô��";

	if ( me->query("gender") == "Ů��")
		return "�����Һ���һ������ΪŮ�����Ǿͺ��ˡ�";

	if ( me->query("int") < 20 )
		return "������Բ��������������䡹���ʺ�����ϰ��";

	if ( me->query("dex") < 15 )
		return "���������䡹����������Ų֮���������ʵ��̫���ˡ�";

	if ( me->query("combat_exp", 1) < 5000000)
		return "���ʵս���黹���������������䡹�����ʺ���������";

	if ( present("kuihua baodian", me))
		return "�ף����������䡹������������ô��������������";

	ob = present("kuihua baodian", this_object());

	if ( ! ob)
		return "Ү�����������䡹���ҷŵ�����ȥ�ˣ�";

	time = time() - me->query("quest/pixie/pxj_time");
	if ( me->query("quest/pixie/pxj_time") && time < 86400 && !wizardp(me))
	 	return "�����ں�æ��û��Ȥ��������¡�";

	quest = me->query("quest/pixie");

	if ( ! quest || ! quest["pxj_passwd"])
		return "���������˵�����������䡹�ģ�";

	if ( quest["pass"] ) {
		if ( ob ) {
			ob->set("owner", me);
			ob->move(me);
			return "�ðɣ��Ȿ���������䡹���û�ȥ�ú��о��о���";
		}
		else
			return "��Ҫ�ġ��������䡹�Ѿ������������ˡ�";
	}

	i = me->query("combat_exp", 1) - 4500000;
	i /= 500000;

	if ( me->query("registered")< 3 && quest["fail"] >= 3)
	 	return "�����ں�æ��û��Ȥ��������£�";

	if ( quest["fail"] >= i )
	 	return "�����ں�æ��û��Ȥ��������£�";

	me->set_temp("pxj_quest", 1);
	kill_ob(me);
	me->kill_ob(this_object());
	return "��ƾ����"+RANK_D->query_rude(me)+"Ҳ���������ҵġ��������䡹��";
}

void die()
{
	object me = query_temp("last_damage_from");
	object ob = present("kuihua baodian", this_object());

	if ( ob ) {
		if ( objectp(me) 
		&& me->query_temp("pxj_quest")
		&& random(me->query_int(1)) > 30 
		&& random(me->query_dex(1)) > 35
		&& random(me->query_kar()) > 15 ) {
			message_vision("\n", me);
			command("say ����������Ҳ������Ե֮�ˣ��Ȿ���������䡹�ͽ�����ɡ�");
			log_file("quest/pixie",
				sprintf(HIR"%-18sʧ��%-2d�κ󣬻�á��������䡹����%d����%d������%d��"NOR,
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/pixie/fail"),
					me->query_int(1), 
					me->query_dex(1), 
					me->query_kar()
				), me
			);
			me->set("quest/pixie/pass", 1);
			me->delete("quest/pixie/pxj_time");
			me->delete_temp("pxj_quest");
			ob->set("owner", me);
			ob->move(me);
		}
		else {
			message_vision(CYN"\n$Nŭ�е�������ʹ�����ˣ����Ҳ����õ����������䡹����������������\n"NOR, this_object());
			message_vision("$N���ǡ��������䡹����˫����һ�꣬����������һ��ԭ��ʮ�ֳ¾ɵĲ�ҳ��ʱ������Ƭ��\n\n", this_object());
			if ( objectp(me) && me->query_temp("pxj_quest")) {
				me->add("quest/pixie/fail", 1);
				me->set("quest/pixie/pxj_time", time());
				me->delete_temp("pxj_quest");
				log_file("quest/pixie", 
					sprintf("%-18s��ͼ��á��������䡹��ʧ��%-2d�Σ���%d����%d������%d��\n",
						me->name(1)+"("+capitalize(getuid(me))+")", 
						me->query("quest/pixie/fail"),
						me->query_int(1), 
						me->query_dex(1), 
						me->query_kar()
					), me
				);
			}
			ob->set("name", HIW"�����������Ƭ"NOR);
			ob->move(environment(this_object()));
		}
	}
	::die();
}

void unconcious()
{
	die();
}
                                                                                              
