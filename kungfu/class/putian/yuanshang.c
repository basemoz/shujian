// /kungfu/class/nshaolin/yuanshang.c
// looklove 2001.7.21

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("元伤尊者", ({
                "yuanshang zunzhe",
                "yuanshang",
                "zunzhe",
        }));
        set("long",
                "一位又矮又瘦的壮年僧人，脸上的表情似笑非笑。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 38);
        set("shen_type", 100);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 2000);
        set("neili", 6000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 500000);

        set_skill("force", 180);
        set_skill("yijin-jing", 180);
        set_skill("dodge", 180);
        set_skill("shaolin-shenfa", 180);
        set_skill("parry", 180);
        set_skill("claw", 180);
        set_skill("staff", 180);
        set_skill("finger", 180);
        set_skill("longzhua-gong", 180);
        set_skill("wuchang-zhang", 180);
        set_skill("yizhi-chan", 180);
        set_skill("medicine", 120);
        set_skill("buddhism", 200);
        set_skill("literate", 140);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "longzhua-gong");
        map_skill("finger", "yizhi-chan");
        map_skill("staff", "wuchang-zhang");
        map_skill("parry", "yizhi-chan");

        prepare_skill("claw", "longzhua-gong");
        prepare_skill("finger", "yizhi-chan");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "finger.qiankun" :),
		(: perform_action, "finger.wofo" :),
		(: perform_action, "claw.canyun" :),
	}));

        create_family("南少林", 23, "弟子");

        setup();

	carry_object("/d/shaolin/obj/chanzhang")->wield();
	carry_object("/d/shaolin/obj/cheng-cloth")->wear();
	carry_object("/d/shaolin/obj/sengxie")->wear();
}

