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

	if ( !arg ) return notify_fail ("ʲô��\n");

	if ( me->is_busy()) return notify_fail ("����æ���ء�\n");

	if ( me->is_exert()) return notify_fail ("������ʹ��"+me->query_exert()+"��\n");

	if ( me->is_perform()) return notify_fail ("������ʹ��"+me->query_perform()+"��\n");

	if ( ! objectp(ob = present(arg, environment(me))) || !living(ob)) return notify_fail ("��Ҫ��˭������\n");

	if ( me->is_fighting() || ob->is_fighting() ) return notify_fail ("���żܸ����˽�������ѽ��\n");

	if ( (int)me->query_skill("linchuang", 1) < 100 ) return notify_fail ("����ٴ�ҽ���ȼ��������޷���������������\n");

	if ( ob->query("gender") != "Ů��" ) return notify_fail ("����ֻ��Ů����������������ܡ�\n");

	if ( ob == me ) return notify_fail ("���Լ������������Űɣ�\n");

//	if ( ! ob->query("baby/born") ) return notify_fail ( ob->name() + "��û�л��С�\n" );

	if ( ! ob->query_condition("pregnant") ) return notify_fail ( ob->name() + "��û�л��С�\n" );

	if ( ! ob->query_condition("pregnant") > 50 )
		return notify_fail ("������" + ob->name() + "�����\n");

	if ( ! place->query("sleep_room") )
		return notify_fail ("����ڴ�ͥ����֮�¸�" + ob->name() + "������\n");

	if ( sizeof(obj) > 2 ) return notify_fail ("�㻹���Ȱ������˵����ȥ�ɡ�\n");

	msg = HIG "$N�ó�һ���ײ���׼��Ϊ$n������\n" NOR;
	message_vision(msg, me, ob);
	tell_object (ob, GRN + me->name() + "����˵��������ȫ����ɣ���Ҫ���š�\n"NOR);
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
	message_vision(HIY"\n$n���Ǵ����죬һֱ���ں������أ�˫�ֽ�����ס$N���ֲ��š�\n" +
		"\nӤ���Ѿ�̽����ͷ������\n"NOR, me, ob);
	call_out("birth2", 20, me, ob);
	return 1;
}

void birth2(object me, object ob)
{
	object baby;
	int number, b_int, b_con, b_dex, b_per, b_str, b_obe, b_tol;
	string msg;

	message_vision(HIY"\n���ۡ�����Ӥ�������ˣ�\n$n��ɫ�԰ף�б���ڴ�ͷ���������������¶��һ˿΢Ц��\n"NOR, me, ob);
	me->start_busy(1);
	ob->start_busy(1);
	ob->set("neili", 0);
	ob->set("qi", 0);
	ob->set("jing", 0);
	ob->add("child", 1);
	number = ob->query("child");

	baby = new("/cmds/usr/baby");
	if ( ob->query("preg/id") == ob->query("marry/id") ) {
		baby->set("long", baby->query("long") + "����" + ob->query("name") + "��" + 
			ob->query("marry/name") + "�ĺ��ӡ�\n" +
			ob->query("name") + "�ĵ�" + chinese_number(number) + "�����ӡ�\n");
		baby->set("pop", ob->query("marry/name") );
		baby->set("popid", ob->query("marry/id") );
	}
	else {
		baby->set("long", baby->query("long") + "����" + ob->query("name") + "��" + 
			ob->query("preg/name") + "��˽���ӡ�\n" +
			ob->query("name") + "�ĵ�" + chinese_number(number) + "�����ӡ�\n");
		baby->set("pop", ob->query("preg/name") );
		baby->set("popid", ob->query("preg/id") );
	}
	if (random(10) < 5) {
		baby->set("gender","����");
		baby->set_name("С" + ob->query("preg/name"), ({"xiao " + ob->query("preg/id"), "baby"}));
		baby->set("baby_title", "��Ӥ");
	}
	else {
		baby->set("gender","Ů��");
		baby->set_name("С" + ob->query("name"), ({"xiao " + ob->query("id"), "baby"}));
		baby->set("baby_title", "ŮӤ");
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
	tell_object(me, GRN"���Ѿ�������" + me->query("jiesheng") + "��Ӥ����\n"NOR);
	msg = "���������š�" + ob->query("name") + WHT"��" + me->query("name") + WHT"�İ�����˳������һ��" +
		baby->query("baby_title") + "��\n";
	message("channel:chat", WHT+msg+NOR, users());

	if(!baby->move(environment(me)))
	baby->move(environment(environment(me)));
}
