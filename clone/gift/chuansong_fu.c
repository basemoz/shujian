// chuansong_fu.c

#include <ansi.h>

inherit ITEM;

void init()
{
	if (environment() == this_player()) {
		add_action("do_fly", "fly");
	}
}

void create()
{
	set_name(HIY "���ͷ�" NOR, ({"chuansong fu","fu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"һ�ŻƲӲӵķ�������ȥ��������������ɼ����������������ơ�\n"
		"������һ��������ƺ����Դ���ȥ�κεط���\n");
		set("value", 100);
		set("unit", "��");
	}
}

int do_fly(string arg)
{
	object me = this_player();
	string dest;

	switch (arg)
	{
		case "yz":
		case "yangzhou":
		case "����":
			dest = "/d/city/kedian";
			break;
		case "wg":
		case "wuguan":
		case "���":
			dest = "/d/wuguan/damen";
			break;
		default:
			dest = arg;
			break;
	}
	
	message_vision(HIG "$N��һ��"
	+name()+
	HIG "���������ϣ����������дʣ���Ȼһ������ӿ��$N��ʧ�����ˡ�\n"
	NOR,me);

	return me->move(dest);
}
