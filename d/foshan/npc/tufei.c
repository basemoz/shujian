// tufei1.c
// Lklv update 2001.9.26

inherit NPC;

void create()
{
	set_name("土匪", ({ "tu fei", "tufei", "bandit","fei" }) );
	set("gender", "男性");
	set("age", 30);
	set("long", "这家伙满脸横肉一付凶神恶煞的模样，令人望而生畏。\n");

	set("combat_exp", 10000+random(30000));
        set("shen_type", -1);

	set("apply/attack", 20);
	set("apply/defense", 20);

	set_skill("unarmed", 40);
	set_skill("sword", 20);
	set_skill("parry", 40);
	set_skill("dodge", 40);

	setup();

        carry_object(BINGQI_D("duanjian"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", 20);
}
