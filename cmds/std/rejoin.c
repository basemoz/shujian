// rejoin.c	重出江湖
// by augx@sj 3/15/2002

#include <ansi.h>
inherit F_CLEAN_UP;

void abandon(object me)
{
	if( !me->query("prepare_rejoin") ) {
		tell_object(me,"你并没有重出江湖啊。\n");
		return;
	}
	me->delete("prepare_rejoin");
	tell_object(me,"你放弃了重出江湖。\n");
}
/*
if( me->query("no_pk") > 3000000 )
		exp = me->query("combat_exp") / 3;
	else
		exp = me->query("combat_exp") / 2;
*/

private void reward_player(object me)
{
	int cuted,exp;
	if(!me) return;
	
	cuted = 5 + me->query("rejoin_times")*10;
	if(cuted >=100) cuted = 95;
		
	exp = me->query("combat_exp") * cuted / 100;
	me->add("combat_exp",-exp);
	
	log_file("static/RETIRE",sprintf("重出江湖：%8s(%-8s) ；cut lit：%d",me->name(1),me->query("id"),cuted),me);
	log_file("static/RETIRE",sprintf("重出江湖：%8s(%-8s) ；cut exp：%d",me->name(1),me->query("id"),exp),me);
	
	if(me->query_skill("literate",1) <= cuted) me->delete_skill("literate");
	else me->set_skill("literate",me->query_skill("literate",1) - cuted );
	
	me->add("rejoin_times",1);
}

int main(object me, string arg)
{
	int exp;

	if( arg && arg=="abandon" ) {
		abandon(me);
		return 1;
	}
	if ( me->query("bxsj_bonus/no_pk") )
			return notify_fail("转站 ID 在15天后会自动解除金盆洗手状态。\n");

	if( !me->query("no_pk") )
		return notify_fail("你并没有金盆洗手啊。\n");

	if( me->query("prepare_rejoin") ) {
		if( (time()-me->query("prepare_rejoin_time")) < 604800 )
			return notify_fail("你重出江湖的时间还未到。\n");
		CHANNEL_D->do_channel(me,"chat",HIY"各位同道，我今日正式重出江湖，从此纵横武林，快意恩仇！"NOR);
		me->delete("prepare_rejoin");
		me->delete("prepare_rejoin_time");
		
		exp = me->query("combat_exp");
		
		reward_player(me);
		
		me->delete("no_pk");		
		me->setup();
		me->save();
		log_file("static/RETIRE",sprintf("重出江湖：%8s(%-8s) ；exp：%d(%d)",me->name(1),me->query("id"),me->query("combat_exp"),exp),me);
	}
	else {
		if( (time()-me->query("prepare_rejoin_time")) < 604800 )
			return notify_fail("你不是刚刚才放弃重出江湖吗？\n");
		CHANNEL_D->do_channel(me,"chat",HIY"各位同道，我不再甘于寂寞，决定在七日之后重出江湖，再次享受快意恩仇的日子！"NOR);
		me->set("prepare_rejoin",1);
		me->set("prepare_rejoin_time",time());
	}

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : rejoin

重新出山，参与江湖争斗。

如果你要重出江湖，在第一次输入此命令后，将有七天的缓冲期，
在七天之内你可以使用命令“rejoin abandon”来放弃重出江湖。
七天之后，请在此输入本命令，即可正式重出江湖。
注意：重出江湖将有一定的经验和读书写字等级 损失。

损失会和你重出江湖的次数有关。

其他相关指令: retire(金盆洗手)

HELP);
	return 1;
}

