#include <ansi.h>

int exercising(object me);
int halt_exercise(object me);
int find(string arg, object me);

int exert(object me, mixed arg)
{
      if(!arg)
          return notify_fail("格式：exert shentong <id> \n"); 
      
      if(objectp(arg))
          return notify_fail("你要找的人就在一旁，还「神通」干什么？\n"); 
          
      if(!stringp(arg))
          return notify_fail("你要「神通」什么？\n"); 
          
      if(arg==me->query("id"))
          return notify_fail("「神通」自己？你不是走火如魔了吧？\n"); 
          
      if( (int)me->query_skill("longxiang-gong",1) < 150 )
          return notify_fail("你的龙象般若功根基不稳，无法运用「神通」！\n"); 
          
      if( (int)me->query_skill("lamaism",1) < 150 )
          return notify_fail("你的密宗心法不够，无法运用「神通」！\n");    
            
      if( me->is_fighting() )
          return notify_fail("「神通」只能在安静的环境中使用。\n");
          
      if( (int)me->query("neili") < 500 || (int)me->query("max_neili")<2000  ) 
          return notify_fail("你的内力不够。\n");
          
      if( (int)me->query_temp("mz_shenyou") ) 
          return notify_fail("你已经在运用密宗大法中了。\n");
          
      if( me->query("jing") < me->query("eff_jing"))        
          return notify_fail("你精神不凝，如何能「神通」？\n");  
          
      if( me->query("jingli") < 800)
          return notify_fail("你目前精力衰竭，恐怕无法「神通」。\n");
          
      if( me->query_int() < 32)
          return notify_fail("只有大智大慧之人才能通晓「神通」，看样子你是不行的了。\n");
          
      me->add("neili", -300);

      message_vision(HIW"\n$N盘膝闭目，口中背诵大乘佛经，夹杂以密宗六字咒。声音阴阳顿挫，有起有伏，暗含音律，开始进入「神游」境界。\n\n" NOR, me);

      me->set_temp("mz_shenyou", 1);
      me->set_temp("period", 1);
      me->set_temp("person", arg);
      me->start_busy((: exercising :), (:halt_exercise:));
      return 1;
}

int exercising(object me)
{
	int period = (int)me->query_temp("period");

	me->receive_damage("jing", 5+random(2));
	me->receive_damage("jingli", 5+random(2));

        if(!living(me)) return 0;
        if(me->query("jing") < 1 || me->query("jingli") < 1){
        	me->delete_temp("mz_shenyou");
        	me->delete_temp("period");
        	me->delete_temp("person");
        	me->unconcious();
        	return 0;
        }
        if(!me->query_temp("person")){
        	 halt_exercise(me);
        	 return 0;
        	 }
	switch(period) {
        case 3:
                write("\n你全身放松，缓缓将呼吸内缄，清除脑中杂念。\n\n");
                break;
        case 8:
                write("\n不一会儿，你觉得自己的神志越来越清醒，而身体也越来越轻了。\n\n");
                break;
        case 13:
                write(HIY"\n渐渐地，你发现你看见了自己盘膝坐在那里，好似形神已经分开了似的。\n\n"NOR);
                break;
        case 18:
                write(HIC"\n你发现自己的神志越伸越远，于瞬时间已经跨过了高山大海，游荡于真空之中！\n\n"NOR);
                me->improve_skill("force", 1);
                break;
        case 23:
                write(HIW"\n你的思感伸张开去，只一刹那，便看见了你想看的东西！\n\n"NOR);
                find(me->query_temp("person"), me);
                me->add("combat_exp", 1);
                break;
        case 28:
                write("\n渐渐地，你的思感又回转回来，一丝轻微的声音传来，身体也开始有了感觉。\n\n");
                me->add("potential", 1+random(5));
                break;
        case 30:
                write("\n你缓缓站起身来，只觉得全身虚脱，十分疲惫。\n\n");
                tell_room(environment(me), me->name()+"长长呼出一口秽气，缓缓站了起来。\n\n", ({ me }));
                me->set("jing", 1);
                me->set("jingli", 1);
                me->delete_temp("period");
                me->delete_temp("person");
                me->delete_temp("mz_shenyou");
                me->start_busy(2);
                return 0;
                break;
        }
        period++;
        me->set_temp("period", period);
        return 1; 
}

int halt_exercise(object me)
{
	me->delete_temp("mz_shenyou");
	me->delete_temp("period");
	me->delete_temp("person");
	me->receive_damage("jing", 50);
	me->receive_damage("jingli", 50);
	write("你心头一阵慌乱，再不能静坐入定，只好睁眼站起。\n");
        tell_room(environment(me), me->name()+"全身一阵抖动，接着呼出一口青气，缓缓站了起来。\n", ({ me }));
        me->start_busy(1+random(5));
	return 1;
}

int find(string arg, object me)
{
        object where, target;

        if (!geteuid()) seteuid(getuid());
        target = LOGIN_D->find_body(arg);
        if (!target) target = find_living(arg);
	if (!target) {
		tell_object(me, YEL"\n你仔细盯了半天，却发现这只是个幻影，真身竟然不知道在那里...\n\n"NOR);
		return 1;
		}
	if (wizardp(target)){
		tell_object(me, MAG"\n你忽然发现，那人竟是忽隐忽现，好似一名漂浮在半空的神！
而且还回过头来，瞪了你一眼！你感到大事不妙，连忙退了回来。\n\n"NOR);
                return 1;
                }
	where = environment(target);
	if (!where) {
		tell_object(me, HIB"\n你于冥冥中感到了这个人的存在，但却发现总是找不到他的所在！
看来，这人是到了一处不为世人所知的地方，只有神在知道的地方。\n\n"NOR);
                return 1;
                }
	"/cmds/std/look"->look_room(me, where);
        tell_object(me, HIW"\n\n这灵光只是一闪，你的思感又慢慢退回来了。\n"NOR);
        return 1;
}

