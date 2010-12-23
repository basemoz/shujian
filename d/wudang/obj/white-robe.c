// white-robe.c 白色道袍
// By Marz

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("白色道袍", ({"pao", "cloth", "dao pao"}) );
    set_weight(4500);
    if( clonep() )
       set_default_object(__FILE__);
    else {
        set("unit", "件");
		set("long", "这是件裁减合体的白色道袍，虽然样式简单，但穿在身上，却
能衬托出一种仙风道骨之气。\n");
        set("material", "cloth");
        set("armor_prop/armor", 10);
    }
    setup();
}
