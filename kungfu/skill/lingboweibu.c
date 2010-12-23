// lingboweibu.c �貨΢��

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$n����һ�����ģ���������б���벽��ǡ�������貨΢���С��������塹�Ĳ��ӣ����˿�����\n" ,
	"dodge"  : 30
]),
([      "action" : "$nʹ���������ѩ������бб���˼������ƺ������·���ȴ�ڼ䲻�ݻ��Ŀ�϶�ж����$N�Ĺ��ơ�\n",
	"dodge"  : 40
]),
([      "action" : "$N����ʽ�������԰�$nΧס����֪���ģ�$nһʽ�����Ʊ��¡���������Ȱ�Ŀ����Ȧ��\n",
	"dodge"  : 50
]),
([      "action" : "$nһʽ���������ҡ���հ֮��ǰ�������ں�$N��ʽ������$n���Ӽ��������֮�\n",
	"dodge"  : 60
]),
([      "action" : "$n����������ͻȻת��ʹ���ˡ������ϡ���$N�ӽ����ƣ����޷�����$nһƬ�½ǡ�\n",
	"dodge"  : 70
]),
([      "action" : "$n���һ����ʹ����է������������������̤��������̤ʵ֮ʱ�����������������ϡ�\n",
	"dodge"  : 80
]),
([      "action" : "$nһʽ��Ʈ�����񡹣�����б�����������ȼá���������δ�á������ü��������۵�$N�����\n",
	"dodge"  : 90
]),
([      "action" : "$nһʽ����Ѹ���ɡ����ƺ��Թ��Ե�̤����������ᣬÿһ����̤�ڱ������벻�������ڡ�\n",
	"dodge"  : 100
])
});

mapping query_action(object me)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("lingboweibu");

	if (level < 80 )
		zhaoshu--;

	if (level < 60 )
		zhaoshu--;

	if (level < 40 )
		zhaoshu--;

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge" || usage == "parry";
}

int valid_learn(object me)
{
    if ((int)me->query_skill("literate", 1) < 100)
		return notify_fail("���֪ʶ�������޷�����貨΢����\n");
 //   if ((int)me->query_skill("qimen-bagua", 1) < 40)
//		return notify_fail("����������е�֪ʶ�������޷�����貨΢����\n");
    if ((int)me->query("int") < 40)
		return notify_fail("������Բ������޷�����貨΢����\n");

	   return 1;
}

string query_dodge_msg(object me)
{
	mapping action;

	action = query_action(me);

	return action["action"];
}

int practice_skill(object me)
{
       if( (int)me->query("max_neili") < 1200 )
		return notify_fail("���������Ϊ̫�ǿ���貨΢��ֻ���߻���ħ��\n");
	if( (int)me->query("jingli") < 30 )
		return notify_fail("�������̫���ˣ��������貨΢����\n");
if( (int)me->query("jing") < 20 )
		return notify_fail("�������̫���ˣ��������貨΢����\n");
if( (int)me->query("qi") < 20 )
		return notify_fail("�������̫���ˣ��������貨΢����\n");

	me->receive_damage("jing", 10);
       me->receive_damage("jingli", 25);
       me->receive_damage("qi", 15);
	me->improve_skill("force", (int)me->query("int")/2);

	return 1;
}
int ob_hit(object ob, object me, int damage)
{
        object wp1;
        string msg;
        int p,j,skill, neili, neili1;
        wp1 = ob->query_temp("weapon");
        skill = me->query_skill("lingboweibu", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

      if(me->query_temp("lingboweibu")){
           me->delete_temp("lingboweibu");
           return 1;
           }
      if(skill > random(ob->query_skill("dodge", 1)) 
         && me->query("combat_exp") > ob->query("combat_exp")/2
         && me->query_skill_mapped("dodge") == "lingboweibu"
         && neili > 400 && skill > 80)
        {
         me->add_temp("lingboweibu", 1);    
         msg = "$N�������κζ�����ֻ������һ��һת�����һ��ת��$n�ı���";
	  tell_object(ob, HIR "��ֻ����ǰһ���������˶��ֵ���Ӱ��\n" NOR);
         if(neili >= neili1+random(neili1)+damage){
              msg += "$nһ�д�գ���æ���������������˻�����\n",
              ob->receive_damage("qi", damage);
              p = ob->query("qi")*100/ob->query("max_qi");
              msg += COMBAT_D->damage_msg(damage/2, "����");
              msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
              j = -(damage*3);
              ob->start_busy(1);
              }             
           else if(neili >= random(neili1)+damage){
              msg += "���$n����������㿪�ˣ�\n", 
              j = -(damage*2+skill*2);
              }
           else if(neili < random(neili1)+damage && neili*2 > random(neili1)+damage){
              msg += "���$n�������������һ�룡\n", 
              j = damage/2;               
              }
           else{
              msg += "���$Nֻ�����$n��һС��������\n", 
              j = damage/2+random(damage/2); 
              }           
           message_vision(msg, me, ob);
           return j;
           }          
}
