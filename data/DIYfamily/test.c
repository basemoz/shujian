//家族令牌 created by lsxk's program.
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIY"测试家族令牌"NOR, ({ "test ling","ling" }));
	set_weight(100);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","块");
		set("long",HIY"这是一块标志测试家族身份的令牌，你可以使用(fhelp ling)来查看详细信息!\n"NOR);
		set("fcolor","HIY");
		set("creatorID","lsxk");
		set("familyID","test");
		set("rank_num",3);
		set("rank/lvl0","老大");
		set("rank/lvl1","老二");
		set("rank/lvl2","老三");
		set("moto","测试啊测试");
	}
	setup();
}
