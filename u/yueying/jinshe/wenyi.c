// /d/city/npc/wenyi

#include <ansi.h>
inherit NPC;

int ask_xia1();
#define this_quest_is_open "yes"
 
void create()
{
        set_name("温仪", ({ "wen yi", "wen" }));
        set("long", 
        "她就是金蛇郎君的妻子温仪。\n"
        "一位三十来岁的女子，容貌清秀，有着一种成熟的韵味。\n");
        set("gender", "女性");
        set("age", 36);
        set("attitude", "friendly");
        set("shen", 1000);
        set("str", 35);
        set("int", 30);
        set("con", 25);
        set("dex", 27);
        
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 10);
        set("combat_exp", 5000);
         

    set_skill("force", 10);
    set_skill("yijin-jing", 10);
    set_skill("dodge", 10);

    set_skill("shaolin-shenfa", 10);
    set_skill("cuff", 10);
    set_skill("wenjia-daofa", 10);
    set_skill("parry", 10);
    set_skill("blade", 10);
    set_skill("wenjia-quan", 10);
    set_skill("literate", 10);

          map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shnfa");
    map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
    prepare_skill("cuff", "wenjia-quan");
    
    set("inquiry", ([
                "温青青" : "青青是我女儿,她姓夏,叫夏青青.\n",
                "夏青青" : "青青是我女儿.\n",
                "温方山" : "温方山是我爹爹.\n",
                "金蛇郎君" : "名震天下的金蛇郎君就是我的夫君。",
                "温家五老" : "哼......",
                "夏雪宜" : (: ask_xia1 :),
        ]));
 
        setup(); 
        carry_object("/clone/misc/cloth")->wear();
         
     
}

void init()
{
        add_action("do_comfort", "comfort");
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("温仪对$N淡淡一笑，又转过身去，眉宇间没有丝毫恐惧。”\n", ob);
        message_vision("$N心中忽然觉得：“自己怎麽这麽无耻，对一个手无寸铁的人也要下此毒手？”\n", ob);
}

int ask_xia1()
{
        object me = this_player();
        string msg;
        msg = CYN"温仪听到$N的询问,身子一震,脸色大变。\n"NOR;
        //msg+= CYN"周伯通开始讲起九阴真经和黄裳的故事。\n"NOR;
        //msg+= CYN"周伯通看$N不问后来怎样，便赌气不说了。\n"NOR;
        message_vision(msg, me);
        me->set_temp("thd/story",1);
        //return 1;
        
    if (me->query("env/debug")){
        call_out("do_happen1",10,me);
    return 1;}
    if (this_quest_is_open == "yes"
     && userp(me)
     && !me->query_temp("quest/jinshe2/fail",1)
     && random(me->query_int()) > 20
     && random(me->query_kar()) > 22) {
        remove_call_out("do_happen1");
                call_out("do_happen1",3,me);
                return 1;
        }
        msg = CYN"温仪脸色变了几变,渐渐平静下来,对$N说:你问他作什么?\n"NOR;
        message_vision(msg,me);
        me->set_temp("quest/jinshe2/fail",1);
        return 1;
}

int do_happen1(object me)
{
        string msg;
        //if (base_name(environment(me)) != HERE)               return 1;
                    msg = CYN"温仪叹了口气,道:既然你是青青的朋友,我就告诉你吧。\n"NOR;
        msg+= CYN"温仪顿了顿道:那是一段陈年旧事,十八年前我遇到了青青的父亲夏雪宜,也就是金蛇郎君。\n"NOR;
        msg+= CYN"温仪突然眼圈发红,哽咽着说不出话来......\n"NOR;
        message_vision(msg, me);
        me->set_temp("quest/jinshe2/step1",1);
        return 1;       
    }
int do_comfort(string arg)
{
        if( !this_player()->query_temp("quest/jinshe2/step1") )  return 0;
        
        if( !arg ) return notify_fail("你说什么？\n");
        
        message_vision("$N轻声安慰道：" + arg + "\n", this_player());
        if( strsrch(arg, "夏夫人") >=0 && (strsrch(arg, "你别难过") >=0
         || strsrch(arg, "是金蛇郎君") >=0 || strsrch(arg, "特意叫我来找你的") >=0 )) {
                command("ah");
                command("say 你说的都是真的?!!!\n");
                command("touch " + this_player()->query("id"));
                this_player()->set_temp("quest/jinshe2/step2",1);
        } else {
                command("say 他这个负心人,丢下我们娘儿俩,一走就是十八年.");
        }
        return 1;
}

int accept_object(object who, object ob)
{
        object me;
        object* dest;
        mapping fam;
        int i , j =0;

        me = this_object();
        fam = who->query("family");

        if(userp(ob)) return 0;
        if(ob->query("id") == "xinjian1" && ob->query("name") == HIB"一封家书"NOR){
                if(this_player()->query("mjling/complete")) {
                        command("smile");
                        command("say 我会帮你好好收著的。");
                        this_player()->add("mjling/ling",ob->query_amount());
                        call_out("destroying", 1, ob);
                        return 1; 
                }
                command("nod");
                command("say 多谢，下次有需要可以再来找我。\n");
                this_object()->add("ling",ob->query_amount());
                call_out("destroying", 1, ob);
                return 1;
        }
        if((string)ob->query("id") == "shenghuo ling"){
                
                        command("thank "+ (string)who->query("id"));
                        command("say 多谢你为本教找回了圣物，不知我应该怎么谢谢你？\n");
                        call_out("destroying", 1, ob);
                        return 1;
                }
                
        
        else return 0;
}
