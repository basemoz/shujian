#include "ansi.h"

#define SJMUD_SEMI			""	//0x1用于分割不同数据节
#define SJMUD_DOT				""	//0x2用于分割数据节中的不同字段
#define SJMUD_BEGIN1_CODE	""	//0x2
#define SJMUD_END_CODE	""		//0x4

#define SJMUD_BEGIN1 SAVEC+BLK+SJMUD_SEMI+SJMUD_BEGIN1_CODE	//
#define SJMUD_END SJMUD_SEMI+SJMUD_END_CODE+REST+NOR				//

int main(object me, string arg)
{
	string *option,outstr;
	int i,isize;
	
	if( !arg ) 
		return notify_fail("你没有带任何参数。\n");
	
	option = explode(arg, " ");
	option -= ({ "" });
	isize = sizeof(option);
	outstr=SJMUD_BEGIN1;
	for (i=0;i<isize;i++)
	{
		outstr+=option[i]+SJMUD_DOT;
	};
	write(outstr+SJMUD_END+"这是一个测试\n");
	return 1;
}


int help(object me)
{
  write(@HELP
指令格式 : ？？？
 
这个指令用于测试sjmud前端.
HELP
    );
    return 1;
}
