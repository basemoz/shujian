// qlmws.c
// 青龙门卧室
inherit ROOM;
void create()
{
	set("short","卧室");
	set("long",@long
此处是青龙门的卧室，屋中的布置很简单，只有几只大床靠墙放着，
供本门教众休息之用。
long);
	set("exits",([
	    "west" : __DIR__"qlm",
]));
      set("sleep_room", 1);
      set("no_fight",1);
//create_door("west", "小门", "east", DOOR_CLOSED);
      set("coor/x",520);
  set("coor/y",430);
   set("coor/z",50);
   setup();
}
	    	
