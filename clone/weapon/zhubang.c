// zhubang.c 竹棒

#include <weapon.h>
inherit STICK;

void create()
{
        set_name("竹棒", ({ "zhu bang", "zhubang", "bang" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "这是一根发黄的竹棒，入手沉甸甸的，似乎相当结实。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中掂了掂。\n");
                set("unwield_msg", "$N将手中的$n轻轻别回腰间。\n");
        }
        init_stick(20);
        setup();
}

