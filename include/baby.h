#include <ansi.h>
#include <combat.h>

string status_color(int current, int max);

void init()
{
	object ob;
	ob = this_object();
	add_action("do_kill",({"kill","fight","hit","steal"}));
	add_action("do_get","get");
	add_action("do_drop","drop");
	add_action("do_shape","qk");
	add_action("do_cun","cundang");
	add_action("do_teach", "jiao");
}

string query_save_file()
{
	string id;

	id = query("momid");
	if( !stringp(id) ) return 0;
	return sprintf("/data/baby/%c/%s", id[0], id+".c");
}


int save()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
                return restore_object(file);
        return 0;
}

void die()
{	
	int i;
	object owner, *enemy;
	int jing,qi,exp;

	exp = (int) query("combat_exp");
	jing = (int) query("max_jing");
	qi = (int) query("max_qi");

	if(!environment()->query("no_death_penalty"))
		set("combat_exp", exp/10 * 9);
	set("eff_qi", qi);
	set("eff_jing", jing);
	set("qi", qi);
	set("jing", jing);

	save();	
	::die();
}

int do_drop(string arg)
{
	object me=this_object(),who=this_player(),env;
	if(!arg) return 0;
	env = environment(who);
	if(present(arg,who)!=me) return 0;
	if(me->move(env)) {
		message_vision("$N��$n�ӻ������������\n",who,me);
		return 1;
	}
	return 0;
}

int do_get(string arg)
{
	object me=this_object(), who=this_player(), env;

	if(!arg) return 0;
	env = environment(who);
	if(present(arg, env)!=me) return 0;
	if( who->query("id") == me->query("momid") || who->query("id") == me->query("popid") ) {
		if(me->move(who)) {
			message_vision("$N��������$n����������§�ڻ��\n",who,me);
		}
		else {
			message_vision("$N������һ��ȴû��$n��������С�һ�ó��ģ�\n",who,me);
		}
	}
	else {
		message_vision("$N������$n�쿪˫�֣�$nȴһ���������ˣ�����\n",who,me);
	}
	return 1;
}

int do_kill(string arg)
{       
	object me,who;
	string name,verb,what,obj;
	if (!arg) return 0;
	verb=query_verb();
	me=this_player();

	if(verb=="steal") {
		if(sscanf(arg, "%s from %s", what, obj)!=2 ) 
		return 0;
	}
	else obj=arg;

	if(!objectp(who=present(obj,environment(me))) || !living(who)) return 0;

	if(who==this_object()) {
		switch(verb) {
			case "kill":
				tell_object(environment(this_object()),
				who->query("name")+"ƴ���ؿ����������������������"+
				me->query("name")+"Ҫɱ�ң����������ѽ��\n");
				break;
			case "hit":
				tell_object(environment(this_object()),
				who->query("name")+"������������������������"+
				me->query("name")+"�۸��ң����������ѽ��\n");
				break;
			case "fight":
				tell_object(environment(this_object()),
				who->query("name")+"�����������������������"+
				me->query("name")+"Ҫ���ҵ��ǳԣ����������ѽ��\n");
				break;
			case "steal":
				tell_object(environment(this_object()),
				who->query("name")+"�����������������������"+
				me->query("name")+"Ҫ͵���ҵ��ǣ�\n");
				break;
			case "beg":
				tell_object(environment(this_object()),
				who->query("name")+"С��һ������������������������"+
				me->query("name")+"Ҫƭ�ҵ��ǳԣ�\n");
				break;
		}
	}
	command(verb);
	return 0;
}

void relay_emote(object ob, string verb)
{
	if( !userp(ob) ) return;

	switch(verb) {
		case "kick":
			command("say �������������"  + ob->query("name") + "����Ү��");
			command("kick " + ob->query("id"));
			break;
		case "slap":
			command("say �������������"  + ob->query("name") + "����Ү����ʹ����������");
			command("slap " + ob->query("id"));
			break;
		case "hit":
			command("pain " + ob->query("id"));
			break;
		case "bite":
			command("face " + ob->query("id"));
			break;  
		case "papaya":
			command("angry");
			break;
	}
}

void relay_whisper(object me, string msg)
{
	if (member_array(me->query("id"), query("parents"))==-1) {
		message_vision((string)this_object()->query("name") + "�ɻ�ؿ���$N��\n", me);
		return;
	}

	//note, do not allow the order contain "chat", "tell"...
	//may need disable more later...
	if( strsrch(msg, "chat") != -1 || strsrch(msg, "tell") != -1 || strsrch(msg, "follow") != -1 ||
		strsrch(msg, "apprentice") != -1 || strsrch(msg, "recruit") != -1 )
		return;
	if (msg) {
		remove_call_out ("relaying");
		call_out ("relaying", 1+random(3), msg);
	}
}

void relaying (string msg)
{
	//execute the order.
	command (msg);
}

string status_color(int current, int max)
{
	int percent;

	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}

int do_shape(string arg)
{
	mapping my;
	string shape;
	int at_pt, pa_pt, do_pt;
	my = query_entire_dbase();
	printf(NOR"����������������������������������������������������������������\n"NOR);
	printf("��"HIY"������%s%6d/%6d %s(%3d%%)"NOR,status_color(my["jing"],my["eff_jing"]),my["jing"],
		my["eff_jing"],status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"]);
	printf(HIY"  ��������%s%6d/%6d %s(%3d%%)  "NOR"��\n",status_color(my["jingli"], my["eff_jingli"]), my["jingli"],
		my["eff_jingli"], status_color(my["jingli"], my["eff_jingli"]),   my["jingli"] * 100 / my["eff_jingli"] );
	printf("��"HIY"����Ѫ��%s%6d/%6d %s(%3d%%)"NOR,status_color(my["qi"],my["eff_qi"]),my["qi"],my["eff_qi"],
		status_color(my["eff_qi"],my["max_qi"]),my["eff_qi"]*100/my["max_qi"]);
	printf(HIY"  ��������%s%6d/%6d (+%3d)  "NOR"��\n",status_color(my["neili"], my["max_neili"]), my["neili"], 
		my["max_neili"],my["jiali"]);
	printf("�����ף� "HIW"%-13s"NOR"ĸ�ף� "HIC"%-13s"NOR"���䣺 %-12s ��\n",
		my["pop"], my["mom"], chinese_number(my["age"])+"��");
	printf("�����ǣ� %d/%-10d���ʣ� %d/%-10d��̬�� %d/%-9d ��\n", query_int(), my["int"], query_con(), 
		my["con"], query_per(), my["per"]);
	printf("���ٶȣ� %d/%-10d������ %d/%-10d���ԣ� %d/%-9d ��\n", query_dex(), my["dex"], query_str(),
		my["str"], query_kar(), my["kar"]);
	printf("�������� %-13d���ԣ� %-13d���飺 "HIR"%-12d"NOR" ��\n", my["obe"], my["tol"], my["combat_exp"]);
	at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
	pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
	do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
	printf("���������� "WHT"%-21d"NOR"�������� "WHT"%-21d"NOR"��\n"NOR, at_pt+1, pa_pt/2+do_pt/2+1);
	printf(NOR"����������������������������������������������������������������\n"NOR);
	return 1;
}

int do_cun(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();

        if ( me->is_busy() )
                return notify_fail("����һ��������û����ɣ�\n");

        if ( me->is_fighting() )
                return notify_fail("�㻹��ר����ս�ɣ�\n");

 	if ( ! (me->query("id") == ob->query("momid") || me->query("id") == ob->query("popid")) )
		return notify_fail("ʲô��\n");

	if ( ob->query_temp("saved"))
		return notify_fail("���������к�ϵͳӲ�̽��������Ժ����ԡ�\n");
//        ob->set_temp("saved", 1);
	ob->save();
	ob->start_call_out( (: call_other, me, "delete_temp", "saved" :), 60 + random(60));

	write("���ӵ�����Ѿ�������ϡ�\n");
	return 1;
}


int do_teach(string arg)
{
	object me, ob;
	int gin_cost,amount, myskill, itskill;
	string student, skill;

	me = this_player();
	ob = this_object();

        if ( me->is_busy()) return notify_fail("��������æ���ء�\n");

        if ( me->is_fighting() ) return notify_fail("�㲻����ս���н���֪ʶ��\n");

	if ( ob->is_busy() ) return notify_fail("���������޷�����������\n");

	if ( !arg || (sscanf(arg, "%s about %s", student, skill) != 2) )
		return notify_fail("ָ���ʽ��jiao <ĳ��> about <����>\n");

	if ( student != ob->query("id") ) return notify_fail("��Ҫ��˭��\n");

	if ( !myskill = me->query_skill(skill, 1)) return notify_fail("���������󻹲����أ�\n");

	if ( me->query("id") != ob->query("momid") && me->query("id") != ob->query("popid") )
		return notify_fail ("�Լ��ĺ����Լ��̣��㲻�õ����������\n");

	if ( !living(ob) ) return notify_fail("��....����Ȱ�" + ob->name() + "Ū����˵��\n");

	if ( ! ob->query("is_baby") ) return notify_fail("�˼�Ҳ��ʦ�����е��������̣�\n");

	itskill = ob->query_skill(skill, 1);

	if(myskill <= itskill) return notify_fail( ob->name()+"�Գ�Ц��Ŀ�������㡣\n");

	if( (int)me->query("potential") < 1 ) return notify_fail("���Ǳ�ܲ�����\n");

	gin_cost = (int)ob->query_int();

	if( (int)me->query("jing") < gin_cost) return notify_fail("����Ȼ̫����û�а취�̣�\n");

	me->receive_damage("jing", gin_cost);
//	me->add("potential",-1);
	amount = (int)me->query("int") + (int)ob->query("int");

	message_vision(sprintf("$N�����䷳�ؽ�$n��%s����\n", to_chinese(skill)), me, ob);

	if( (int)ob->query_temp("is_hungry") > 30+random(5) || ob->query("is_hungry") ) {
		ob->set("is_hungry", 1);
		ob->delete_temp("is_hungry");
		return notify_fail ("���Ӵ�޴��֣������Ƕ���\n");
	}
	if( random(30) > ob->query("tol") ) {
		if (ob->query("age") < 5)
			message_vision("$n���۵ش��������$N˵ʲôҲ�岻ס��\n", me, ob);
		else
			message_vision("$n��޴��֣�˵ʲôҲ����$N����\n", me, ob);
	}
	else {
		ob->add_skill(skill, amount);
//		ob->improve_skill(skill, amount);
		ob->add( "combat_exp", amount/20+random(amount/20) );
		message_vision(sprintf("$N�ƺ����ѧ����һЩ��%s����\n", to_chinese(skill)), ob);
		me->add("combat_exp", 30);
		me->start_busy(random(2)+1);
		ob->start_busy(1);
		ob->add_temp("is_hungry", 1);
	}
	return 1;
}

varargs void add_skill(string skill, int amount)
{
	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) ) skills = ([]);
	if( undefinedp(skills[skill]) ) skills[skill] = 0;

	if( !amount ) amount = 1;

	if( !mapp(learned) ) learned = ([ skill : amount ]);
	else (int)learned[skill] += amount;

	if( learned[skill] > (skills[skill] + 1) * (skills[skill] + 1) ) {
		skills[skill]++;
		learned[skill] = 0;
		this_object()->set_skill(skill, skills[skill]+1);
	}
}

int accept_object(object me, object obj)
{
object ob;
	ob = this_object();
	if ( me->query("id") != ob->query("momid") && me->query("id") != ob->query("popid") )
		return notify_fail ("�˼Ҹ�ĸ���չ��Լ��ĺ�������\n");
/*
	if( ! obj->wear() )  {
		command("cry");
                return 0;
	}
*/
        call_out ("baby_wear", 1, me, obj);
        return 1;
}

void baby_wear(object me, object obj)
{
	message_vision(sprintf("$N���Լ��ĺ��Ӵ���һ%s%s��\n", obj->query("unit"), obj->query("name")), me);
	obj->move(this_object());
	obj->wear();
}
