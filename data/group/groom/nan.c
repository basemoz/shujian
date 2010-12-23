// Room: /data/group/nan.c
inherit ROOM;

void create()
{
  set ("short", "[1;31mÈÕÔÂÉñ½Ì[1;32m ×ÜÌ³[0;37;0m");
  set ("long", @LONG
  ÕâÀïÊÇÈÕÔÂÉñ½ÌµÄ×ÜÌ³¡£ÉÏÃæ¹©·îµÄÊÇÇ°ÈÎÀú´ú°ïÖ÷µÄÁéÅÆ£¬
Á½Î»×ÜÌ³»¤·¨ËÅÁ¢ÔÚÏÂÊ×¡£·Ç±¾°ïµÜ×Ó²»ÄÜËæ±ã½øÈë£¬·ñÔò¿ÉÄÜ»á
ÈÇÀ´É±ÉíÖ®»ö¡£
LONG);

  set("skill_lvl", 250);
  set("hard", 2000);
  set("g_name", "ÈÕÔÂÉñ½Ì");
  set("exits", ([ /* sizeof() == 1 */
"out":"/data/group/zongtan",
]));
  set("combat_exp", 2000000);
  set("objects", ([ /* sizeof() == 2 */
"/data/group/obj/ling-pai.c":1,
"/data/group/npc/hufa.c":2,
]));
  setup();
  replace_program(ROOM);
}
