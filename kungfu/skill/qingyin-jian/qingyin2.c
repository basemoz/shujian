// qingyin.c 双桥清音
// Created by snowman@SJ 18/03/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int is_pfm() { return 1;}

#define PFM_NAME 	"双桥清音"
string perform_name(){ return HIM+PFM_NAME+NOR; }

int perform(object me, object target)
{     
      	if( (int)me->query_skill("qingyin-jian",1) < 300 )
           	return notify_fail("你的清音剑法不够娴熟，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query_skill("sword",1) < 300 )
           	return notify_fail("你的基本剑法等级不够，不能使用" + PFM_NAME + "！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 300 )
           	return notify_fail("你的三乘功法等级不够，不能使用" + PFM_NAME + "！\n");

      	if (me->query_skill_mapped("force") != "sancheng-gong")
           	return notify_fail("你所使用的内功不是三乘功法。\n");

      	if( (int)me->query("max_neili") < 6000 )
           	return notify_fail("你的内力太弱，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query("neili") < 1000 )
           	return notify_fail("你的内力太少了，无法使用出" + PFM_NAME + "！\n"); 
        
        if( !target ) target = offensive_target(me);
        
       	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 500 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	object weapon, ob;
		
      	if( !me->is_fighting() 
        || me->query("neili") < 500 || me->query("jingli") < 100 )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                	
	weapon = me->query_temp("weapon");
      	if (!weapon
       	|| weapon->query("skill_type") != "sword"
       	|| me->query_skill_mapped("sword") != "qingyin-jian" )
       		return notify_fail("你现在无法使用" + PFM_NAME + "！\n");      
       		
       	if( !me->query_temp("pfm/qingyin") ){
       		foreach (ob in all_inventory(environment(me))){
       			if( !ob || !ob->is_character() || !living(ob) 
       			|| ob == me || !me->visible(ob) ) continue;
       			if( ob->query("family/family_name") != "峨嵋派" ) continue;
       			if( ob->query_temp("pfm/qingyin") )
       				return (int)call_other( this_object(), "second_attack", me, ob);
       		}
       		call_out("check_fight", 1 , me, 20);
       		return (int)call_other( this_object(), "first_attack", me, target);
       	}

       	message_vision(HIG"\n$N招式一变，道：看我的" + perform_name() + HIG"，连出三剑，直袭$n！\n"NOR, me, target);
       	me->add_temp("apply/attack", 50);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(4));
      	if( me->is_fighting(target) )
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

      	me->add_temp("apply/attack", -50);
      	me->delete_temp("pfm/qingyin");
      	me->start_perform(4, PFM_NAME);	
       	return 1;
       	
}

void check_fight(object me, int i)
{       
        if( !me ) return; 
        if( !me->query_temp("pfm/qingyin") ) return;
        
        i--;
        if( !me->is_fighting() 
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "qingyin-jian"
        ||  me->query_skill_mapped("force") != "qingdai-shengang") {
        	me->delete_temp("pfm/qingyin");  
        	return;
        }
        call_out("check_fight", 1, me, i);
}

void attacking(object me)
{
	object target = offensive_target(me);
	
       	if( !target 
       	|| !target->is_character() 
       	|| !me->is_fighting(target) 
       	|| !living(target) 
        || environment(target) != environment(me) )
        	return;
        me->add_temp("apply/attack", 100);
        me->add_temp("apply/damage", 40);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
      	me->add_temp("apply/attack", -100);
        me->add_temp("apply/damage", -40);
        	
}

int second_attack(object me, object ob)
{
	int i = me->query_skill("qingyin-jian", 1)/40;
	if( i > 7 ) i = 7;
	
	me->delete_temp("pfm/qingyin");
	ob->delete_temp("pfm/qingyin");
	
       	message_vision(HIG"\n$N将手中宝剑洒出，随即一声清啸，身形幻动，和$n一来一往相互交错，无数的剑光从中闪出，这便是娥眉绝技" + perform_name() + HIG"！\n"NOR, me, ob);
        while( i-- ){
        	if( me->is_fighting() )
        		attacking(me);
        	if( ob->is_fighting() )
        		attacking(ob);
        }
       	me->start_perform(5, PFM_NAME);	
       	ob->start_perform(5, PFM_NAME);	
       	return 1;
}

int first_attack(object me, object target)
{
	me->set_temp("pfm/qingyin", 1);
       	message_vision(HIG"\n$N放声一声长啸，手中宝剑上下连晃，散出一片剑幕！\n"NOR, me);
       	me->add_temp("apply/attack", 50);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	me->add_temp("apply/attack", -50);
       	me->start_perform(1, PFM_NAME);	
       	return 1;
}

int help(object me)
{
	write(HIG"\n清音剑法「" + perform_name() + HIG"」："NOR"\n");
	write(@HELP
			杰然高阁出清音，仿佛神山下抚琴。
			试立双桥一倾耳，分明两水漱牛心。
			
	月朗风轻之夜，山色朦胧如黛，万籁俱静，唯有悠扬清越的水声回荡在无
	穷的空间。坐在水潭前洗心台上，人们恍惚进入一个“清音”入化的世界。
	静听清音，人的心灵因之而宁怡，而超脱，忘却自己的存在，仿佛自身与
	大自然融合为一，化作声声清音，萦绕了太空。此绝招可单人双人使用，
	招招连环，式式夺命，功能毁天灭地！
	
	要求：	
		清音剑法等级 300 以上；
		基本剑法等级 300 以上；
		三乘功法等级 300 以上；
		最大内力 6000 以上； 
		内力 1000 以上。
HELP
	);
	return 1;
}

