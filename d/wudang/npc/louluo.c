// NPC : /d/wudang/npc/louluo.c 喽罗

inherit NPC;

void create()
{
        set_name("小喽罗", ({"xiao louluo", "louluo"}) );
        set("gender", "男性" );
        set("age", 18);
        set("long", "这是一个年纪不大的小喽罗，神情让人讨厌。\n");

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set("combat_exp", 10);
		set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","aggressive");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 10);
}
