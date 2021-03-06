        // zhenwu.c
// By Scatter 1/4/2002

inherit F_CLEAN_UP;

#include <ansi.h>
#include <skill.h>



inherit F_SSERVER;
string *position = ({
                                         "在阳方","在阴方","在阴方","在阴方","在阳方","在阳方","在阳方"
});

string *sword = ({
        "虚步提腰，一招「蜻蜓点水」，手中的剑轻轻颤动，一剑剑点向对手的左手。",
        "右脚独立，一招「大魁星」，剑由前向后反刺对手的左脚。",
        "一招「探海式」，右脚独立，左膝提起，剑向前抡劈对手的腰部。",
        "一招「右拦扫」，一招「左拦扫」，剑锋平指，一气呵成横扫对手的手臂。",
        "使出「三环套月」，剑划出三个圆圈，剑锋直出，绵绵不断划向对手。",
        "一转身，剑向后斜带，一招「风卷荷叶」，砍向对手。",
        "向前连跳两步，一招「野马跳涧」，剑向前平刺对手的胸部。",
        "左脚向前进一步，剑由后划一整圆向前托起，一招「迎风掸尘」，刺向对手的右脚。",
        "紧接着左脚前进一步，右手的剑一招「顺水推舟」，向右后方刺向对手的右臂。",
        "右脚向前垫步，一招「海底捞月」，剑由上向后划一个大弧，向前撩向对手。",
        "剑招未曾使老，已然圈转。突然之间，对手眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已。"
});

string *zhen =  ({
        "配合天时，地利，人和，阵式由弱势转为强势，由阴转为阳。",
        "真武七截阵的阵势令人叹为观止，当场将士气提升到最高。",
        "只见着真武七截阵使出借力打力的最高境界，对手的武功暂时不起任何作用。",
        "只见真武七截阵里的所有人配合的天衣无缝，眼看对手的气数以尽。"
});


int check_ob(object ob,object me);
void start_zhenwu(object ob, int mypos,int zhenwu_time );
int zhenwu(object me);
int halt_zhenwu(object me);
int do_zhenwu(string arg);
int zhenwu(object me);
int halt_zhenwu(object me);
int stop_zhenwu();

void create() { seteuid(getuid()); }


int main(object me, string arg)
{
                  object enemy;
                  int zhenwu_time,i,mypos=0,power,zw_power;
                  object here;
                  string name1,name2,enemy_id;
                  object ob1,ob2,ob3;

                                  if( !this_player()->query("canzhenwu") )
                                          return notify_fail("你还不能使出真武七截阵！\n");
                  if( this_player()->is_busy() )
                  {
                                return notify_fail("你正忙着呢！\n");
                  }

                  here = environment( this_player() );

                  if( !arg || sscanf(arg, "%s %s %s", enemy_id,name1,name2)!=3 )
                                         return notify_fail("zhenwu enemy ally1 ally2\n");

                  if( !(enemy = present(enemy_id, here) ) )
                  {
                                return notify_fail(enemy_id+"不在这里！\n");
                  }

                  if( enemy->query("race") != "人类" )
                  {
                                return notify_fail("杀鸡焉用牛刀？\n");
                  }

                  if( enemy->query("family/family_name") == "武当派" )
                  {
                                return notify_fail("你要清理门户？\n");
                  }


                  if( !(ob1 = present(name1, here ) ) )
                  {
                                return notify_fail(name1+"不在这里！\n");
                  }

                  if( ob1->is_busy() )
                  {
                                return notify_fail(name1+"正忙着呢！\n");
                  }
                  
                  i = check_ob(ob1,me);
                  if(  i !=1) return i;

                  if( !(ob2 = present(name2, here) ) )
                  {
                                return notify_fail(name2+"不在这里！\n");
                  }

                  if( ob2->is_busy() )
                  {
                                return notify_fail(name2+"正忙着呢！\n");
                  }

                  i = check_ob(ob2,me);
                  if(  i !=1) return i;

                  if( name1 == me->query("id") ||   name2 == me->query("id")  )
                  {
                                return notify_fail("想一身数用？你不会分身术吧？\n");
                  }

                  if( name1 == name2 )
                  {
                                return notify_fail(name1 + "不会分身术吧？\n");
                  }


                  power = me->query("force") + ob1->query("force")+ob2->query("force");
                  power += me->query("sword") + ob1->query("sword")+ob2->query("sword");
                  power += me->query("str") + ob1->query("str")+ob2->query("str");
                  power += me->query("dex") + ob1->query("dex")+ob2->query("dex");
                  zw_power = me->query("taiji-shengong") + ob1->query("taiji-shengong")+ob2->query("taiji-shengong");
                  power = power / 140/2;
                  zw_power /= 70/5;
                  power *= zw_power;

                  if(power>50)power=50;
                  if(power,15)power=15;


                  start_zhenwu(me,0,power);
                  start_zhenwu(ob1,1,power);
                  start_zhenwu(ob2,2,power);

                  here->set_temp("ob1",me->query("id"));
                  here->set_temp("ob2",ob1->query("id"));
                  here->set_temp("ob3",ob2->query("id"));

                  message_vision(HIR"\n$N对$n喝道：" + RANK_D->query_rude(enemy) + "你一向为非作歹，今天武当派要替天行道，纳命来！\n"NOR, me, enemy);
                  me->kill_ob(enemy);
                  ob1->kill_ob(enemy);
                  ob2->kill_ob(enemy);
                  enemy->kill_ob(me);
                  enemy->kill_ob(ob1);
                  enemy->kill_ob(ob2);
                  message_vision(HIY"$N突然身形移动，发动武当弟子就站战斗位置，摆出了"+ HIW +"「真武七截阵」"+ HIY + "阵法。\n\n"NOR, me);
                                  message_vision(HIG"

        MM.                M;                              ,. -M.                 MM
        MM;MXH             MM                              MM  M;.M               MM
     ==MMMMMMM,            $M ,            =               -M  M; MX        -M+.  MM$@
   =MMMMM;-,             = MM MMM.        .MM            ;;MMMMM; %M      $MMMM;M@MM$@
       ,M ;;           =HM=-M  %$          M;            ,;;M  @; :,      ;M @    M$=M+
     M@MMMMM:         MM@; .M.;;           M=             -HMHMHMMMM$     ;M,M MM;MM/MM
     MMMMMMM          .-MMMMMMMM           M, .HMMMM   =MMMM;- ;M         ;M M;HM;MMMMM
     MH$; -M        ;$MMM@. M              M;MMMMH$M      MMMX  M- M+     ;M $M=M;MX M%
     MMMMMMM        :MM-M;  MH       -$MMMMM@$;-         MM;MMM;HM MM     ;M;MM-M;MMMM;
     M+M;,-M            M;..$X        :MH  M             MX$M%, :M:M:     ;M    %%MH-@ "NOR, me);
                                message_vision(HIG"
     MHMMMMM         MM MMMM;M;            M            MMMMMMM:.MMM      MM    , MM=;MMM
     M;;:.;M+MM;     -M M;   MM            M,          ;H;M;MMM; MM       $M MMMMMMMMMMMM.
  --:MXMMMMMMMMM:     M M;:%. M            M+    :;      +X$M+   XM       M$  .   M;      
 ;MMMM;;--M$         .M@MM+,  MM  M        /MMMMMMM%     $M;MMMM=MM/ ;    M$      M;      
     $MM  ,M$,     -$MM$=     =M,-M          ---;        HX$;, ,@+XM:M    +;      M;      
    @M@;   MMM      XM$        MMMM                      M;   ,M;  MMM            M=      
  ;;@-      :M                  ;MM                      /-   .     $M-           M.\n"NOR, me);
                                                                          
                  return 1;
}


int check_ob(object ob,object me)
{
        string ob_name;
        object weapon;
        float exp_diff;

                          if( !objectp(ob) )
                          {
                                         return notify_fail("可惜没有这个人。\n");
                          }
                                  ob_name = ob->query("name");

                                  if ( !present( ob->query("id"), environment(me) ) )
                                  {
                                         return notify_fail("可惜"+ob_name+"不在这里。\n");
                                  }

                                  if ( ob->query("family/family_name") != "武当派" )
                                  {
                                         return notify_fail("可惜"+ob_name+"不是武当弟子，不会「太极神功」。\n");
                                  }


                                  if ( ob->query_skill("taiji-jian",1) <100 || ob->query("combat_exp",1)<50000 ||
                                                ob->query_skill("dodge") < 100
                                          )
                                  {
                                         return notify_fail("可惜"+ob_name+"武功太差，不会「太极神功」。\n");
                                  }

                                  exp_diff = (float)( ob->query("combat_exp" ) - me->query("combat_exp") ) / (float)me->query("combat_exp");

                                  if( exp_diff > 0.3 || exp_diff < -0.3 )
                                         return notify_fail("可惜"+ob_name+"武功和你差距太大，不能共摆「真武七截阵」。\n");

                 return 1;
}

void start_zhenwu(object ob, int mypos,int zhenwu_time )
{
                        ob->set_temp("pending/zhenwu", 1);
                        ob->set_temp("zhenwu_time", zhenwu_time*2);
                        ob->set_temp("zw_pos", mypos);
                        ob->set_temp("zw_power",zhenwu_time);
                        ob->start_busy((: zhenwu :), (:halt_zhenwu:));
}




void destruct_me(object me)
{
        if(me)
                destruct(me);
}

void check_leaving(object me)
{
        string name = me->query("id");

         if( !userp(me) )
                {
                 object enemy = offensive_target(me);
                 if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
                 {
                         message_vision(HIY"\n$N作了个楫道：剩下来的就交给你们，在下先告退了！\n"NOR, me);
                         call_out("destruct_me",10,me);
                         return;
                  }

                  call_out("check_leaving",5,me);
          }
}

int zhenwu(object me)
{
                  object  where = environment(this_player());
                  int zhenwu_time = (int)me->query_temp("zhenwu_time");
                  object room, obj,enemy,weapon;
                  int cost, bonus,mypos=me->query_temp("bd_pos");
                  int power;
                  object ob1,ob2,ob3,ob4,ob5,ob6,ob7;


                  if( !(room = environment(this_player())) )

                  {

                                  if(!objectp(weapon = me->query_temp("weapon"))

                                                || (string)weapon->query("skill_type") != "sword" )
                                                {
                                                        message_vision(HIW"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西拨开，退出了「真武七截阵」。\n"NOR, me);
                                                }
                                else
                                        message_vision(HIW"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);

                                me->remove_all_enemy();

                                me->delete_temp("pending/zhenwu");
                                me->delete_temp("zhenwu_time");
                                me->delete_temp("zw_pos");
                                me->delete_temp("zw_power");
                                call_out("check_leaving",2,me);

                          return 0;

                        }

                  enemy = offensive_target(me);


                  if( enemy && enemy->query_temp("yield") )

                  {

                                  if(!objectp(weapon = me->query_temp("weapon"))

                                                || (string)weapon->query("skill_type") != "sword" )
                                                {
                                                        message_vision(HIG"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西拨开，退出了「真武七截阵」。\n"NOR, me);
                                                }
                                        else
                                          message_vision(HIG"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);


                                        message_vision(HIY"\n$N大声道：武当不杀不反手之人，这位"+RANK_D->query_respect(enemy)+HIY"请走吧！\n"NOR, me);

                                        me->remove_all_enemy();

                                        me->delete_temp("pending/zhenwu");
                                        me->delete_temp("zhenwu_time");
                                        me->delete_temp("zw_pos");
                                        me->delete_temp("zw_power");
                                        room->delete_temp("ob1");
                                        room->delete_temp("ob2");
                                        room->delete_temp("ob3");

                                        call_out("check_leaving",2,me);
                                        return 0;
                  }


                  if ( me->query("neili") < 60 || me->query("jingli")<50 )
                  {
                                  if(!objectp(weapon = me->query_temp("weapon"))
                                                || (string)weapon->query("skill_type") != "sword" )
                                                {
                                                        message_vision(HIR"\n$N体力不支，只好身子向后一纵，退出「真武七截阵」。\n"NOR, me);
                                                }
                                  else
                                                message_vision(HIR"\n$N体力不支，只好身子向后一纵，退出「真武七截阵」。\n"NOR, me);

                                        me->remove_all_enemy();
                                        me->delete_temp("pending/zhenwu");
                                        me->delete_temp("zhenwu_time");
                                        me->delete_temp("zw_pos");
                                        me->delete_temp("zw_power");
                                        call_out("check_leaving",2,me);
                                         return 0;
                  }

                  if( !( room->query_temp("ob1",1) &&
                                (objectp(ob1=present( room->query_temp("ob1",1),where) ) ) && ob1->query_temp("zhenwu_time") &&
                                (objectp(ob2=present( room->query_temp("ob2",1),where) ) ) && ob2->query_temp("zhenwu_time") &&
                                (objectp(ob3=present( room->query_temp("ob3",1),where) ) ) && ob3->query_temp("zhenwu_time") )
                         )
                         {
                                  if(!objectp(weapon = me->query_temp("weapon"))
                                                || (string)weapon->query("skill_type") != "sword" )
                                                {
                                                        message_vision(HIW"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西拨开，退出了「真武七截阵」。\n"NOR, me);
                                                }
                                        else
                                          message_vision(HIW"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);

                                        me->remove_all_enemy();
                                        me->delete_temp("pending/zhenwu");
                                        me->delete_temp("zhenwu_time");
                                        me->delete_temp("zw_pos");
                                        me->delete_temp("zw_power");
                                        room->delete_temp("ob1");
                                        room->delete_temp("ob2");
                                        room->delete_temp("ob3");

                                        call_out("check_leaving",2,me);
                                        return 0;
                         }


                  zhenwu_time = zhenwu_time-1;
                  me->set_temp("zhenwu_time", zhenwu_time);

                  bonus = random( ( me->query("int")+me->query("con")+25 ) / 30 ) + (me->query("int")+me->query("con")+25 ) / 30;
                  if( bonus > 3 ) bonus = 3;


                  if(enemy) bonus = bonus * 2 * ( enemy->query("combat_exp") - me->query("combat_exp") ) / me->query("combat_exp");
                  else bonus = 0;

                  if( bonus <0 ) bonus = 0;
                  if( bonus > 8 ) bonus = 8;

                  if( (int)me->query("potential") < (int)me->query("max_potential") )
                                         me->add( "potential", bonus/2 );

                  me->add( "combat_exp", bonus*2/3 );
                  me->improve_skill( "taiji-shengong", random(bonus*2/3) );

                  enemy = offensive_target(me);

                  power = me->query_temp("zw_power",1)*4;


                  if( random(6)==1 )
                  {
                          tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());

                          if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
                                  enemy->start_busy( random(2) );
                  }

                  if( objectp(enemy) && objectp( present( enemy->query("id"),environment(me) )) )
                  {
                          me->set_temp("apply/parry",me->query_temp("apply/parry",1)+power);
                          me->set_temp("apply/armor",me->query_temp("apply/armor",1)+power);
                          if( random(2)==1 )
                          {
                                  if(random(2)==0)
                                          message_vision("\n" + position[mypos] + "位上的$N踏上乾卦，使出此阵最强攻击力，凝重的攻势有如真武大帝的龟将临阵不乱。", me);
                                  else message_vision("\n" + position[mypos] + "位上的$N由阳转阴，由乾转坤，出招身法轻浮犹如蛇将，似左似右，犹如灵蛇出洞一般，另敌人难以招架。", me);

                                  me->set_temp("apply/damage",me->query_temp("apply/damage",1)+power/2);
                                  me->set_temp("apply/attack",me->query_temp("apply/attack",1)+power/2);
                                  COMBAT_D->do_attack(me, enemy, me->query_temp("weapon"));
                                  me->set_temp("apply/damage",me->query_temp("apply/damage",1)-power/2);
                                  me->set_temp("apply/attack",me->query_temp("apply/attack",1)-power/2);
                                  me->receive_damage("jingli", 15+random(15), "运转真武七截阵累死了");
                                  me->add("neili", -20-random(20));
                          }
                          me->set_temp("apply/parry",me->query_temp("apply/parry",1)-power);
                          me->set_temp("apply/armor",me->query_temp("apply/armor",1)-power);
                          return 1;
                  }
                  else
                  {
                                if ( random(3)==1 )
                                {
                                        if( ( weapon = me->query_temp("weapon") )
                                                 && (string)weapon->query("skill_type") == "sword" )
                                        {
                                                message_vision("\n" + position[mypos] + "位上的$N"+ sword[random(10)]+"\n", me);
                                        }

                                        me->receive_damage("jingli", 15+random(10), "练习真武七截阵累死了");
                                        me->add("neili", -20-random(15) );
                                }
                  }


         me->delete_temp("pending/zhenwu");
         me->delete_temp("zhenwu_time");
         me->delete_temp("zw_pos", mypos);
          if(!objectp(weapon = me->query_temp("weapon"))
                        || (string)weapon->query("skill_type") != "sword" )
                        {
                                message_vision(HIW"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西拨开，退出了「真武七截阵」。\n"NOR, me);
                        }
                else
                        message_vision(HIW"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);


         call_out("check_leaving",5,me);
         return 0;
}

void restart (object me)
{
        start_zhenwu(me, me->query_temp("zw_pos"), me->query_temp("zhenwu_time",1) );
}

int halt_zhenwu(object me)
{
          object weapon;
          int zhenwu_time = (int)me->query_temp("zhenwu_time",1);
          if (zhenwu_time > 0)
          {
                        if( !living(me) ) return 1;

                        if(random(2)==1)
                        {
                                message_vision(HIY"\n$N受到敌手出奇不意的一击，$N赶紧使出四两拨千斤，敌手被震开了，$N差点站不稳。\n"NOR, me);
                        }
                        else message_vision(MAG"\n$N被打的晃了几晃，$N赶紧使出四两拨千斤，敌手被震开了，又站稳了步子。\n"NOR, me);
                        call_out("restart",4,me);
                        return 1;
          }

          if(!objectp(weapon = me->query_temp("weapon"))
                        || (string)weapon->query("skill_type") != "sword" )
                {
                        message_vision(HIW"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西拨开，退出了「真武七截阵」。\n"NOR, me);
                }
                else
                        message_vision(HIW"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);

          me->delete_temp("pending/zhenwu");
          me->delete_temp("zhenwu_time");
          me->delete_temp("zw_pos");
          me->delete_temp("zw_power");
          return 1;
}

int stop_zhenwu()
{
          object weapon,me=this_player();
          if(!me->query_temp("pending/zhenwu"))
                                         return notify_fail("停什么？你不在运行「天罡北斗阵」。\n");
          if(!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword" )
          {
                message_vision(HIG"\n$N身子向后一纵，使一招『四两拨千斤』将周围的东西震开，退出了「真武七截阵」\n"NOR, me);
                }
         else
                message_vision(HIG"\n$N身子向后一纵，使一招『青龙出水』，在空中倒刺一下，退出了「真武七截阵」。\n"NOR, me);

          me->remove_all_enemy();
          me->delete_temp("pending/zhenwu");
          me->delete_temp("zhenwu_time");
          me->delete_temp("zw_pos");
          me->delete_temp("zw_power");
          return 1;
}



int help(object me)
{
                  write(@HELP
指令格式 : zhenwu <enemy> <对象1> <对象2> <对象3>

「真武七截阵」为张三丰所创，武当山一向供奉「真武大帝」。张三丰一日心血来潮，\n
见到真武神像座前的龟蛇二将，想起长江和汉水之会的蛇山、龟山，心想长蛇灵动，乌龟凝重，\n
真武大帝左右一龟一蛇，正是兼收至灵至重的两件物性，因而创了一套精妙无方的武功出来。\n
这套武功便是从龟蛇二山大气磅礴，从山势演化出来的武功，森然万有，包罗极广。\n
这套武功最大特色为若是七为高人合使，便如同六十四人高手合使一般，其威力之猛，\n
实是无可比拟。

HELP
                  );
                  return 1;
}
