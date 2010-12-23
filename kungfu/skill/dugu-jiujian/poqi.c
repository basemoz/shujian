// poqi.c 破气式
// By Spiderii更新，有门派特殊exert标记没加上的
// 谁有空帮我完善下
 
#include <ansi.h>
 
inherit F_SSERVER;
 
string perform_name() {return HIC"破气式"NOR;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, p, force, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian",1);

        if( !(me->is_fighting() ))
                return notify_fail("「破气式」只能对战斗中的对手使用。\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( skill < 150)
                return notify_fail("你的独孤九剑等级不够, 不能使用「破气式」！\n");

        if( me->query("neili") < 1000 )
                return notify_fail("你的内力不够，无法运用「破气式」！\n");
 
        msg = HIC "$N潜运独孤九剑「破气式」，运气贯剑使其由利返钝，毫无花俏地直刺$n的丹田。\n";
        ap = me->query_skill("sword") + skill;
        dp = target->query_skill("force")/2;
        if( dp < 1 )
                dp = 1;
        if( random(ap + 20) > dp ){
                if(userp(me))
                        me->add("neili",-(200+random(200)));
           msg += "$N运起「破气式」, $n顿时觉得眼前一花，气海穴上微微一痛，全身真气狂泄而出！\n" NOR;

           p = (int)me->query_skill("force") + random(me->query_skill("force")*2);
   
           force = target->query_skill_mapped("force");

	switch(force) {
		case "huntian-qigong":
			if( intp(p = target->query_temp("htqg/powerup")) ){
				target->add_temp("apply/armor", - p*2);
				target->add_temp("apply/dodge", - p);
				target->delete_temp("htqg/powerup");
				tell_object(target, HIR"你的丹田要穴被伤，混天气功的效果自然消失了！\n"NOR);
				break;
			}
		case "yijin-jing":
			if( intp(p = target->query_temp("jingang_armor")) ){
				target->add_temp("apply/armor", - p);
				target->delete_temp("fanzhen");
				target->delete_temp("no_skill_hit_ob");
				target->delete_temp("jingang_armor");
				tell_object(target, HIR"你的丹田要穴被伤,「金刚不坏体神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "jiuyang-shengong":
			if( intp(p = target->query_temp("jiuyang/powerup")) ){
				target->add_temp("apply/armor", - p);
				target->add_temp("apply/dexerity", -p/2);
				target->delete_temp("jiuyang");
				target->delete_temp("no_skill_hit_ob");
				tell_object(target, HIR"你的丹田要穴被伤,「九阳神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "linji-zhuang":
			if( target->query_temp("ljz/riyue") ){
				target->delete_temp("ljz/riyue");
				tell_object(target, HIR"你的丹田要穴被伤,「日月」庄所聚天地之精气已散回日月之间！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/yinyang")) ){
				target->add("max_qi", - p);
				target->receive_wound("qi", p, "「阴阳」庄被破，脱力而");
				target->delete_temp("ljz/yinyang");
				tell_object(target, HIR"你的丹田要穴被伤,「阴阳」庄提升的效应也消失了！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/fengyun")) ){
				target->add_temp("apply/dexerity", - p);        
				target->delete_temp("ljz/fengyun");
				tell_object(target, HIR"你的丹田要穴被伤,「风云」庄效果消失，略觉步履沉重了一些。\n"NOR);
				break;
			}
			if( target->query_temp("ljz/wuwo")){
				target->delete_temp("ljz/wuwo");
				tell_object(target, HIR"你的丹田要穴被伤,「无我」心法被破，又恢复了原来的你！\n"NOR);
				break;
			}
		case "yinyun-ziqi":
			if( target->query_temp("tj/太极") ){
				target->delete_temp("tj/太极");
				tell_object(target, HIR"你的丹田要穴被伤,慌忙之中，太极不能连贯而行，效应也消失了！\n"NOR);
				break;
			}
		case "dulong-dafa":
			if( intp(p = target->query_temp("sld/wudi2") ) ){
				target->add_temp("apply/attack", - p);
				target->add("max_qi",- target->query_temp("sld/wudiqi"));
				target->add_temp("apply/armor", -target->query_temp("sld/wudi"));
				target->delete_temp("sld");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi", target->query("max_qi"));
				tell_object(target, HIR"你丹田要穴被伤，心神一松，再也支持不住了！！\n"NOR);
				if(random( target->query("qi")) < 100) 
					target->unconcious();
				break;
			}
			else if( intp(p = target->query_temp("sld/wudi")) ){
				target->add("max_qi",- target->query_temp("sld/wudiqi"));
				target->add_temp("apply/armor", -p);
				target->delete_temp("sld/wudiqi");
				target->delete_temp("sld/wudi");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi",target->query("max_qi"));
				tell_object(target, HIR"你丹田要穴被伤，心神一松，好象虚脱了一样，突然垮了下来！！\n"NOR);
				break;
			}
		case "hanbing-zhenqi":
			if ( intp(p = target->query_temp("hbzq/huti")) ){
				target->add_temp("apply/parry", -p);
				target->add_temp("apply/dodge", -p);
				target->delete_temp("hbzq/huti");
				tell_object(target, HIR"你丹田要穴被伤，周身的寒气散尽，不再能起到保护的作用了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/focus")){
				target->delete_temp("ss/focus");
				tell_object(target, HIR"你丹田要穴被伤，周身的寒气渐渐的散去了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/hb")){
				target->delete_temp("ss/hb");
				tell_object(target, HIR"你丹田要穴被伤，手上的寒气渐渐的散去了。\n"NOR);
				break;
			}
		case "huagong-dafa":
			if( intp(p = target->query_temp("hgdf/judu")) ){
				target->add_temp("apply/armor", -p);
				target->delete_temp("hgdf/judu");
				tell_object(target, HIR"你丹田要穴被伤，心神一松，所聚毒素全都垮了！！\n"NOR);
				break;
			}
			else if( intp(p = target->query_temp("hgdf/huadu")) ){
				target->add_temp("apply/dodge", -p); 
				target->add_temp("apply/armor_vs_force", -p/2);           
				target->delete_temp("hgdf/huadu");
				tell_object(target, HIR"你丹田要穴被伤，心神一松，化毒所聚毒素全都垮了！！\n"NOR);
				break;
			}
		case "yunu-xinjing":
			if( target->query_temp("gm/xinjing") ){
				p  = target->query_temp("gm/xinjing");
				target->add_temp("apply/intelligence", -p/10);
				target->add_temp("apply/dexerity", -p/10);
				if ( target->query_skill("yunu-xinjing", 1) > 200 ){
					target->add_temp("apply/armor_vs_force", -p/5);
					if ( target->query("gender") == "女性") {
						target->add_temp("apply/dodge", -p/5);
						target->add_temp("apply/parry", -p/5);
						target->add_temp("apply/armor", -p/5);
					}
				}
				target->delete_temp("gm/xinjing");
				tell_object(target, HIR"你的丹田要穴被伤,「心经」字决效应也消失了！\n"NOR);
				break;
			}
		case "shenyuan-gong":
			if ( intp(p = target->query_temp("shenyuan")) ){
				target->add_temp("apply/parry", -p/3);
				target->add_temp("apply/dexerity", -p/5);
				target->delete_temp("shenyuan");
				tell_object(target, HIR"你丹田要穴被伤，防守招式已经减弱了。\n"NOR);
				break;
			}
		case "xuantian-wuji":
			if ( target->query_temp("kl/riyue")){
				target->delete_temp("kl/riyue");
				tell_object(target, HIR"你丹田要穴被伤，身前的气墙逐渐缩小，终于消失于无形。\n"NOR);
				break;
			}
			if ( intp( p = target->query_temp("kl/taxue")) ) {
				target->add_temp("apply/dodge", -p);
				target->delete_temp("kl/taxue");
				tell_object(target, HIR"立定了脚步，身法回复了正常！\n"NOR);
				break;
			}
		case "longxiang-boruo":
			if ( intp(p = target->query_temp("xs/shield")) ) {
				target->add_temp("apply/dodge", -p);
				target->add_temp("apply/armor", -p*2);
				target->delete_temp("xs/shield");
				tell_object(target, HIR"你丹田要穴被伤，脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR);
				break;
			}
			if ( intp(p = target->query_temp("xs/longxiang")) ) {
				target->add_temp("apply/attack", -p);
				target->delete_temp("xs/longxiang");
				tell_object(target, HIR"你丹田要穴被伤，脸上紫气一闪，又恢复如常。\n" NOR);
				break;
			}
		case "qiantian-yiyang":
			if( intp(p = target->query_temp("dali_jing")) ){
				target->add_temp("apply/intelligence", -p);
				target->delete_temp("dali_jing");
				tell_object(target, HIR"你丹田要穴被伤，无法继续潜修了。\n" NOR);
				break;
			}
		case "guiyuan-tunafa":
			if ( intp(p = target->query_temp("tz/focus")) ){
				target->add_temp("apply/attack", p);
				target->add_temp("apply/damage", p/2);
				target->delete_temp("tz/focus");
				tell_object(target, HIR"你丹田要穴被伤，精神有些委顿，力道随即恢复常态。\n"NOR);
				break;
			}
		case "kurong-changong":
			if( intp(p = target->query_temp("krcg_kurong")) ){
				target->delete_temp("krcg_kurong");
				target->add_temp("apply/armor", -p/2);
				target->add_temp("apply/parry", -p/4);
				tell_object(target, HIR"你丹田要穴被伤，「枯荣」大法立刻消散了！\n" NOR);
				break;
			}
			
		case "bihai-chaosheng":
			if ( intp(p = target->query_temp("thd/maze")) ){
				target->add_temp("apply/armor", - (p/4));
				target->delete_temp("thd/maze");
                                if(weapon = target->query_temp("thd/maze_target") && weapon = target->query_temp("thd/mazed")){
					weapon->delete_temp("thd/mazed");
					weapon->add_temp("apply/dexerity", p/10);
					weapon->add_temp("apply/dodge", p/10);
					weapon->add_temp("apply/damage", p/10);
					tell_object(weapon, target->name() + "对你布的迷阵已经被"+me->name()+"的「破气诀」打散了。\n");
				}
				tell_object(target, HIR"你丹田要穴被伤，布的迷阵瞬间消散了！\n" NOR);
				break;
			}
           }
	         qi_wound = ap+random(ap/2) ;
                neili_wound = random(qi_wound/2);
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                       qi_wound = target->query("qi");
                if(random(2)== 1)
                target->apply_condition("no_perform", 1+ random(2));
                target->add("neili", -neili_wound);
                target->add("qi", -qi_wound);
                target->add("eff_qi", -qi_wound);
                target->add_busy(2);
                me->start_busy(random(2));
                me->start_perform(5,"破气式");

        }
        else
        {
                if(userp(me))
                        me->add("neili",-200);
                msg += "可是$n看破了$N的企图，立刻守紧门户，几经艰难终于还招挡开。\n"NOR;
                me->start_busy(2);
                me->start_perform(3,"破气式");
        }
        message_vision(msg, me, target);

        return 1;
}
int help(object me)
{
	write(HIC"\n独孤九剑「破气式」："NOR"\n");
	write(@HELP
	运独孤九剑剑意，破敌之真气，制敌之先机。

	
	要求：	内力 1000 以上；      
		独孤九剑等级 150 lv以上；      
		手持兵器。
HELP
	);
	return 1;
}

