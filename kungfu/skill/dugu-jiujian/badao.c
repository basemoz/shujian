//拔刀术
//lestat for daya-jian
//取自日本明治维新期间传说中的杀人者雨村剑心的绝学
//雨村剑心的剑法属于飞天御剑流,维新期间号称拔刀齐
//由于其剑法神速,另有拔刀术著称,也是绰号拔刀齐的由来
//被誉为日本剑术的一个神话

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
		||	!target->is_character()
		||	!me->is_fighting(target) )
		return notify_fail("拔刀术只能对战斗中的对手使用。\n");
	message_vision(RED"$N收剑入鞘目不转睛地盯着$n，准备发出致命一击。\n"NOR,me,target);
    me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), random(1)+1);
	me->start_busy(5);
	if (userp(target))
		target->start_busy(4);
	if (!userp(target))
		target->start_busy(6);
	return 1;
}
void kill_him(object me, object target)
{
	string msg,str;
	int damage, ap, dp,qixue,eff_qi,max_qi,qi_pcg,force;
	eff_qi=me->query("eff_qi");
	max_qi=me->query("max_qi");
	qi_pcg=eff_qi*100/max_qi;
	force=target->query("force");
	if(me->is_fighting() && target->is_fighting() &&
		environment(me) == environment(target))
	{
		msg = HIB "$N拔剑出鞘，一道弧形"NOR+HIC"剑光"NOR+HIB"划过，$n"NOR+HIB"只觉得腰部一凉！！！" ;
		msg +=  "\n一股血箭喷涌而出．．$N剑指向天冷冷的站着，一滴滴鲜血从手中逆刃刀上滴下．．\n" NOR;

		message_vision(msg, me, target);
		if (!userp(target))
		      str=target->query("name")+"被"+me->query("name")+"用传说中的杀人剑法:"HIC"拔刀术"NOR+HIM"斩了，尸体齐腰而断！";
		if (userp(target))
		         str=target->query("name")+"被"+me->query("name")+"用传说中的杀人剑法:"HIC"拔刀术"NOR+HIM"击伤！";
			message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
		if (userp(target))
		{
			target->set("qi", 0);
			target->set("jing",0);
			target->set("eff_qi",eff_qi*random(5)/10);
			target->set("force",1);
			target->set("eff_jing",me->query("eff_jing")*random(5)/10);
			call_out("huifu",5,target,force);
		}
		if (!userp(target))
		target->die();
	}
	return ;
}

void huifu(object target,int force)
{
	if (target)
		target->set("force",force);
}
