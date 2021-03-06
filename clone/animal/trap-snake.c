// trap-snake by Darken@SJ
// Modify by Looklove@SJ
// Modify By River@SJ 2002.11

inherit NPC;
#include <ansi.h>
#include <pktime.h>
int do_target(string arg);
int do_pickup(string arg);

void create()
{
	set_name("小青蛇", ({ "qing she","she" }));
	set("race", "野兽");
	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );
	set("shen", 1);
	set("attitude", "peaceful");
	set("age", 1+ random(3));
	set("combat_exp", 1);
	set("no_get",1);
	set("max_qi",1);
	set("eff_qi",1);
	set("qi",1);
	set("max_jing",1);
	set("eff_jing",1);
	set("jing",1);
	set("max_jingli",1);
	set("eff_jingli",1);
	set("jingli",1);
	set("neili",1);
	set("jiali", 1);
	set("max_neili",1);
	set_skill("force",1);
	set_skill("dodge",1);
	set_skill("parry",1);
	set_skill("unarmed",1);
	set("chat_chance", 3);
	set("chat_msg", ({
		"小青蛇列成环型阵势，围在你周围。\n",
		"小青蛇爬过来，在你的腿边爬来爬去。\n",
		"小青蛇向着你，慢慢爬了过来。\n",
	}) );
	setup();
}

void init()
{
	object me,snake;

	me = this_player();
	snake = this_object();

	if (me->query("id") == query("target")
	 && userp(me)
	 && !environment(me)->query("no_fight")){
		if ( snake->query_leader() != me ) {
			snake->set_leader(me);
			message_vision("小青蛇决定和$N一起行动。\n",me);
			snake->add_busy(1);
			me->start_busy(1);
		}
		snake->kill_ob(me);
	}
	if (present(snake, environment(me)) && query("owner") == me->query("id")) {
		add_action("do_target","target");
		add_action("do_pickup","pickup");
	}
}


void kill_ob(object ob)
{
	object me;
	if(!ob) return;
	if(!stringp(query("owner")))
	{
		::kill_ob(ob);
		return;
	}
	me = find_player(query("owner"));
	if(!me)
	{
		::kill_ob(ob);
		return;
	}
	
	//洗手id 不可以杀
	if(userp(ob) && ob->query("no_pk"))
	{
		remove_killer(ob);
		remove_enemy(ob);
		ob->remove_enemy(this_object());
		ob->remove_killer(this_object());
		tell_object(ob,"你已经金盆洗手，还是不要介入江湖争斗吧！\n");
		return;
	}
	
	//pk time
	if(pktime_limit(ob, me))
	{
		remove_killer(ob);
		remove_enemy(ob);
		ob->remove_enemy(this_object());
		ob->remove_killer(this_object());
		return;		
	}
}

int hit_ob(object me, object victim, int damage)
{
	victim->add_condition("snake_poison", 8+random(6));
	return 0;
}

int do_target(string arg)
{
	object me, *ob, obj;
	int i,j,e;
	me=this_player();

	if (!arg || ! obj=(find_player(arg)))
		return notify_fail("你要对付谁？\n");
	if (present(arg))
		return notify_fail("你要对付的人就在旁边，不太好吧？\n");
	if (me->query("combat_exp") >= 5000000)
		return notify_fail("你这样的高手还要用这种下三滥的东西，不怕自贬身份，贻笑江湖吗？\n");

        if (userp(obj) && me->query("no_pk"))
                return notify_fail("你已经金盆洗手，还是不要介入江湖争斗吧！\n");

        if (userp(me) && obj->query("no_pk") && !obj->query_condition("pk"))
                return notify_fail(obj->name()+"已经金盆洗手，还是不要介入江湖争斗吧！\n");

        if (!wizardp(me))
                if(pktime_limit(me, obj)) return 0;

	if (environment(me)->query("no_fight"))
		return notify_fail("这里不适合组蛇阵。\n");

	message_vision(HIG"$N发出一些古怪的声音，对著蛇比手划脚。\n"NOR, me);
	j = (me->query("max_pot")-100) / 2 * 3;
	e = me->query("combat_exp") / 5 * 3;
	if (e > 1000000) e = 1000000+random(200000);
	if (j > 200) j = 200 + random(30);
	ob = all_inventory(environment(me));

	for (i=0;i<sizeof(ob);i++) {
		if (ob[i]->id("qing she") && ob[i]->query("owner")==me->query("id")) {
			if (ob[i]->is_fighting())
				return notify_fail("你的蛇正忙着呢，现在没空听你指挥。\n");
			if (!me->query_temp("other_kill/"+obj->query("id")) 
			|| ! obj->query_temp("kill_other/"+ me->query("id"))
			|| ! me->query_temp("revenge/"+ obj->query("id"))) {
				me->add_condition("killer", 15);
				obj->set_temp("other_kill/"+me->query("id"), 1);
			}
			ob[i]->set("target",arg);
			ob[i]->set("combat_exp", e);
			ob[i]->set("max_qi", me->query("max_qi"));
			ob[i]->set("max_jing", me->query("max_jing"));
			ob[i]->set("eff_jingli", me->query("eff_jingli"));
			ob[i]->set("max_neili", me->query("max_neili"));
			ob[i]->set("jiali", me->query("jiali"));
			ob[i]->set("str", me->query("str"));
			ob[i]->set("con", me->query("con"));
			ob[i]->set("dex", me->query("dex"));
			ob[i]->set("int", me->query("int"));
			ob[i]->set_skill("unarmed",j +random(50));
			ob[i]->set_skill("force",j + random(50));
			ob[i]->set_skill("dodge",j + random(50));
			ob[i]->set_skill("parry",j + random(50));
			ob[i]->reincarnate();
			ob[i]->set("long", "一条小青蛇，看起来是"+me->name(1)+"("+capitalize(me->query("id"))+")所驯养的。\n");
			call_out("check_place", 1, me, ob[i]);
		}
	}
	return 1;
}

void check_place(object me, object ob)
{
	if ( !ob ) return;
	if ( ob->query_leader()) return;
	if ( !ob->query("target")) return;
	if ( !me || environment(me) != environment(ob)){
		tell_room(environment(ob), ob->name() + "哧溜一声，钻入附近的草堆不见了。\n", ({ ob }));
		destruct(ob);
		return;
	}
	call_out("check_place", 1, me, ob);
}

int do_pickup(string arg)
{
	object me, *ob;
	int i;
	me=this_player();

	if(!arg || arg != "qing she")
		return notify_fail("请用pickup qing she指令拿起小青蛇。\n");

	if(!present(arg,environment(me)))
		return notify_fail("你要捡什么？\n");

	ob = all_inventory(environment(me));
	for (i=0;i<sizeof(ob);i++) {
		if (ob[i]->id("qing she") && ob[i]->query("owner")==me->query("id")) {
			ob[i]->move(me);
			ob[i]->delete("target");
			ob[i]->set_leader(0);
		}
	}
	message_vision(HIG"$N发出一些古怪的声音，蛇便乖乖的爬回$N身上。\n"NOR, me);
	return 1;
}

void unconcious()
{
	::die();
}
