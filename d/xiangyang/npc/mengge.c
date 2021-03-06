//定义任务刷新地点，方便检查标记。 By lsxk@hsbbs 2007/7/10
#define JOB_CHECK_PLACE "/d/xiangyang/cross2"

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
int ask_attack();

void create()
{
    	set_name("蒙哥", ({ "meng ge", "meng", "ge" }));
    	set("title","蒙古元帅");
    	set("gender", "男性");
    	set("long", "这是此次负责进攻襄阳的蒙古元帅。\n");
    	set("age", 25);
    	set("str", 30);
    	set("int",20);
    	set("con",30);
    	set("dex",20);
    	set("combat_exp", 300000);
    	set("attitude", "friendly");
    	set("max_qi",2000);
    	set("max_jing",1000);
    	set("neili",2000);
    	set("max_neili",2000);
    	set("qi",2000);
    	set("jing",1000);
    	set("jingli",1000);
    	set("score", 100);
    	set("unique", 1);
        set("no_get", 1);
    	set("no_quest",1);

    	set_temp("special_die",1);
    	set_temp("xyjob/mg_attack",1);
    	set_temp("living", 1);

    	set_skill("force", 100);
    	set_skill("dodge", 100);
    	set_skill("parry", 100);
        set_skill("yijin-jing", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("blade", 100);
        set_skill("xiuluo-dao",100);
        set_skill("buddhism", 100);
        set_skill("literate", 100);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "xiuluo-dao");
        map_skill("blade", "xiuluo-dao");

// 限制人数
        set("sljob",3);
        set("xxjob",4);
        set("xsjob",2);
        set("gjob",1);
        set("job",6);

        set("inquiry", ([
          	"攻城": (: ask_attack :),
        ]) );

        setup();
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/clone/armor/armor")->wear();
}
int accept_object(object who, object obj)
{
    object me = present("meng ge", load_object("/d/xiangyang/yingzhang"));

    if(obj->query("id")!="menggu mihan"){
        command("? "+ who->query("id"));
        return 0;
    }
    if(JOB_CHECK_PLACE->query("xyjobing")){
        command("say 我军都已经在和襄阳守军苦战了，"+who->query("name")+"你到现在才送这封密函来。。。。。");
        command("sigh "+ who->query("id"));
        command("kick2 "+ who->query("id"));
        call_out("destroy_letter",1,obj);
        log_file("job/xyjob", sprintf(HIR"%8s%s欲在xyjob过程中使用蒙古密函开启襄阳攻防战,开启失败。"NOR, ctime(time())[4..19],who->name(1)+"("+who->query("id")+")")  );
        return 1;
    }
    command("thank "+who->query("id"));
    command("say 多谢"+who->query("name")+"前来送信，原来目前襄阳守军不足，正是我蒙古进军的好时机！");
    command("grin");
//    JOB_CHECK_PLACE->job_check(me);
    me->start_call_out( (: call_other, "/d/xiangyang/cross2", "xyjob_1" :),2 );
        log_file("job/xyjob", sprintf(HIG"%8s%s使用"+HIR+"蒙古密函"+HIG+"成功开启襄阳攻防战。"NOR, ctime(time())[4..19],who->name(1)+"("+who->query("id")+")")  );
    call_out("destroy_letter",1,obj);
    return 1;
}
void destroy_letter(object obj)
{
   if (!obj) return;
   destruct(obj);
   return;
}

int ask_attack()
{
        int i, a_exp = 0, d_exp= 0;
        object me, guo, room;
       	object *attackers, *defenders;

	me = this_player();
        room = load_object("/d/xiangyang/xuanwumen");
        guo = present("guo jing", room);

   if(wizardp(me))
	{
           command("say 神仙还是不要参加的好!");
		return 1;
	}

        if (!query("ready_attack") || !guo)
        {
            	command(" say 目前我军先锋无法攻破襄阳防守，本将军还在研究相应之策。");
            	return 1;
        }

	if (query("start_attack"))
        {
            	command(" say 我军已经开始进攻了，别问了！");
            	return 1;
        }

        if (me->query("combat_exp")<1000000)
        {
            	command("sneer");
            	command("say 就凭你这种三脚猫的功夫，能干什么?");
            	return 1;
        }

	if (me->query_conditions_by_type("poison") || me->query_conditions_by_type("hurt"))
        {
        	command("say 你身中剧毒，如何帮助我攻城？\n");
        	return 1;
        }

        if (me->query_condition("killer")) {
                notify_fail("你还是了结完江湖恩怨再来帮忙吧。\n");
                return 1;
        }

        if (me->query_temp("xyjob"))
        {
            	command("say 别心急，人手足了，我就会下令开战。");
           	return 1;
        }
        if (!"/cmds/std/xyjob"->player_list())
        	"/cmds/std/xyjob"->add_xyjob(me);

        defenders = filter_array("/cmds/std/xyjob"->player_list(), (: $1->query_temp("xyjob/xy_defend") :));
 	attackers = filter_array("/cmds/std/xyjob"->player_list(), (: $1->query_temp("xyjob/mg_attack") :));
        for(i = 0; i < sizeof(defenders); i++)
        {
		d_exp += defenders[i]->query("combat_exp");
		if (query_ip_number(defenders[i]) == query_ip_number(me))
		{
			command("say 你已经在防守襄阳了，难道还想来做奸细？\n");
			return 1;
		}
	}
    	for(i = 0; i < sizeof(attackers); i++)
	{
		a_exp += attackers[i]->query("combat_exp");
		if (query_ip_number(attackers[i]) == query_ip_number(me))
		{
			command("say 壮士不是已经在帮助我们了，开什么玩笑？\n");
			return 1;
		}
	}
    	if (a_exp - d_exp > 10000000)
	{
		command("say 我军高手众多，拿下襄阳城易如反掌，不用劳烦阁下了。\n");
		return 1;
	}

        command("ok");
        command("say 你就在此准备，等待我的军令，当作我军攻击襄阳的先锋!");
        "/cmds/std/xyjob"->add_xyjob(me);
        me->set_temp("special_die", 1);
        me->set_temp("special_poison", 1);
        me->set_temp("xyjob/attack", 1);
        me->set_temp("xyjob/mg_attack", 1);
        me->set_temp("living", 1);
        me->set_temp("apply/short", ({HIR"蒙古先锋军 "NOR+me->name()+"("+capitalize(me->query("id"))+")"}));
        me->apply_condition("job_busy", 100);
        me->set("job_name", "襄阳攻防战");
        return 1;
}

void kill_ob(object me)
{
	if (!me->query_temp("xyjob") || !me->query_temp("living"))
	{
        	me->remove_killer(this_object());
 		remove_killer(me);
 		return;
 	}
        ::kill_ob(me);
}

void die()
{
        object killer;

        command("chat 可恶啊，襄阳就... 就在眼前了...");
        command("chat* dead");

        if(objectp(killer = query_temp("last_damage_from")) && killer->query_temp("xyjob/xy_defend"))
                killer->add_temp("xyjob/defend", 1);
        if(objectp(killer = query_temp("last_damage_from")) && killer->query_temp("xyjob/mg_attack"))
                killer->add_temp("xyjob/attack", -1);
        ::die();
}
