//�������� created by lsxk's program.
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIY"���Լ�������"NOR, ({ "test ling","ling" }));
	set_weight(100);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIY"����һ���־���Լ�����ݵ����ƣ������ʹ��(fhelp ling)���鿴��ϸ��Ϣ!\n"NOR);
		set("fcolor","HIY");
		set("creatorID","lsxk");
		set("familyID","test");
		set("rank_num",3);
		set("rank/lvl0","�ϴ�");
		set("rank/lvl1","�϶�");
		set("rank/lvl2","����");
		set("moto","���԰�����");
	}
	setup();
}
