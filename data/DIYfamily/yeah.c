//家族令牌 created by lsxk's program.
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"lsxk没jj家族令牌"NOR, ({ "yeah ling","ling" }));
	set_weight(100);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","块");
		set("long",HIW"这是一块标志lsxk没jj家族身份的令牌，你可以使用(fhelp ling)来查看详细信息!\n"NOR);
		set("fcolor","HIW");
		set("creatorID","spiderii");
		set("rank_num",3);
		set("rank/lvl0","帮主");
		set("rank/lvl1","第2等级");
		set("rank/lvl2","第3等级");
		set("moto","打倒lsxk");
	}
	setup();
}
