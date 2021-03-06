//Create by lsxk@hsbbs 2008/3/17
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int gifts, max_gifts;
    string gifts_name;

    max_gifts = me->query("relife/gift/now");

    if(!arg){
        tell_object(me,"请按照“"+HIG+"giftadd 天赋点数 to 天赋中文名称"+NOR+"”的格式进行添加天赋!\n\n"NOR);
        write("当前可用的天赋名称如下：\n\n");
        write(HIR"       进攻系"+HIY+"    防御系"+HIC+"    文学系"+HIM+"    解谜系"+HIG+"    恢复系\n"NOR);
        write(HIR"      绝世命中"+HIY+"  绝世招架"+HIC+"  绝世奇才"+HIM+"  探险奇人"+HIG+"  绝世筋骨\n"NOR);
        write(HIR"      极度杀戮"+HIY+"  极品体质"+HIC+"  神童在世"+HIM+"  探险专家"+HIG+"  死而后生\n"NOR);
        write(HIR"      嗜血元神"+HIY+"  铜墙铁壁"+HIC+"  博学天才"+HIM+"  领悟大师"+HIG+"  千古奇人\n\n"NOR);
        return 1;
    }

    if(!sscanf(arg, "%d to %s", gifts, gifts_name)){
        tell_object(me,"请按照“"+HIG+"giftadd 天赋点数 to 天赋中文名称"+NOR+"”的格式进行添加天赋!\n"NOR);
        return 1;
    }
    else{
        if(gifts<1)
            return notify_fail("你脑子转身转坏掉了？\n");

        if(gifts > max_gifts)
            return notify_fail("你现在没这么多天赋点数可以分配！\n请用"+HIR+" mygift "+NOR+"指令来查看你现在拥有多少点天赋!\n");
        //进攻系
        if(gifts_name == "绝世命中"){
            if((int)me->query("relife/attack/jsmz",1)>15 - gifts)
               return notify_fail("“绝世命中”天赋最多只能添加15点天赋点数！请重新选择！\n"NOR);
            else{
               me->add("relife/attack/jsmz",gifts);
               me->add("relife/gift/now",-gifts);
               me->add("relife/gift/used",gifts);
               tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIR+"绝世命中"+NOR+"”！\n");
            }
            return 1;
        }

        if(gifts_name == "极度杀戮"){
            if((int)me->query("relife/attack/jsmz",1)<5)
               return notify_fail("你必须在“绝世命中”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/attack/jdsl",1)>10 - gifts)
               return notify_fail("“极度杀戮”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/attack/jdsl",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIR+"极度杀戮"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "嗜血元神"){
            if((int)me->query("relife/attack/jdsl",1)<5)
               return notify_fail("你必须在“极度杀戮”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/attack/sxys",1)>5 - gifts)
               return notify_fail("“嗜血元神”天赋最多只能添加5点天赋点数！请重新选择！\n"NOR);
            me->add("relife/attack/sxys",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIR+"嗜血元神"+NOR+"”！\n");
            return 1;
        }
        //防御系
        if(gifts_name == "绝世招架"){
            if((int)me->query("relife/defend/jszj",1)>15 - gifts)
               return notify_fail("“绝世招架”天赋最多只能添加15点天赋点数！请重新选择！\n"NOR);
            me->add("relife/defend/jszj",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIY+"绝世招架"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "极品体质"){
            if((int)me->query("relife/defend/jszj",1)<5)
               return notify_fail("你必须在“绝世招架”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/defend/jptz",1)>10 - gifts)
               return notify_fail("“极品体质”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/defend/jptz",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIY+"极品体质"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "铜墙铁壁"){
            if((int)me->query("relife/defend/jptz",1)<5)
               return notify_fail("你必须在“极品体质”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/defend/tqtb",1)>5 - gifts)
               return notify_fail("“铜墙铁壁”天赋最多只能添加5点天赋点数！请重新选择！\n"NOR);
            me->add("relife/defend/tqtb",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIY+"铜墙铁壁"+NOR+"”！\n");
            return 1;
        }
        //文学系
        if(gifts_name == "绝世奇才"){
            if((int)me->query("relife/study/jsqc",1)>10 - gifts)
               return notify_fail("“绝世奇才”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/study/jsqc",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIC+"绝世奇才"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "神童在世"){
            if((int)me->query("relife/study/jsqc",1)<5)
               return notify_fail("你必须在“绝世奇才”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/study/stzs",1)>15 - gifts)
               return notify_fail("“神童在世”天赋最多只能添加15点天赋点数！请重新选择！\n"NOR);
            me->add("relife/study/stzs",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIC+"神童在世"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "博学天才"){
            if((int)me->query("relife/study/stzs",1)<5)
               return notify_fail("你必须在“神童在世”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/study/bxtc",1)>5 - gifts)
               return notify_fail("“神童在世”天赋最多只能添加5点天赋点数！请重新选择！\n"NOR);
            me->add("relife/study/bxtc",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIC+"博学天才"+NOR+"”！\n");
            return 1;
        }

        //解密系
        if(gifts_name == "探险奇人"){
            if((int)me->query("relife/quest/txqr",1)>15 - gifts)
               return notify_fail("“探险奇人”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/quest/txqr",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIM+"探险奇人"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "探险专家"){
            if((int)me->query("relife/quest/txqr",1)<5)
               return notify_fail("你必须在“探险奇人”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/quest/txzj",1)>10 - gifts)
               return notify_fail("“探险专家”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/quest/txzj",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIM+"探险专家"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "领悟大师"){
            if((int)me->query("relife/quest/txzj",1)<5)
               return notify_fail("你必须在“探险专家”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/quest/lwds",1)>5 - gifts)
               return notify_fail("“领悟大师”天赋最多只能添加5点天赋点数！请重新选择！\n"NOR);
            me->add("relife/quest/lwds",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIM+"领悟大师"+NOR+"”！\n");
            return 1;
        }
        //恢复系
        if(gifts_name == "绝世筋骨"){
            if((int)me->query("relife/recover/jsjg",1)>10 - gifts)
               return notify_fail("“绝世筋骨”天赋最多只能添加10点天赋点数！请重新选择！\n"NOR);
            me->add("relife/recover/jsjg",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIG+"绝世筋骨"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "死而后生"){
            if((int)me->query("relife/recover/jsjg",1)<5)
               return notify_fail("你必须在“绝世筋骨”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/recover/sehs",1)>15 - gifts)
               return notify_fail("“死而后生”天赋最多只能添加15点天赋点数！请重新选择！\n"NOR);
            me->add("relife/recover/sehs",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIG+"死而后生"+NOR+"”！\n");
            return 1;
        }

        if(gifts_name == "千古奇人"){
            if((int)me->query("relife/recover/sehs",1)<5)
               return notify_fail("你必须在“死而后生”天赋上花费至少5点天赋后，方可分配此天赋！\n"NOR);
            if((int)me->query("relife/recover/qgqr",1)>5 - gifts)
               return notify_fail("“千古奇人”天赋最多只能添加5点天赋点数！请重新选择！\n"NOR);
            me->add("relife/recover/qgqr",gifts);
            me->add("relife/gift/now",-gifts);
            me->add("relife/gift/used",gifts);
            tell_object(me,"你成功得添加了"+HIW+chinese_number(gifts)+NOR+"点天赋至“"+HIG+"千古奇人"+NOR+"”！\n");
            return 1;
        }

        //输错参数
        return notify_fail("请选择正确的天赋名称来添加天赋点数，指令格式："+HIR+"giftadd 天赋点数 to 天赋中文名称 "+NOR+"!\n");
    }

    return 1;
}
