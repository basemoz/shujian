// NPC: /d/huashan/npc/cong_bq.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("从不弃",({"cong buqi", "cong", "buqi" }));
        set("title","华山派第十二代剑宗小弟子");
        set("nickname","恶剑客");
        set("long", "一个流里流气的市井小人，一双手格外粗大。\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_quest",1);

        set("max_qi",2500);
        set("qi", 2500);
        set("max_jing", 1400);
        set("jing",1400);
        set("eff_jingli", 1700);
        set("jingli", 1700);
        set("max_neili", 3500);
        set("neili", 3500);
        set("jiali", 50);
        set("combat_exp", 800000);
        set("score", 30000);

        set_skill("zhengqi-jue",  200);
        set_skill("sword",  140);
        set_skill("dodge",  140);
        set_skill("force",  140);
        set_skill("parry",  140);
        set_skill("huashan-qigong", 100);
        set_skill("huashan-jianfa",  160);
        set_skill("huashan-shenfa",  160);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");

        prepare_skill("strike","hunyuan-zhang");

        set("chat_chance_combat",40);
	set("chat_msg_combat", ({
		(: perform_action, "strike.wuji" :),
	}));

        create_family("华山派",13,"弟子");

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "华山派"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
                if(ob->query("quest/huashan")=="气宗"){
                command("heng");
                command("say 你不是华山气宗高徒么？怎么？来我们剑宗找死？");
                return;
        }

 //       if (ob->query_skill("huashan-qigong",1) < 100 ) {
 //               command("say 你的华山气功修为太差，抓紧修炼吧。");
 //               return;
 //       }
        if ((int)ob->query("shen") <= 0) {
                command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派剑宗争口气。");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"华山派剑宗亲传弟子"NOR);
        ob->set("quest/huashan","剑宗");

}

/*
void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

	if (interactive(ob) && !environment(ob)->query("no_fight")) {
		command("say 敢进入我剑宗禁地,只有死！！！\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}
*/