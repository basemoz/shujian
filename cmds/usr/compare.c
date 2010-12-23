// 以实战经验 气的最大值 防御力 攻击力 str con 及 杀气
// 以公式判断敌我 并加入 实力差别之级数 


#include <ansi.h>
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object ob, string str)
{
	int range,range1,range2,range3;
	int ex1,ex2,ke1,ke2,se1,se2,wc1,wc2,be1,be2,dz1,dz2;
	int at1,at2,st1,st2,co1,co2,force1,force2,mana1,mana2;
	object me = this_player();
	
	ex2 = me->query("combat_exp");
	ke2 = (int)me->query("max_jing");
	se2 = (int)me->query("max_jingli");
	force2 = (int)me->query("max_neili");
	mana2 = (int)me->query("max_qi");
	wc2 = (int)me->query_temp("apply/armor");
	at2 = (int)me->query_temp("apply/damage");
	st2 = (int)me->query("str");
	co2 = (int)me->query("con");
	be2 = (int)me->query("int");
	dz2 = (int)me->query("dex");

	range1=(force2/2+mana2/2+ex2/4+ke2+se2+wc2*2+be2+dz2+at2*2+st2+co2);

	    if(!str) {
		notify_fail("使用方法 : <compare [对象]>\n");
		return 0;
	    }
	    ob = present(str,environment(me));
	    if(!ob) {
		notify_fail(str+" 不在这里\n");
		return 0;
	    }
		if( !ob->is_character() || ob->is_corpse() || ob->is_ghost() )
	       	return notify_fail("看清楚一点，那并不是活物。\n");//By waiwai@2001/05/05 changed.
	
	    if(ob==me) {
	        notify_fail("自己和自己比较的结果是一样的。\n");
	        return 0;
	    }
	ex1=ob->query("combat_exp");
	ke1=(int)ob->query("max_jing");
	se1=(int)ob->query("max_jingli");
	force1=(int)ob->query("max_neili");
	mana1=(int)ob->query("max_qi");
	wc1=(int)ob->query_temp("apply/armor");
	at1=(int)ob->query_temp("apply/damage");
	st1=(int)ob->query("str");
	co1=(int)ob->query("con");
	be1=(int)ob->query("int");
	dz1=(int)ob->query("dex");
	
	range3=((ex1+ex2)/200);
	
	range2= (se1+force1/2+mana1/2+ex1/4+ke1+wc1*2+be1+dz1+at1*2+st1+co1);

	if(wizardp(me)) printf("range3=%d\n",range3);
	if(!range3) range3=1;
	if(!range2) range2=1;

	range= ((range2/range3)-(range1/range3));

	if( userp(ob) ) {
	
	if( time()-me->query_temp("compare_time")<0) {
        notify_fail("请不要频繁骚扰别人。。。\n");
        return 0;
	} else {
	tell_object(ob,
	YEL"你突然感到好象" WHT+ me->name() +NOR YEL "正在鬼鬼祟祟地探测你……\n"NOR);
	me->set_temp("compare_time",time()+180);

       }
	}
       write("你仔细的上前打量了"+HIG+ob->name()+NOR+"一番。\n");
       if(range < - 30) {
       write("你要杀死"+HIG+ob->name()+NOR+"就如要踩死蚂蚁般容易。\n");
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIR"超级菜鸟肉脚"NOR"的级数。\n");
       return 1;
    }
       if(range < -25) {
      	write("哇哈哈哈～, "+HIG+ob->name()+NOR+"看起来根本不是你的对手!\n");
	write("你以本身修为判断"+ob->name()+"的江湖历练大约是"HIR"普通菜鸟肉脚"NOR"的级数。\n");
	return 1;
     }
     if (range < -20) {
	write("你感觉"+HIG+ob->name()+NOR+"不过是个大肉脚, 根本不屑一顾。\n");
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIC"小卒仔"NOR"的级数。\n");
         return 1;
     }
       if (range < -15) {
	write("虽然从各方面看来你都比"+HIG+ob->name()+NOR+"略胜一筹, 但是也不能轻敌。\n");
	write("你以本身修为判断"+ob->name()+"江湖历练大约是"HIC"普通角色"NOR"的级数。\n");
      return 1;
     }
        else if(range < -5) {
	write("你感觉"+HIG+ob->name()+NOR+"跟你势钧力敌, 看来将有一场龙争虎斗。\n");
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIY"不分上下，伯仲之间"NOR"的级数。\n");
       return 1;
      }
      else if(range < 10) {
	write("你感觉"+HIG+ob->name()+NOR+"比你强一点, 你必需要有充份的准备才有胜算。\n");
	write("你以本身修为判断"+ob->name()+"的江湖历练大约是"HIY"普通硬角"NOR"的级数。\n");
          return 1;
       }
       else if(range < 20) {
       write("小心点，"+HIG+ob->name()+NOR+"比你略胜一筹, 你的胜算不大。\n");
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIY"一般高手"NOR"的级数。\n");
       return 1;
       }
        else if(range < 25) {
       write("小心点，"+HIG+ob->name()+NOR+"可是很硬的喔, 得花一番功夫。\n");
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIM"武林高手"NOR"的级数。\n");
       return 1;
	}
        else if(range < 30) {
          write("算了吧, 要打倒 "+HIG+ob->name()+NOR+" 得再回去苦练十年。\n");
          write(HIC"你开始感觉到一股强大的气息向你逼进。\n"NOR);
	  write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIM"深不可测"NOR"的级数。\n");
        return 1;
       }
       else if(range <35) {
          write("凭你的实力想打倒"+ob->name()+", 简直是难如登天。\n");
	write(HIY"你感觉到一股十分强大的气息向你迫进。\n"NOR);
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIW"空前绝后"NOR"的级数。\n");
         return 1;
      } else {
	write("别梦想了 , 直接去自杀也许对你还比较快喔, "+HIG+ob->name()+NOR+"的实力深不可测!\n");
	write(HIY"你感觉到十分惊人的力量和杀气从"+HIG+ob->name()+HIY+"身上散发出来。\n"NOR);
	write("你以本身修为判断"+HIG+ob->name()+NOR+"的江湖历练大约是"HIW"天神般无所伦比"NOR"的级数。\n");
       return 1;  
    }
}

int help()
{
write(@LONG

指令格式 : compare [对象]
指令说明 : 比较你和对方的强度

关联参数：
最大气血，最大精，最大内力，最大精力
力量，根骨，悟性，身法，盔甲保护

LONG);
	return 1;
}

