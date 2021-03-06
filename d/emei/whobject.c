#define HTML_FILE "/doc/html/name.htm"
#include "ansi.h"

inherit ITEM;

int sort_user(object ob1, object ob2)
{
        string name1, name2;

        reset_eval_cost();
        if( wiz_level(ob1) != wiz_level(ob2) )
                return wiz_level(ob2)
                        - wiz_level(ob1);
        
        name1 = ob1->query("family/family_name");
        name2 = ob2->query("family/family_name");

        if (intp(name1)) name1 = "";
        if (intp(name2)) name2 = "";
        if (name1 > name2) return -1;
        if (name1 < name2) return 1;

        return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}

void create()
{
        set_name("奇怪的东西", ({ "dongxi", "object" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
		set("long", "看不出来这是个什么东西。\n");
        }
        setup();
}

void init()
{
	add_action("do_who2htm", "who2htm");
}

int do_who2htm()
{
    int i;
    object *list, *ob;
    string s,s1,s2;
    string str= "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">"
                "<title>北京书剑在线玩家列表</title><meta name=\"GENERATOR\" content=\"Microsoft FrontPage 3.0\">"
                "</head><body><p align=\"center\"><big>北京书剑在线玩家列表</big></p>"
                "<table border=\"1\" width=\"100%\"><tr><td width=\"10%\" align=\"center\">称谓</td>"
                "<td width=\"85%\" align=\"center\">玩家人物信息</td><td width=\"5%\" align=\"center\">状态</td></tr>";

    ob = filter_array(objects(), (: userp :));
    list = sort_array(ob, (: sort_user :));
    i = sizeof(list);
    while( i-- ) {
        if( !environment(list[i]) ) continue;
        sscanf( RANK_D->query_rank(list[i]), "%s【%s】%s", s1, s, s2);
        str = sprintf("%s<tr><td>%s<td>%s<td>%s</tr>",
              str, s,
              list[i]->short(1),
              interactive(list[i])?(query_idle(list[i]) > 120?"发呆":"在线"):"断线"
              );
    }
    str = sprintf("%s</table><p align=\"right\">%s</body></html>",str, ctime(time()));
    write_file(HTML_FILE,str,1);
    return 1;
}
