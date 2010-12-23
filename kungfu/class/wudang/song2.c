// song.c ��Զ��

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "/kungfu/class/wudang/place.h"
string ask_me();

string ask_me1();

string ask_me2();

string ask_me3();

string ask_me4();
void create()
{
       set_name("��Զ��", ({ "song yuanqiao", "song" }));
       set("nickname", "�䵱����");
       set("long", 
               "������������Ĵ���ӡ��䵱����֮�׵���Զ�š�\n"
               "��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
               "���������ʮ������ݳ���������⡣�񵭳�ͣ���Ĭ���ԡ�\n");
       set("gender", "����");
       set("unique", 1);
       set("age", 61);
       set("attitude", "peaceful");
       set("shen", 10000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);
set("no_get","��Զ�Ŷ������̫���ˡ�");
       
       set("max_qi", 1500);
       set("max_jing", 1000);
       set("neili", 2000);
       set("max_neili", 2000);
       set("jiali", 50);
       set("combat_exp", 1000000);
//     set("score", 60000);
       set_skill("force", 130);
       set_skill("yinyun-ziqi", 130);
       set_skill("dodge", 130);
       set_skill("wudang-quan", 130);
       set_skill("tiyunzong", 130);
       set_skill("strike", 180);
       set_skill("zhenshan-mianzhang", 180);
       set_skill("parry", 130);
       set_skill("literate", 100);
       set_skill("xuanxu-daofa", 140);
       set_skill("sword", 180);
       set_skill("taiji-jian", 180);
       map_skill("sword", "taiji-jian");
       set_skill("wudang-quan", 140);
       map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "zhenshan-mianzhang");
       map_skill("parry", "zhenshan-mianzhang");
       prepare_skill("strike", "zhenshan-mianzhang");
       create_family("�䵱��", 2, "����");

       set("inquiry", ([
                "�ؼ�" : (: ask_me :),
                "��Ҫ" : (: ask_me1 :),
                "����" : (: ask_me2 :),
                 "job" : (: ask_me2 :),
                "Ѳɽ" : (: ask_me2 :),
              "fangqi" : (: ask_me3 :),
                "����" : (: ask_me3 :),
             "abandon" : (: ask_me3 :),
                "����" : (: ask_me4 :),
                "����" : (: ask_me4 :),
                "����" : (: ask_me4 :),

       ]));
       set("book_count1", 1);
       set("book_count2", 1);
       setup();
//     carry_object("/clone/weapon/changjian")->wield();
       carry_object("/d/wudang/obj/white-robe")->wear();

}
void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 0, ob);
        }       
     
}

void greeting(object ob)
{
        int e,p,shen,count;
        mapping fam;
        fam = this_player()->query("family");

        if (!ob) return;        // Yuj 19991111

        count = ob->query("wd_job",1);
             if(count < 100)     e = 80 + random(20);
        else if(count < 200)     e = 110 + random(20);
        else if(count < 500)     e = 130 + random(20);
        else if(count < 1000)    e = 180 + random(30);
        else if(count < 2000)    e = 230 + random(20);
        else if(count < 3000)    e = 250 + random(30);
        else if(count < 4000)    e = 300 + random(40);
        else if(count < 5000)    e = 320 + random(60);
        else if(count < 10000)   e = 340 + random(90);
        else if(count < 1000000) e = 350 + random(150);
        p = e/6 + random(e/10) ;
        shen = e*10 + p*10;
        if(ob->query("wd/wd_job_lost2") )
       {
        command("faint "+ob->query("id"));
        command("say "+ob->name()+"���Ѿ����˰�����Ƕ����������ˣ�");
        ob->delete("wd/wd_job");
        ob->delete("wd/wd_job_place");
        ob->delete("wd/wd_job_lost2");
        ob->apply_condition("job_busy",3+random(6));
       }
        if(ob->query("wd/wd_job_lost") )
       {
        command("sigh "+ob->query("id"));
        command("say "+ob->name()+"����ô��ģ���Ȼ���Ƕ��������ˣ�");
        ob->delete("wd/wd_job");
        ob->delete("wd/wd_job_place");
        ob->delete("wd/wd_job_lost");
        ob->apply_condition("job_busy",3+random(6));
       }
        if(ob->query("wd/wd_jobok") ){
        command("thumb "+ob->query("id"));
        command("say �ܺã�ף���������������ȥ��Ϣ��Ϣ�ɣ�");
        ob->add("wd_job",1);
        count += 1;
        ob->add("combat_exp",e);
        ob->add("potential",p);
if( ob->query("family/family_name")!="�һ���")
            ob->add("shen",shen);
        ob->delete("wd/wd_job");
        ob->delete("wd/wd_job_place");
        ob->delete("wd/wd_jobok");
        if ( (int)ob->query("potential", 1) > (int)ob->query("max_pot", 1) )
        ob->set("potential" , ob->query("max_pot", 1) );
        tell_object(ob, GRN"
������"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ�ܣ�����������������ˣ�\n"NOR);
        write_file( "/log/job/wd_job",sprintf("%s %s(%s)��%d��������%d�㾭�飬%d��Ǳ�ܣ����飺%d\n",
ctime(time())[4..19],ob->name(),ob->query("id"),count,e,p,ob->query("combat_exp")));
          ob->apply_condition("wd_job",1+random(2)+e/120);
        }
        return;
}

int accept_object(object who, object ob, object me)
{
        int e,p,shen;
        mapping fam;

        who = this_player();
        e = 100 + random((int)who->query("wd_job")/2);
        if(e > 300) e = 280 + random(30);
        p = e/6 + random(e/10) ;
        shen = e*10 + p*10;
        if(ob->query("id") != "corpse"){
             command("? "+ (string)who->query("id"));
             command("say ����������ʲô��");
return 0;
}
        if( !who->query("wd/wd_job")) {
             command("? "+ (string)who->query("id"));
             call_out("destroying", 1, ob);
             return 1;
            }
        if(ob->query("kill_by") != who){
             command("kick "+ (string)who->query("id"));
             command("say ������ֲ�����ɱ�ģ����������ƭȡʲô��");
             call_out("destroying", 1, ob);
             return 1;
            }
        if ( ob->query("victim_id") != "robber" ){
             command("? "+ (string)who->query("id"));
             call_out("destroying", 1, ob);
             return 1;
            }
        if ( ob->query("victim_user") ){
             command("consider "+ (string)who->query("id"));
             command("say ���������ñ���ʹ����ƭ���ֶΣ������Ͽ�������£���");
             call_out("destroying", 1, ob);
             return 1;
            }
        command("touch "+who->query("id"));
        command("say ��ϲ��ϲ�����Ȼ�������������������̫���ˣ���ȥ��Ϣ��Ϣ�ɣ�");
        call_out("destroying", 1, ob);
        who->add("wd_job",1);
        who->add("combat_exp",e);
        who->add("potential",p);
        fam = this_player()->query("family");
        if (fam["family_name"] != "�һ���")
            who->add("shen",shen);
        who->delete("wd/wd_job");
        who->delete("wd/wd_job_place");
        who->delete("wd/wd_jobok");
        if ( (int)who->query("potential", 1) > (int)who->query("max_pot", 1) )
        who->set("potential" , who->query("max_pot", 1) );
        tell_object(who, GRN"
�㱻�ر�����"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ�ܣ���о���������������\n"NOR);
        write_file( "/log/job/wd_job",sprintf("%s %s(%s)ɱ�������ر���%d�㾭�飬%d��Ǳ�ܣ�Ŀǰʵս���飺%d\n",
ctime(time())[4..19],who->name(),who->query("id"),e,p,who->query("combat_exp")));
        who->apply_condition("wd_job",2+random(5));
        return 1;    
}

void kill_ob(object me)
{
        //set("combat_exp", 750000);    
        //set("max_qi", 2500);
        //set("max_neili", 2000);
        //set("neili", 2000);
        //set("jiali", 100);
       set("chat_chance_combat", 20);
       set("chat_msg_combat", ({
               (: perform_action, "strike.bingdi" :),
               (: perform_action, "dodge.zong" :),
        }));
        ::kill_ob(me);       
} 

int accept_fight(object me)
{
        if((int)me->query("shen") < 1) {
           command("say ϰ��֮��Ӧ־�ڳ�����ƣ�"+RANK_D->query_respect(me)+"Ŀ¶��������Υ��ѧ֮����");
           return 0;
        }
        ::fight_ob(me);
         return 1;
}

void attempt_apprentice(object ob)
{
       if ((int)ob->query("shen") < 10000) {
               command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����");
               return;
       }
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
}

string ask_me()
{
       mapping fam; 
       object ob;
       if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
               return RANK_D->query_respect(this_player()) + 
               "�뱾��������������֪�˻��Ӻ�̸��";
       if(query("book_count2") < 1)
         return "�������ˣ����ɵ��ڹ��ķ����ڴ˴���";
       add("book_count2",-1);       
       ob = new(__DIR__"force_book");
       ob->move(this_player());
       return "�ðɣ��Ȿ��̫��ʮ��ʽ�����û�ȥ�ú����С�";
}

string ask_me1()
{
        mapping fam; 
        object ob,song;        
        song = this_object();
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
                return RANK_D->query_respect(this_player()) + 
                "�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count1") < 1)
           return "�������ˣ�������Ҫ�Ѿ����ڴ˴��ˡ�";
        add("book_count1",-1);         
        ob = new(__DIR__"blade_book");
        ob->move(this_player());
        return "�Ȿ���н����ĵ���Ҫ�죬���ȥ�ú��о�һ�¡�";
}
string ask_me2()
{
        object me, ob;
        string *place,objwhere,str,str2;

        me=this_player();
        str2 = me->query("wd/wd_job_place");

        if (me->query("menggu"))
           return "�ߣ����������ɹţ�������ʲô��";
        if (me->query("wd/wd_job") && !me->query("wd/wd_job_place"))
           return "���������Բ��𣬵ص�������������������ɡ�";
        if (me->query("wd/wd_job"))
           return "�Ҳ��Ǹ���������������"+ str2 +CYN"�������ҡ���Ϳ�ȥ�ɣ�";
        if (((int)me->query("shen")<0) && !wizardp(me) )
  return "����ô�����������а��֮ʿ��";
        if ((int)me->query("combat_exp") < 200000 )
           return "��λ" + RANK_D->query_respect(this_player()) + "�书δ�ɣ�����ȥ���������������ͭ���Ĺ����ɣ�";
        if( me->query_condition("wd_job"))
           return "������ʱ��û�й�������ȥ����";
        if ( me->query_condition("dali_songxin")
          || me->query_condition("gb_mission")
          || me->query_condition("gb_busy")
          || me->query_condition("xx_task")
          || me->query_condition("guanfu_task") 
          || me->query_condition("xs_job"))
            return "��������æ�������������أ�";

        while (1) {
                objwhere = names[random(sizeof(names))];
                if (load_object(objwhere)) break;
        }
        place = explode(objwhere, "/");
        str = " ";
        if(place[0] == "d")
                switch(place[1]){
                        case "baituo":  str = "�������ɽ"; break;
                        case "hj":      str = "����ؽ�"; break;
                        case "mingjiao":str = "��������"; break;
                        case "shaolin": str = "������ɽ����"; break;
                        case "songshan":str = "������ɽ"; break;
                        case "wudang":  str = "�����䵱ɽ"; break;
                        case "xingxiu": str = "�������޺�"; break;
                        case "city":    str = "�������ݳ�"; break;
                        case "emei":    str = "�Ĵ�����ɽ"; break;
                        case "fuzhou":  str = "�Ͻ�����"; break;
                        case "jiaxing": str = "���ϼ���"; break;
                        case "taishan": str = "ɽ��̩ɽ"; break;
                        case "dali":    str = "���ϴ����"; break;
                        case "tls":     str = "����������"; break;
                        case "tiezhang":str = "��������ɽ"; break;
                        case "fairyland":str = "����ɽ��"; break;
                        case "gumu":    str = "����ɽ��Ĺ"; break;
                        case "chengdu": str = "�Ĵ��ɶ�"; break;
                        case "huashan": str = "������ɽ"; break;
                        case "xiangyang":str = "��������"; break;
                        case "xueshan": str = "������ѩɽ"; break;
                        case "gaibang": str = "ؤ��ֶ�"; break;
                        case "hz":      str = "���Ϻ���"; break;
                        case "village": str = "����С��"; break;
                        case "wuguang": str = "�������"; break;
                        case "thd":     str = "�����һ���"; break;
                        case "gb":      str = "ؤ��"; break;
                        case "mr":      str = "����Ľ��"; break;
                       }
        me->set("wd/wd_job",1);
        me->set("wd/wd_job_place", str);
    me->apply_condition("wd_job",20);
        command("nod "+me->query("id"));
        ob=new("/d/wudang/npc/robber");
        ob->set_temp("target", me->query("id") );
        ob->move(objwhere);
write_file( "/log/job/wd_job",sprintf("%s %s(%s)��ʼ��wd job,Ŀǰʵս���飺%d\n", ctime(time()),me->name(),me->query("id"),me->query("combat_exp")));
        return "��˵������"+ str + objwhere->query("short") +CYN"�������ң�������ȥ����Ѳ��һȦ��";
}

string ask_me3()
{
        object ob;
        ob = this_player();
        if(ob->query("wd/wd_job"))
        {
         ob->delete("wd/wd_job");
         ob->delete("wd/wd_job_place");
         ob->apply_condition("job_busy",10+random(10) );
         ob->apply_condition("wd_job",10+random(10) );
         message_vision(CYN"��Զ��һ�ѱ���һ������ؿ��ţ���$N���������ôû��Ϣ��������ô�Ե�������ȥ�ĵ��ﰡ��\n"NOR,ob);
         return ""+ob->name()+"����̫����ʧ���ˣ���Ȼ��ô���ɲ��ã������°ɣ�";
        }
        return ""+ob->name()+"������û��������������Ϲ����ʲôѽ��";
}
string ask_me4()
{
        object ob;
        ob = this_player();
        if(!ob->query("wd_job"))
        {
         return "�Բ���"+ob->name()+"�������û������������������أ����͸ɰɣ�";
        }
        return ""+ob->name()+"�����Ѿ��ɹ��ز�����"+CHINESE_D->chinese_number((int)ob->query("wd_job"))+"��������";
}
void destroying(object obj)
{     
    if (!obj) return;
    if (userp(obj)) command("drop "+obj->parse_command_id_list()[0]);
    else destruct(obj);
}

