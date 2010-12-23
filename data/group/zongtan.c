
inherit ROOM;

void create()
{
	set("short", "总坛入口");
	set("long", @LONG
  这里是到达各个帮派总坛的入口，可以到达各个帮派的总坛。
LONG
	);

	set("exits", ([
		"south" : "/d/city/wroad3",
	]));

	set("inited",0);
	setup();
}

void init()
{
	int line = 1;
	string dir,file;
	string s_log;
	
	//根据log文件动态设置出口
	if( !query("inited") )
	{
        while( s_log = read_file(__DIR__"/groom/log",line,1) )
        {
if(sscanf(s_log,"帮派总坛 %s 出口 %s",file,dir)==2)
            {
set("exits/"+dir[0..strlen(dir)-2],file);
            }
            line ++;
        }
        
        set("inited",1);
	}
}
