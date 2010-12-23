// wizardb.c
// By Spiderii������Ҷ���
// By Spiderii�ϲ�ͬ�����lsxk�ļӽ���
// by lsxk@hsbbs  ���Ӷһ��Խ�ɽׯ��Ʒ  2008/06/27
inherit NPC;
#include <ansi.h>

int ask_buchang();
int ask_buchang2();
int ask_sjling();
int ask_sjsz();

void create()
{
        set_name("��ʦ",({  "wizard", "wushi" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "����һ�������������µ���ʦ��\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set_temp("apply/defense", 10);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        set("inquiry", ([
              "�Խ���": (: ask_sjling :),
              "�Խ�ɽׯ": (: ask_sjsz :),
              "��������": (: ask_buchang :),
              "��������": (: ask_buchang2 :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}

int ask_sjsz(){
    object me = this_player();

    int i = me->query("SJ_YuanBao");

    if(i<3){
        command("say ����Խ�Ԫ������������");
        return 1;
    }

    me->add("SJ_YuanBao",-3);
    command("haha");
    command("say ��Ȼ�����Խ�ɽׯ������Ϊ�����Ҿ�ͨ���£�����ȥ��һ��ɽׯ�ɣ�");
    me->add_temp("get_in_sjsz",1);
    CHANNEL_D->do_channel(this_object(), "rumor",sprintf("%s����ʦ��������һ�ν���"+HIW+"�Խ�ɽׯ"+HIM+"�Ļ��ᣡ", me->name(1)));
    return 1;
}

int ask_sjling(){
    object me = this_player();
    object ob;

    int i = me->query("SJ_YuanBao");

    if(i<5){
        command("say ����Խ�Ԫ������������");
        return 1;
    }

    me->add("SJ_YuanBao",-5);
    ob = new("/cmds/leitai/bwdh/obj/sjsz_ling");
    ob->move(me);
    command("say �һ���ϣ�");
    return 1;
}

int ask_buchang()
{
        object ob;
        object letter;
      
        ob = this_player();

     
        if(ob->query("duanzao_buchang")){
                command("say �㲻���Ѿ���������ô��");
                return 1;
        }
        if(ob ->query("combat_exp") >= 800000 && objectp(letter = new("/d/wuguan/npc/obj/letter")) ) {
                command("nod "+ob->query("id"));
                command("say ���������Spiderii������Ҷ��켼�ܵ����������Ի�ò�����");
                command("say ����㲻��ұ������֮��������ʹ�� help dazao �����ϸ��Ϣ��");
                letter->move(ob);
                message_vision("$n��$Nһ�⡸"+letter->query("name")+"����\n",ob,  this_object());        
                ob->set("duanzao_buchang",1);
                return 1;
        }
        else {
                command("pat "+ob->query("id"));
                command("say ��λ" + RANK_D->query_respect(ob)+"������ʱ��������Ҫ�󣬼���Ŭ���ɡ�");
                return 1;
        }
}
int ask_buchang2()
{
        object ob;
        mapping myfam;
        ob = this_player();

        myfam = (mapping)ob->query("family");
        
        if(!myfam || myfam["family_name"] != "����")
        return 0;
        if(ob->query("mjxl_buchang")){
                command("say �㲻���Ѿ���������ô��");
                return 1;
        }
       ob->add("job_time/����Ѳ��",250);
       ob->set("mjxl_buchang",1);
       write("������ϣ����250������Ѳ������!\n");
       return 1;
}
