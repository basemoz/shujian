// mai.c ��

#include <ansi.h>

inherit NPC;

//int waiting(object me);
//int checking(object me);
//int do_chase(object me);
//int do_kill(object me, object dest);
//void 
string ask_me();

void create()
{
       set_name("��", ({ "mai jing", "mai" }) );
       set("title", "�޾������");
       set("gender", "����" );
       set("shen_type", -1);
       set("age", 50);
       set("str", 30);
       set("con", 10);
       set("int", 10);
       set("dex", 30);
       set("long",
               "����Ǻ����ߺ��Ĵ������ɱ����������Ϊ��\n" );
       set("combat_exp", 600000);
       set("attitude", "peaceful");
       set("chat_chance", 2);
       set("chat_msg", ({
           "��˵��: �޾����Ǻ��ϵ�һ��˭Ҳ���¡�\n",
         (: random_move :)
         }));
          set("chat_chance_combat", 20);
          set("chat_msg_combat", ({
             (: exert_function, "powerup" :),
               }));
       set("max_qi", 3000);
       set("max_jing", 400);
       set("neili", 3000);
       set("max_neili", 3000);
       set("jiali", 150);
       set("shen_type", -1);
       set("env/wimpy", 60);
       set("score",10000);
       set_skill("force", 150); 
       set_skill("unarmed", 150);
       set_skill("huntian-qigong",150);
       set_skill("blade", 150);
       set_skill("xiuluo-dao",150);
       set_skill("dodge", 120);
       set_skill("ding-dodge", 120);
       set_skill("parry", 150);
       set_skill("cuff",150);
       set_skill("luohan-quan",150);
       map_skill("dodge", "ding-dodge");
       map_skill("blade","cibei-dao");
       map_skill("parry","cibei-dao");
       map_skill("cuff","luohan-quan");
       prepare_skill("cuff","luohan-quan");
       setup();
       carry_object("/d/city/obj/blade")->wield(); 
       carry_object("/d/city/obj/cloth")->wear();
       carry_object("/u/hunthu/npc/obj/qzling2");
 }
  void unconcious()
{
    object me,ob;
    me=this_player();
    ob=load_object("/u/hunthu/npc/obj/qzling2");
          if (objectp(present(ob,this_object()) {
          if (me->query_temp("promotion_target")=="��ɰ�����Ԫ�㲨") {
          if (query_temp("last_damage_from") == me {
             add_money("gold", 10);
           //message_vision("\n$N�������³������֣���......" + query("hire")[0..1] + "......��\n", this_object());
               } else
              message_vision("\n$Nа���Ц������ϧ����Զ�ò�����������...\n", this_object());
              destruct(ob); 
       }
       ::die();
}
   ::unconcious();  
}
