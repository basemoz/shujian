// edit.c Yuj@SJ 20000212
#include <ansi.h>

int edit(function callback)
{
	write("结束离开用 "HIY"."NOR" 取消输入用 "HIY"q\n"NOR);
	write(repeat_string("—", 39) + "\n1: ");
	input_to("input_line", "", callback, 1);
	return 1;
}

void input_line(string line, string text, function callback, int ln)
{
	if( line=="." ) {
		if (this_object()->query_temp("big5")) text = "/adm/daemons/gb_b5d"->b5_gb(text);
		(*callback)(text);
		return;
	}
	if( line=="q" ) {
		write("输入取消。\n");
		return;
	}
	if (strlen(line) > 100) write(HIY + "请将每行文字控制在 100 个英文或 50 个汉字以内。\n" NOR);
	else {
		text += line + "\n";
		ln++;
	}
	if (strlen(text) > 15000 || ln > 150) {
		write(HIY + "已经写了很长了，系统自动终止，未写完的请另外再写。\n" NOR);
		if (this_object()->query_temp("big5")) text = "/adm/daemons/gb_b5d"->b5_gb(text+"(未完待续)......\n");
		(*callback)(text);
		return;
	}
	if (strlen(text) > 10000 || ln > 100) write(HIY + "请长话短说或者另外续写。\n" NOR);
	write(CSI"5D" + ln + ": ");
	input_to((: input_line :), text, callback, ln);
}
