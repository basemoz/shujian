// olduser.c YUJ@SJ 2002-04-05
// 读取老站数据，将经过处理的数据设置回 dbase skills learned，保存
// 注意：操作者应该对老数据目录有读权限，对新数据目录有写权限
/* 用法举例：假设本文件放在 /clone/user 下
	#define ODB "/clone/user/olduser"
	mapping olddb, newdb = ([ ]);

	if (!ODB->restore("/old/user/y/yuj.o")) return 0;	// 读数据失败
	olddb = ODB->query_dbase();
	// 将指定的项目一一复制到 newdb
	...
	newdb["combat_exp"] = olddb["combat_exp"];
	newdb["id"] = olddb["id"];				// 或者判断是否需要换 id
	...
	// 将新 dbase 设置回去
	ODB->set_dbase(newdb);
	// 保存
	if (!ODB->save("/new/user/y/yuj.o")) return 0;		// 写数据失败
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
	ret = dbquery("REPLACE "+dbase["from_site"]+"_Data SET "
	//ret = dbquery("REPLACE Data SET "
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
