//shenxing-baibian.c
// By Spiderii@ty 参照SJ从新编辑
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$n一式「行云流水」，身不倾，脚不移，身体如行云流水般直滑出丈余。\n" ,
        "dodge"  : 120
]),
([      "action" : "$n一式「潜音夜行」，忽然一弯腰，全身贴地而行，顿时闪过了$N的凌厉攻势。\n",
        "dodge"  : 100
]),
([      "action" : "$n一式「移步换形」，足不动，手不抬，一转眼间便绕到了$N的身后!\n",
        "dodge"  : 150
]),
([      "action" : "$n一式「分身化影」，一转身间，四面八方飘动着无数个$n的身影，令$N手足无措。\n",
        "dodge"  : 180
]),
([      "action" : "$n一式「临行秋波」，身行倏的从$N的眼前直绕到身后，$N瞪大了两眼，不明所以。\n",
        "dodge"  : 130
]),
([      "action" : "$n一式「更上层楼」，身在空中，左脚在右足上一点，从$N头顶腾空而过。\n",
        "dodge"  : 210
]),
([      "action" : "$n一式「仙子出水」，长袖一拂，全身化为一道白影，幽幽地从$N头顶飘落。\n",
        "dodge"  : 230
]),
([      "action" : "$n一式「峰回路转」，身体如陀螺般急转，登时一股气流涌出，令$N难以动弹。\n",
        "dodge"  : 130
])
});

mapping query_action(object me)
{
        int zhaoshu;

        zhaoshu = sizeof(action);
        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
       if(this_player()->query("quest/baibian"))
	return usage == "dodge";
}

int valid_learn(object me)
{
      if((int)me->query("qi") < 50 )
           return notify_fail("你的体力太差了，不能练神行百变。\n");

      if((int)me->query("neili") < 30 )
           return notify_fail("你的内力太差了，不能练神行百变。\n");

      me->receive_damage("qi", 40);
      me->add("neill", -14);
      return 1;
}

string query_dodge_msg(object me)
{
        mapping action;

        action = query_action(me);

        return action["action"];
}

string perform_action_file(string action)
{
        return __DIR__"shenxing-baibian/" + action;
}


int practice_skill(object me)
{
        if ( !me->query("quest/baibian"))
             return notify_fail("你没有成功研究，怎么能偷学神行百变。\n");
        
	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("你的内力修为太差，强练神行百变只会走火入魔。\n");

        if( (int)me->query("jingli") < 40 )
                return notify_fail("你的体力太差了，不能练神行百变。\n");
        if( (int)me->query("jing") < 25 )
                return notify_fail("你的体力太差了，不能练神行百变。\n");
        if( (int)me->query("qi") < 20 )
                return notify_fail("你的体力太差了，不能练神行百变。\n");
        if( (int)me->query("neili") < 20 )
		return notify_fail("你的内力太差了，不能练神行百变。\n");

	me->receive_damage("jing", 15, "练功走火入魔");
	me->receive_damage("jingli", 35);
	me->receive_damage("qi", 10, "练功走火入魔");
	me->receive_damage("neili", 10);
	return 1;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int skill, neili, neili1;
	int j = 0;
	skill = me->query_skill("shenxing-baibian", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if(me->query_temp("shenxing-baibian")){
		me->delete_temp("shenxing-baibian");
		return j;
	}

	if(skill/2 > random(ob->query_skill("dodge", 1))
	 && me->query("combat_exp") > ob->query("combat_exp")/2	 
	 && me->query_skill_mapped("dodge") == "shenxing-baibian"
	 && neili > 400
	 && skill > 80 ) {
		me->add_temp("shenxing-baibian", 1);
		msg =random(2)? HIR + action[random(sizeof(action))]["action"]+NOR :
				HIC + action[random(sizeof(action))]["action"]+NOR ; 
		tell_object(ob, HIR "你只觉眼前一花，不见了对手的身影！\n" NOR);
		if(neili >= neili1+random(neili1)+damage*2){
			msg += "结果$N的力道被躲开了！\n", 
			j = -(damage*2+skill*3);
		}
		else if(neili > neili1+damage){
			msg += "结果$N的力道被躲过了一半！\n", 
			j=-damage/2;               
		}
		else {
			msg += "结果$n只躲过了$N的一小半力道！\n", 
			j = -(damage/2+random(damage/2)); 
		}
		message_vision(msg, ob, me);
		return j;
	}
	return j;   
}
