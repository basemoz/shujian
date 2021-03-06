// name.c
// last modify by Look@SJ

// Modified by mxzhao 2004/02/18

inherit F_CLEAN_UP;

#include <ansi.h>
#include <mudlib.h>

int main(object me, string arg)
{
	string tmp;
	object ob = me;
	mixed ret;
//	mixed mysql;

	if( !arg )
		return notify_fail("你要给谁取什么名字？\n");

	if (sscanf(arg, "%s %s", tmp, arg) == 2) {
		if (arg == "noname")
			arg = "名字待定";
		ob = LOGIN_D->find_body(tmp);
	}

	if (!ob)
		return notify_fail("没有这个玩家。\n");

	if (wiz_level(me) < wiz_level(ob))
		return notify_fail("你不能帮巫师等级比你高的巫师改名。\n");

	if (strlen(arg) < 4)
		return notify_fail("这个名字太短了，想一个长一点的、响亮一点的。\n");

	if (strlen(arg) > 8)
		return notify_fail("这个名字太长了，想一个短一点的、响亮一点的。\n");

	ret = dbquery("select U_Name from Users where U_Name='" + arg + "'");

	if (!ret)
	{
		write("数据库连接失败。\n");
		return 0;
	}

	if (sizeof(ret) > 0 && arg !="名字待定")
	{
		write("此中文名已被其他人使用。\n");
		return 1;
	}

	if (!dbquery("update Users set "
		"U_Name='" + strip(arg) + "' "
		"where U_Username='" + ob->query("id") + "'"))
	{
		write("数据库连接失败。\n");
		return 1;
	}

	if (me != ob) 
	{
		write(HIY"你将"HIW+ob->name(1)+HIY"的名字改为"HIW+arg+HIY"。\n"NOR);
		tell_object(ob, HIY+me->name()+"将你的名字改为"HIW+arg+HIY"。\n" NOR);
	}
	else
	{
		write(HIY"你将自己的名字改为"HIW+arg+HIY"。\n"NOR);
	}

	ob->set("name", arg);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式: name [玩家] 名字

修改玩家或自己的名字，将从银行存款中扣除两百锭黄金的手续费。

HELP );
	return 1;
}
