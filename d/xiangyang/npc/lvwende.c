// /d/xiangyang/npc/lvwende.c
// by looklove 2000/8/23
inherit NPC;
string ask_me();
void create()
{
        set_name("吕文德", ({ "lv wende", "lv" }));
        set("title", "襄阳知府");
        set("gender", "男性");
        set("age", 40);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("long", "他是襄阳的现任知府，在襄阳率领大宋军民与蒙古鞑子对抗。\n");
        set("combat_exp", 350000);
        set("attitude", "peaceful");
       set("max_qi", 1200);
       set("max_jing", 1200);
       set("eff_jingli", 1000);
       set("jiali", 30);
       set_skill("force", 70); 
       set_skill("unarmed", 80);
       set_skill("strike", 70);
       set_skill("sword", 70);
       set_skill("dodge", 70);
       set_skill("parry", 70);
       set_skill("qingmang-jian", 80); 
       map_skill("sword", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       set("inquiry", ([              
                "弃暗投明" : (: ask_me :),
                "投诚" : (: ask_me :),
       ]));
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

void kill_ob(object ob)
{
//        ob->remove_killer(this_object());
//        remove_killer(ob);
        command("say 杀人啦！救命啊！");
        ob->add_condition("killer", 5);
        ::kill_ob(ob);
}

int accept_object(object me, object obj, object ob)
{            
        int i = me->query("combat_exp")/20000;
        ob = this_object();

i *= 10000;
if (i < 200000) i = 200000;

if(obj->query("money_id")){
 if(me->query("menggu") && me->query_temp("money_ask")){
  if(obj->value() >= i){
              command("haha " + me->query("id"));
              command("whisper "+me->query("id")+" 你就放心吧，这件事包在我身上！");
                me->delete("menggu");
                me->delete_temp("money_ask");
              return 1;
              }
          else {
              command("say 才这么点钱能干什么？");
              return 1;
              }
          }
        else {
             command("say 才这么点钱能干什么？");
             return 1;
             }
}
    
if(userp(obj))
        return 0;
        if(obj->query("id") == "renshen guoo") return 0;//屏蔽rsg
        if(obj->query("treasure"))
        {
           command("thumb " + me->query("id"));
           command("touch " + me->query("id"));
           tell_object(me,"吕文德对你赞道：值此襄阳危难之际"+RANK_D->query_respect(me)+"献此奇珍，真乃忠义之士也！\n");
            if (obj->query("value")>2000)
            {
            me->add("shen", (obj->query("value")/20));
            }
            else 
            me->add("shen", (obj->query("value") * 5));
            call_out("destroy", 1, obj);
            return 1;
        }
        else
        {
        command("hmm " + me->query("id"));
command("say 我对"+obj->name()+"不稀罕。");
//             call_out("destroy", 1, obj);
}
return 1;
}

string ask_me()
{
object me = this_player();
        int i = me->query("combat_exp")/20000;
    
    if(!me->query("menggu")) return "哪儿跟哪啊？别烦我！";
        if (i < 20) i = 20;
    me->set_temp("money_ask", 1);
    message_vision("\n$N对着$n哈哈大笑：想投降我大宋了是吧？\n", this_object(), me);
    command("whisper "+me->query("id")+" "+chinese_number(i)+"两黄金。");
    return "你知道，上头对蒙古人的态度…，你也不能让我难做吧？\n";
}

void destroy(object obj)
{
destruct(obj);
}
