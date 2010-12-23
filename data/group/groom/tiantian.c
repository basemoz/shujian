// Room: /data/group/groom/tiantian.c
inherit ROOM;

void create ()
{
  set ("short", "[1;31mÌìÌÃ[1;32m×ÜÌ³·ÏĞæ[0;37;0m");
  set ("long", @LONG
ÕâÀïÔø¾­ÊÇÌìÌÃµÄ×ÜÌ³£¬µ«ÊÇÏÖÔÚÒÑ¾­±»±ğÈËµ·»ÙÁË¡£
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "out" : "/data/group/zongtan",
]));

  setup();
  replace_program(ROOM);
}
