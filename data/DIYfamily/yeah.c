//�������� created by lsxk's program.
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"lsxkûjj��������"NOR, ({ "yeah ling","ling" }));
	set_weight(100);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIW"����һ���־lsxkûjj������ݵ����ƣ������ʹ��(fhelp ling)���鿴��ϸ��Ϣ!\n"NOR);
		set("fcolor","HIW");
		set("creatorID","spiderii");
		set("rank_num",3);
		set("rank/lvl0","����");
		set("rank/lvl1","��2�ȼ�");
		set("rank/lvl2","��3�ȼ�");
		set("moto","��lsxk");
	}
	setup();
}
