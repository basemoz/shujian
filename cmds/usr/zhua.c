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
	return notify_fail("�㵱ǰû�б�ϵͳ�ж�Ϊ�����ˣ�����Ҫ�ٻ�����ɱ�֡�\n");
        for(i=0;i<sizeof(inv);i++)
        	if( inv[i]->query("name")=="����ɱ��") 
	return notify_fail("һ��ֻ���ٻ�һ������ɱ�֣�\n");                
        if (me->query_temp("robot_try")>10)
	return notify_fail("����ɱ���ٻ�ʧ�ܣ�\n");    
   
        ob = new("/clone/npc/antirobotnew");
        if (me->is_vip() && me->query_temp("robot_prize"))
        {
	ob->test_robot(me);
	me->delete_temp("robot_prize");
	tell_object(me,HIY"��������һ������ɱ�֡�\n");
        }
        else
        {   
	ob->test_robot(me);
	me->add_temp("robot_try",1);
	tell_object(me,HIY"��������һ������ɱ�֡�\n");   
        }   
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : zhua

��ָ�����������һ������ɱ�֡�

HELP
    );
    return 1;
}

