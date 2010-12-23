// Room: /d/shaolin/luohan3.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "罗汉堂三部");
	set("long", @LONG
这是一间极为简陋的禅房。环视四周，除了几幅佛竭外，室内空荡荡地
别无他物。地上整齐的摆放着几个破烂且发黑的黄布蒲团，几位须发花白的
老僧正在坐在上面闭目入定。这里是本寺十八罗汉参禅修行的地方，不少绝
世武功便是在此悟出。
LONG
	);

	set("exits", ([
		"south" : __DIR__"luohan2",
		"north" : __DIR__"luohan4",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/cheng-ming" : 1,
	]));
	set("coor/x",-10);
  set("coor/y",260);
   set("coor/z",120);
   set("coor/x",-10);
 set("coor/y",260);
   set("coor/z",120);
   setup();
}



