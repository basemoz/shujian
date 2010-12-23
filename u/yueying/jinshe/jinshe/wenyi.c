// /d/city/npc/wenyi

#include <ansi.h>
inherit NPC;

int ask_xia1();
#define this_quest_is_open "yes"
 
void create()
{
        set_name("����", ({ "wen yi", "wen" }));
        set("long", 
        "�����ǽ����ɾ����������ǡ�\n"
        "һλ��ʮ�����Ů�ӣ���ò���㣬����һ�ֳ������ζ��\n");
        set("gender", "Ů��");
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
                "������" : "��������Ů��,������,��������.\n",
                "������" : "��������Ů��.\n",
                "�·�ɽ" : "�·�ɽ���ҵ���.\n",
                "�����ɾ�" : "�������µĽ����ɾ������ҵķ����",
                "�¼�����" : "��......",
                "��ѩ��" : (: ask_xia1 :),
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
        message_vision("���Ƕ�$N����һЦ����ת����ȥ��ü���û��˿���־塣��\n", ob);
        message_vision("$N���к�Ȼ���ã����Լ����������޳ܣ���һ�����޴�������ҲҪ�´˶��֣���\n", ob);
}

int ask_xia1()
{
        object me = this_player();
        string msg;
        msg = CYN"��������$N��ѯ��,����һ��,��ɫ��䡣\n"NOR;
        //msg+= CYN"�ܲ�ͨ��ʼ��������澭�ͻ��ѵĹ��¡�\n"NOR;
        //msg+= CYN"�ܲ�ͨ��$N���ʺ����������������˵�ˡ�\n"NOR;
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
        msg = CYN"������ɫ���˼���,����ƽ������,��$N˵:��������ʲô?\n"NOR;
        message_vision(msg,me);
        me->set_temp("quest/jinshe2/fail",1);
        return 1;
}

int do_happen1(object me)
{
        string msg;
        //if (base_name(environment(me)) != HERE)               return 1;
                    msg = CYN"����̾�˿���,��:��Ȼ�������������,�Ҿ͸�����ɡ�\n"NOR;
        msg+= CYN"���Ƕ��˶ٵ�:����һ�γ������,ʮ����ǰ������������ĸ�����ѩ��,Ҳ���ǽ����ɾ���\n"NOR;
        msg+= CYN"����ͻȻ��Ȧ����,������˵��������......\n"NOR;
        message_vision(msg, me);
        me->set_temp("quest/jinshe2/step1",1);
        return 1;       
    }
int do_comfort(string arg)
{
        if( !this_player()->query_temp("quest/jinshe2/step1") )  return 0;
        
        if( !arg ) return notify_fail("��˵ʲô��\n");
        
        message_vision("$N������ο����" + arg + "\n", this_player());
        if( strsrch(arg, "�ķ���") >=0 && (strsrch(arg, "����ѹ�") >=0
         || strsrch(arg, "�ǽ����ɾ�") >=0 || strsrch(arg, "��������������") >=0 )) {
                command("ah");
                command("say ��˵�Ķ������?!!!\n");
                command("touch " + this_player()->query("id"));
                this_player()->set_temp("quest/jinshe2/step2",1);
        } else {
                command("say �����������,�������������,һ�߾���ʮ����.");
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
        if(ob->query("id") == "xinjian1" && ob->query("name") == HIB"һ�����"NOR){
                if(this_player()->query("mjling/complete")) {
                        command("smile");
                        command("say �һ����ú������ġ�");
                        this_player()->add("mjling/ling",ob->query_amount());
                        call_out("destroying", 1, ob);
                        return 1; 
                }
                command("nod");
                command("say ��л���´�����Ҫ�����������ҡ�\n");
                this_object()->add("ling",ob->query_amount());
                call_out("destroying", 1, ob);
                return 1;
        }
        if((string)ob->query("id") == "shenghuo ling"){
                
                        command("thank "+ (string)who->query("id"));
                        command("say ��л��Ϊ�����һ���ʥ���֪��Ӧ����ôлл�㣿\n");
                        call_out("destroying", 1, ob);
                        return 1;
                }
                
        
        else return 0;
}
