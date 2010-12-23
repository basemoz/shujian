// dagou-bang.c �򹷰���
// Code By Looklove@SJ 2001/4/1
// Modify By Looklove 2001.4.8
// Looklove modified at 2001.5.5
// Looklove modified at 2001.5.18
// Lane@SJ modified at 2005.7.26
// Update by lsxk@hsbbs 2007/7/3

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$Nһ������������$w��ʹ��һʽ����ݾ��ߡ�����ɨ��$n��$l",
	"lvl" : 0,
	"skill_name": "��ݾ���",
	"damage_type": "����"
]),
([
	"action": "$N������Ծ������$w���һζ���һ�С�����Ѱ�ߡ���$n��$l��ȥ",
	"lvl":10,
	"skill_name": "����Ѱ��",
	"damage_type": "����"
]),
([
	"action": "$N����$wһȦ��ʹ��һ�С����Ŵ򹷡���$n����˷�Χ���ܲ�͸��",
	"lvl" : 20,
	"skill_name": "���Ŵ�",
	"damage_type": "����"
]),
([
	"action": "$N��̤��λ��ʩ�����������졹�����ֽ�$w����������$n��ȥ",
	"lvl" : 30,
	"skill_name": "��������",
	"damage_type": "����"
]),
([
	"action": "$N���һ����������ǽ��������һ������$w��ͷ����$n��$l",
	"lvl" : 50,
	"skill_name": "������ǽ",
	"damage_type": "����"
]),
([
	"action": "$Nʹ��һ�С�����˫Ȯ��������$w���������������$n��$l",
	"lvl" : 80,
	"skill_name": "����˫Ȯ",
	"damage_type": "����"
]),
([
	"action": "$N����һ����һ�С���Ȯ��·����������$w��$n��ȥ�Ʒ��˹�ȥ",
	"lvl" : 100,
	"skill_name": "��Ȯ��·",
	"damage_type": "����"
]),
([
	"action": "$Nһ�С�����ͷ����ֻ��$wͻȻ����ֱ��$n�Ķ���",
	"lvl" : 120,
	"skill_name": "����ͷ",
	"damage_type": "����"
]),
([
	"action": "ֻ��$Nʹ��һ�С�б�򹷱���������š����$wб����$n��$l",
	"lvl" : 140,
	"skill_name": "б�򹷱�",
	"damage_type": "����"
]),
([
	"action": "$N���һ����ʹ��һ�С����ع��Ρ������ֽ�$w����$n��$l",
	"lvl" : 160,
	"skill_name": "���ع���",
	"damage_type": "����"
]),
([
	"action": "$Nһ�С����붴������$w���˸���������ɨ$n��$l",
	"lvl" : 180,
	"skill_name": "���붴",
	"damage_type": "����"
]),
([
	"action": "$N�����������$wһ�ϣ�ʹһ�С�ѹ�繷��������ͷ��������$n��$l",
	"lvl" : 200,
	"skill_name": "ѹ�繷��",
	"damage_type": "����"
]),
});

string *wugou_action=({
HIC"��Ȼ$N��������������ٰ�б����ʹ���������޹�����һ�䣬����$n�ļ�ͷ��"NOR,
HIW"$N���������ʹ���������޹����ڶ��䣬�Ӱ���ɨ$n�Ľ��ס�"NOR,
HIG"$Nʹ���������޹��������䣬�����а���Բ�ˣ�ͻȻֱͱ$n���۾���"NOR,
HIB"ֻ�������Ӱһͣ��$N���������޹������ı�ʹ�����������а���һ��һ��,бб����$n��С����"NOR,
HIR"$Nʹ���������޹�������䣬����ǵذ������������Ӱ���в���$n�����š�"NOR,
HIY"$N����ƫ�壬��������Ӱ����Ȼʹ���ǡ������޹��������䡣ɲ�Ǽ������Ӱ��ס$nȫ��!"NOR
});

int valid_enable(string usage) { return (usage == "stick") || (usage == "parry"); }

int valid_learn(object me)
{
	if( me->query("family/master_name") != "���߹�" )
		return notify_fail("�򹷰���ֻ�ܴӺ��߹���ѧ����\n");
	if( me->query_skill("stick", 1) < 20 )
		return notify_fail("��Ļ�������̫��, ����᲻�˴򹷰�����\n");
	if( me->query("gender") == "����" )
		return notify_fail("��һ�����в�Ů֮�������ѧ�򹷰���\n");
	if( me->query("max_neili") < 100 )
		return notify_fail("�������������\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if( level > action[i]["lvl"] )
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, j, m, level,wx,deads;
	string msg;

	deads = (int)me->query("death_times") - 100;
	deads = deads/2 + random(deads/2);

	if( me->query("combat_exp") < 1000000 ) m = 50;
	else if( me->query("combat_exp") < 3000000 ) m = 100;
	else if( me->query("combat_exp") < 5000000 ) m = 150;
	else if( me->query("combat_exp") < 7000000 ) m = 200;
	else if( me->query("combat_exp") < 9000000 ) m = 250;
	else m = 300;

	if( deads < 0 ) deads = 0;
	if( deads > m ) deads = m;

	wx = (int)me->query_int(1)/3+random(me->query_skill("bangjue",1)/10);
	wx += me->query("gender") == "Ů��"?deads/8:deads/10;
//   if( wizardp(me) ) tell_object(me, HIY"��"YEL"("BLK"Ұ��"YEL")"HIY"���������ӳ�(�ۼ�����)ָ��Ϊ��"+wx+"�㡣\n"NOR);

 	weapon = me->query_temp("weapon");
	level  = (int)me->query_skill("dagou-bang", 1);

   if( me->query_temp("dgb/wugou") ) {
           msg = wugou_action[(int)me->query_temp("dgb/wugou")-1];
           return ([
                   "action":       msg,
                   "dodge":        random(20)+wx,
                   "parry":        random(20)+wx,
                   "damage":       140+random(160),
                   "force":        260+random(360),
                   "damage_type":  "����"
           ]);
   }

	if( me->query_temp("shuangjue/dgb") ) {
		switch((int)me->query_temp("shuangjue/dgb") ) {
			case 3: msg = HIW"$N���������Ȼһ����Х�����������Ӱ����$n��$l"NOR; break;
			case 2: msg = HIG"$N��ȻбŲһ�����������һ��������$w"HIG"��ɨ��$n��$l"NOR; break;
			case 1: msg =  HIC"$N����ͻ�䣬��ȻԾ��ֻ��$w"HIC"����һ�Ű�Ӱֱ��$n��$l��ȥ"NOR;break;
			default: msg = HIW"$N���������Ȼһ����Х�����������Ӱ����$n��$l"NOR; break;
		}
		me->add_temp("shuangjue/dgb", -1);
		return ([
			"action":	msg,
			"dodge":	random(20)+wx,
			"parry":	random(20)+wx,
			"damage":	130+random(140),
			"force":	250+random(350),
			"damage_type":	"����"
		]);
	}
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action" : action[j]["action"],
				"dodge": me->query("gender")=="Ů��"?random(20)-10+wx:random(20)-15+wx,
				"parry": me->query("gender")=="Ů��"?random(30)+wx/2:random(20)+wx/2,
				"damage": me->query("gender")=="Ů��"?80+random(140):70+random(130),
				"force" : me->query("gender")=="Ů��"?200+random(350):180+random(320),
				"attack": random(wx/4)+wx/4,
				"lvl" : action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
			]);
		}
}

int practice_skill(object me)
{
	object weapon;
	int lvl = me->query_skill("dagou-bang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if( !objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "stick" )
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( me->query("jingli") < 50 )
		return notify_fail("��ľ����������򹷰�����\n");

	if( me->query("neili") < 20 )
		return notify_fail("��������������򹷰���\n");

	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dagou-bang/" + action;
}


int ob_hit(object ob, object me, int damage)
{
	object weapon,twp;
	string msg;
	int j, p, level;

	weapon = me->query_temp("weapon");
	twp = ob->query_temp("weapon");
	level = me->query_skill("dagou-bang",1);

	if( me->query_temp("fanzhen") ) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if( me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang"
	 || ! weapon
	 || weapon->query("skill_type") != "stick"
	 || ob->query("env/invisibility"))
		return 0;

	if( random(level) > 100
	 && random(me->query_skill("bangjue", 1)) > 100
	 && me->query("neili") > 500
	 && random(level) > ob->query_skill("parry", 1)/2
	 && random(20) > 7) {
		me->add("neili", -50);
		if( twp ) {
			msg = HIM"$n"+ twp->name() +HIM"һ�и���������$Nʹ�����⡹�־�����ӰƮƮ����ʱ���Լ�\n"NOR;
			msg += HIM"��ǰ����֮�ؾ�����ס�ˡ�$n����֮�£�ֻ�к���һ�������۱仯��\n"NOR;
			ob->add_busy(1+random(2));
			me->add("neili",-70);
			j = -damage;
		}
		else {
			msg = HIM"$n����ָ��Ҫ����$N����ͻȻֻ����Ӱ������"NOR;
			msg += HIM""+weapon->name() +HIM "һ�ơ��⡹�־������������޷���\n"NOR;
			msg += HIM"$n�����ѱ����ص�����һ�£���æ������������ɫб�������Ͼ�����һ���亹��\n"NOR;
			ob->receive_damage("qi", damage/3 > 0?damage/3:20, me);
			ob->receive_wound("qi", damage/5 > 0?damage/5:10, me);
			p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			me->add("neili",-100);
			j = -damage;
		}
		me->set_temp("fanzhen", 1);
		message_vision(msg, me, ob);
		return j;
	}
}

int help(object me)
{
        write(HIG"\n�򹷰���"NOR"\n");
        write(@HELP
        �򹷰����а����������������������⡢ת�˾������������µ�
        ؤ�������������ᡢ�顢�桢����ƣ��轫�������Ĵ�ֻ����Ӱ
        ������Ӱ����ѧ�����Ե�����������ǧ����˴򹷰����ľ�����
        ���������֡���ϰʱ�粻ͬʱѧϰ�������ս��޷���ɡ�

HELP
        );
        return 1;
}

                                                                                      
