// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("穆人清",({"mu renqing", "mu", "renqing"}));
        set("nickname","神剑轩辕");
        set("long", "这就是在江湖中侠名远播，疾恶如仇，华山派神剑轩辕穆人清。\n");
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
        create_family("华山派",12,"弟子");

        setup();
        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "华山派"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
	if (ob->query("fengset")) {
		command("say 你不是已经拜了风清扬他老人家为师了么？");
		return;
	}
	        if(ob->query("quest/huashan")=="剑宗"){
                command("heng");
                command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
                return;
        }
	if (ob->query_skill("zixia-gong",1) < 100 ) {
		command("say 你的紫霞功修为太差，抓紧修炼吧。");
		return;
	}
        if ((int)ob->query("shen") <= 0) {
	        command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
	        command("say 在德行方面，" + RANK_D->query_respect(ob)+"是否还做得不够？");
	        return;
        }
        if ((int)ob->query("max_pot") < 230) {
	        command("say " + RANK_D->query_respect(ob)+"现在不需要我来指导，回去安心找你师傅学艺去吧。");
	        return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派气宗争口气。");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"华山派气宗亲传弟子"NOR);
        ob->set("quest/huashan","气宗");
}
