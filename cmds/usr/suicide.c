// suicide.c

// Modified by mxzhao 2004/02/21

#include <ansi.h>
#include <command.h>
#include <mudlib.h>
#include <database.h>

private void check_password(string passwd, object me, int forever);
private void confirm_password(string passwd, object me, int forever);

int main(object me, string arg)
{
	if (wiz_level(me) && getuid(me)!="ciwei")
	{
		return notify_fail("�����������ɱ��"
			"�������ʱ��ʲô�벻���ģ����Ƕ�ʹ�����İɡ�\n");
	}

	if( me->is_busy() || me->is_fighting() )
	{
		return notify_fail("����һ��������û��ɡ�\n");
	}

	if( arg && arg != "-f") 
	{
		return notify_fail("���� suicide -f ȷ����ɱ��\n");
	}
	
	if (environment(me)->query("no_fight"))
	{
		return notify_fail("�����ƺ�û����ɱ��������\n");
	}

	if (!me->query_temp("link_ob"))
	{
		return notify_fail("�㲻���������߽���ģ�������ɱ��\n");
	}
	
	if(!arg)
	{
		object weapon;
		object zhong;
		int needdest = 0;
		
		if(me->query("age") < 30 ) return notify_fail("����ͻ��ᣬδ����ΰ��Σ�ǰ;�ǹ����Σ�\n");
				
		weapon = me->query_temp("weapon");		
		zhong = find_object(NPC_D("zhong-shentong"));
		if(!zhong)
		{
			zhong = load_object(NPC_D("zhong-shentong"));
			needdest = 1;
		}
				
		if( zhong->query("winner") == me->query("id") )
		{
			if(needdest) destruct(zhong);
			return notify_fail("����Ϊ��������������Ծ�����\n");
		}
		
		if(needdest) destruct(zhong);
												
		if(weapon)
		{
			string* weapon_list = ({ "sword","axe","blade","dagger","fork","hook","spear",});
			
			if( member_array(weapon->query("skill_type"),weapon_list)==-1 )
			{
				return notify_fail("������"+weapon->name()+"����������\n");
			}
			//sharpness
		}
		else
		{
			if( me->query_skill("force") < 500 )
			{
				return notify_fail("����ڹ���Ϊ���������ԶϾ�����\n");				
			}			
			if( me->query("neili") < 4000 )
			{
				return notify_fail("������������ˡ�");
			}			
		}
		
		write("Ҳ����Ϸ�����Ļ����䣬Ҳ������˶�����ܵ�֪������\nȷ���Ļ����������ĵ�½���룺");
		input_to("check_password_die", 1, me, 1);
		return 1;
	}
	write("ѡ����ɱ���ȥ���־��飬��ʮ��Сʱ֮�ڲ������µ�¼��\n"
		"ȷ���Ļ����������ĵ�½���룺");

	input_to("check_password", 1, me, 1);
	return 1;
}

private void check_password_die(string passwd, object me, int forever)
{
	string old_pass = PASSWD_D->get_passwd(geteuid(me));
	object weapon = me->query_temp("weapon");
	
	if (!old_pass)
	{
		tell_object(me, "��ʱ������ɱ��\n");
		return;
	}

	if( crypt(passwd, old_pass)!=old_pass )
	{
		tell_object(me, "�������\n");
		return;
	}
	
	tell_object(me,"\n\n");
	
	if(weapon)
	{
		message_vision(HIR"$N������������������վ���������Ե�������������У����Լ��ʺ�����Ĩȥ����\n"NOR,me);
		tell_object(me,"������ɲ�Ǽ��罦��ӿ��������Ҳ���ɻ����Ǻ쳾���¡���\n");
		me->set_temp("last_damage_from","��"+environment(me)->query("short")+"���ض�����");
	}
	else
	{
		message_vision(HIR"$N��ȻһЦ����ϥ�������������죬����������������ת��ֱ�����Լ����澭��������\n"NOR,me);
		tell_object(me,"�����ɫ�ɺ������Ұף��ɲҰ��������ƣ����ް����������\n");
		me->set_temp("last_damage_from","��"+environment(me)->query("short")+"�ԶϾ���������");
	}
			
	me->delete_temp("faint_by");
	me->die();
}

private void check_password(string passwd, object me, int forever)
{
	string old_pass = PASSWD_D->get_passwd(geteuid(me));

	if (!old_pass)
	{
		tell_object(me, "��ʱ������ɱ��\n");
		return;
	}

	if( crypt(passwd, old_pass)!=old_pass )
	{
		tell_object(me, "�������\n");
		return;
	}

	if (!me->query("confirm_passwd"))
	{
		confirm_password(passwd, me, forever);
	}
	else
	{
		write("����������ȷ�����룺");
		input_to("confirm_password", 1, me, forever);
	}
}

private void confirm_password(string passwd, object me, int forever)
{
	string confirm_pass = me->query("confirm_passwd");
	
	if ( confirm_pass && crypt(passwd, confirm_pass) != confirm_pass)
	{
		write("ȷ���������\n");
		return;
	}

	if (forever)
	{
		tell_object( me, HIR "\n�����Ҫ��ɱ�ˡ�\n\n" NOR);

		if (!wiz_level(me)) 
		{
			CHANNEL_D->do_channel(this_object(), "rumor", 
				me->short(1) + "����Ҫ��ɱ�ˡ�");
		}

		me->set_temp("suicide_countdown", 6);
		me->start_busy( (: call_other, this_object(), "slow_suicide" :),
			(: call_other, this_object(), "halt_suicide" :) );
	}
}

private int slow_suicide(object me)
{
	object link_ob = me->query_temp("link_ob");
	int stage = me->add_temp("suicide_countdown", -1);

	if (!link_ob)
	{
		return 0;
	}

	if (stage > 1)
	{
		if( stage%5 == 0 )
		{
			tell_object(me, HIR "�㻹��" + chinese_number(stage+stage) 
				+ "�������ʱ�䣬��ֹͣ���� halt��\n" NOR);
		}

		return 1;
	}

	log_file("static/SUICIDE",	sprintf("%s ��ɱ\n", geteuid(me)), me);

	seteuid(getuid());

	write(HIY"����һ�����飬�ú���Ϣ�ɣ�\n"NOR);

	if (me->query("g_title") && me->query("g_level") == 1)
	{
		write_file("/log/group", sprintf("%s %s ��ɢ��%s ( %s ) ��ɱ��\n", 
			ctime(time())[4..19], me->query("g_title"), 
			me->query("name"), me->query("id")));
	}

	rm(link_ob->query_save_file() + ".o");
	rm(me->query_save_file() + ".o");

	if(!wiz_level(me))
	{
		foreach (object inv in all_inventory(me))
		{
			if (inv->query("money_id"))
			{
				destruct(inv);
			}
			else if ( !inv->query_autoload() )
			{
				DROP_CMD->do_drop(me, inv);
			}

			me->delete("balance");
		}
	}

	if (wiz_level(me))
	{
		link_ob->save();
		me->save();

		cp(link_ob->query_save_file() + SAVE_EXTENSION, 
			link_ob->query_save_file() + ".ooo");
		rename(me->query_save_file() + SAVE_EXTENSION, 
			me->query_save_file() + ".ooo");
	}
	else if (me->query("combat_exp") < 20000)
	{
		dbquery("delete from Users "
			"where U_Username='" + geteuid(me) + "'");
		// ɾ����̳�ʺ�
		BBS_D->add_Bbs_Up_Map(WEB_DB_NAME, "DELETE FROM members 
		WHERE username = '"+
		geteuid(me) +"@"+lower_case(INTERMUD_MUD_NAME)+"'");

		rm(link_ob->query_save_file() + SAVE_EXTENSION);
		rm(me->query_save_file() + SAVE_EXTENSION);
	}
	else
	{
		link_ob->set("last_on", time() + 86400);
		link_ob->save();

		if (!environment(me)->query("no_save"))
		{
			me->set("startroom", base_name(environment(me)));
		}

		if (me->query("registered") == 3)
		{
			me->add("combat_exp", -me->query("combat_exp")/20);
		}
		else
		{
			me->add("combat_exp", -me->query("combat_exp")/10);
		}

		me->save();

		rm(link_ob->query_save_file() + ".ooo");
		rm(me->query_save_file() + ".ooo");
	}

	tell_room(environment(me), me->name() +
		"��ɱ�ˣ��Ժ�����Ҳ������������ˡ�\n", ({me}));

	if (!wiz_level(me))
	{
		CHANNEL_D->do_channel(this_object(),"rumor", 
			me->short(1) + "��ɱ�ˣ��Ժ�����Ҳ������������ˡ�");
	}

	destruct(link_ob);
	destruct(me);
	return 0;
}

int halt_suicide(object me)
{
	tell_object(me, "���������ɱ����ͷ��\n");

	if (!wiz_level(me))
	{
		CHANNEL_D->do_channel(this_object(), "rumor", 
			me->name(1) + "���������¸ҵػ���ȥ��");

		me->start_busy(600);
	}

	write("�������˳�ʱ��ĳ�˼֮�С�\n");
	return 1;
}


int help (object me)
{
	write(@HELP
ָ���ʽ: suicide [-f]

�����Ϊĳ��ԭ���㲻����ˣ������ѡ����ɱ��
��ɱ��ʮ��Сʱ�Ժ�������µ�¼��

��ͨ�û���ȥ10%�ľ��飬VIP�û���ȥ5%�ľ��顣

����С�� 20K ����ҵ���ֱ��ɾ����

������� -f ����������ʾ��ɱһ�Ρ�

HELP);

	return 1;
}
