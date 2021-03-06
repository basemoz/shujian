// create by athoi@sj
#include <ansi.h>
inherit F_SAVE;

string query_save_file()
{
        return "/log/xyjob" ;
}

object *xyjob;

void xyjob_player_reset(object player)
{
	player->delete_temp("xyjob");
	player->delete_temp("special_die");
	player->delete_temp("special_poison");
	player->delete_temp("living");
	player->delete_temp("apply/short");
}

void add_xyjob(object player)
{
        int num = sizeof(xyjob);
        if( !pointerp(xyjob) || !sizeof(xyjob) )
                xyjob = ({ player });
        else
        {
                while (num--)
                {
                        if (xyjob[num] == player)
                                return;
                }
                xyjob += ({ player });
        }
        save();
}

void del_xyjob(object player)
{
        xyjob -= ({ player });
        save();
}

void xyjob_list(object me)
{
        int num = sizeof(xyjob);
        string defend = "守方尚存人员：";
        string defend_die = "守方阵亡人员：";
        string attack = "攻方尚存人员：";
        string attack_die = "攻方阵亡人员：";
        while (num--)
        {
        	if (!xyjob[num])
        		continue;
                if (xyjob[num]->query_temp("xyjob/xy_defend"))
                {
                        if (xyjob[num]->query_temp("living"))
                                defend += " " + xyjob[num]->query("name") + "(" + xyjob[num]->query("id") + ")";
                        else
                                defend_die += " " + xyjob[num]->query("name") + "(" + xyjob[num]->query("id") + ")";
                }
                else
                {
                        if (xyjob[num]->query_temp("living"))
                                attack += " " + xyjob[num]->query("name") + "(" + xyjob[num]->query("id") + ")";
                        else
                                attack_die += " " + xyjob[num]->query("name") + "(" + xyjob[num]->query("id") + ")";
                }
        }

        write(HIR"襄阳攻防战参战人员表：\n"NOR);
        write(HIB + attack + "\n"NOR);
        write(BLU + attack_die + "\n"NOR);
        write(HIG + defend + "\n"NOR);
        write(GRN + defend_die + "\n"NOR);
}

object *player_list()
{
        return xyjob;
}

void xyjob_reset()
{
	int num = sizeof(xyjob);
	while (num--)
		if (xyjob[num])
			xyjob_player_reset(xyjob[num]);
	xyjob = ({});
        save();
}

void create()
{
        seteuid(getuid());
        restore();
}

int main(object me,string arg)
{
        if (wizardp(me) && arg == "reset")
        {
                xyjob_reset();
                tell_object(me, "列表清理完毕。\n");
                return 1;
        }
        xyjob_list(me);
        return 1;
}
