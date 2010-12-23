// Cmd:  zhua.c
// Created by Numa 1999-12-10
// Add Log

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        object *inv = all_inventory(me);
        int i;
        if (!me->is_robot())
	return notify_fail("你当前没有被系统判断为机器人，不需要召唤银翼杀手。\n");
        for(i=0;i<sizeof(inv);i++)
        	if( inv[i]->query("name")=="银翼杀手") 
	return notify_fail("一次只能召唤一个银翼杀手！\n");                
        if (me->query_temp("robot_try")>10)
	return notify_fail("银翼杀手召唤失败！\n");    
   
        ob = new("/clone/npc/antirobotnew");
        if (me->is_vip() && me->query_temp("robot_prize"))
        {
	ob->test_robot(me);
	me->delete_temp("robot_prize");
	tell_object(me,HIY"你召来了一个银翼杀手。\n");
        }
        else
        {   
	ob->test_robot(me);
	me->add_temp("robot_try",1);
	tell_object(me,HIY"你召来了一个银翼杀手。\n");   
        }   
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : zhua

此指令可让你召来一个银翼杀手。

HELP
    );
    return 1;
}

