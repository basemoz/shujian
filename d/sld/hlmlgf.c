// hlmlgf.c
// 黑龙门练功房
inherit ROOM;
void create()
{
	set("short","练功房");
	set("long",@long
此处是黑龙门教众平时练功习武的地方。房中靠墙有个兵器架，上面
插着不少兵器，旁边放着几个石锁，屋子中间是一个梅花桩，房子的大粱
上则吊着几个沙袋。
long);
	set("exits",([
	    "east" : __DIR__"hlm",
]));
	set("coor/x",500);
  set("coor/y",430);
   set("coor/z",60);
   setup();
}
	    	
