// 用这个 code 选择是否加入帮派

#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
    set("unit","封");
    set("no_get", 1);
    set("no_drop", 1);
    set("no_put", 1);
    set("no_give", 1);
    set("material", "paper");
    set_weight(1);
    setup();
}

void init()
{
    object me = this_player();
    if (!me->query_temp("g_name") )
    {
	    set_name (HIR"邀请信"NOR, ({ "invite letter","letter"}));
        set("long", "这是一封邀请信。愿意加入就 gjoin <邀请者id> ，不愿意加入可以拒绝 gjoin cancel。\n");
    }
    else
    {
        set_name (HIR + me->query_temp("g_name") + me->query_temp("g_type")
        	+ "邀请信"NOR, ({ "invite letter","letter" }));
        set("long", "这是一封来自"HIG + me->query_temp("g_name") + me->query_temp("g_type")
            + NOR "的邀请信，上面写到：\n"
            + me->query("name") + RANK_D->query_respect(me) + "：\n"
            + "    " + me->query_temp("g_name") + me->query_temp("g_type") + "诚邀"
            + RANK_D->query_respect(me) + "加盟。\n    本" + me->query_temp("g_type")
            + "宗旨：" + me->query_temp("g_idea")
            + "。\n                         " + me->query("g_invite_name")
            + "\n愿意加入就 gjoin <邀请者id> ，不愿意加入可以拒绝 gjoin cancel。\n");
    }
    if (me && present(this_object(), me))
        add_action("do_agree", "gjoin");
}

int do_agree(string str)
{
    object ob1, me = this_player();
    string st1;

    if (!str || str=="") return notify_fail ("你要接受谁的邀请？\n");

    if ( str=="cancel")
    {
	    message_vision("$N拒绝了邀请，决定暂时不加入帮派组织。\n",me);
        message_vision("$N偷偷的把邀请信扔掉了。\n",me);
        me->delete_temp("g_level");
        me->delete_temp("g_name");
        me->delete_temp("g_type");
        me->delete_temp("g_header_name");
        me->delete_temp("g_idea");
        me->delete_temp("g_number");
        me->delete("g_invite_name");
        me->delete("g_invite_id");
        destruct(this_object() );
        return 1;
    }

    if (!ob1 = find_living(str)) ob1 = LOGIN_D->find_body(str);
    if (!ob1) return notify_fail(""+ str + "现在不在这里。\n");

    if(!objectp(ob1 = present(str, environment(me))) )
        return notify_fail(""+ str + "现在不在这里。\n");
    if ( str != me->query("g_invite_id") )
        return notify_fail("不是 "+ str + " 邀请你加入帮会的。\n");
    if( !living(ob1) )
        return notify_fail("你等" + ob1->name() + "醒来再说吧。\n");
    else
    {
        me->set("g_level",me->query_temp("g_level"));
        me->set("g_name",me->query_temp("g_name"));
        me->set("g_type",me->query_temp("g_type"));
        me->set("g_idea",me->query_temp("g_idea"));
        me->set("g_number",me->query_temp("g_number"));
        st1 = me->query_temp("g_header_name");
        me->set("g_header_name",st1);
        me->set("old_title",me->query("title"));
        switch((int)me->query_temp("g_level"))
        {
        case 2:
        	me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"副"+ me->query("g_type") +"主"NOR);
            break;
        case 3:
        	me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"长老"NOR);
            break;
        case 4:
        	me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"使者"NOR);
            break;
        case 5:
        	me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"香主"NOR);
            break;
        default:
        	me->set("title","［"HIW+ me->query("g_name") + me->query("g_type") + NOR "］"+ HIG +"帮众"NOR);
        }
        me->set("new_title",me->query("title") );
        new("/data/group/obj/ling")->move(me);
        message_vision("$n接收了$N的邀请，加入了［" HIW+ me->query("g_name") + me->query("g_type") + NOR"］。\n",ob1,this_player() );
        message_vision("$n交给$N一个［" HIW+ me->query("g_name") + me->query("g_type") + NOR"］令牌 。\n",this_player(),ob1 );
        me->delete_temp("g_level");
        me->delete_temp("g_name");
        me->delete_temp("g_type");
        me->delete_temp("g_header_name");
        destruct(this_object() );
        return 1;
    }
}
