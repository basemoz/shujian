// liaoyuan.c 燎原百击

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl, skill, skill1,jiali;
	object weapon;
	string name;

	weapon = me->query_temp("weapon");
	if (weapon) name = weapon->query("name");

	if( !target ) target = offensive_target(me);
     
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("燎原百击只能在战斗中对对手使用。\n");

	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("你手里没有剑，无法使用燎原百击！\n");             

	if( (int)me->query_skill("huifeng-jian",1) < 120 )
		return notify_fail("你的回风拂柳剑不够娴熟，不能使用燎原百击！\n");
      
	if( (int)me->query_skill("sword",1) < 120 )
		return notify_fail("你的基本剑法等级不够，不能使用燎原百击！\n");  

	if( (int)me->query_skill("jieshou-jiushi", 1) < 120 )
		return notify_fail("你的截手九式等级不够，不能使用燎原百击！\n");
      
	if( (int)me->query_skill("linji-zhuang", 1) < 120 )
		return notify_fail("你的临济十二庄等级不够，不能使用燎原百击！\n");

	if (me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("你所使用的内功不对。\n");

	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("你的内力太弱，不能使用燎原百击！\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你的内力太少了，无法使用出燎原百击！\n");

	if (me->query_skill_prepared("hand") != "jieshou-jiushi"
	 || me->query_skill_mapped("hand") != "jieshou-jiushi")
		return notify_fail("你不会截手九式，现在无法使用燎原百击进行攻击。\n");

	skill = me->query_skill("huifeng-jian", 1);
	skill1 = me->query_skill("jieshou-jiushi", 1);

	lvl =  skill / 8;
	lvl += skill1 / 8;
	jiali = me->query("jiali");

	message_vision(HIW"\n$N长啸一声，身子往高空升去，刚好拦住$n，右手中"+name+HIW"刹那间填满空间。\n"NOR, me,target);
	message_vision(HIW"左手使出截手九式，带起无数小气旋，威力顿然加强。\n"NOR, me,target);
	me->add("neili", -350); 
	me->add("jingli", -100); 

	if ( skill > 200)
		lvl = to_int((skill+skill1)/8.0* skill/200.0);

	if ( jiali > 100) {
		me->set("jiali", 100);
		me->set_temp("lyjiali", 1);
	}

	me->set_temp("liaoyuan", 1);
	me->add_temp("apply/attack", lvl);
	me->add_temp("apply/damage", lvl/2);

	me->add_temp("apply/sword", lvl);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);//以前是random(4) by lsxk@hsbbs

	me->add_temp("apply/sword", -lvl);
	me->add_temp("apply/damage", -lvl/2);
	weapon->unequip(); 
	me->add_temp("apply/hand", lvl);
	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi",1) > 150)
           COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi", 1) > 200)
           COMBAT_D->do_attack(me, target, 0, 3); //以前是random(4)?1:3  by lsxk@hsbbs
	weapon->wield();
	me->add_temp("apply/hand", -lvl);

	if ( me->query_temp("lyjiali")){
		me->set("jiali", jiali);
		me->delete_temp("lyjiali");
	}
	me->add_temp("apply/attack", -lvl);
	me->delete_temp("liaoyuan");
	me->start_busy(random(2));
	me->start_perform(3, "燎原百击");
	return 1;
}

string perform_name(){ return HIW"燎原百击"NOR; }

int help(object me)
{
	write(HIW"\n回风拂柳剑之「燎原百击」："NOR"\n\n");
	write(@HELP
	要求：	当前内力 500 以上；
		最大内力 1000 以上；
		当前精力 300 以上；
		回风拂柳剑等级 120 以上；
		截手九式等级 120 以上；
		临济十二庄等级 120 以上；
		基本剑法等级 120 以上；
		激发内功为临济十二庄；
		激发剑法为回风拂柳剑；
		激发手法为截手九式；
		备手法为截手九式；
		且手持兵器。

HELP
        );
        return 1;
}
