// test.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if (me->id("linux"))
	{
		if (!arg) return notify_fail("指令格式：lupdate <文件名>\n");
		"/cmds/common/jiami.c"->main(me,arg);
		"/cmds/imm/update.c"->main(me,arg);
		write("加密，编译成功！\n");
	}

	return 1;

}