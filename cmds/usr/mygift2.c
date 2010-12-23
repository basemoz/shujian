// mygift  by lsxk@hsbbs 2008/3/15 
// 专为转身设置，查看自身天赋分配情况，未转生玩家无法使用！  by lsxk@hsbbs 2008/3/15

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int AP,DP,SP,QP,RP,A1,A2,A3,D1,D2,D3,S1,S2,S3,Q1,Q2,Q3,R1,R2,R3;
    string str_attack,str_defend,str_study,str_quest,str_recover,str_help;

    if(arg && objectp(find_player(arg)) && wizardp(me)) me = find_player(arg);

    A1 = (int)me->query("relife/attack/jsmz",1);
    A2 = (int)me->query("relife/attack/jdsl",1);
    A3 = (int)me->query("relife/attack/sxys",1);
    D1 = (int)me->query("relife/defend/jszj",1);
    D2 = (int)me->query("relife/defend/jptz",1);
    D3 = (int)me->query("relife/defend/tqtb",1);
    S1 = (int)me->query("relife/study/jsqc",1);
    S2 = (int)me->query("relife/study/stzs",1);
    S3 = (int)me->query("relife/study/bxtc",1);
    Q1 = (int)me->query("relife/quest/txqr",1);
    Q2 = (int)me->query("relife/quest/txzj",1);
    Q3 = (int)me->query("relife/quest/lwds",1);
    R1 = (int)me->query("relife/recover/jsjg",1);
    R2 = (int)me->query("relife/recover/sehs",1);
    R3 = (int)me->query("relife/recover/qgqr",1);

    AP = A1 + A2 + A3;
    DP = D1 + D2 + D3;
    SP = S1 + S2 + S3;
    QP = Q1 + Q2 + Q3;
    RP = R1 + R2 + R3;

    if(!me->query("relife/times")){
        write(me->query("name")+"果然很是天赋异秉..... -____________________-!\n");
        return 1;
    }

    str_help =sprintf(HIY"※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※"NOR);
    str_help += sprintf(HIY"\n%s%92s%s"NOR,"※"," ","※");
    str_help += sprintf(HIY+"\n※"HIC"%35s当前分配的天赋点数如下："HIY"%35s\n%s%94s\n"NOR,me->query("name"),"※","※","※");
    str_help += sprintf(HIY"※"HIR"%4s进攻系("+HIW+"%2d"+HIR+"/30)%5s"+HIY+"防御系("+HIW+"%2d"+HIY+"/30)%5s"+HIC+"文学系("+HIW+"%2d"+HIC+"/30)%5s"+HIM+"解谜系("+HIW+"%2d"+HIM+"/30)%5s"+HIG+"恢复系("+HIW+"%2d"+HIG+"/30)"HIY"%5s\n"NOR," ",AP," ",DP," ",SP," ",QP," ",RP,"※");
    str_help += sprintf(HIY"※"HIR"%3s绝世命中("+HIW+"%2d"+HIR+"/15)%3s"+HIY+"绝世招架("+HIW+"%2d"+HIY+"/15)%3s"+HIC+"绝世奇才("+HIW+"%2d"+HIC+"/10)%3s"+HIM+"探险奇人("+HIW+"%2d"+HIM+"/15)%3s"+HIG+"绝世筋骨("+HIW+"%2d"+HIG+"/10)"HIY"%4s\n"NOR," ",A1," ",D1," ",S1," ",Q1," ",R1,"※");
    str_help += sprintf(HIY"※"HIR"%3s极度杀戮("+HIW+"%2d"+HIR+"/10)%3s"+HIY+"极品体质("+HIW+"%2d"+HIY+"/10)%3s"+HIC+"神童在世("+HIW+"%2d"+HIC+"/15)%3s"+HIM+"探险专家("+HIW+"%2d"+HIM+"/10)%3s"+HIG+"死而后生("+HIW+"%2d"+HIG+"/15)"HIY"%4s\n"NOR," ",A2," ",D2," ",S2," ",Q2," ",R2,"※");
    str_help += sprintf(HIY"※"HIR"%3s嗜血元神("+HIW+"%2d"+HIR+"/ 5)%3s"+HIY+"铜墙铁壁("+HIW+"%2d"+HIY+"/ 5)%3s"+HIC+"博学天才("+HIW+"%2d"+HIC+"/ 5)%3s"+HIM+"领悟大师("+HIW+"%2d"+HIM+"/ 5)%3s"+HIG+"千古奇人("+HIW+"%2d"+HIG+"/ 5)"HIY"%4s\n"NOR," ",A3," ",D3," ",S3," ",Q3," ",R3,"※");
    str_help += sprintf(HIY"%s%92s%s\n"NOR,"※"," ","※");
    str_help += sprintf(HIY"※"HIW"%61s目前"+((me->query("relife/gift/now")>=1)?("还有"+HIR+"%2d"+HIW+"点天赋点数可以分配!"):"已无任何天赋点数可以分配!")+HIY"%4s\n"NOR,me->query("name"),me->query("relife/gift/now")>=1?(int)me->query("relife/gift/now",1):"  ※","※");
    str_help += sprintf(HIY"%s%92s%s\n"NOR,"※"," ","※");
    str_help +=sprintf(HIY"※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※"NOR);
    str_help += HIC"\n如果你要查看详细内容，请使用"+HIR+" mygift ["+HIW+"天赋系"+HIR+"] "+HIC+"的格式来查看。\n\n"NOR;

    if(AP > 0){
        str_attack = "╭─┬─────────────────────────╮\n";
        str_attack +="│  │        你在进攻系花费的天赋点数为："+sprintf(((AP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,AP)+"         │\n";
        str_attack +="│进├────┬────────────────────┤\n";
        str_attack +="│  │天赋名称│          当    前    效    果          │\n";
        str_attack +="│  ├────┼────────────────────┤\n";
        str_attack +="│  │绝世命中│降低对方对你所有物理攻击"+sprintf(HIR"%2d",A1)+"%"+NOR+"的躲闪几率！ │\n";
        str_attack +="│攻│("+sprintf(HIY"%2d"NOR,A1)+"/15) │下一等级效果："+((A1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,A1+1))+"                       │\n";
        str_attack +="│  ├────┼────────────────────┤\n";
        str_attack +="│  │极度杀戮│提升自己所有物理攻击"+sprintf(HIR"%2d",A2)+"%"+NOR+"伤害！           │\n";
        str_attack +="│  │("+sprintf(HIY"%2d"NOR,A2)+"/10) │下一等级效果："+((A2>9)?"N/A":sprintf(HIC"%2d%%"NOR,A2+1))+"                       │\n";
        str_attack +="│系├────┼────────────────────┤\n";
        str_attack +="│  │嗜血元神│你有"+sprintf(HIR"%2d",A3)+"%"+NOR+"的几率,在击中对方后额外获得一次额│\n";
        str_attack +="│  │ ("+sprintf(HIY"%1d"NOR,A3)+"/5)  │外物理攻击击！                          │\n";
        str_attack +="│  │        │下一等级效果："+((A3>4)?"N/A":sprintf(HIC"%2d%%"NOR,A3+1))+"                       │\n";
        str_attack +="╰─┴────┴────────────────────╯\n";

    }

    if(DP > 0){
        str_defend = "╭─┬─────────────────────────╮\n";
        str_defend +="│  │        你在防御系花费的天赋点数为："+sprintf(((DP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,DP)+"         │\n";
        str_defend +="│防├────┬────────────────────┤\n";
        str_defend +="│  │天赋名称│          当    前    效    果          │\n";
        str_defend +="│  ├────┼────────────────────┤\n";
        str_defend +="│  │绝世招架│增加自己对所有物理攻击"+sprintf(HIR"%2d",D1)+"%"+NOR+"的招架几率！   │\n";
        str_defend +="│御│("+sprintf(HIY"%2d"NOR,D1)+"/15) │下一等级效果："+((D1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,D1+1))+"                       │\n";
        str_defend +="│  ├────┼────────────────────┤\n";
        str_defend +="│  │极品体质│降低"+sprintf(HIR"%2d",D2)+"%"+NOR+"所有物理攻击对你所造成伤害！     │\n";
        str_defend +="│  │("+sprintf(HIY"%2d"NOR,D2)+"/10) │下一等级效果："+((D2>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,D2+1))+"                       │\n";
        str_defend +="│系├────┼────────────────────┤\n";
        str_defend +="│  │铜墙铁壁│你有"+sprintf(HIR"%2d",D3)+"%"+NOR+"的几率,在被击中后对敌人进行一次必│\n";
        str_defend +="│  │ ("+sprintf(HIY"%1d"NOR,D3)+"/5)  │中的物理攻击击！                        │\n";
        str_defend +="│  │        │下一等级效果："+((D3>4)?"N/A":sprintf(HIC"%2d%%"NOR,D3+1))+"                       │\n";
        str_defend +="╰─┴────┴────────────────────╯\n";

    }

    if(SP > 0){
        str_study = "╭─┬─────────────────────────╮\n";
        str_study +="│  │        你在文学系花费的天赋点数为："+sprintf(((SP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,SP)+"         │\n";
        str_study +="│文├────┬────────────────────┤\n";
        str_study +="│  │天赋名称│          当    前    效    果          │\n";
        str_study +="│  ├────┼────────────────────┤\n";
        str_study +="│  │绝世奇才│提高你的读书和学习效率"+sprintf(HIR"%2d",S1*5)+"%"+NOR+"！             │\n";
        str_study +="│学│("+sprintf(HIY"%2d"NOR,S1)+"/10) │下一等级效果："+((S1>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S1+1)*5))+"                       │\n";
        str_study +="│  ├────┼────────────────────┤\n";
        str_study +="│  │神童在世│提高你的练习和领悟效率"+sprintf(HIR"%2d",S2*2)+"%"+NOR+"！             │\n";
        str_study +="│  │("+sprintf(HIY"%2d"NOR,S2)+"/15) │下一等级效果："+((S2>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S2+1)*2))+"                       │\n";
        str_study +="│系├────┼────────────────────┤\n";
        str_study +="│  │博学天才│你有"+sprintf(HIR"%2d",S3*2)+"%"+NOR+"的几率,在技能升级时，使得这个技能│\n";
        str_study +="│  │ ("+sprintf(HIY"%1d"NOR,S3)+"/5)  │额外再升一级！                          │\n";
        str_study +="│  │        │下一等级效果："+((S3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(S3+1)*2))+"                       │\n";
        str_study +="╰─┴────┴────────────────────╯\n";

    }

    if(QP > 0){
        str_quest = "╭─┬─────────────────────────╮\n";
        str_quest +="│  │        你在解谜系花费的天赋点数为："+sprintf(((QP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,QP)+"         │\n";
        str_quest +="│解├────┬────────────────────┤\n";
        str_quest +="│  │天赋名称│          当    前    效    果          │\n";
        str_quest +="│  ├────┼────────────────────┤\n";
        str_quest +="│  │探险奇人│提高你"+sprintf(HIR"%2d",Q1)+"%"+NOR+"的解谜成功率！                 │\n";
        str_quest +="│谜│("+sprintf(HIY"%2d"NOR,Q1)+"/15) │下一等级效果："+((Q1>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,Q1+1))+"                       │\n";
        str_quest +="│  ├────┼────────────────────┤\n";
        str_quest +="│  │探险专家│你有"+sprintf(HIR"%2d",Q2)+"%"+NOR+"机会在解谜失败时,再获得一次机会！│\n";
        str_quest +="│  │("+sprintf(HIY"%2d"NOR,Q2)+"/10) │下一等级效果："+((Q2>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,Q2+1))+"                       │\n";
        str_quest +="│系├────┼────────────────────┤\n";
        str_quest +="│  │领悟大师│你有"+sprintf(HIR"%2d",Q3*10)+"%"+NOR+"的几率，解谜获得新技能时，直接领 │\n";
        str_quest +="│  │ ("+sprintf(HIY"%1d"NOR,Q3)+"/5)  │悟该技能到你技能上限！                  │\n";
        str_quest +="│  │        │下一等级效果："+((Q3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(Q3+1)*10))+"                       │\n";
        str_quest +="╰─┴────┴────────────────────╯\n";

    }

    if(RP > 0){
        str_recover = "╭─┬─────────────────────────╮\n";
        str_recover +="│  │        你在恢复系花费的天赋点数为："+sprintf(((RP>29)?HIC:HIY)+"%-2d"+HIC"/30"NOR,RP)+"         │\n";
        str_recover +="│恢├────┬────────────────────┤\n";
        str_recover +="│  │天赋名称│          当    前    效    果          │\n";
        str_recover +="│  ├────┼────────────────────┤\n";
        str_recover +="│  │绝世筋骨│提高你的运功疗伤功效"+sprintf(HIR"%2d",R1*8)+"%"+NOR+"！               │\n";
        str_recover +="│复│("+sprintf(HIY"%2d"NOR,R1)+"/10) │下一等级效果："+((R1>9)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R1+1)*8))+"                       │\n";
        str_recover +="│  ├────┼────────────────────┤\n";
        str_recover +="│  │死而后生│增加你在战斗中自动疗伤效果"+sprintf(HIR"%2d",R2*2)+"%"+NOR+"！         │\n";
        str_recover +="│  │("+sprintf(HIY"%2d"NOR,R2)+"/15) │下一等级效果："+((R2>14)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R2+1)*2))+"                       │\n";
        str_recover +="│系├────┼────────────────────┤\n";
        str_recover +="│  │千古奇人│战斗中被击中，自动恢复总气血的"+sprintf(HIR"%2d",R3*2)+"%"+NOR+"，并且 │\n";
        str_recover +="│  │ ("+sprintf(HIY"%1d"NOR,R3)+"/5)  │降低各类毒性发作时间。                  │\n";
        str_recover +="│  │        │下一等级效果："+((R3>4)?"N/A":sprintf(HIC"%2d"+"%%"NOR,(R3+1)*2))+"                       │\n";
        str_recover +="╰─┴────┴────────────────────╯\n";

    }


    if(arg == "进攻系"){
        write(str_attack);
        return 1;
    }
    else if(arg == "防御系"){
        write(str_defend);
        return 1;
    }
    else if(arg == "文学系"){
        write(str_study);
        return 1;
    }
    else if(arg == "解谜系"){
        write(str_quest);
        return 1;
    }
    else if(arg == "恢复系"){
        write(str_recover);
        return 1;
    }
    else{
        write(str_help);
        return 1;
    }

    return 1;
}
