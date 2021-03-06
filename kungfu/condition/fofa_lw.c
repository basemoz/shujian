#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        me->apply_condition("fofa_lw", duration - 1);
        
        if(random(10)==1)
	{
		tell_room(environment(me), me->name() + "身形似乎显得异常高大。\n", ({ me }));		
	}

        if( ! me->query_temp("fofa_long") ) 
        {
		tell_object(me, HIY"你长长的舒了口气，身形似乎也缩小了一些。\n"NOR);		
		me->clear_condition("fofa_lw");
		return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "fofa";
}
