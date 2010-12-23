// zhemei-shou ��ɽ��÷��
// cck 14/6/97

inherit SKILL;

int lvl_temp;

string *action_msg = ({
"$N��������һָͻ�����ںϽ�����ָ�����壬�ṹ�Ͻ������ƺ�ΰ��ָָ������$n",
"$N���������������������Ե��������������ݺᣬ�������У���·�����븫���ϳ�һ·����$n",
"$N˫���Եý������أ�ʹ��ʱԽ��Խ��ɬ�������趯һ�����ȣ�����Խ��Խ�أ�����ֹ��",
"$Nʮָ̽�������ֻ�����������Ʈ���л�ȥ��$n��������ȴ�̺������ҵķ�����ʽ",
"$N˫�������˦�������������޹ǣ��鶯֮������һ�ƣ���һ�����Ƶ�$n����һ����Ҳ��������",
});

int valid_enable(string usage)
{
	return usage == "hand" || usage == "parry";
}

int valid_combine(string combo)
{
	return combo=="liuyang-zhang";
}

mapping query_action(object me, object weapon)
{
	lvl_temp = random((int)me->query_skill("zhemei-shou", 1));
	if ( lvl_temp > 80 && ! random(3)) {
		if ( lvl_temp <= 120 )
			return ([
				"action":	"$N����һ�䣬������������֮����������Ϣ����$n�ġ�����Ѩ����������ȭ�ͻ�����������$n�ؿڵġ�����Ѩ��",
				"damage_type":	"����",
				"damage":	60,
				"dodge": 	random(30),
				"parry":	random(30),
				"force":	450 +random(100),
			]);

		if ( lvl_temp <= 180 )
			return ([
				"action":	"$N��������һ��������һ���ھ��������м���������һǰһ�����$n",
				"damage_type":	"����",
				"damage":	70,
				"dodge":	30,
				"parry":	random(30),
				"force":	500,
			]);

		if ( lvl_temp <= 240 )
			return ([
				"action":	"$N����ת�˸�СȦ���ȿ���׼����ֻ��ָ����$n���󣬴�Ĵָ��Сָ���ű㼴��£����ס$n���ţ�$n��ʱ��������",
				"damage":	80,
				"damage_type":	"����",
				"parry":	random(30),
				"dodge":	30,
				"force":	550,
			]);

		if ( lvl_temp <= 300 ) {
			return ([
				"action":	"$N˫����ץ��ʹ������ɽ��÷�֡��ĸ����书��ץ�д��ۣ����м��ƣ�����$n�����Ŵ�Ѩ",
				"damage_type":	"����",
				"damage":	90,
				"dodge":	20,
				"parry":	random(30),
				"force":	600,
			]);
		}
		return ([
			"action": "��ʱ$N����������������ң�����ַ��ӵ����쾡�£������������ۣ���������\n"
				 "Ȼ����ң����ѧ��������������Ȼ��Ȼ��Ҳʹ�˳�������ʹ�����������տ̶�\n"
				 "$N�������գ��Թ���$nҪ����ֱ����$n���òҿ��ޱ�",
			"damage_type": "����",
			"dodge": 	50,
			"parry": 	50,
			"damage":	100,
			"force": 	650,
		]);

	}
	return ([
		"action":	action_msg[random(sizeof(action_msg))],
		"damage_type":	random(2)?"����":"����",
		"parry":	random(30),
		"dodge":	random(30),
		"force":	300 + random(350),
		"damage":	50 + random(50),
	]);
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("���������������ɽ��÷�֡�\n");
	if ((int)me->query("neili") < 30)
		return notify_fail("���������������ɽ��÷�֡�\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

int valid_learn(object me)
{
	if(!me->query("tonglao/ok"))
		return notify_fail("���޷�ѧϰ��ɽ��÷�֡�\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ɽ��÷�ֱ�����֡�\n");
	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������������\n");
//	if ((int)me->query_skill("bahuang-gong", 1) < 100)
//		return notify_fail("��İ˻�����Ψ�Ҷ��𹦻��̫ǳ��\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zhemei-shou/" + action;
}

mixed hit_ob(object me, object target, int damage_bonus, int factor)
{
	int damage, amount;
	if( lvl_temp > 80) {
		if( (lvl_temp <= 100) && (me->query("neili") > 30)) {
			target->add_condition("cold_poison", random(2)+1);
			me->add("neili", -30);
			return 1;
		 }
		 if( (lvl_temp <= 120) && (me->query("neili") > 50) ) {
			damage = (int)me->query_skill("zhemei-shou", 1);
			damage = damage/2 + random(damage);
			target->receive_damage("qi", (random(4)+ 1)*damage);
			target->receive_wound("qi", damage/2);
			me->add("neili", -50);
			return 1;
		 }

		 if( (lvl_temp <= 140) && (me->query("neili") > 50)
		    && (random(me->query("combat_exp")) > target->query("combat_exp")/3)) {
			target->start_busy((int)me->query_skill("zhemei-shou", 1) / 20);
			me->add("neili", -50);
			return 1;
		 }
		 if( (lvl_temp <= 160) && (me->query("neili") > 50)
			 && (target->query_temp("weapon")) 
			 && (random(me->query("combat_exp")) > target->query("combat_exp")/3)) {
//			"cmds/std/drop"->main(target,target->query_temp("weapon"));
			target->query_temp("weapon")->move(me);
			me->add("neili", -50);
			return 1;
		 }

		 if( (lvl_temp > 160) 
		&& (me->query("neili") > 100) 
		&& (me->query_temp("marks/add") != 1)) {
                        amount = (int)me->query_skill("zhemei-shou", 1) / 3;
			me->add_temp("apply/attack", amount);
			me->add_temp("apply/defense", amount);
			me->add_temp("apply/dodge", amount);
			me->add("neili", -100);
			me->set_temp("marks/add", 1);
			call_out("reset_temp", 10, me);	
			return 1;	
		}

	 }
}

int reset_temp(object me)
{
	int amount;

	if (!me) return 0;
	amount = (int)me->query_skill("zhemei-shou", 1) / 3;

	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/defense", -amount);
	me->add_temp("apply/dodge", -amount);
	me->delete_temp("marks/add");
	return 1;
}
