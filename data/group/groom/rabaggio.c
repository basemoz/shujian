// Room: /data/group/rabaggio.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31mÇå·çÒ¹ÓêÂ¥[1;32m×ÜÌ³·ÏĞæ[0;37;0m");
  set ("long", @LONG
ÕâÀïÔø¾­ÊÇÇå·çÒ¹ÓêÂ¥µÄ×ÜÌ³£¬µ«ÊÇÏÖÔÚÒÑ¾­»Ä·ÏÁË¡£
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));

  setup();
  replace_program(ROOM);
}
