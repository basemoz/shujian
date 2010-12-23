//shenxing-baibian.c
// By Spiderii@ty ����SJ���±༭
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$nһʽ��������ˮ�������㣬�Ų��ƣ�������������ˮ��ֱ�������ࡣ\n" ,
        "dodge"  : 120
]),
([      "action" : "$nһʽ��Ǳ��ҹ�С�����Ȼһ������ȫ�����ض��У���ʱ������$N���������ơ�\n",
        "dodge"  : 100
]),
([      "action" : "$nһʽ���Ʋ����Ρ����㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����!\n",
        "dodge"  : 150
]),
([      "action" : "$nһʽ������Ӱ����һת��䣬����˷�Ʈ����������$n����Ӱ����$N�����޴롣\n",
        "dodge"  : 180
]),
([      "action" : "$nһʽ�������ﲨ��������ٿ�Ĵ�$N����ǰֱ�Ƶ����$N�ɴ������ۣ��������ԡ�\n",
        "dodge"  : 130
]),
([      "action" : "$nһʽ�����ϲ�¥�������ڿ��У������������һ�㣬��$Nͷ���ڿն�����\n",
        "dodge"  : 210
]),
([      "action" : "$nһʽ�����ӳ�ˮ��������һ����ȫ��Ϊһ����Ӱ�����ĵش�$Nͷ��Ʈ�䡣\n",
        "dodge"  : 230
]),
([      "action" : "$nһʽ�����·ת�������������ݰ㼱ת����ʱһ������ӿ������$N���Զ�����\n",
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
           return notify_fail("�������̫���ˣ����������аٱ䡣\n");

      if((int)me->query("neili") < 30 )
           return notify_fail("�������̫���ˣ����������аٱ䡣\n");

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
             return notify_fail("��û�гɹ��о�����ô��͵ѧ���аٱ䡣\n");
        
	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("���������Ϊ̫�ǿ�����аٱ�ֻ���߻���ħ��\n");

        if( (int)me->query("jingli") < 40 )
                return notify_fail("�������̫���ˣ����������аٱ䡣\n");
        if( (int)me->query("jing") < 25 )
                return notify_fail("�������̫���ˣ����������аٱ䡣\n");
        if( (int)me->query("qi") < 20 )
                return notify_fail("�������̫���ˣ����������аٱ䡣\n");
        if( (int)me->query("neili") < 20 )
		return notify_fail("�������̫���ˣ����������аٱ䡣\n");

	me->receive_damage("jing", 15, "�����߻���ħ");
	me->receive_damage("jingli", 35);
	me->receive_damage("qi", 10, "�����߻���ħ");
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
		tell_object(ob, HIR "��ֻ����ǰһ���������˶��ֵ���Ӱ��\n" NOR);
		if(neili >= neili1+random(neili1)+damage*2){
			msg += "���$N���������㿪�ˣ�\n", 
			j = -(damage*2+skill*3);
		}
		else if(neili > neili1+damage){
			msg += "���$N�������������һ�룡\n", 
			j=-damage/2;               
		}
		else {
			msg += "���$nֻ�����$N��һС��������\n", 
			j = -(damage/2+random(damage/2)); 
		}
		message_vision(msg, ob, me);
		return j;
	}
	return j;   
}
