// dugu-jiujian.c ���¾Ž�
// By Spiderii ���Ƹ��� ����450 lv ��ԾЧ��������auto���趨ΪA������
// Update by lsxk@hsbbs �趨ֻ�н��ڲſ���ʹ�ã����Ч������һ������must_be_hit.  2007/7/26

inherit SKILL;
#include <ansi.h>
#include <combat.h>

string *dodge_msg = ({
"$nͦ��һ�����ǡ����Ƴ�ᶡ��ش�$N��$l����ͼ��$N�Ĺ��ƻ��⡣\n",
"$n�������ܣ��ٽ������ʹ�������両�ࡹ����$N��$l���뵲��$N���С�\n",
"ֻ��$n���˷���������Ʈ�磬�����һʽ�������������������޶�����׽����ָ��$N��$l��\n",
"$n�˽���磬��������з���$N��$l�����Ա�$N���أ��������ǡ���ħ�����ġ�����ʽ����\n",
"$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$N�͹����ػӳ���λ�����̩ɽ���������������\n",
"ȴ��$n̤ǰһ������ʽбָ$N��$l����Ҫʹ$N������ˡ�\n",
"$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ�����ġ������������ع�$N��\n",
"$n�ٽ���ӣ�Ѹ���ޱȵص���$N��$l��ȴ���˿�������������ʲô��ʽ��\n",
});

string *msg = ({
"$Nͦ���ش�$n��$l���������ǻ�ɽ�����ġ����Ƴ�ᶡ�����ɽ�����ġ��������ڡ����Ƶ�$n���أ�ֹͣ��$N�Ĺ���",
"$N������ת�������̳�ʮ�Ž�����Ȼ�ǻ�ɽ����Ůʮ�Ž��������������ʮ�Ž�����һ�У��ַ�֮�죬ֱ�Ƿ�����˼",
"$N������$n�ӳ���Ȫ��ܽ�ء����������ϸǡ�����ʯ�����������������������������ף�ڡ���ɽ����",
"$NͻȻʹ��������ɷ罣���ġ����ڤڤ�������Ƿ�λȴ����ƫ�$w����$nһ�ʣ���ͼͻ��$n�Ĺ���",
"$N����ͻ�䣬ʹ����ɽ�ġ�һ������㡹������$n��$l����֪������;��ͻȻת�򣬴��$n����֮��",
"$N����$w��ʹ��̫���������⣬�������СС������ԲȦ�������޾�ԴԴ�����ز���$n",
"ȴ��$N���潣�ߣ����һ�գ��ұ�һ�䣬����Ҳ��ԽתԽ�Ӻ�����������̩ɽʮ���̡�Ϊһ������$n",
"$N��ɫ���أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n������ħ���������¶����",
"$N���ƺ��������裬�������������������ɽ����Ϊһ������$n������ȥ",
"$NͻȻ�˽����һ�ֹ���ġ������罣��������Ȼ��$n�����Ҵ�����",
"$N����ͻ������ɭ�ϣ�����ǧ�������۶�������ǹ��ꪣ���ɳǧ�������ɽ���ƻ���$n",
"$N����$wԽתԽ�죬ʹ�ľ�Ȼ�Ǻ�ɽ�ġ��ٱ�ǧ������ʮ��ʽ������ʽ�����ƾ���ӿ���Թ��߲��ɵ�ĿΪ֮ѣ",
"ֻ��$N����������һ�����ǡ�������ɽ��������$w����ն�䣬ֱ����$n��$l",
"����$Nͦ����ϣ�$wһ����һ�з·�̩ɽ�����ġ�������Ȫ��ֱ��$n��$l",
"$n��׼$Nһ�л�ɽ�������з����ǡ������ƣ�׼�����з�����ȴ��$NͻȻ�鲽������ʹ�������䵱�����ѵ�ˮ����һ��",
"$n����$N��$l��$N���˷�����ʹ����ɽ���С�������롹��ɭɭ������������",
"$N����Ծ�𣬳������硸�����ա��������Ƚ��б��ϣ���תΪ�����������������⻮��$n��$l",
"$N����һ�£���������һ���׺磬��$nֱ�̹�ȥ����һ�ж�����ΰ��������ɽ�����еġ�ǧ���������������ǻ�ɽ�����ġ��ޱ���ľ��",
"$N�������أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n������Ħ���������¶����",
"$N��Ц����������ׯ�ϣ�$w��ӣ����ڡ���Ħ����Ϊһʽ������ش���$n"
});

string *feiyue_msg = ({
"$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��֪����Ǻ�",
"$N����һ��ָ��$n���������$n���������ڣ��˵����������ף�����˼��",
"$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮����ʵ�����Ѳ�",
"$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����ʲô����",
"$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ��������ȵ�$n���ò���",
"$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������$n��$l",
"$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N��������ʵ",
"$N���ֺὣ����$n��$l���������������е�һ��������ȴ�����$n���Կ��彣������",
});


int valid_enable(string usage)
{
   //if ( this_player()->query("fengset") && this_player()->query("quest/huashan")=="����" )
		return (usage == "sword") || (usage == "parry") || (usage =="dodge");
}

int valid_learn(object me)
{
	mapping my_fam  = me->query("family");
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if(!my_fam || my_fam["master_name"] != "������")
		return notify_fail("�㲻�Ƿ�����ĵ��ӣ�����ѧϰ�����¾Ž�����\n");

	if ( me->query("max_neili") < 1000)
		return notify_fail("�������������\n");

	if ( me->query_skill("dugu-jiujian",1) > 60 && me->query_skill("dugu-jiujian", 1) < 300 )
		return notify_fail("���׽����Ҿͽ̵�������Ժ��Ҫ�����Լ�ȥ�����ˡ�\n");
	return 1;
}


mapping query_action(object me, object weapon)
{
	int i, j, level, damage;

	level = me->query_skill("dugu-jiujian", 1);
	i = random(me->query_skill("sword"))+50;
	if( i<100 ) i = 100;
	j = random(40)-5;
	damage = (random(6)+1)*35;
	if( damage < 50 ) damage =50;

		if( level > 450 ) {
			return ([
                           "action": HIW+replace_string(replace_string(feiyue_msg[random(sizeof(feiyue_msg))], "$w", "$w"), "$w", "$w"HIW)+NOR,
				"damage": 150 + random(120),
				"damage_type": "����",
				"dodge":  random(20),
				"parry":  random(20),
				"force":  300 + random(250),

			]);
		}

		else return ([
			"action": msg[random(sizeof(msg))],
			"damage": 130 + random(140),
			"damage_type": "����",
			"dodge":  random(30),
			"force":  250 + random(300),
		]);
	}


string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if ( me->query_skill("dugu-jiujian", 1 ) < 300)
		return notify_fail("���¾Ž�ֻ��ͨ����������ߡ�\n");

	if ( me->query("jingli") < 50)
		return notify_fail("����������������¾Ž���\n");
	if ( me->query("neili") < 20)
		return notify_fail("�������������ϰ���¾Ž���\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dugu-jiujian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1;
	int i;
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;

	i = me->query_skill("dugu-jiujian", 1);

   if(i>=350){
       if(random(i)>(int)victim->query_skill("parry",1)*2/3
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIG"$n��ʱ����$N���������й����Լ������������޷�����ܿ������º�Ȼ������\n"NOR,me,victim);
            victim->set_temp("must_be_hit",1);
            call_out("dgjj_must_be_hit",2,me,victim,random(i/50));
       }
   }

   if(i>=250){
       if(random(i)>(int)victim->query_skill("dodge",1)/2
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIB"$nֻ��$N���й����Լ�������ֻ�ó��з��أ�˿��û�н������ᣡ\n"NOR,me,victim);
            victim->set_temp("no_fight",1);
            victim->apply_condition("no_fight",1);
       }
   }

	if( weapon1 && i >= 200 && living(victim)
	 && me->query_skill_mapped("parry") == "dugu-jiujian"
	 /*&& random(me->query("combat_exp")) > victim->query("combat_exp")/2*/ ) {
		message_vision(HIW"$Nһ���Ϻȣ�ʹ�����¾Ž�������ء��ƽ�$n��"+weapon->name()+HIW"�ó����ؽ�Ӱ������˿����$n����"+weapon1->name()+HIW"��ȥ��\n"NOR, me,victim);
		if( random(me->query("int")) > victim->query("int")/3 ) {
			me->add("neili", -50);
                   victim->add_busy(1+random(2));
			message_vision(HIC"$N��ʱ����ѹ������������һ�飬����"+weapon1->name()+"���ֶ�����\n"NOR, victim);
			weapon1->unequip();
			weapon1->move(environment(victim));
		}
		else {
			message_vision(HIC"����$n������$N�Ľ�·�����̲�ȡ���ƣ�ʹ$N�ġ�����ء�û�����κ����á���\n"NOR, me,victim);
                    me->start_perform(2,"������ء�");
		}
	}
     
}

void dgjj_must_be_hit(object me,object target,int i)
{
    if(!target) return;
    if(!me) {
        target->delete_temp("must_be_hit");
        if(living(target))
            message_vision(HIY"$n�������˿������ֽŻָ���������\n"NOR,target);
        return;
    }
    if(wizardp(me) && me->query("env/dgjj_test")) write("i is "+i+"\n"NOR);
    if(me->query_skill_mapped("sword")!="dugu-jiujian"
     ||me->query_skill_mapped("parry")!="dugu-jiujian"
     ||i<=0){
        if(living(target))
            message_vision(HIY"$n�������˿������ֽŻָ���������\n"NOR,me,target);
        target->delete_temp("must_be_hit");
        return;
    }
    call_out("dgjj_must_be_hit",1,me,target,--i);
}
