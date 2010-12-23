#include <ansi.h>
#include <net/dns.h>
inherit ITEM;
#define IDLE 600
void init()
{
       add_action("do_gift","gift");
}
void create()
{
        set_name( HIM"�����������", ({ "falling" }) );
        set_weight(1000);
                set("unit", "��");
        
        setup();
}
int do_gift(string arg)
{
    int count;
    object me,ob; 
    string target,gift_file;
    me = this_player();
    if(!arg)  return notify_fail("gift �������������ң������ʽ�� gift </·��/../Ŀ���ļ���> <����>\n\n");
    if (sscanf(arg, "%s %d", target, count) != 2 ) target = arg;  
    gift_file = target + ".c";
    if (file_size(gift_file) == -1) return notify_fail("�Ҳ����ļ�"+gift_file+"��\n");
    foreach (object player in users()) {
      if (!environment(player) || base_name(environment(player)) == "/d/jianyu" || query_idle(player) > IDLE || player->query_temp("netdead")) continue;
         ob=new(target);
         if (count > 1 && ob->query("base_unit")) ob->set_amount(count);
          ob->move(player);
            tell_object(me, HIW "\n\n��Ȼ�Ӽ��߼�Զ������м��ٽ���һֻ���������"HIR"���"HIW"��������ҫ�߲ʹ�â��\n" NOR);
          tell_object(me, HIC "��צ���ƺ�ץ��ʲô������ͻȻ"HIC"���"HIW"�ɿ���צ���и�����ֱ�������������\n" NOR);
          tell_object(me, HIG "����һ��������һԾ�ɸ߽�����ץ�����У���������Ʈ����档\n\n" NOR);
    }
    return 1;
}

