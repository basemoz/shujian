#include "ansi.h"

#define SJMUD_SEMI			""	//0x1���ڷָͬ���ݽ�
#define SJMUD_DOT				""	//0x2���ڷָ����ݽ��еĲ�ͬ�ֶ�
#define SJMUD_BEGIN1_CODE	""	//0x2
#define SJMUD_END_CODE	""		//0x4

#define SJMUD_BEGIN1 SAVEC+BLK+SJMUD_SEMI+SJMUD_BEGIN1_CODE	//
#define SJMUD_END SJMUD_SEMI+SJMUD_END_CODE+REST+NOR				//

int main(object me, string arg)
{
	string *option,outstr;
	int i,isize;
	
	if( !arg ) 
		return notify_fail("��û�д��κβ�����\n");
	
	option = explode(arg, " ");
	option -= ({ "" });
	isize = sizeof(option);
	outstr=SJMUD_BEGIN1;
	for (i=0;i<isize;i++)
	{
		outstr+=option[i]+SJMUD_DOT;
	};
	write(outstr+SJMUD_END+"����һ������\n");
	return 1;
}


int help(object me)
{
  write(@HELP
ָ���ʽ : ������
 
���ָ�����ڲ���sjmudǰ��.
HELP
    );
    return 1;
}
