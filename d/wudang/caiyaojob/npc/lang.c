// wolfdog.c

inherit NPC;

void create()
{
set_name("野狗", ({ "lang gou", "gou" }) );
	set("race", "野兽");
	set("age", 4);
	set("long", "一只灰色的狼，两只眼睛泛着绿光。\n");
        set("attitude", "aggressive");
	
	set("str", 26);
	set("cor", 30);

	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 1000);
	set("chat_msg_combat", ({
		(: this_object(), "random_move" :),
		"野狼警惕的注视着四周！\n",
		 
	}) );
		
	set_temp("apply/attack", 15);
	set_temp("apply/damage", 6);
	set_temp("apply/armor", 2);

	setup();
}

void init()
{
	object ob;
	::init();
	if (living(this_object()) && interactive(ob = this_player()) &&
		random(ob->query_kar() + ob->query_per()) < 30) {
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob); 
	}	
}

void die()
{
	object ob;
	message_vision("\n$N惨嚎一声，死了！\n", this_object());
	ob = new(__DIR__"obj/goupi");
	ob->move(environment(this_object()));
	destruct(this_object());
}
