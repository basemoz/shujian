// test.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if (me->id("linux"))
	{
		if (!arg) return notify_fail("ָ���ʽ��lupdate <�ļ���>\n");
		"/cmds/common/jiami.c"->main(me,arg);
		"/cmds/imm/update.c"->main(me,arg);
		write("���ܣ�����ɹ���\n");
	}

	return 1;

}