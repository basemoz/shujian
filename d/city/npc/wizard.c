// wizardb.c
// By Spiderii补偿玩家锻造
// By Spiderii合并同类项，把lsxk的加进来
// by lsxk@hsbbs  增加兑换试剑山庄物品  2008/06/27
inherit NPC;
#include <ansi.h>

int ask_buchang();
int ask_buchang2();
int ask_sjling();
int ask_sjsz();

void create()
{
        set_name("巫师",({  "wizard", "wushi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "这是一个成天无所事事的巫师。\n");

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
              "试剑令": (: ask_sjling :),
              "试剑山庄": (: ask_sjsz :),
              "补偿锻造": (: ask_buchang :),
              "补偿九阳": (: ask_buchang2 :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}

int ask_sjsz(){
    object me = this_player();

    int i = me->query("SJ_YuanBao");

    if(i<3){
        command("say 你的试剑元宝数量不够！");
        return 1;
    }

    me->add("SJ_YuanBao",-3);
    command("haha");
    command("say 既然你在试剑山庄略有作为，那我就通融下，你再去闯一次山庄吧！");
    me->add_temp("get_in_sjsz",1);
    CHANNEL_D->do_channel(this_object(), "rumor",sprintf("%s从巫师这里获得了一次进入"+HIW+"试剑山庄"+HIM+"的机会！", me->name(1)));
    return 1;
}

int ask_sjling(){
    object me = this_player();
    object ob;

    int i = me->query("SJ_YuanBao");

    if(i<5){
        command("say 你的试剑元宝数量不够！");
        return 1;
    }

    me->add("SJ_YuanBao",-5);
    ob = new("/cmds/leitai/bwdh/obj/sjsz_ling");
    ob->move(me);
    command("say 兑换完毕！");
    return 1;
}

int ask_buchang()
{
        object ob;
        object letter;
      
        ob = this_player();

     
        if(ob->query("duanzao_buchang")){
                command("say 你不是已经补偿过了么？");
                return 1;
        }
        if(ob ->query("combat_exp") >= 800000 && objectp(letter = new("/d/wuguan/npc/obj/letter")) ) {
                command("nod "+ob->query("id"));
                command("say 你符合天神Spiderii补偿玩家锻造技能的条件，可以获得补偿。");
                command("say 如果你不解冶铁煅造之术，可以使用 help dazao 获得详细信息。");
                letter->move(ob);
                message_vision("$n给$N一封「"+letter->query("name")+"」。\n",ob,  this_object());        
                ob->set("duanzao_buchang",1);
                return 1;
        }
        else {
                command("pat "+ob->query("id"));
                command("say 这位" + RANK_D->query_respect(ob)+"，你暂时还不符合要求，继续努力吧。");
                return 1;
        }
}
int ask_buchang2()
{
        object ob;
        mapping myfam;
        ob = this_player();

        myfam = (mapping)ob->query("family");
        
        if(!myfam || myfam["family_name"] != "明教")
        return 0;
        if(ob->query("mjxl_buchang")){
                command("say 你不是已经补偿过了么？");
                return 1;
        }
       ob->add("job_time/明教巡逻",250);
       ob->set("mjxl_buchang",1);
       write("补偿完毕，添加250次明教巡逻任务!\n");
       return 1;
}
