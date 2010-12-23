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
        set_name( HIM"怪你过分美丽", ({ "falling" }) );
        set_weight(1000);
                set("unit", "个");
        
        setup();
}
int do_gift(string arg)
{
    int count;
    object me,ob; 
    string target,gift_file;
    me = this_player();
    if(!arg)  return notify_fail("gift 派礼物给在线玩家，命令格式： gift </路径/../目标文件名> <数量>\n\n");
    if (sscanf(arg, "%s %d", target, count) != 2 ) target = arg;  
    gift_file = target + ".c";
    if (file_size(gift_file) == -1) return notify_fail("找不到文件"+gift_file+"。\n");
    foreach (object player in users()) {
      if (!environment(player) || base_name(environment(player)) == "/d/jianyu" || query_idle(player) > IDLE || player->query_temp("netdead")) continue;
         ob=new(target);
         if (count > 1 && ob->query("base_unit")) ob->set_amount(count);
          ob->move(player);
            tell_object(me, HIW "\n\n忽然从极高极远的天空中极速降下一只浑身烈焰的"HIR"火凤"HIW"，周身闪耀七彩光芒。\n" NOR);
          tell_object(me, HIC "它爪下似乎抓着什么东西，突然"HIC"火凤"HIW"松开脚爪，有个东西直向你掉落下来。\n" NOR);
          tell_object(me, HIG "你猛一提气纵身一跃丈高将此物抓在手中，又潇洒的飘落地面。\n\n" NOR);
    }
    return 1;
}

