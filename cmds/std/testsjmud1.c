#include "ansi.h"

#define SJMUD_SEMI			""	//0x1���ڷָͬ���ݽ�
#define SJMUD_DOT				""	//0x2���ڷָ����ݽ��еĲ�ͬ�ֶ�
#define SJMUD_BEGIN1_CODE	""	//0x2
#define SJMUD_END_CODE	""		//0x4

#define SJMUD_BEGIN1 SAVEC+BLK+SJMUD_SEMI+SJMUD_BEGIN1_CODE	//
#define SJMUD_END SJMUD_SEMI+SJMUD_END_CODE+REST+NOR				//

int main(object me, string arg)
{
//	write(SAVEC+BLK+"xky is ok----"+REST+NOR+"xkysisok\n");
	write(SJMUD_BEGIN1+"1hahahahahaha2"+SJMUD_END+"xkysisok\n");
	return 1;
}
