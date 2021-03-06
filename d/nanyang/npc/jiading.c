// jiading.c 家丁
// tangfeng@SJ

//第一使用skills_pfm.h，感谢Campsun@SJ

//inherit NPC;
inherit FIGHTER;
#include <ansi.h>
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

string *str_menpai = ({ "wd","hs","gm","gb","tz","mj","thd","kl"});       
#include "/d/city/npc/skills_pfm.h";
void create()
{
	set_name("家丁", ({ "jia ding", "jiading", "jia", "ding" }));
	set("long", "一个二十来岁的家丁，相貌并不十分凶猛。\n");
	set("gender", "男性");
	set("age", 24);
	set("attitude", "peaceful");
	set("shen", -100);

	set("str", 28);
	set("int", 20);
	set("con", 25);
	set("dex", 20);

	set("max_qi", 500);
	set("max_jing", 5000);
	set("eff_jingli",4000);
	set("neili", 100);
	set("max_neili", 100);
	set("jiali", 20);
	set("combat_exp", 3000+random(500));

	set_skill("force", 70);
	set_skill("dodge", 80);
	set_skill("unarmed", 70);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("cuff", 80);
	set("inquiry", ([
		"丐帮" : "丐帮是天下第一大帮！\n",
		"萧峰" : "江湖败类。\n",
	]));
	setup();
	carry_object(ARMOR_D("shoes"))->wear();
	carry_object(ARMOR_D("cloth"))->wear();

}
void init()
{
    object me, ob;  
    string good_skills;
    int i;     
    ::init();
    ob = this_object();
    me = this_player();
	if(environment(me)!=environment(ob)) return;
	if(!me->query_temp(QUESTDIR3+"start")) return;
    if(!me->query(QUESTDIR3+"start")) return;
    if(me->query(QUESTDIR3+"over")) return;
    if(me->query_temp(QUESTDIR3+"kill")) return;
	if(me->query_condition("killer")) return;
    if(ob->query("setok")) return;
	i=me->query("max_pot");
	if(i<350) i=350;
	i=i-100;	 
    ob->set("setok",1);
	ob->set("kill_id",me->query("id"));
   	ob->set("party",str_menpai[random(sizeof(str_menpai))]);     
	ob->copy_menpai(({ob->query("party")}),1,random(2),50+random(50));	//复制npc的门派武功，							
	ob->copy_state();				//根据门派更新npc 的一些状态
    ob->set_skills_level(i-random(100)+random(50));
	ob->set("max_neili",me->query("max_neili"));
  	ob->set("max_jingli",me->query("max_jingli"));
    ob->set("max_qi",me->query("max_qi")*(1+random(3))/3);
  	ob->set("max_jing",me->query("max_jing"));
    
	ob->set("neili",query("max_neili")*3/2);
	ob->set("jingli",query("max_jingli")*3/2);
	ob->set("eff_jingli",query("max_jingli")*3/2);
	ob->set("qi",query("max_qi"));
	ob->set("eff_qi",query("max_qi"));
	ob->set("jing",query("max_jing")*3/2);
	ob->set("eff_jing",query("max_jing")*3/2);

	if (ob->query("f_skill2")) 
		good_skills=to_chinese(ob->query("f_skill"))+"和"+to_chinese(ob->query("f_skill2"));
	else	
		good_skills=to_chinese(ob->query("f_skill"));

   	ob->set("long",
       	 	"\n此人竟然是"HIW+ob->query("family/family_name")+NOR"的高手，不知道为何在此隐名埋姓。\n"
       	 	"小心他的成名绝技是："HIC+good_skills+NOR"。\n"
       	 	);
    ob->set("jiali",50+random(100));
    ob->set("combat_exp",me->query("combat_exp"));
	ob->set_skill("literate",ob->query("int")*10); 	 											//full literate
	ob->set_skill("wuxing-zhen",ob->query("int")*10); 	 									
	remove_call_out("zhen");
	call_out("zhen",2,ob);
	remove_call_out("do_kill");
	call_out("do_kill",6, me);
}
void zhen(object ob) 
{
   if( !ob ) return;                   
   command("lineup with guan jia");
   command("lineup with jia ding");
   command("lineup form wuxing-zhen");   
   command("lineup with guan jia");
   command("lineup with jia ding");
   call_out("zhen",1,ob);
}
int do_kill(object me)
{
	object ob = this_object();
	string good_skills;
	if(!me) return 0;
	if(!me->query_condition("killer") && me->query_temp(QUESTDIR3+"start") && me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over") && !me->query_temp(QUESTDIR3+"kill"))
	{
		if (ob->query("f_skill2")) 
			good_skills=to_chinese(ob->query("f_skill"))+"和"+to_chinese(ob->query("f_skill2"));
		else	
			good_skills=to_chinese(ob->query("f_skill"));
		if(random(2)) message_vision(HIG"$N突然神色一变，道：“看来今天只能拿出真本事来了！”$n定眼一看，这家伙竟然是"+ob->query("family/family_name")+"的高手！\n"NOR,ob,me);
		else message_vision(HIY"\n$N慢慢地从角落里走了出来，冷笑一声道：“不知天高地厚，看我的绝招"+good_skills+"！”"NOR,ob);
		log_file("quest/TLBB", sprintf("%s纪录：%s(%s)正准备闯聚贤庄。经验%d。\n", ob->name(1),me->name(1),me->query("id"), me->query("combat_exp")) );
		remove_call_out("checking");
		call_out("checking", 2, me, ob);
	}
	::do_kill(me);
}

//检查，quest过程不允许死亡
int checking(object me, object ob)
{
	int ret =  ::checking(me,ob);
	//me=this_palyer(),ob=this_object()
	if(!ret) return 0;
	if(!living(me) && living(ob) && ob->query("jing")>0 && ob->query("jingli")>0 && ob->query("qi")>0  ){
		remove_call_out("checking");
		if(me->query(QUESTDIR3+"start")) 
			tell_object(me,HIB"\n你败走聚闲庄，任务失败。\n"NOR);
		me->delete(QUESTDIR3+"start");
		me->delete_temp("quest/busy");//任务系统冲突标志
		me->delete_temp("quest/天龙八部");   
		me->set("quest/天龙八部/time",time());
		me->set("quest/天龙八部/combat_exp",me->query("combat_exp"));
		me->set("qi",100);			
		me->set("jing",100);
		me->set("jingli",100);
		tell_room(environment(ob), HIB"\n"+ob->name()+"哼了一声，这点本事也敢闯我聚贤庄。\n"NOR);
		if(environment(ob)== environment(me))
		{
			tell_room(environment(me), HIY"\n"+me->name()+"被"+ob->name()+"一脚踹了出去。\n"NOR); 
			me->move("/d/xiangyang/damen");
			tell_room(environment(me), HIY"\n呼的一个东西落了下来，原来是"+me->name()+"被"+ob->name()+"一脚踹到大门口。\n"NOR);
		}
		log_file("quest/TLBB", sprintf("%s纪录：%s(%s)闯聚贤庄失败。经验%d。\n", ob->name(1),me->name(1),me->query("id"), me->query("combat_exp")) );
		ob->delete("setok");
		ob->remove_all_killer();
		me->remove_all_killer();
		return 1;
	}
	if(!me || environment(ob)!= environment(me)||me->query("eff_qi")<me->query("max_qi")/15||me->query("qi")<me->query("max_qi")/20){
		remove_call_out("checking");
		remove_call_out("do_lost");
		call_out("do_lost",0);
		return 1;
	}
	if(!ob->query("setok")) 
	{
		remove_call_out("checking");
		return 1;
	}
	remove_call_out("checking");
	call_out("checking", 1, me, ob);
   if(!me->is_fighting(ob))
   {
	   remove_call_out("do_kill");  
	   call_out("do_kill",1,me);
   }
}
void do_lost()
{
	object ob,me;
	ob = this_object();
	me = find_player(ob->query("kill_id"));   
	ob->remove_all_killer();
	ob->delete("setok");
	if(!me) return;
	me->delete(QUESTDIR3+"start");
	me->delete_temp("quest/busy");//任务系统冲突标志
	me->delete_temp("quest/天龙八部");   
	me->set("quest/天龙八部/time",time());
	me->set("quest/天龙八部/combat_exp",me->query("combat_exp"));
	tell_room(environment(ob), HIB"\n"+ob->name()+"哼了一声，这点本事也敢闯我聚贤庄。\n"NOR);
	if(environment(ob)== environment(me)){
		tell_room(environment(me), HIY"\n"+me->name()+"被"+ob->name()+"一脚踹了出去。\n"NOR);
		me->move("/d/xiangyang/damen");
		tell_room(environment(me), HIY"\n呼的一个东西落了下来，原来是"+me->name()+"被"+ob->name()+"一脚踹到大门口。\n"NOR);
	}
	log_file("quest/TLBB", sprintf("%s纪录：%s(%s)萧峰身世篇聚贤庄失败。经验%d。\n", ob->name(1),me->name(1),me->query("id"), me->query("combat_exp")) );
	me->remove_all_killer();
}
