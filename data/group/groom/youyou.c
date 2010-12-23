// Room: /data/group/youyou.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31mÉÍÉÆ·£¶ñÃË[1;32m ×ÜÌ³[0;37;0m");
  set ("long", @LONG
  ÕâÀïÊÇÉÍÉÆ·£¶ñÃËµÄ×ÜÌ³¡£ÉÏÃæ¹©·îµÄÊÇÇ°ÈÎÀú´ú°ïÖ÷µÄÁéÅÆ£¬
Á½Î»×ÜÌ³»¤·¨ËÅÁ¢ÔÚÏÂÊ×¡£·Ç±¾°ïµÜ×Ó²»ÄÜËæ±ã½øÈë£¬·ñÔò¿ÉÄÜ»á
ÈÇÀ´É±ÉíÖ®»ö¡£
LONG);

  set("combat_exp", 4500000);
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 350);
  set("hard", 4500);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("g_name", "ÉÍÉÆ·£¶ñÃË");

  setup();
  replace_program(ROOM);
}
