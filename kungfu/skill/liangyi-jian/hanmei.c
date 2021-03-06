// Code Of ShenZhou 
// 昆仑派 - 两仪剑 - 寒梅剑阵 hanmei.c  
// by keny

#include <ansi.h> 
#define MAX_INARRAY 5 
#define MIN_INARRAY 2 
       
inherit F_DBASE; 
inherit F_SSERVER; 
       
string *ran_msg = ({ 
"低头闭眼，缓缓的拨动琴弦，原来是一首“雀巢”", 
"眼望远方，似有所思，弦中之音依稀是一首“绿衣”", 
"抚琴按弦，弹出一首“关雎”", 
}); 
       
string *ran_color = ({ HIC, HIG, HIY, HIR, HIM }); 
       
private string location(string direct); 
void check_fight(object leader); 
private void reset_effect(object *inarray, int partner, int ori_effect, int skill); 
private void remove_effect(object inarray, int skill); 
void random_msg(object leader); 
       
int perform(object me) 
{ 
int skill, ori_effect; 
int partner, num; 
int user_num; 
object victim, weapon; 
object leader, *obj, *inarray, env; 
object *user_list; 
string id; 
           
leader = 0; 
inarray = ({0, 0 , 0, 0, 0, 0}); 
           
if( me->query("family/family_name") !="昆仑派") 
return notify_fail("你不是昆仑派弟子耍这个干什么。 \n"); 
                       
if( (int)me->query_temp("hanmei") )  
return notify_fail("你已经在寒梅剑阵内。\n"); 

if( me->query_skill("sword") < 100 ) 
return notify_fail("你的两仪剑法还没熟练，令悟不了寒梅剑阵的精要！\n"); 
       
if( me->query_skill("dodge") < 100 ) 
return notify_fail("你的踏雪无痕还没熟练，令悟不了寒梅剑阵的步伐！\n");

if( !victim ) victim = offensive_target(me); 
       
if( !victim || !victim->is_character() || !me->is_fighting(victim) ) 
return notify_fail("寒梅剑阵只能对战斗中的对手使用。\n"); 
       
if( victim->query("family/family_name") == "昆仑派" )  
return notify_fail("你发疯了呀？干什么要对自己的同门这样。\n");  
               
if( me->query_skill_mapped("sword") != "liangyi-jian" || !objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword" )     
return notify_fail("你不用两仪剑法，怎样怖下寒梅剑阵呀？\n"); 
env = environment(me); 
obj = all_inventory(env); 
num = sizeof(obj); 
partner = 0;        
              
for( int i = 0; i < num; i++ ) { 
if( obj[i]->query_temp("hanmei") ) { 
if( !leader ) { 
if( obj[i]->query_temp("hanmei/is_leader") == -1 ) 
leader = obj[i]->query_temp("hanmei/data"); 
else 
leader = obj[i]; 
victim = leader->query_temp("hanmei/data")[0][MAX_INARRAY]; 
} 
partner++; 
} 
} 
                        
if( partner == 0 ) { 
inarray[0] = me; 
inarray[MAX_INARRAY] = victim; 
                                 
message_vision(HIG"$N手持"+(me->query_temp("weapon"))->query("name")+HIG"指住$n，等待著昆仑派弟子来助使出昆仑派的"+HIM"‘寒梅剑阵’。\n" NOR, me, victim); 
                      
user_list = users(); 
user_num = sizeof(user_list); 
             
while( user_num-- ) { 
if( !environment(user_list[user_num]) ) continue; 
if( user_list[user_num]->query("family/family_name") != "昆仑派") continue; 
if( environment(user_list[user_num]) == env ) continue; 
if( !living(user_list[user_num]) ) continue; 
if( location(file_name(env)) == location(file_name(environment(user_list[user_num]))) ) 
tell_object( user_list[user_num], HIG"你仿佛听见" + me->query("name") + "好象在准备用寒梅剑阵对付" + victim->query("name") + "。" + "\n听方向好象是" + env->query("short") + "。\n\n"NOR ); 
else  
tell_object( user_list[user_num], HIG"你仿佛听见" + env->query("short") + "传来的兵器硬碰声，好象有人在" + env->query("short") + "打斗著！\n\n"NOR );  
}  
                              
partner = 1; 
skill = me->query_skill("sword"); 
                      
for( int i=0; i < num; i++) { 
if( obj[i] == me ) continue; 
if( !living(obj[i]) ) continue; 
if( !obj[i]->is_character() || obj[i]->is_corpse() ) continue; 
if( !obj[i]->is_fighting(victim) ) continue; 
if( obj[i]->query_skill_mapped("sword") != "liangyi-jian" ) continue; 
if( !objectp(weapon = obj[i]->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword" ) continue;  
if( !obj[i]->is_fighting(victim) ) continue;                                              
if( (int)obj[i]->query_temp("hanmei") ) continue;               
                              
inarray[partner] = obj[i]; 
message_vision(HIY"$N一边长嚎说道：“既然同门有难，我就帮上一把吧。”" + "说著一边包围着$n。\n" NOR, inarray[partner], victim );  
skill += inarray[partner]->query_skill("sword"); 
partner++; 
if( partner == MAX_INARRAY ) break; 
} 
                     
me->set_temp("hanmei/is_leader", 1); 
me->set_temp("hanmei/data", ({ inarray, skill, partner }) ); 
                     
skill = (int)(skill / (partner*3)); 
if( partner > 1 ) { 
for( int i = 0; i < partner; i++ ) { 
inarray[i]->add_temp("apply/dodge",  skill ); 
if( i > 0 ) { 
inarray[i]->set_temp("hanmei/is_leader", -1); 
inarray[i]->set_temp("hanmei/data",  me ); 
} 
} 
} 
            
call_out("random_msg", 3, me); 
            
me->start_call_out( (: call_other, __FILE__, "check_fight", me :), 1); 
     
} 
              
else if( partner >= MAX_INARRAY )  
return notify_fail("寒梅剑阵只能够由二到五人施出。\n"); 
      
else { 
inarray = leader->query_temp("hanmei/data")[0]; 
skill = leader->query_temp("hanmei/data")[1]; 
ori_effect = (int)(skill / (partner*3)); 
if(partner == 1)  
leader->add_temp("apply/dodge", ori_effect ); 
me->add_temp("apply/dodge", ori_effect ); 
inarray[partner] = me; 
partner += 1; 
skill += me->query_skill("sword"); 
leader->set_temp("hanmei/data", ({ inarray, skill, partner }) ); 
reset_effect(inarray, partner, ori_effect, skill);       
me->fight_ob(victim); 
victim->fight_ob(me); 
me->set_temp("hanmei/is_leader", -1); 
me->set_temp("hanmei/data", leader); 
message_vision(HIG"$N一边长声喝道：“大胆的东西警然想伤害我们昆仑弟子”" + "一边加入寒梅剑阵，一边包围$n。\n" NOR, me, victim );  
for( int i = 0; i < partner-1; i++ ) 
tell_object(inarray[i], HIG"\n你看见有同门加入，不由得兴奋起来。\n"NOR);
} 
      
return 1; 
} 
      
private string location(string direct) 
{ 
int start, end, count, next; 
      
while (count != 3) { 
if( direct[next] == '/' ) count++; 
if (count == 2 && start == 0)  
start = next+1; 
next++; 
} 
end = next-2; 
direct = direct[start..end]; 
return direct; 
} 
      
void check_fight(object leader) 
{ 
object weapon, *inarray; 
int partner, skill, ori_effect, ori_partner; 
              
if( !leader->query_temp("hanmei") ) return; 
              
inarray = leader->query_temp("hanmei/data")[0]; 
skill = leader->query_temp("hanmei/data")[1]; 
partner = leader->query_temp("hanmei/data")[2]; 
ori_effect = (int)(skill / (partner*3)); 
ori_partner = partner; 
         
if( !living(inarray[MAX_INARRAY])  
|| !present(inarray[MAX_INARRAY]->query("id"), environment(leader))  
|| inarray[MAX_INARRAY]->query("qi") <= 50  
|| !leader->is_fighting(inarray[MAX_INARRAY])  
|| leader->query_skill_mapped("sword") != "liangyi-jian" 
|| !objectp(weapon = leader->query_temp("weapon"))  
|| (string)weapon->query("skill_type") != "sword" )   
{ 
if ( partner != 1 ) { 
for ( int i = 0; i < partner; i++ ) 
remove_effect(inarray[i], ori_effect); 
if (living( leader )) 
message_vision(HIB"$N大喊一声：“散阵！”。曲终人散，人散阵散。\n\n"NOR, leader); 
else 
message_vision(HIM"众人看见$N离去，再打下去也没有什么意思，慢慢的散去。\n\n"NOR, leader); 
} 
else { 
leader->delete_temp("hanmei"); 
if ( living(leader) ) 
message_vision(HIM"$N看见没有同门加入，心感人间没情，散开了寒梅方位。\n\n"NOR, leader);
} 
return; 
} 
                
else { 
for ( int i = 1; i < ori_partner; i++ ) { 
if ( inarray[i] == 0 ) break; 
if ( !inarray[i]->is_fighting(inarray[MAX_INARRAY])  
|| inarray[i]->query_skill_mapped("sword") != "liangyi-jian" 
|| !objectp(weapon = inarray[i]->query_temp("weapon"))  
|| (string)weapon->query("skill_type") != "sword" )  
{ 
message_vision(HIG"$N一边说道：“这就多谢各位同门的帮助，它日必定答报”，" + "一边说一边退出了寒梅剑阵。\n"NOR, inarray[i]);  
remove_effect(inarray[i], ori_effect); 
skill -= inarray[i]->query_skill("sword"); 
partner -= 1; 
if( i != partner ) {                       
inarray[i] = inarray[partner]; 
inarray[partner] = 0;                    
i--; 
} 
                          
else inarray[i] = 0; 
} 
} 
                  
if( ori_partner != partner ) { 
leader->set_temp("hanmei/data", ({inarray, skill, partner})); 
reset_effect(inarray, partner, ori_effect, skill);               
} 
} 
          
call_out("check_fight", 1, leader); 
} 
      
private void reset_effect(object *inarray, int partner, int ori_effect, int skill) 
{ 
skill = (int)(skill/(partner*3)); 
              
if(partner == 1)  
{ 
inarray[0]->add_temp("apply/dodge", -ori_effect ); 
return; 
} 
              
else { 
for( int i = 0; i < partner; i++ ) 
{ 
if(inarray[i] == 0 ) break; 
inarray[i]->add_temp("apply/dodge", -ori_effect ); 
inarray[i]->add_temp("apply/dodge", skill ); 
} 
} 
} 
      
private void remove_effect(object inarray, int skill) 
{ 
inarray->add_temp("apply/dodge", -skill ); 
inarray->delete_temp("hanmei"); 
} 
      
void random_msg(object leader) 
{ 
int partner; 
int ran; 
int ran_usr, ran_usr1; 
object obj, obj1, victim, weapon; 
              
if ( !leader->query_temp("hanmei/data") ) return;
if( partner = leader->query_temp("hanmei/data")[2] ) { 
if(random(5) < 2) { 
if( partner > 1 ) { 
ran_usr = random(partner); 
obj = leader->query_temp("hanmei/data")[0][ran_usr]; 
ran = random(5); 
message_vision( ran_color[ran] + "$N在寒梅剑阵外" + ran_msg[ran] + "\n" NOR, obj); 
victim = leader->query_temp("hanmei/data")[0][MAX_INARRAY]; 

if ( random(2) == 1 ) { 
if( obj->query_skill_prepare()["strike"] == "kunlun-zhang" ) { 
message_vision(ran_color[ran] + "$N招势万变，出掌攻向$n。\n"NOR, obj, victim); 
weapon = obj->query_temp("weapon"); 
COMBAT_D->do_attack(obj, victim, weapon, 1); 
COMBAT_D->do_attack(obj, victim, weapon, 1); 
obj->delete_temp("weapon"); 
obj->set_temp("action_flag",1); 
COMBAT_D->do_attack(obj, victim); 
COMBAT_D->do_attack(obj, victim); 
obj->set_temp("weapon", weapon);
obj->set_temp("action_flag",0); 
if ( obj->query("neili") >= 150 ) obj->add("neili", -10); 
}
}

else {   
do { 
ran_usr1 = random(partner); 
} while ( ran_usr1 == ran_usr); 
                                          
obj1 = leader->query_temp("dagou/data")[0][ran_usr1]; 
message_vision(ran_color[ran] + "$N和$n冒险使出昆仑快剑，双剑合壁，所向无敌。\n"NOR, obj, obj1); 
COMBAT_D->do_attack(obj, victim, obj->query_temp("weapon"), 1); 
COMBAT_D->do_attack(obj, victim, obj->query_temp("weapon"), 1); 
obj1->set_temp("action_flag", 1); 
COMBAT_D->do_attack(obj1, victim, obj1->query_temp("weapon"), 1);
COMBAT_D->do_attack(obj, victim, obj->query_temp("weapon"), 1);  
obj1->set_temp("action_flag", 0); 
if ( obj->query("neili") >= 150 ) obj->add("neili", -5); 
if ( obj1->query("neili") >= 150 ) obj1->add("neili", -5); 
} 
} 
else 
message_vision( ran_color[ran] + "$N仍然孤身作战，跳到阵外" + ran_msg[ran] + "并尽量避免硬碰硬，等待支缓。\n"NOR, leader);  
} 
                              
call_out("random_msg", 3, leader);
} 
}
