// yideng.c һ�ƴ�ʦ By River@SJ 2002.6.6

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("һ�ƴ�ʦ", ({ "yideng dashi", "yideng", "dashi" }) );
	set("title",HIW"�ϵ�"NOR);
	set("gender", "����" );
	set("class", "bonze");
	set("age", 78);
	set("str", 35);
	set("con", 40);
	set("dex", 35);
	set("int", 35);
	set("per", 28);
	set("unique", 1);

	set("max_qi", 12000);
	set("max_jing", 7500);
	set("eff_jingli", 8500);
	set("neili", 22000);
	set("max_neili", 22000);
	set("jiali", 150);
	set("combat_exp", 4900000);
	set("score", 20000);

	create_family("������", 12, "�׼ҵ���");

	set("long", "һ�����ֲ�ɮ�ۣ����������İ�ü���۽Ǵ�����������Ŀ���飬\n"+
		"ü����������࣬��һ��Ӻ�ݸ߻�����ɫ��ȴ��һ����֪��\n");

	set("combat_exp", 4900000);

	set_skill("parry", 400);
	set_skill("dodge", 380);
	set_skill("qingyan-zhang", 380);
	set_skill("strike", 380);
	set_skill("buddhism",200);
	set_skill("force", 400);
	set_skill("literate", 250);
	set_skill("sword", 180);
	set_skill("duanjia-jianfa", 380);
	set_skill("cuff", 200);
	set_skill("axe",200);
	set_skill("pangen-fu",380);
	set_skill("duanjia-quan", 400);
	set_skill("yiyang-zhi", 400);
	set_skill("finger", 400);
	set_skill("qiantian-yiyang", 400);
	set_skill("tianlong-xiang", 400);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
	set("inquiry", ([
		"here": "�������ʯ�ݡ�",
	]));

	setup();
	carry_object("/d/tls/obj/jiasha")->wear();
	carry_object("/d/tls/obj/sengxie")->wear();
}

void attempt_apprentice(object ob)
{
	if ( ob->query_skill("qiantian-yiyang",1) < 180 ){
		command ("hmm");
		command ("say ��Ǭ��һ�������֮��ҿɲ����㣡");
		return;
	}
	if( ob->query_int(1) < 34){
		command("say ��ѧ֮���������Ըߣ����ҿ�" + RANK_D->query_respect(ob) + "�������ƺ�������");
		return;
	}
	if(ob->query("shen") < 0){
		command("say ���������û��ң�����λ" + RANK_D->query_respect(ob) + "��¶�׹⣬�ҿ����ʺ����Ҵ������ȥ�ˡ�");
		return;
	}
	if(ob->query_skill("liumai-shenjian", 1)){
		command("say ��λ" + RANK_D->query_respect(ob) +"�Ѿ�ѧ���������񽣣������ʺϰ���Ϊʦ�ˡ�");
		return;
	}
/*
	if (ob->query("tls")) {
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
		return;
	}
*/
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
	command("recruit " + ob->query("id") );
	ob->delete("tls");
	ob->delete("class");
	ob->set("title",HIW"������ϵ۴���"NOR);
}
