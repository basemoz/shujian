// ��
#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_UNIQUE;
void create()
{
	set_name(HIW "�Ի�����" NOR, ({ "mihun shenzhen", "zhen", "needle", "shenzhen" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ö");
		set("long", "һö͸����ϸ�룬ɢ�����������޵�����������֮���ƺ���������ʧ���ġ�\n");
		set("value", 2000);
		set("rigidity", 10);
		set("sharpness", 10);
		set("material", "steel");
		set("unique", 2);
		set("needle", 1);
		set("weapon_prop/dodge", 2);
		set("wield_msg", "$N��ɳֽ����������һö$n��\n");
		set("unwield_msg", "$N��$n��ɰֽ���������ػػ��С�\n");		
		set("treasure", 1);
		set("poisoned", "miyao");
		set("poison_number", 500);
	}
	init_sword(45);
	setup();
}
