// olduser.c YUJ@SJ 2002-04-05
// ��ȡ��վ���ݣ�������������������û� dbase skills learned������
// ע�⣺������Ӧ�ö�������Ŀ¼�ж�Ȩ�ޣ���������Ŀ¼��дȨ��
/* �÷����������豾�ļ����� /clone/user ��
	#define ODB "/clone/user/olduser"
	mapping olddb, newdb = ([ ]);

	if (!ODB->restore("/old/user/y/yuj.o")) return 0;	// ������ʧ��
	olddb = ODB->query_dbase();
	// ��ָ������Ŀһһ���Ƶ� newdb
	...
	newdb["combat_exp"] = olddb["combat_exp"];
	newdb["id"] = olddb["id"];				// �����ж��Ƿ���Ҫ�� id
	...
	// ���� dbase ���û�ȥ
	ODB->set_dbase(newdb);
	// ����
	if (!ODB->save("/new/user/y/yuj.o")) return 0;		// д����ʧ��
*/

mapping dbase;
mapping skills;
mapping learned;
string *autoload;
mapping alias;
mapping skill_map;
mapping skill_prepare;
mapping conditions;

int restore(string file)
{
	return restore_object(file);
}

int save(string file)
{
	string data;
	mixed ret;
	
	assure_file(file);	
	if (!save_object(file)) 
	{
		return 0;
	}			
	data = replace_string(read_file(file), "", "");
	data = replace_string(data, "\\", "");
	data = replace_string(data, "\"", "");
	data = replace_string(data, "'", "");
	
	file = sprintf(DATA_DIR "user/%c/%s%s", dbase["id"][0], dbase["id"],SAVE_EXTENSION);
	//ret = dbquery("REPLACE "+dbase["from_site"]+"_Data SET "
	ret = dbquery("REPLACE Data SET "
		"U_ID=" + save_variable(file) + ","
		"U_Time=" + save_variable(time()) + ","
		"U_Data=" + save_variable(data));
	//if (!rm(file))
	//	log_file("Change_site_log",
	//		sprintf("Can not delete save file:%-8s from site %s",
	//			dbase["id"],
	//			dbase["from_site"]),
	//		this_object());
	if(!ret) return 0;
	return 1;
}

mapping query_dbase()
{
	return copy(dbase);
}

void set_dbase(mapping data)
{
	dbase = copy(data);
}

int delete_skill(string skill)
{
	if( mapp(skills) ) {
		map_delete(skills, skill);
		if( mapp(learned) ) {
			map_delete(learned, skill);
			return undefinedp(learned[skill]);
		}
		return undefinedp(skills[skill]);
	}
	return 0;
}

void set_skill(string skill, int val)
{
	if( !find_object(SKILL_D(skill))
	&& file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) ) skills = ([ skill: val ]);
	else skills[skill] = val;
}

int query_skill(string skill)
{
	if( mapp(skills) && !undefinedp(skills[skill]) ) return skills[skill];
	return 0;
}

void create()
{
	seteuid(getuid());
}
