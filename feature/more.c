// more.c

#include <ansi.h>
#define LINES_PER_PAGE		40
static string *text;
static int size;
static int width;

private void more(string cmd, int line)
{
	int i;

	write(REST+ESC+"[K");
	switch(cmd) {
		case "q":
			write("\n");
			return;
		case "b":
			line -= LINES_PER_PAGE * 2;
			if (line < 1) line = 1;
		default:
			for (i=line + LINES_PER_PAGE; line <= size && line < i; line++) {
				if (size > LINES_PER_PAGE)
					write(sprintf("%*d:", width, line));
				write(sprintf(" %s\n", text[line-1]));
			}
			if (line > size) return;
	}
	write(sprintf(SAVEC+"== 还剩 "HIY"%*d"NOR" 行 == (ENTER 继续下一页，q 离开，b 前一页)"+ESC+"[A",
		width, size - line + 1)
	);
	input_to((:more:), 0, line);
}

void start_more(string msg)
{
	if (!stringp(msg)) return;
	write("\n"+SAVEC);
	text = explode(msg, "\n");
	size = sizeof(text);
	width = strlen(size+"");
	more("", 1);
}
