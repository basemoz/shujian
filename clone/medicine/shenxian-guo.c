// rsg.c

#include <ansi.h>

inherit ITEM;

void init()
{
	if (environment() == this_player()) {
		add_action("do_eat", "eat");
		add_action("do_eat", "chi");
	}
}

void create()
{
	set_name(HIG "���ɹ�" NOR, ({"shenxian guo","guo"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"��˽������Թ��Ķ�������������һ���װ����ֵ�С�к���\n"
		"�лָ����������ӹ���������Ч����\n");
		set("value", 100);
		set("unit", "ö");
		//set("no_drop", 1);
        //set("unique", 2);
        //set("treasure", 1);
	}
}

int do_eat(string arg)
{
	object me = this_player();
	if (!id(arg)) return 0;
	message_vision(HIG "$N����һö"
	+name()+
	HIG "����ʱ���þ�����ʢ���������ٸе��ɿʼ�����\n"
	NOR,me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	me->reincarnate();

	//destruct(this_object());
	return 1;
}
