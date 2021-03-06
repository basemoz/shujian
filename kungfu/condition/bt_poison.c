#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
    	if( !living(me) ){
    		message("vision",HIW + me->name() + "的身体突然抽动了一下！\n"NOR, environment(me), me);
    	}
    	    
      	tell_object(me, HIB "你忽然感到身体僵直，已经不听使唤了。\n" NOR );      
      	me->set_temp("last_damage_from", "体内怪蛇之毒发作");      
      	me->receive_wound("qi", 50 + random(50));
      	if( !me->is_busy() ) me->start_busy(3);
      	if(userp(me))
           	me->receive_wound("jing", me->query_skill("force") + 40 + random(50));
      	else 	me->receive_wound("jing", me->query_skill("force") + 120);
      	
      
      	if( me->query("jing") >= 500)
              	tell_room(environment(me), YEL+me->name()+"突然只膝弯曲，身子慢慢垂下，口中发出似人似兽的荷荷之声。\n" NOR, ({ me }));            
      	else if( me->query("jing") < 500 && me->query("jing") >= 350)
              	tell_room(environment(me), BLU+me->name()+"忽然满面堆欢裂嘴嘻笑，更显得诡异无伦。\n" NOR,  ({ me }));        
      	else if( me->query("jing") < 350 && me->query("jing") >= 150)
              	tell_room(environment(me), HIB+me->name()+"此时神智更加胡涂，指东打西，乱□乱咬。\n" NOR,({ me }));           
      	else    tell_room(environment(me), HIR+me->name()+"突然缩成一团，滚在地上不停地发颤。\n" NOR,({ me }));

      	if( duration < 1 ) return 0;           
      	me->apply_condition("bt_poison", duration - 1);
      	return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}
