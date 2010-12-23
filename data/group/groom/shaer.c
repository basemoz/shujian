// Room: /data/group/groom/shaer.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31mÇØ·çÂ¥[1;32m ×ÜÌ³[0;37;0m");
  set ("long", @LONG
  ÕâÀïÊÇÇØ·çÂ¥µÄ×ÜÌ³¡£ÉÏÃæ¹©·îµÄÊÇÇ°ÈÎÀú´ú°ïÖ÷µÄÁéÅÆ£¬
Á½Î»×ÜÌ³»¤·¨ËÅÁ¢ÔÚÏÂÊ×¡£·Ç±¾°ïµÜ×Ó²»ÄÜËæ±ã½øÈë£¬·ñÔò¿ÉÄÜ»á
ÈÇÀ´É±ÉíÖ®»ö¡£
LONG);

  set("combat_exp", 5800000);
  set("g_name", "ÇØ·çÂ¥");
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 380);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("hard", 5800);

  setup();
  replace_program(ROOM);
}
