// yingshe-boook.c
// by daidai
#include <ansi.h>
 
inherit ITEM;
 
void create()
 {
         set_name(HIC"鹰蛇生死搏秘籍残本"NOR, ({ "yingshe miji","miji","book" }));
         set_weight(200);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "本");
                 set("long","这是一本记录鹰蛇生死搏的秘籍，但是残缺不全，一般人无法领悟。\n");
                 set("value", 500000);
                 set("no_get","这是那人的宝贝，你如何拿的走？\n");
                 set("no_drop","这么珍贵的东西，你敢乱丢？\n");
                 set("treasure",1);
                 set("unique",1);
                 set("material", "paper");
         } 
 }
 
 void init()
 {
         add_action("do_du", "read");
 }
 
 int do_du(string arg)
 {
         object me = this_player();
         int neili, lev, lim;
         
         if(!id(arg)) return 0;
 
         if(me->is_fighting())
                 return notify_fail("你无法在战斗中专心下来研读新知！\n");
         if(me->is_busy()) 
                 return notify_fail("你现在正忙着呢。\n");
 
         if(!me->query("quest/华山派/鹰蛇生死搏/pass"))
                 return notify_fail("你从哪里偷来的秘籍？可不能偷读哦！\n");
         if(this_object()->query("clone_by_wizard") && !wizardp(me)) 
                 return notify_fail("你从哪里偷来的？可不能偷读哦！\n"); 
         if(!me->query_skill("literate", 1)) 
                 return notify_fail("你是个文盲，先学点文化(literate)吧。\n");        
         if(me->query("jing") < 20)
                 return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");
         lev = me->query_skill("yingshe-shengsibo", 1);
         if (lev >150)
                 return notify_fail("你已经不能从这本书里得到任何指点了。\n");
             neili = 20+random(20);
              if (me->query("neili") < neili) 
                 return notify_fail("你内力不够，无法钻研这么高深的武功。\n");
          if (!lev)
                 write(HIC"\n你看了看秘籍，封皮上赫然写道："HIW"\n\n\t\t\t鹰蛇生死搏\n\n"HIY"你翻开秘籍，发现残破的书页上记载着不少练功插图与口诀，但是好像有些残缺。\n"NOR);
         write("你研读「鹰蛇生死搏」秘籍残本，对照自己的领悟要诀，似乎有些心得。\n");
         me->receive_damage("jing", 20);
         me->receive_damage("neili", neili);
         me->improve_skill("yingshe-shengsibo", me->query_skill("literate", 1) );
         me->improve_skill("hand", random(me->query_skill("literate", 1)) );
         me->improve_skill("claw", random(me->query_skill("literate", 1)) );
 
         if (!random(5))
                 message("vision", me->name() + "拿着一本残缺的秘籍一边研读一边手中不断比划着。\n", environment(me), ({me}));
         return 1;
 } 
 
 


