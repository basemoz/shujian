// Color.C
// Create By Yixian
// Last Modify By Yixian

#include <ansi.h>
#pragma optimize
#pragma save_binary

string *color = ({
        NOR"", RED"", HIR"",
        GRN"", HIG"", YEL"",
        HIY"", BLU"", HIB"",
        MAG"", HIM"", CYN"",
        HIC"", WHT"", HIW"",
});

string random_color(string arg)
{
        return color[random(sizeof(color))] + arg + NOR;
}

string replace_color(string arg)
{
                arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$BLK$", BLK);        
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
                arg = replace_string(arg, "$HBRED$", HBRED);
        arg = replace_string(arg, "$HBGRN$", HBGRN);
        arg = replace_string(arg, "$HBYEL$", HBYEL);
        arg = replace_string(arg, "$HBBLU$", HBBLU);
        arg = replace_string(arg, "$HBMAG$", HBMAG);
                arg = replace_string(arg, "$BLINK$", BLINK);
                arg = replace_string(arg, "$HBCYN$", HBCYN);
                arg = replace_string(arg, "$HBWHT$", HBWHT);
                arg += NOR;
        return arg;
}
string remove_color(string arg)
{
        arg = replace_string(arg, HBRED, "");
        arg = replace_string(arg, HBGRN, "");
        arg = replace_string(arg, HBYEL, "");
        arg = replace_string(arg, HBBLU, "");
        arg = replace_string(arg, HBMAG, "");
        arg = replace_string(arg, BLINK, "");
        arg = replace_string(arg, HBCYN, "");
        arg = replace_string(arg, HBWHT, "");
        arg = replace_string(arg,HIW,"");
        arg = replace_string(arg,HIM,"");
        arg = replace_string(arg,HIG,"");
        arg = replace_string(arg,HIC,"");
        arg = replace_string(arg,HIY,"");
        arg = replace_string(arg,HIR,"");
        arg = replace_string(arg,HIB,"");
        arg = replace_string(arg,RED,"");
        arg = replace_string(arg,CYN,"");
        arg = replace_string(arg,BLU,"");
        arg = replace_string(arg,WHT,"");
        arg = replace_string(arg,MAG,"");
        arg = replace_string(arg,YEL,"");
        arg = replace_string(arg,GRN,"");
        arg = replace_string(arg,NOR,"");

        return arg;
}

