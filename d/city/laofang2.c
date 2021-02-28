// Room: /d/city/laofang.c
// Build by Looklove@sj 2000/10/16
// 2001.9.29 update

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "牢房");
	set("long", @LONG
这里是牢房，房间里很潮湿，光线昏暗，空气弥漫着一股臭气，让人浑身
都不舒服。几个在街上到处裸奔的囚犯躺在角落里呻吟着。透过冰冷厚重的铁
门，偶尔传来一阵阵的吆喝声。大概又是在提审什么犯人。
LONG
	);

        set("no_fight", 1);
	set("no_sleep_room", 1);
	set("no_update", 1);
        set("valid_startroom", 1);
        set("objects", ([
		__DIR__"npc/yuzu2" : 1,
	]));
	setup();
}
//
//void init()
//{
//	object me = this_player();
//        if (me->query_temp("nude"))
//        	call_out("do_succor",90,me);
//        else if(userp(me)) {
//        	me->move("/d/city/dilao");
//        	tell_object(me,"你耳边不停传来一个声音，下不为例，下不为例啊！");
//        }
//        
//}

int do_kill(string arg)
{
        string action = query_verb();
        switch (action) {
        case "kill":
        case "hit":
        case "throw":
        case "fight":
        case "perform":
        case "dazuo":
        case "exercise":
        case "tuna":
        case "lian":
        case "practice":
        case "du":
        case "study":
        case "respirate":
        write("都已经到这个地方了，还想那些俗事做什么？\n");
        return 1;
        }
	return 0;
}
void do_succor(object me)
{
	if (!me) return;
        message_vision(HIW"突然外面传来一阵声音，$N因屡次裸奔，虽然有碍风化，但也已经收到惩罚，这次就绕了他，下回就没这么简单了。”\n"NOR, me);
	tell_object(me,CYN"你自言自语道：真他妈的晦气。"NOR);
	me->delete_temp("nude");
	me->move("/d/city/dilao");

}
