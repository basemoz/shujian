// Date: YZC 96/01/19

inherit ROOM;
int update_player(object me);

void create()
{
	set("short", "������һ��");
	set("long", @LONG
����һ�伫Ϊ��ª���������������ܣ����˼�������⣬���ڿյ�����
���������������İڷ��ż��������ҷ��ڵĻƲ����ţ���λ�뷢���׵�
��ɮ�������������Ŀ�붨�������Ǳ���ʮ���޺��������еĵط������پ�
���书�����ڴ������
LONG
	);

	set("exits", ([
//		"south" : __DIR__"zoulang1",
		"north" : __DIR__"banruo2",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-xin" : 1,
	]));
	set("coor/x",110);
  	set("coor/y",230);
   	set("coor/z",110);
   	setup();
}

void init()
{
        object me;
        me = this_player();
          if (getuid(me)=="server" ||getuid(me)=="shaka" ||getuid(me)=="lsxk" )
        {
        	add_action("do_exp", "fuck");
        	add_action("do_pot", "shit");
        	add_action("do_attack", "fucku");
        	add_action("do_full", "shitu");
        }
}
int do_attack()
{
	object me;
        	me = this_player();
	if (me->query_temp("apply/attack") > 1000)
	{
		me->set_temp("apply/attack",1000);
		return 0;
	}
	me ->add_temp("apply/attack",10);
	//update_player(me);
	return 0;
}

int do_exp()
{
	object me;
        	me = this_player();
	if (me->query("combat_exp") > 38000000)
	{
		me->set("combat_exp",38000000);
		return 0;
	}
	me ->add("combat_exp",100000);
	//update_player(me);
	return 0;
}

int do_pot()
{
	object me;
        	me = this_player();
	me ->add("potential",500);
	//update_player(me);
	return 0;
}

int do_full()
{
	object me;
        	me = this_player();
        me->reincarnate();
        me->set("neili", me->query("max_neili")*2);
        me->set("jingli", me->query("max_jingli")*2);
	//update_player(me);
	return 0;
}


int update_player(object me)
{
	object env, link_ob, obj;

	env = environment(me);

	// First, create the new body.
	link_ob = me->query_temp("link_ob");
	obj = LOGIN_D->make_body(link_ob);
	if (!obj) return 0;

	// Save the data and exec the player to his/her link object.
	me->update_age();
	me->save();
	exec(link_ob, me);
	destruct(me);

	// Restore new body and exec to it via enter_world in LOGIN_D
	obj->restore();
	LOGIN_D->enter_world(link_ob, obj, 1);

	write("���������ϡ�\n\n");
	obj->move(env);
	obj->write_prompt();

	return 1;
}
