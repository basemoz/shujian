// pill.c
// snowman 15.12.98
/*
在文件尾加上 inherit F_PILL

 药物里加上set("healup", "...") 是药物的作用。比如：
    set("healup", ([
	"add_neili": 2000,
	"add_jingli": 2000,	
	]));

 加 set("drug_msg", ([
	   "start_eat": "$N服下一份玉真散。\n",
           "finish_eat": "$N的脸色渐渐开始好转了。\n",
      ]));

 其他还有：heal_eff_qi，heal_eff_jing，等等。
 加上no_fight，表示fight时不能吃这种药
 CONDITION_EAT 是连续吃药所造成的后果，方便起见，用 #define :), 比如：
      #define CONDITION_EAT me->add("neili", -100)

不好的是，这个 inherit F_PILL;  必须放在文件尾，而不是文件头。

*/

#ifndef CONDITION_EAT
#define CONDITION_EAT me->add("neili", -100)
#endif

#include <ansi.h>
#include <dbase.h>
#include <name.h>

void init()
{
	add_action("do_eat", "fu");
}
int do_drug(string key, mixed i)
{
        switch(key) {
             case "heal_eff_qi": if ((int)this_player()->query("eff_qi") < (int)this_player()->query("max_qi"))
                             this_player()->receive_curing("qi", i); break;
             case "heal_eff_jing": if ((int)this_player()->query("eff_jing") < (int)this_player()->query("max_jing"))
                             this_player()->receive_curing("jing", i); break;
             case "add_jingli": this_player()->add("jingli", i); break;             
             case "add_neili": this_player()->add("neili", i); break;
             case "add_max_jingli": this_player()->add("max_jingli", i); break;
             case "add_max_neili": this_player()->add("max_neili", i); break;
             case "food": this_player()->add("food", i); break;
             case "water": this_player()->add("water", i); break;
             case "clear_all_condition": this_player()->clear_condition(); break;
             case "clear_type": this_player()->clear_conditions_by_type(i); break;
             case "apply_condition": this_player()->apply_condition(i); break;
             case "del_temp": this_player()->delete_temp(i); break;
             case "del": this_player()->delete(i); break;
             case "add_str": this_player()->add_temp("apply/strength", i); break;
             case "add_dex": this_player()->add_temp("apply/dexerity", i); break;
             case "add_int": this_player()->add_temp("apply/intelligence", i); break;
             case "add_con": this_player()->add_temp("apply/constitution", i); break;
             case "add_damage": this_player()->add_temp("apply/damage", i); break;
             case "add_attack": this_player()->add_temp("apply/attack", i); break;
        default: break;
        }
    return 1;
}
int do_eat(string arg)
{
	mapping healup, msg;
        object me, ob;
        string *key;
        int i;
        me = this_player();
        ob = this_object();

        if(!this_object()->id(arg) || !living(this_player())) return 0;
	if(me->is_busy() )
		return notify_fail("你正忙着呢。\n");
        if(!mapp(healup = ob->query("healup")) )
		return notify_fail("这样东西不能服用。\n");
        if(query("no_fight") )
                return notify_fail("你战斗中吃药有害五益！\n");	
        
        msg = ob->query("drug_msg");

	if (!msg || undefinedp(msg["start_eat"]))
                message_vision("$N吃下一"+ob->query("unit")+"$n。\n", me, ob);
        else
                message_vision(msg["start_eat"], me, ob);

        if((int)query("condition") && me->query_condition("medicine") > 0){
                if (!msg || undefinedp(msg["condition_eat"]))
                       message_vision(HIR"$N看起来摇摇欲坠，原来是连续服药导致药性过猛！\n"NOR, me, ob);
                else   message_vision(msg["condition_eat"], me, ob);
                CONDITION_EAT;
                return 1;
                }
        key = keys(healup);
        i = sizeof(key);
        while(i--) do_drug(key[i], healup[key[i]]);

        if (!msg || undefinedp(msg["finish_eat"]))
                EMOTE_D->do_emote(me, "stuff");
        else    message_vision(msg["finish_eat"], me, ob);

        if((int)query("condition"))
                me->apply_condition("medicine", query("condition"));
        if(query("busy_time")) 
                me->start_busy(query("busy_time"));
        else me->start_busy(1);
        if(ob->query_amount()) ob->add_amount(-1);
        else destruct(ob);
	return 1;
}


