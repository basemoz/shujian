//    ����ȭ


inherit SKILL;

#include <ansi.h>

mapping *action = ({
([
	"action" : "$Nʹ�����ա��־�����ȭ������ȭʽ�������ޣ��ƺ�������������ȴ�־�ֱϮ��$n",
	"lvl" : 0,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ���������־���ȭ�к����Ϳ�����Ʋ����·�����ȭ��ȴֱָ$n��$l",
	"lvl" : 10,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ���������־�����ȭ�ƺ��ɶ��д�����������������ʽȴ���ͱ��ˣ��ݺݵػ���$n",
	"lvl" : 20,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����ɡ��־�����ȭ����������������ػ�������ƮƮ�ػ���$n��$l",
	"lvl" : 30,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����硹�־�����ȭ����������һ����磬$n�վ������壬ȭ�о���Ϯ������ǰ",
	"lvl" : 40,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ����ͨ���־���ȭ���۶���ɢ�����д�֮ͨ�Σ�ֱ��$n��$l",
	"lvl" : 50,
	"skill_name" : "ͨ�־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����ݡ��־���ȭ�߿�����������ݣ�����ʵ�أ�������$n���ض�ȥ",
	"lvl" : 60,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����Ρ��־���ȭ�����Σ����ڰ��ΰ��ѣ�$nһʱ��ڣ�ȭ����Ȼ����",
	"lvl" : 70,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����塹�־�����ȭֱ����ȭʽ�������ᣬ��$n��$l��ȥ",
	"lvl" : 80,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ������־��������ʵ�֮�Σ�ȭ����Ȼ�Գ���;ĩ·��ȴ����ɱ������$n��������ʩ��ȭ",
	"lvl" : 90,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����С��־�����ȭ������������ƫ���У�����ָ�����У�ȭ��ȴ��$n��������ס",
	"lvl" : 100,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ����Ū���־���ȭ�ж�Ȼ���Σ�������Ū$n��ȴ�ְ�������",
	"lvl" : 110,
	"skill_name" : "Ū�־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ����ͯ���־�����ȭ����ͯ������·������һ���$n��$l",
	"lvl" : 120,
	"skill_name" : "ͯ�־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ����ӹ���־�����ȭ����ʱ����򵥵���ʽ��ƽƽ���棬����ȴ��ס��$n����·",
	"lvl" : 130,
	"skill_name" : "ӹ�־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ���������־������������繭��ȭ���Ƽ���Ѹ�ݵ�Ϯ��$n",
	"lvl" : 140,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�����桹�־�������������棬ȭ��Ҳ�����䶯��$n���޷��ж���һȭ������",
	"lvl" : 150,
	"skill_name" : "���־�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	if ( this_player()->query("quest/jiebai/pass"))
		return usage=="cuff" || usage=="parry"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("ѧ����ȭ������֡�\n");
	if (!me->query("quest/jiebai/pass"))
		return notify_fail("��û�к��ܲ�ͨ���壬�����ѧ����ȭ��\n");
	if (me->query("max_neili") < 1000) 
		return notify_fail("�������������\n");
	if (me->query_skill("force", 1) < 40)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ȭ��\n");
	if (me->query("max_neili") < 250)
		return notify_fail("�������̫�����޷�������ȭ��\n");
	return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	object target=offensive_target(me);

	level   = (int) me->query_skill("kongming-quan",1);
	if( me->query_temp("kongming/ming")
	 && !me->query_temp("kongming/attack")
	 && random(level) > 50 ) {
		me->add_temp("kongming/attack",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
		me->delete_temp("kongming/attack");
		message_vision(HIW"\n$Nȭ�����գ������������ϣ���Ȼ��˫�ֺ�ֱ���ף�����һȭֱ��������\n"NOR,me);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	300 + random(350),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("kongming-quan", 1);
	int i = sizeof(action);
	mapping learned = me->query_learned();

	if (!mapp(learned)) learned = ([]);
	if (!learned["kongming-quan"])
		while (i--) 
			if (lvl == action[i]["lvl"])
				return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ������ͯѧ�µ���ʽ���޷���ý����ˡ�\n");

	if ( me->query("jingli") < 60)
		return notify_fail("�������̫���ˡ�\n");
	if ( me->query("neili") < 30)
		return notify_fail("�����������������ȭ��\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"kongming-quan/" + action;
}

int ob_hit(object ob, object me, int damage)
{

	if(me->query_skill_prepared("cuff")!= "kongming-quan"
	|| me->query_skill_mapped("parry") != "kongming-quan"
	|| me->query_temp("weapon")) 
		return 0;

	if ( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_temp("kongming/kong")
	&& random(me->query_skill("parry")) > ob->query("force", 1)/3
	&& !random(3)) {
		me->set_temp("fanzhen", 1);
		if( ob->query_skill_prepared("cuff")=="taiji-quan" 
			&& !ob->query_temp("weapon") 
			&& ob->query("family/family_name")=="�䵱��" ) {
			message_vision( HIW"$NǱ�ˡ��ա��־�����Ҫ��ȥ�Է��Ĵ����������$n���������ޱȣ�"
				+"������飬��Ȼ������ʵ����\n"NOR,me,ob );
			return 0;
		}
		if( !me->query_temp("kongming/ming") 
		&& random(me->query_skill("kongming-quan",1)) < ob->query_skill("force",1)/2 ) {
			message_vision( HIW"$NǱ�ˡ��ա��־���������$n�Ĵ󲿷ֹ�����\n"NOR,me,ob );
			return -damage*3/4;
		}
		else if( !me->query_temp("kongming/ming")) {
			message_vision( HIW"$NǱ�ˡ��ա��־�����$n�Ĵ����������Ρ�\n"NOR,me,ob );
			return -damage;
		}
		else {
			message_vision( HIW"$NǱ�ˡ��ա��־����������ķֶ��ã��޷��������������ֻ������$n��С���ֹ�����\n"NOR,me,ob );
			return -damage/3;
		}
	}
	return -damage/4;
}
