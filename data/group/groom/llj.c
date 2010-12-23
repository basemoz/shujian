// Room: /data/group/llj.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31m¸¯Ê¬°ï[1;32m ×ÜÌ³[0;37;0m");
  set ("long", @LONG
  ÕâÀïÊÇ¸¯Ê¬°ïµÄ×ÜÌ³¡£ÉÏÃæ¹©·îµÄÊÇÇ°ÈÎÀú´ú°ïÖ÷µÄÁéÅÆ£¬
Á½Î»×ÜÌ³»¤·¨ËÅÁ¢ÔÚÏÂÊ×¡£·Ç±¾°ïµÜ×Ó²»ÄÜËæ±ã½øÈë£¬·ñÔò¿ÉÄÜ»á
ÈÇÀ´É±ÉíÖ®»ö¡£
LONG);

  set("combat_exp", 2100000);
  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));
  set("skill_lvl", 260);
  set("hard", 2100);
  set("objects", ([ /* sizeof() == 2 */
  "/data/group/obj/ling-pai.c" : 1,
  "/data/group/npc/hufa.c" : 2,
]));
  set("g_name", "¸¯Ê¬°ï");

  setup();
  replace_program(ROOM);
}
