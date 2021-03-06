// update.c

#include "/doc/help.h"
#include <ansi.h>

inherit F_CLEAN_UP;

int update_player(object me);

int main(object me, string arg)
{
        int i;
        object obj, *inv;
        string err, file;
        mixed *call_info;

        seteuid(geteuid(me));
        
        if (!arg)
                arg = me->query("cwf");
        if (sscanf(arg, "%s %s", file, arg) != 2)
                file = arg;
        if (file == "-f")
        {
                file = 0;
                arg = "-f";
        }
        if (!file)
                file = me->query("cwf");
        if (!file)
                return notify_fail("你要重新编译什么档案？\n");

        if ((obj = present(file, environment(me))) && interactive(obj))
                return update_player(obj);
        if (obj)
                file = base_name(obj);

        if( file == "me" )
                return update_player(me);
        else
        {
                file = resolve_path(me->query("cwd"), file);
                if (!sscanf(file, "%*s.c"))
                        file += ".c";
        }
 
        if( file_size(file) < 0 )
                return notify_fail("没有这个档案。\n");

        me->set("cwf", file);

        if (obj = find_object(file))
        {
                if( file_name(obj)==VOID_OB )
                        return notify_fail("你不能在 VOID_OB 里重新编译 VOID_OB。\n");
                if (sizeof(call_info = filter_array(call_out_info(), (: $1[0]==$2 :), obj)))
                {
                        tell_object(me, HIR"目标程序有以下 call_out 未完成。\n"NOR);
                        foreach (mixed *item in call_info)
                                tell_object(me, sprintf("%-40s %d\n", item[1], item[2]));
                        if (wiz_level(me) < 4)
                                return notify_fail("更新终止。\n");
                        if (arg != "-f")
                                return notify_fail("如想强制更新，请使用-f参数。\n");
                }
                inv = all_inventory(obj);
                i = sizeof(inv);
                while(i--)
                        if( userp(inv[i]) )
                                inv[i]->move(VOID_OB, 1);
                        else
                                inv[i] = 0;
                err = "/binaries"+file[0..<3]+".b";
                tell_object(me, "删除二进制文件 "+err+" ...");
                if( file_size(err) < 0 )
                        tell_object(me, "不存在。\n");
                else if (rm(err))
                        tell_object(me, "成功。\n");
                else
                        tell_object(me, "失败。\n");
                destruct(obj);
        }

        if (obj)
                return notify_fail("无法清除旧程式码。\n");

        tell_object(me, "重新编译 " + file + " ...");
        err = catch(call_other(file, "???"));
        if (err)
                tell_object(me, sprintf("发生错误：\n%s\n", err));
        else
        {
                tell_object(me, "成功！\n");
                if( (i=sizeof(inv)) && (obj = find_object(file)))
                {
                        while(i--)
                                if( inv[i] && userp(inv[i]) )
                                        inv[i]->move(obj, 1);
                }
        }

        return 1;
}

int update_player(object me)
{
        object env, link_ob, obj;

        env = environment(me);

        // First, create the new body.
        link_ob = me->query_temp("link_ob");
        obj = LOGIN_D->make_body(link_ob);
        if (!obj)
                return 0;
        // Save the data and exec the player to his/her link object.
        me->update_age();
        me->save();
        exec(link_ob, me);
        destruct(me);

        // Restore new body and exec to it via enter_world in LOGIN_D
        obj->restore();
        LOGIN_D->enter_world(link_ob, obj, 1);

        write("身体更新完毕。\n\n");
        obj->move(env);
        obj->write_prompt();

        return 1;
}

int help(object me)
{
        write( @HELP
指令格式 : update <档名|here|me|玩家名>
这个指令可以更新档案, 并将新档的内容载入记忆体内. 若目标为
'here' 则更新所在环境. 若目标为 'me' 则更新自己的人物. 若目
标为玩家则可更新玩家物件.

HELP
        );
        return 1;
}

