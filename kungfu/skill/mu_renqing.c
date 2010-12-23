// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("������",({"mu renqing", "mu", "renqing"}));
        set("nickname","����ԯ");
        set("long", "������ڽ���������Զ����������𣬻�ɽ������ԯ�����塣\n");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 9000);
        set("max_jing", 7800);
        set("eff_jingli", 7500);
        set("max_neili", 16000);
        set("neili", 16500);
        set("jiali", 100);
        set("combat_exp", 4200000);
        set("score", 29000);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
        	(: perform_action, "cuff.leidong" :),
        }));
        set_skill("sword",  350);
        set_skill("dodge",  350);
        set_skill("force",  360);
        set_skill("cuff", 350);
        set_skill("poyu-quan", 340);
        set_skill("huashan-jianfa", 350);
        set_skill("parry",  360);
        set_skill("literate", 230);
        set_skill("zixia-gong", 350);
        set_skill("huashan-shenfa", 350);
        set_skill("zhengqi-jue", 200);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("cuff","poyu-quan");
        map_skill("parry","huashan-jianfa");
        map_skill("sword","huashan-jianfa");
        prepare_skill("cuff", "poyu-quan");

	set_temp("apply/damage", 80);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 80);
        create_family("��ɽ��",12,"����");

        setup();
        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "��ɽ��"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
	if (ob->query("fengset")) {
		command("say �㲻���Ѿ����˷����������˼�Ϊʦ��ô��");
		return;
	}
	        if(ob->query("quest/huashan")=="����"){
                command("heng");
                command("say �ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��");
                return;
        }
	if (ob->query_skill("zixia-gong",1) < 100 ) {
		command("say �����ϼ����Ϊ̫�ץ�������ɡ�");
		return;
	}
        if ((int)ob->query("shen") <= 0) {
	        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
	        command("say �ڵ��з��棬" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
	        return;
        }
        if ((int)ob->query("max_pot") < 230) {
	        command("say " + RANK_D->query_respect(ob)+"���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
	        return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ��������������");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"��ɽ�������״�����"NOR);
        ob->set("quest/huashan","����");
}
