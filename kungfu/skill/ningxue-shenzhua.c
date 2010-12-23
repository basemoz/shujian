// ningxue-shenzhua.c ��Ѫ��ץ

#include <ansi.h>
inherit SKILL;  

mapping *action = ({
([
"action": "$N˫��ƽƽ�ᵽ��ǰ����ɫ���صĻ���ʩ����"HIG"����̽צ"NOR"��ץ��$n��$l",
"lvl" : 0,
"damage_type": "����"
]),
([
"action": "$NͻȻ���η���˫�־Ӹ�����һ�С�"HIC"��ӥ����"NOR"��ץ��$n��$l",
"lvl" : 30,
"damage_type": "����"
]),
([
"action": "$N����һ�С�"HIB"�ڻ�����"NOR"����Ѹ���ޱȵ�ץ��$n��$l",
"lvl" : 80,
"damage_type": "����"
]),
([
"action": "$N˫��ʩ��һ�С�"HIY"̩ɽѹ��"NOR"�����������ŷ���ץ��$n��$l",
"lvl" : 130,
"damage_type": "����"
]),
([
"action": "$N���־۳ɻ�צ״������һ�С�"HIR"��Ѫ��ץ"NOR"������ץ��$n��$l",
"lvl" : 200,
"damage_type": "����"
]),
});

int valid_enable(string usage)
{
return usage=="claw" ||  usage=="parry"; 
}

int valid_learn(object me)
{
if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
return notify_fail("����Ѫ��ץ������֡�\n");
if ((int)me->query("max_neili") < 100)
return notify_fail("�������̫�����޷�����Ѫ��ץ��\n");
if ( me->query_skill("ningxue-shenzhua", 1) < 150 )
return notify_fail("�����ڵ���Ѫ��ץ��ֻ��ͨ�����������ߡ�\n");
return 1;
}

string query_skill_name(int level)
{
int i = sizeof(action);

while (i--)
if(level > action[i]["lvl"])
return action[i]["skill_name"];
}

mapping query_action(object me)
{
int i, j, level;
level = me->query_skill("ningxue-shenzhua",1);

for(i = sizeof(action); i > 0; i--){
if(level > action[i-1]["lvl"]){
j = NewRandom(i, 20, level/5);
if( me->query_temp("nxsz_pfm")) {
return ([
"action":HIR + replace_string(action[j]["action"], NOR, HIR)+NOR,
//"action" :HIR+action[j]["action"]+NOR,
"damage_type":"����",
"dodge":random(35),
"parry":random(35),
"force":350 + random(350),
"damage":50 + random(50),
]);
}
return ([
"action":action[j]["action"],
"damage_type":action[j]["damage_type"],
"lvl":action[j]["lvl"],
"force":300 + random(350),
"dodge":random(30),
"parry":random(30),
]);
}
}
}

void ningxue(object me, object victim)
{
if (!me || !victim || !me->is_fighting(victim))
return;

if( random(me->query_skill("ningxue-shenzhua", 1)) > 150 
&& me->query("neili") > 1500 
&& !me->query_temp("weapon")) {
message_vision(HIR"\n$N��$n�������֮�ʣ��Ҳ�̤ǰ�����ֺ�ڳ�ץʽ�͹�$n���У�\n"NOR, me, victim);
me->set_temp("nxsz_pfm", 1);
me->add_temp("apply/claw", me->query_skill("ningxue-shenzhua", 1)/3);
COMBAT_D->do_attack(me, victim, 0, random(3)?1:3);
if (me->is_fighting(victim))
COMBAT_D->do_attack(me, victim, 0, random(2)?1:3);
me->add_temp("apply/claw", -me->query_skill("ningxue-shenzhua", 1)/3);
me->delete_temp("nxsz_pfm");
}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
if ( !me->query_temp("nxsz_pfm"))
call_out((: ningxue :), 1, me, victim);
}

int practice_skill(object me)
{
if ( me->query("jingli") < 60)
return notify_fail("��ľ������������书��\n");
if ( me->query("neili") < 30)
return notify_fail("����������������书��\n");
me->receive_damage("jingli", 50);
me->add("neili", -20);
return 1;
}

string perform_action_file(string action)
{
return __DIR__"ningxue-shenzhua/" + action;
}
