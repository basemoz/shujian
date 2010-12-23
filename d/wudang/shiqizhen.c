// shiqizhen.c 十偃镇
// By Spdierii@ty 加入yttlg quest
#include <ansi.h>
inherit ROOM;
string look_caocong();
string look_dache();
void create()
{
        set("short", "十偃镇");
	set("long", @LONG
这里是武当山下东北方向的十偃镇。这一带山上人迹稀少,有些荒凉。
道旁一辆大车(dache)歪歪的倒卧在草丛(caocong)之中,透露出些古怪。
LONG
	);
	set("item_desc",([
		"caocong"	:	(: look_caocong :),
              "dache"       :      (: look_dache :),
	]));
setup();
}
void init()
{    
        object me = this_player();

       if (me->query_temp("quest/yttlg/story")){
       add_action("do_bo", "bo");
	add_action("do_get", "get");
  }
}

string look_dache()
{
     	
  	return "但见拉车的骡子头骨破碎，脑浆迸裂，死在地下,其状甚惨。  \n";
}
string look_caocong()
{
     	
  	return "却见长草中一人俯伏，动也不动，似已死去多时！\n";
}
int do_bo(string arg)
{      
        object me = this_player();
        
        if ( !arg || arg != "长草" )
                return notify_fail("你要做什么？\n");
       
        message_vision("$N心中怦怦乱跳，抢将过去，瞧后影正是三师兄俞岱岩，急忙伸臂抱起\n"
                       "只见他双目紧闭，脸如金纸，神色甚是可怖，你不由得又惊又痛,伸过自\n"
                       "己脸颊去挨在他的脸上，感到略有微温,心下大喜，伸手摸他胸口，觉得\n"
                       "他一颗心尚在缓缓跳动，只是时停时跳，说不定随时都能止歇,不由垂泪\n"
                       "大哭。又见其双手双足软软垂下，原来四肢骨节都已被人折断。但见指骨\n"
                       "、腕骨、臂骨、腿骨到处冒出鲜血，显是敌人下手不久，而且是逐一折断\n"
                       "，下手之毒辣，实令人惨不忍睹。\n", me);
         return 1;

}
int do_get(string arg)
{      
        object me = this_player();
        
        if ( !arg || arg != "俞岱岩" )
                return notify_fail("你要做什么？\n");
       
        message_vision("$N但觉怒火攻心，目眦欲裂，知道敌人离去不久，凭着健马脚力，当可追赶得上\n"
                       "狂怒之下，便欲赶去厮拚，但随即想起:三哥命在顷刻，须得先救他性命要紧。君\n"
                       "子报仇，十年未晚。当下稳稳的将他抱在手中，展开轻功，向山上疾行。\n", me);
        me->move("/d/wudang/houyuan");
        me->set_temp("quest/yttlg/story1",1);
        me->delete_temp("quest/yttlg/story");
        return 1;

}

