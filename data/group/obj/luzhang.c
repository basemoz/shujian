#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("路障", ({ "lu zhang" }) );
	set_weight(3000);
	if( clonep() ) {
		call_out("set", 600, "no_get", 0);
		set_default_object(__FILE__);
	} else {
		set("unit", "个");
        set("long", @LONG
    这是一个路障，通常用来在抢劫的时候拦住过往的行人。如果你不
愿意冒险，可以花钱买路(mailu)，要是没有足够的钱，那就只能夺路
而逃了(duolu <方向>)。如果你运气不错，碰上抢劫的人心情好，也许
会放你一马(fang)。
LONG
		);
		set("value", 1000);
		set("material", "wood");
		set("no_get",1);
		set("location",1);
	}
	setup();
}

void init()
{
	object rob;
	object me=this_player();
	object ob=this_object();

	if( !ob->query("robber") ) return;
	
	if (!userp(me) || wizardp(me) || me->query("combat_exp")<100000) return;
    
	if(!objectp(rob = present(ob->query("robber"), environment(ob))) && interactive(me) ) {
		message_vision( HIC "$N惊讶地“哦”了一声：“谁在这里放了一个路障？我把它拆了吧。”\n" NOR, me );
		call_out("remove_luzhang",0,ob );
		return;
    	}
    
    	if( me->query("g_name") == rob->query("g_name") 
    	&& me->query("g_type") == rob->query("g_type") 
    	&& me->query("id") != rob->query("id"))
    	return;

	if( userp(me) && me->query("id") != rob->query("id") 	
		&& !me->query_temp("g_robbed"))
		message_vision( HIR "$N“托”地跳了出来，横刀当道，对着$n一声大喊："
			+ "此路是我开，此树是我栽，若要从此过，留下买路财！\n" NOR, rob,me );

	me->set_leader(0);

	add_action("do_mailu", "mailu");
	add_action("do_duolu", "duolu");
	add_action("do_fang", "fang");
	add_action("do_action", "");
}

int do_mailu( string arg )
{
	object me = this_player(), ob1,ob3,ob4,ob5;
	object ob = this_object();
	int i;

	if( me->query("id") == ob->query("robber") ) return 0;

	if(!objectp(ob1 = present(query("robber"), environment(me)))) return notify_fail( "这里没有收你的买路钱的人。\n" );
	if( !living(ob1) ) return notify_fail( "你等" + ob1->query("name") + "醒了再说吧。\n" );

	i = me->query("combat_exp") / 200000 + 1;
    	ob3 = present( "gold", me );
    	if(!ob3)
        	return notify_fail( "你身上没有黄金。\n" );
    	if( ob3 -> query_amount() < i )
        	return notify_fail( "你身上没有这么多的黄金。\n" );

    	ob3->set_amount( ob3->query_amount() - i );
    	ob4 = present( "gold", ob1 );
    	if( !ob4 )
    	{
    	ob5 = new( "/clone/money/gold" );
		ob5->set_amount( i );
        ob5->move( ob1 );
    	}
    	else
    	{
        ob4->set_amount( ob4->query_amount() + i );
    	}
     
    	message_vision( sprintf( "$N给$n一些黄金。\n" ), me, ob1 );
	message_vision( HIC "$N在$n的屁股上狠狠地踢了一脚，大笑道：算你这"
		+ RANK_D->query_rude( me )
		+ "识相，"
		+ RANK_D->query_self_rude( ob1 )
		+ "今天就放你一马。\n" NOR, ob1, me );
	me->set_temp("g_robbed",1);
	ob1->add_condition("killer", 6);
	return 1;
}

int do_duolu( string arg )
{
	object me = this_player(), ob1;
	object  env = environment( me );
	mapping exits;
	object ob = this_object();

	if( me->query("id") == ob->query("robber") ) return 0;

	if( !arg || arg == "" )
		return notify_fail( "你要往哪个方向跑？\n" );

    	if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return notify_fail( "直接走就可以了，不用和别人拼命。\n" );
    	if( !living(ob1) ) 
        	return notify_fail( "直接走就可以了，不用和别人拼命。\n" );

	if( me->is_busy() )
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("你还是等打完了架再说吧。\n");

	exits = env->query("exits");

   	if( mapp(exits) )
    	{
    	if( !exits[arg] )
    	{
    		return notify_fail( "这个方向没有出路。\n" );
    		return 1;
    	}
   
	}
	
	message_vision( HIC "$N大叫一声“挡我者死！”，奋力向前夺路逃去。\n" NOR, me );
	if( random( me->query("combat_exp") ) > ob1->query("combat_exp")/4 || random(10) < 2)
	{
		message_vision( HIC "$N见$n来势凶猛，不禁往后一退，$n趁势冲了过去。\n" NOR, ob1,me);
		"/cmds/std/go" -> main( me, arg );
		return 1;
	}
	else
	{
		message_vision( HIC "$N一把抓住$n，“想跑，没这么容易。”\n" NOR, ob1,me);
		message_vision( HIR "“" + ob1->query("name")
			+ "，"
			+ RANK_D->query_self_rude( me )
			+ "我今天跟你拼了！”\n" NOR, me );
		me->fight_ob( ob1 );
		me->start_busy(1);
		return 1;
	}
	
	return 0;
}

int do_fang( string arg )
{
	object me = this_player(), ob1;
	object ob = this_object();

	if( !ob )
		return 0;
	if( me->query("id") != ob->query("robber") )
	{
		return 0;
	}

	if( !arg || arg == "" )
		return notify_fail( "你要放谁走路？\n" );
			
    	if (!ob1 = find_living(arg)) ob1 = LOGIN_D->find_body(arg);
    	if (!ob1) 
    		return notify_fail(""+ arg + "现在不在这里。\n");
        
    	if(!objectp(ob1 = present(arg, environment(me))) )
       		return notify_fail(""+ arg + "现在不在这里。\n");
    	if( !living(ob1) ) 
        	return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
        
    	if( arg == me->query("id") )
    		return notify_fail( "你没有毛病吧？\n" );

	if( ob1->query_temp("g_robbed") )
		return notify_fail( "这个人不需要你放行。\n" );
		
	if( ob1->query("combat_exp") <= me->query("combat_exp") )
	{
		message_vision( HIC "$N在$n的屁股上狠狠地踢了一脚，大笑道：算你这"
			+ RANK_D->query_rude( ob1 )
			+ "走运，碰上"
			+ RANK_D->query_self_rude( me )
			+ "心情好，今天就放你一马。\n" NOR, me, ob1 );
		ob1->set_temp("g_robbed",1);
		return 1;
	}
	else
	{
		message_vision( HIC "$N一下子吓得跪在地上：“我是混蛋，我有罪！我是混蛋，我有罪！”\n" NOR, me );
		message_vision( HIC "“小的有眼不识泰山，" + ob1->query("name" ) 
			+ "您大人不记小人过，您请，您请。”\n" NOR, me, ob1 );
		message_vision( HIC "$N卯足了劲煽自己耳光，跟大伙说：快来煽我，不煽白不煽。”\n" NOR, me, ob1 );
		message_vision( HIR "$n“啪啪”两个嘴巴，$N顿时痛的昏了过去。。。\n" NOR, me,ob1 );
	    	me->unconcious();
		ob1->set_temp("g_robbed",1);
		return 1;
	}
	
	return 0;
}


int remove_luzhang( object ob )
{
	if(!ob ) 
		return 1;
		
	destruct( ob );
	return 1;
}


int do_action(string arg)
{
	object me = this_player(), ob1;
	string action = query_verb();
	mapping exits = environment()->query("exits");
	string *dir=({});
	
	if (sizeof(exits)) dir = keys(exits);
	if( member_array(action,dir) != -1 ||
		( action == "go" && member_array(arg,dir) != -1 ) )
	{
		if( me->query("id") == query("robber") )
		{
			write( "你正在抢劫，不能离开。\n");
			return 1;
		}
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;
	        
		if( me->query("combat_exp")<100000)
			return 0;	        
	    if( me->query("g_name") == ob1->query("g_name") 
	    	&& me->query("g_type") == ob1->query("g_type") )
	    	return 0;

		write( ob1->query("name") + "一把把你拦住：小子，交了买路钱再走。\n" );
		return 1;
	}
	
	switch( action )
	{
	case "follow":
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;

		if( me->query("id") == query("robber") )
		{
			write( "想跑？可没有这么容易。\n" );
			return 1;
		}
		
		if( me->query("g_name") == ob1->query("g_name")
			&& me->query("g_type") == ob1->query("g_type") )
			return 0;

		write( "你还是先应付了面前的抢劫再说吧。\n" );
		return 1;
		break;	
	case "dazuo":
	case "tuna":
	case "respirate":
	case "exercise":
	case "practice":
		if( me->query_temp("g_robbed") )
			return 0;
	    if(!objectp(ob1 = present(query("robber"), environment(me))) )
        	return 0;
	    if( !living(ob1) ) 
	        return 0;
		if( me->query("id") == query("robber") )
			return 0;
		if( me->query("combat_exp")<100000)
			return 0;
		if( me->query("g_name") == ob1->query("g_name")
			&& me->query("g_type") == ob1->query("g_type") )
			return 0;

		write( "你还是先应付了面前的抢劫再说吧。\n" );
		return 1;
		break;
	}
	
	return 0;
}
