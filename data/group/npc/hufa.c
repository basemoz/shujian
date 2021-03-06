inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include <ansi.h>

string ask_rob();

string *skill = ({ 
	"longzhua-gong", "ruying-suixingtui", "yizhi-chan", "jingang-quan",
	"qianye-shou", "nianhua-zhi", "zhenshan-mianzhang", "jieshou-jiushi",
	"yiyang-zhi", "qishang-quan", "lanhua-shou", "poyu-quan",
	"xianglong-zhang", "huagu-mianzhang", "jiuyin-baiguzhua", "anran-zhang",
	}); 

string *force = ({
	"yijin-jing", "yijin-jing", "yijin-jing", "yijin-jing",
	"yijin-jing", "yijin-jing", "yinyun-ziqi", "linji-zhuang",
	"qiantian-yiyang", "shenghuo-shengong", "bihai-chaosheng","zixia-gong",
	"huntian-qigong", "dulong-dafa", "linji-zhuang", "yunu-xinjing",
	});

string *perform = ({
	"canyun", "ruying", "wofo", "fumo",
	"qianshou", "fuxue", "bingdi", "foguang",
	"sandie", "qishang", "fuxue", "leidong",
	"paiyun", "bujue", "jiuyin", "anran",
	});

string *base = ({
	"claw", "leg", "finger", "cuff",
	"hand", "finger", "strike", "hand",
	"finger", "cuff", "hand", "cuff",
	"strike", "strike", "claw", "strike",
	}); 

void create()
{
    set_name("护法", ({ "hufa zhanglao", "hufa", "zhanglao"}));

	set("init",0);
	
    set("gender", "男性");
    set("age", 20 + random(60));
    set("long", "这是一位武林高手。\n"
    	+ "负责保卫总坛的安全。\n" );
	set("no_get", "护法长老对你而言太重了。\n");
	if( random(10) < 2 )
		set("double_attack",1);

    set("inquiry", ([
        "抢劫"          		: (: ask_rob :),
        ]));

}       

void init()
{
    object ob1;
	object ob = environment(this_object());
	int lvl = ob->query("skill_lvl");
	string s_skill,s_force,s_perform,s_base;
	int index;
        
    ::init();

	if( query("init") == 0 )
	{
		set("init", 1);

		index = random( sizeof( skill ) );

		s_skill = skill[ index ];
		s_force = force[ index ];
		s_perform = perform[ index ];
		s_base = base[ index ];
     
	    set_name(ob->query("g_name") + "护法", ({ "hufa zhanglao", "hufa", "zhanglao"}));

	    set("gender", "男性");
	    set("age", 20 + random(60));
	    set("long", "这是" + ob->query("g_name") + "从外地重金聘请来的一位武林高手。\n"
	    	+ "负责保卫总坛的安全。\n" );
	    set("combat_exp", ob->query("combat_exp"));
	    set("meitude", "peaceful");
	    set("str", 30 + random( 20 ) );
	    set("int", 30 + random( 20 ) );
	    set("con", 30 + random( 20 ) );
	    set("dex", 30 + random( 20 ) );
	    set("shen",0);
	    set("max_qi", 10000);
	    set("max_jing", 3000);
	    set("max_neili", 6000 + ob->query("combat_exp")/500 );
	    set("eff_jingli",3000);
	    set("neili", 6000 + ob->query("combat_exp")/500 );
	    set_skill(s_skill, lvl );
	    set_skill(s_force, lvl );
	    set_skill(s_base, lvl);
	    set_skill("dodge", lvl);
	    set_skill("force", lvl);
	    set_skill("parry", lvl);
	    set_skill("tiyunzong", lvl);

	    map_skill("force", s_force);
	    map_skill("dodge", "tiyunzong");
	    map_skill("parry", s_skill);
	    map_skill(s_base, s_skill);
	    prepare_skill(s_base, s_skill);
	
		set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
			(: perform_action, s_base + "." + s_perform :)
		}) );

	    setup();
	    carry_object(ARMOR_D("cloth"))->wear();
    }
    
        
    if( interactive(ob1 = this_player()) )
    {
        remove_call_out("greeting");
        call_out("greeting", 0, ob1);
    }
}

void greeting(object ob)
{
    object me = this_object();
    object ob2 = environment();
        
    if (!ob || !present(ob, environment()) )
        return;

	if( interactive(ob) && ob->query("g_name")+ob->query("g_type")==ob2->query("g_name") )
		return;
		
	if( userp(ob)&& ob->is_fighting() && ob->query("g_name")+ob->query("g_type")!=ob2->query("g_name"))
	// add userp by Looklove 限制利用hufa do job //
	{
		say( HIR"大胆狂徒，竟敢在我帮总坛如此撒野！看招！\n"NOR );
		me->kill_ob(ob);
		return;
	}

	call_out("greeting",1,ob);

    return;
}



string ask_rob()
{
	object me = this_player();
	object env = environment( me );
	
	if( me->query("g_name") + me->query("g_type" ) != env->query("g_name") )
	{
        return RANK_D->query_respect(me) + 
           "和本帮素无来往，此话不知从何谈起？";
	}
	
	if( me->query("g_level") > 3 )
	{
        return RANK_D->query_respect(me) + 
           "纵有此心，奈何在帮中的影响力还不够！";
	}
	
	return 0;	
}
