// linglong.c �������

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBCYN"�������"NOR; }
int perform(object me, object target)
{
//       string msg;
       int ap, dp, damage, jl, i;
       object weapon;

       weapon = me->query_temp("weapon");
       if( !target ) target = offensive_target(me);

       if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
             return notify_fail("�����������ֻ����ս����ʹ�á�\n");

       if (!weapon 
        || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang")
             return notify_fail("�������ް����޷�ʹ�á������������\n");
       
       if((int)me->query_int() < 20)
             return notify_fail("�����Բ���,����ʹ�á������������\n");

       if( (int)me->query_skill("huntian-qigong", 1) < 200 )
             return notify_fail("��Ļ���������Ϊ������ʹ���������������������\n");

       if (me->query_skill_mapped("force") != "huntian-qigong")
             return notify_fail("û�л���������Ϊ���������޷�ʹ������������������ģ�\n"); 

       if((int)me->query_skill("dagou-bang",1) < 200)
             return notify_fail("��Ĵ򹷰�����Ϊ����,Ŀǰ������ʹ�á������������\n");

       if ((int)me->query_skill("bangjue",1) < 150)
             return notify_fail("��������������Դ򹷰���Ϊ�����ģ�������������ʹ�ã�\n");

       if((int)me->query("max_neili") < 2000)
             return notify_fail("��������Ϊ���ڲ���, �����á������������\n");

       if ((int)me->query("neili") < 800)
             return notify_fail("�������þ�, �����á������������\n");

       if( target->query_temp("dgb_chan"))
             return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɢ�\n");

       message_vision( HIY"\n$N����һЦ�������Ѽ���˫Ŀ�������䣬���������дʡ�", me, target);
       message_vision(    "�������ӻ�����һ�ű�Ӱ���͵�$n����\n��ǿ�䡱�����縮����", me, target);
       message_vision(    "����׵��������̨���������ࡱ����ҪѨ��ֻҪ�����˵��У��������ˡ�\n"NOR, me, target);
     //  message_vision(msg, me, target);  
ap= random(me->query_skill("dagou-bang",1))+me->query_skill("bangjue",1)/50*(1+random(me->query_int()/2));
dp= (int)target->query_skill("dodge",1);
       me->add("neili", -200);
       if( ap > dp ) {
       damage = me->query_skill("dagou-bang",1)*2+me->query_skill("bangjue",1)*(1+random(me->query("int")/3));
         if (damage > 2000) damage=2000+random(damage/5);
   message_vision(CYN"\n$n�������ã����ڲ��������мܣ�ֻ����ǰ��Ծ���ܣ���֪$N�ĵ�����಻�ϣ�һ�㲻�У�\n"+
                "�ֵ�һѨ����Ӱֻ��$n�����Ѩ�ϻ�����ȥ��$nһ��������������!\n"NOR,me,target);
         target->receive_damage("qi",damage);
         target->receive_damage("jingli",damage/2);
         target->receive_wound("qi",damage/2);
 switch(random(3)) {
             	case 3: target->apply_condition("no_exert",3); message_vision(    HIR"$n��$Nһ��������"+(random(2)?"��"HIC"ǿ��Ѩ"HIR"��":"��"HIW"��̨Ѩ"HIR"��")+"����ʱͷ����ѣ�����������޷���ת���硣\n"NOR, me, target);
   
break;
 case 2:target->apply_condition("no_force",3); message_vision(    HIR"$n��$Nһ��������"+(random(2)?"��"HIG"�縮Ѩ"HIR"��":"��"HIY"�ٻ�Ѩ"HIR"��")+"����ʱ��ɫ�԰ף���Ϣ���ҡ�\n"NOR, me, target);
 
break;
 
case 1:target->apply_condition("no_perform",3);
message_vision(    HIR"$n��$Nһ��������"+(random(2)?"��"HIM"��׵Ѩ"HIR"��":"��"HIB"����Ѩ"HIR"��")+"����ʱ�ж��ٻ��������⹦����ʹ�á�\n"NOR, me, target);
break;default: target->apply_condition("no_exert",3); 
message_vision(    HIR"$n��$Nһ��������"+(random(2)?"��"HIC"ǿ��Ѩ"HIR"��":"��"HIW"��̨Ѩ"HIR"��")+"����ʱ��ɫ�԰ף����������޷���ת���硣\n"NOR, me, target);
break;} COMBAT_D->report_status(target, 0);  me->add("neili", -300);
         me->start_busy(1);
  if(wizardp(me)) tell_object(me,sprintf("damage=%d\n",damage));
           //  message_vision(msg, me, target);
    
       me->start_perform(4,"�����������");
   }
       else if(ap > dp/3*2){
        message_vision( HIG"$N�����е�����������ǽ��δ� �����������β��������֮��$n���̽����������С�\n" NOR,me,target);
        // message_vision(msg,me,target); 
         me->add("neili", -200);
  target->start_busy(1);
       for (jl=0; jl<4 ;jl++)
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
          //  me->start_busy(1);
   
       me->start_perform(4,"�����������");
    }
       else if( ap > dp/2){
          message_vision( HIG"$N����������������ӵ�ʩ���� �����˫ȮĪ��ͷ����, ��֮��Ӱ���Ӷ��£�$n�����������м��¡�\n"NOR, me, target);
       //  message_vision(msg, me, target);
         me->add("neili", -200);
 i = random(5) +3;
         target->add_busy(i);
         target->set_temp("dgb_chan", 1);
    
       me->start_perform(5,"�����������");
     call_out("check_fight", 1, me, target, weapon, i);
       }
       else {
           message_vision(WHT"$n��ʶ��ؤ����񼼡�������������������ϵл���ԶԶ���˿�ȥ��\n"NOR, me, target);
        me->start_busy(1+random(2));
       //   message_vision(msg, me, target);
    
       me->start_perform(3,"�����������");
   }
       me->add("jingli", -100);
    return 1;
}

void check_fight(object me,object target,object weapon, int count)
{
       if( !target) return;
       if( !target->query_temp("dgb_chan")) return;
       if( ! me
        || !me->is_fighting()
        || weapon != me->query_temp("weapon")
        || count < 1){
         target->delete_temp("dgb_chan");
         if( target->is_busy())
          target->start_busy(1);
         return;
       }
       call_out("check_fight",1 ,me ,target ,weapon, count -1);
}

