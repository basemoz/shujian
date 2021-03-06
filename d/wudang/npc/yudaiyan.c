#include <ansi.h>

inherit NPC;

string ask_me_2();
string ask_me_3();
string ask_dan1();
string ask_dan2();

void create()
{
        set_name("俞岱岩", ({ "yu daiyan", "yu" }));
        set("nickname", "武当三侠");
        set("long", 
"他就是张三丰的三弟子、武当三侠俞岱岩。因被奸人所害，可能
下半辈子只能在躺椅上渡过了！他身穿一件洗得发白的蓝色长衫。
形骸憔悴，脸色惨白，眼神深沉，象是回忆着什么！\n");
        set("gender", "男性");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 5);
        set("max_qi", 900);
        set("max_jing", 900);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 60);
set("combat_exp", 1000000); 
              set("unique", 1);
        set_skill("force", 120);
        set_skill("yinyun-ziqi", 120);
set_skill("dodge", 180);
set_skill("tiyunzong", 180);
set_skill("cuff", 180);
set_skill("taiji-quan", 180);
set_skill("parry", 180);
set_skill("sword", 180);
        set_skill("taiji-jian", 60);
        set_skill("literate", 100);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");

        create_family("武当派", 2, "弟子");

        set("inquiry", ([
                "九转结气丸" : (: ask_me_2 :),
                      "采药" : (: ask_me_3 :),
                "天心解毒丹" : (: ask_dan1 :),
                "天王护心丹" : (: ask_dan2 :),
                      "看守" : "武当弟子可在这里看守(kanshou)铜鼎。",
                     "放弃"  : "如果不想干了，可以随时离开(leave)。",
        ]));

        set("wan_count", 1 + random(2));
        set("wan_count1", 3);
        set("wan_count2", 3);
        set("letter_count", 1 + random(1));
set("guard_count",0);

        setup();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}


string ask_me_2()
{
                mapping fam; 
object ob, me,yu;
              me = this_player();
              yu = this_object();
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] !="武当派")
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";

               if ( (int)this_player()->query_condition("medicine" ) > 0 )
                return RANK_D->query_respect(this_player()) + 
                "你是不是刚吃过药，怎麽又来要了？欲速则不达，下次再来吧。";

        if (  present("jieqi wan", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "你现在身上不是有颗药丸吗，怎麽又来要了？修道之人岂能象你这般贪婪？！";
// if ((int)me->query("max_neili") >= (int)me->query_skill("force")*10)
// return RANK_D->query_respect(this_player()) + "怎麽老想吃要呢,你武功已经不凡,去打坐提高修为吧。"
        if (query("wan_count") < 1) return "对不起，九转结气丸已经发完了。";
        ob = new("/clone/medicine/jieqi-wan");
         yu->add("wan_count",-1);
        ob->move(this_player());
        message_vision("$N获得一颗九转结气丸。\n",this_player());
        return "好吧，记住，此乃武当圣药，不可轻易给人。";


}

string ask_dan1()
{
              mapping fam; 
              object ob, me,yu;
              me = this_player();
              yu = this_object();
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] !="武当派")
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";

               if ( (int)this_player()->query_condition("medicine" ) > 0 )
                return RANK_D->query_respect(this_player()) + 
                "你是不是刚吃过药，怎麽又来要了？欲速则不达，下次再来吧。";

        if (  present("jiedu dan", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "你现在身上不是有颗药丸吗，怎麽又来要了？修道之人岂能象你这般贪婪？！";
        if (query("wan_count1") < 1) return "对不起，天心解毒丹已经发完了。";
ob = new("/clone/medicine/jiedu-dan");
        ob->move(this_player());
        yu->add("wan_count1",-1);

        message_vision("$N获得一颗天心解毒丹。\n",this_player());
        return "好吧，记住，此乃武当疗毒灵药，不可轻易给人。";


}

string ask_dan2()
{
              mapping fam; 
              object ob, me, yu;
              me = this_player();
              yu = this_object();
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] !="武当派")
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";

               if ( (int)this_player()->query_condition("medicine" ) > 0 )
                return RANK_D->query_respect(this_player()) + 
                "你是不是刚吃过药，怎麽又来要了？欲速则不达，下次再来吧。";

        if (  present("huxin dan", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "你现在身上不是有颗药丸吗，怎麽又来要了？修道之人岂能象你这般贪婪？！";
// if ((int)me->query("eff_qi") >= (int)me->query("max_qi")/2);
// return RANK_D->query_respect(this_player()) + "，天王护心丹必须重伤时才能服用。";
        if (query("wan_count2") < 1) return "对不起，天王护心丹已经发完了。";


ob = new("clone/medicine/huxin-dan");
        ob->move(this_player());
        yu->add("wan_count2",-1);

        message_vision("$N获得一颗天王护心丹。\n",this_player());
        return "好吧，记住，此乃武当圣药，不可轻易给人。";


}
string ask_me_3()
{
        mapping fam;
        object applicant;
        object ob;
        int exp;

        applicant=this_player();
        if (!(fam = applicant->query("family")) || fam["family_name"] != "武当派")
        return RANK_D->query_respect(this_player())+"与本派素无来往，何谈为我派采药啊？";
        exp=(int)applicant->query("combat_exp",1); 
           if(exp>75000)
         return "你还是多勤学武艺，采药让你的师弟们去做吧。\n"; 
        if(exp<10000)
         return "你还太小，采药有一定危险，你现在不适合去！\n";

        if((int)applicant->query_skill("medicine", 1) < 20){
         command("shake "+(string)applicant->query("id"));
         return "你不学点草本药理，怎麽能分辨出草药呢！\n";
         } 
       if(interactive(applicant) && applicant->query_temp("mark/wd_mission"))  
         return "你为什麽还不去采药？\n";
       if(interactive(applicant) && applicant->query_condition("wd_busy"))  
         return "现在已经有足够的人手去采药拉。\n";
   
        ob = new("/d/wudang/caiyaojob/obj/yaolou");
        ob->move(applicant);
        applicant->set_temp("mark/wd_mission",1);
//        applicant->apply_condition("wd_busy",10);
        return "武当治伤良药三黄宝蜡丸主要由麻黄，雄黄和藤黄三味草药制成，传闻
武当后山长有此草药，"+RANK_D->query_respect(applicant)+"如果不怕辛苦，可以到那里找找看！";
}

int accept_object(object who, object ob,object me)
{       
        mapping fam;

         object ob_letter;

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="武当派")
           {
             command("say 你与本派素无来往，不知为何送此物于我？ \n");
             return 1;
            }
        
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return notify_fail("你没有这件东西。");  
         
 if(who->query_temp("mark/wd_mission")) {
        if (ob->query("id") != "yao lou" ){
             command("? "+(string)who->query("id"));
             return 0;
             }
       if(!present("ma huang", ob)){
             command("say 你好象没有采到麻黄啊？！");
             return 0;
             }
       if(!present("teng huang", ob)){
             command("say 你好象没有采到藤黄啊？！");
             return 0;
             }
       if(!present("xiong huang", ob)){
             command("say 你好象没有采到雄黄啊？！");
             return 0;
             }
    //   if(!who->query_temp("mark/wd_mission")){
    //         command("say 你并没让你去采药啊？！");
    //         return 0;
    //         }
        command("pat " + who->query("id"));
        command("say 你如此勤劳，他日必有所成。\n");
        call_out("destroying", 1, ob);        
if( (int)who->query("potential", 1) < (int)who->query("max_pot", 1) ) {
        who->add("combat_exp",(3+random(10))*12);
        who->add("potential",(3+random(10))*4);
      }
        who->set("wd_job",1);
        who->delete_temp("mark/wd_mission");
        return 1;
} else 
     {
         if ((string)ob->query("id") == "changsheng guo")
        {
            if (query("letter_count") > 0) 
              {
                command("ah "+(string)who->query("id"));
                command("say "+"你心地淳朴，学武定有大成!可惜我是个残废，不能教你武功。\n");
                ob_letter=new("/d/wudang/obj/letters");
                ob_letter->move(who);
                add("letter_count", -1);

                message_vision("$N获得一封书信。\n",this_player());
                command("say 你拿我这封信去拜我师兄俞莲舟为师吧，也算是我们结交一场！\n");
                remove_call_out("destroying");
                call_out("destroying", 1, ob);

               } 
             else
               {
                command("touch "+(string)who->query("id"));
                command("say 可是已有人给过我这仙果了!\n");
               }
            return 1;
        }
        
            command("hmm "+ (string)who->query("id"));
        command("say 无缘无故送我东西？");
        return 0;     
     }
}

void destroying(object obj)
{
     destruct(obj);
     return;
}
