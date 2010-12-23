// By River@SJ 2001/9  

inherit ROOM;

void create()
{
        set("short", "驿道");
        set("long", @LONG
你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的行商，赶着大
车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。不时还有两三骑快马从身
边飞驰而过，扬起一路尘埃。道路两旁是整整齐齐的杨树林。
LONG
        );
        set("outdoors", "沧州城");
        set("exits", ([ 
                "east" : "/d/cangzhou/wroad1",
                "southwest" : "/d/cangzhou/wroad3",
        ]));
	set("group", 1);
        setup();
}
