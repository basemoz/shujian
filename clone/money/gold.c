// gold.c

#include <ansi.h>

inherit MONEY;

void create()
{
	set_name(HIY "黄金" NOR, ({"gold", "gold_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "gold");
                set("long", "黄澄澄的金子，人见人爱的金子，啊～～金子！\n");
                set("unit", "些");
                set("base_value", 10000 );
		set("base_unit", "锭");
		set("base_weight", 250);
        }
	set_amount(1);
}

int check_gold()
{
	object me = environment();
	object* inv;
	int limit;

	if (!me || !interactive(me) || !living(me))
		return 0;
	
	if(environment(me) && inv = all_inventory(environment(me)) )
	{
		for(limit=0;limit<sizeof(inv);limit++)
			if(objectp(inv[limit]) && inherits(F_BANKER,inv[limit])!=0) return 0;
	}
	
	if (!stringp(me->query_temp("user_type")))
		me->query_user_type();

	if (me->query("combat_exp") < 100000)
		limit = 100;
	else if (me->query_temp("user_type")=="worker")
		limit = 50 + me->query("combat_exp") / 666;
	else
		limit = 50 + me->query("combat_exp") / 1333;

	if( query_amount() > limit ) {
		set_amount(limit);
		return 1;
	}
	return 0;
}

void autoload(string param)
{
	int amt = atoi(param);

	set_amount(amt);
	check_gold();
}
