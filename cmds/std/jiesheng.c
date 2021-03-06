// /cmds/skill/jiesheng.c
// by akuma 3:54 PM 2/18/2002

#include <ansi.h>
#include <mudlib.h>
inherit F_CLEAN_UP;

int main ( object me, string arg )
{
	int jl, jl2, ji, q;
	object ob, ob2, place, *obj;
	string msg;

	obj = all_inventory(environment(me));
	place = environment(me);

	if ( !arg ) return notify_fail ("什么？\n");

	if ( me->is_busy()) return notify_fail ("你正忙着呢。\n");

	if ( me->is_exert()) return notify_fail ("你正在使用"+me->query_exert()+"。\n");

	if ( me->is_perform()) return notify_fail ("你正在使用"+me->query_perform()+"。\n");

	if ( ! objectp(ob = present(arg, environment(me))) || !living(ob)) return notify_fail ("你要给谁接生？\n");

	if ( me->is_fighting() || ob->is_fighting() ) return notify_fail ("打着架给别人接生？酷呀！\n");

	if ( (int)me->query_skill("linchuang", 1) < 100 ) return notify_fail ("你的临床医术等级不够，无法从事这样工作。\n");

	if ( ob->query("gender") != "女性" ) return notify_fail ("好像只有女孩子有生孩子这项技能。\n");

	if ( ob == me ) return notify_fail ("给自己接生？够不着吧？\n");

//	if ( ! ob->query("baby/born") ) return notify_fail ( ob->name() + "并没有怀孕。\n" );

	if ( ! ob->query_condition("pregnant") ) return notify_fail ( ob->name() + "并没有怀孕。\n" );

	if ( ! ob->query_condition("pregnant") > 50 )
		return notify_fail ("你想让" + ob->name() + "早产吗？\n");

	if ( ! place->query("sleep_room") )
		return notify_fail ("你就在大庭广众之下给" + ob->name() + "接生？\n");

	if ( sizeof(obj) > 2 ) return notify_fail ("你还是先把闲杂人等请出去吧。\n");

	msg = HIG "$N拿出一叠白布，准备为$n接生。\n" NOR;
	message_vision(msg, me, ob);
	tell_object (ob, GRN + me->name() + "对你说：现在先全身放松，不要紧张。\n"NOR);
	me->start_busy(100);
	ob->start_busy(100);
	jl = ob->query("max_jingli") * 2 / 3;
	jl2 = ob->query("max_jingli") * 3 / 4;
	ji = ob->query("max_jing") * 2 / 3;
	q = ob->query("max_qi") / 2;
	ob->add("jingli", -jl);
	ob->add("jing", -ji);
	ob->add("qi", -q);
	me->add("jingli", -jl2);
	ob->clear_condition("pregnant");
	call_out("birth1", 20, me, ob);
	return 1;
}


int birth1(object me, object ob)
{
	message_vision(HIY"\n$n已是大汗淋漓，一直都在呼天抢地，双手紧紧扣住$N的手不放。\n" +
		"\n婴儿已经探出了头．．．\n"NOR, me, ob);
	call_out("birth2", 20, me, ob);
	return 1;
}

void birth2(object me, object ob)
{
	object baby;
	int number, b_int, b_con, b_dex, b_per, b_str, b_obe, b_tol;
	string msg;

	message_vision(HIY"\n「哇」……婴儿出世了！\n$n面色苍白，斜倚在床头，看看孩子满意地露出一丝微笑。\n"NOR, me, ob);
	me->start_busy(1);
	ob->start_busy(1);
	ob->set("neili", 0);
	ob->set("qi", 0);
	ob->set("jing", 0);
	ob->add("child", 1);
	number = ob->query("child");

	baby = new("/cmds/usr/baby");
	if ( ob->query("preg/id") == ob->query("marry/id") ) {
		baby->set("long", baby->query("long") + "这是" + ob->query("name") + "和" + 
			ob->query("marry/name") + "的孩子。\n" +
			ob->query("name") + "的第" + chinese_number(number) + "个孩子。\n");
		baby->set("pop", ob->query("marry/name") );
		baby->set("popid", ob->query("marry/id") );
	}
	else {
		baby->set("long", baby->query("long") + "这是" + ob->query("name") + "和" + 
			ob->query("preg/name") + "的私生子。\n" +
			ob->query("name") + "的第" + chinese_number(number) + "个孩子。\n");
		baby->set("pop", ob->query("preg/name") );
		baby->set("popid", ob->query("preg/id") );
	}
	if (random(10) < 5) {
		baby->set("gender","男性");
		baby->set_name("小" + ob->query("preg/name"), ({"xiao " + ob->query("preg/id"), "baby"}));
		baby->set("baby_title", "男婴");
	}
	else {
		baby->set("gender","女性");
		baby->set_name("小" + ob->query("name"), ({"xiao " + ob->query("id"), "baby"}));
		baby->set("baby_title", "女婴");
	}
	baby->set("mom", ob->query("name") );
	baby->set("momid", ob->query("id") );

	b_int = ( ob->query("int") + ob->query("preg/int") ) / 2;
	if ( random(10) > 5 ) b_int = ( ob->query("int") + b_int ) / 2;
	else b_int = ( ob->query("preg/int") + b_int ) / 2;

	b_con = ( ob->query("con") + ob->query("preg/con") ) / 2;
	if ( random(10) > 5 ) b_con = ( ob->query("con") + b_con ) / 2;
	else b_con = ( ob->query("preg/con") + b_con ) / 2;

	b_dex = ( ob->query("dex") + ob->query("preg/dex") ) / 2;
	if ( random(10) > 5 ) b_dex = ( ob->query("dex") + b_dex ) / 2;
	else b_dex = ( ob->query("preg/dex") + b_dex ) / 2;

	b_str = ( ob->query("str") + ob->query("preg/str") ) / 2;
	if ( random(10) > 5 ) b_str = ( ob->query("str") + b_str ) / 2;
	else b_str = ( ob->query("preg/str") + b_str ) / 2;

	b_per = ( ob->query("per") + ob->query("preg/per") ) / 2;
	if ( random(10) > 5 ) b_per = ( ob->query("per") + b_per ) / 2;
	else b_per = ( ob->query("preg/per") + b_per ) / 2;

	b_obe = ( ob->query("int") + ob->query("preg/int") + ob->query("pur") + ob->query("preg/pur") ) / 4;
	if ( random(10) > 5 ) b_obe = ( ob->query("pur") + b_obe ) / 2;
	else b_obe = ( ob->query("preg/pur") + b_obe ) / 2;

	b_tol = ( ob->query("kar") + ob->query("preg/kar") + ob->query("pur") + ob->query("preg/pur") ) / 4;
	if ( random(10) > 5 ) b_tol = ( ob->query("pur") + b_tol ) / 2;
	else b_tol = ( ob->query("preg/pur") + b_tol ) / 2;

	baby->set("int", b_int);
	baby->set("con", b_con);
	baby->set("dex", b_dex);
	baby->set("str", b_str);
	baby->set("str", b_per);
	baby->set("obe", b_obe);
	baby->set("tol", b_tol);
	baby->set("mom_age", ob->query("age"));
	ob->set("baby_on", 1);
	ob->save();
	me->add("jiesheng", 1);
	tell_object(me, GRN"你已经接生了" + me->query("jiesheng") + "个婴儿。\n"NOR);
	msg = "【江湖传闻】" + ob->query("name") + WHT"在" + me->query("name") + WHT"的帮助下顺利产下一名" +
		baby->query("baby_title") + "。\n";
	message("channel:chat", WHT+msg+NOR, users());

	if(!baby->move(environment(me)))
	baby->move(environment(environment(me)));
}
