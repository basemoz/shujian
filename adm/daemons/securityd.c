// securityd.c
// 我加了 tmp 下 各wiz有对自己文件夹可读可写权限 有问题就改 Ciwei
// by spiderii@ty 这里要严格控制，变态的很
#include <login.h>

// By Annihilator@Eastern.Stories (11/25/94)
// Modify by Yuj@ShuJian (??/??/98)
// This is the "effective" access status compare to the "status" property
// in login object that this mapping determine wizards' access rights
// directly. It is important to make the "status" property matches this
// mapping for wizards higher than regular wizard such as sage, arch and
// admin. For thoese users whose name doesnot appear in this mapping, they
// are divided into three groups (wizard),(player) and (object) using
// wizardp() and interactive() efun.
// The parenthesis is nessessary to prevend players naming themself "admin"
// to hack the security system.

mapping wiz_status;

string *wiz_levels = ({
	"(player)",
	"(immortal)",
	"(apprentice)",
	"(wizard)",
	"(arch)",
	"(assist)",
	"(admin)"
});

// A valid write attempt must pass 2 checks: your uid or status must not be
// "excluded" and must be "trusted" on that directory in order to write in
// that directory. The directories containing the file is searched backward
// from the current directory to root. And exclude is checked prior than
// trusted.

void create()
{
	string *wizlist, wiz_name, wiz_level;

	wizlist = explode(read_file(WIZLIST), "\n");
	wiz_status = allocate_mapping(sizeof(wizlist));
	foreach (string item in wizlist)
		if (item[0] != '#' && sscanf(item, "%s %s", wiz_name, wiz_level) == 2)
			wiz_status[wiz_name] = wiz_level;
}

string *query_wizlist()
{
	return keys(wiz_status);
}

string *get_wizlist()
{
	return query_wizlist();
}

// This function returns the status of an uid.
string get_status(mixed ob)
{
	string euid;

	if (objectp(ob)) {
		if (getuid(ob) != ROOT_UID && !userp(ob))
			return "(player)";
		if (!(euid = geteuid(ob)))
			euid = getuid(ob);
	} else if (stringp(ob))
		euid = ob;

        if (euid == "zmud" )
		return "(admin)";
	if (!mapp(wiz_status))
		return "(player)";
	if (!undefinedp(wiz_status[euid]))
		return wiz_status[euid];
	if (member_array(euid, wiz_levels) != -1)
		return euid;
	return "(player)";
}

int get_wiz_level(object ob)
{
	return member_array(get_status(ob), wiz_levels);
}

int set_status(mixed ob, string status)
{
	string uid, *wiz, wizlist;

	if (geteuid(previous_object()) != ROOT_UID)
		return 0;

	if (stringp(ob))
		uid = ob;
	else if (userp(ob))
		uid = getuid(ob);
	else return 0;

	if (status == "(player)")
		map_delete(wiz_status, uid);
	else
		wiz_status[uid] = status;
	wiz = sort_array(keys(wiz_status), (: strcmp($1, $2) :));
	wizlist = "";
	foreach (string item in wiz)
		wizlist += item + " " + wiz_status[item] + "\n";
	write_file(WIZLIST, wizlist, 1);
	return 1;
}

// valid_write - called by the master object to determine whether if an user
//	is allowed to write on a certain file.
// NOTE:
//	The argument user should be an object according to the source code
// of driver. However, it is a mixed type in the released docs. We assume
// it is an object in normal case here and issue an error if it was not
// an object.

mapping exclude_read = ([
	"adm":				({ "(arch)", "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
	"adm/daemons/aliasd.c":		({ "(all)" }),
	"adm/daemons/channeld.c":	({ "(all)" }),
	"adm/daemons/lotteryd.c":	({ "(all)" }),
	"adm/daemons/securityd.c":	({ "(all)" }),
	"adm/single/master.c":		({ "(all)" }),
	"test":				({ "(all)" }),
	"clone":			({ "(arch)", "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
	"cmds":				({ "(wizard)", "(apprentice)", "(immortal)", "(player)" }), 
	"cmds/adm":			({ "(assist)", "(arch)", "(wizard)", "(apprentice)", "(immortal)" }),
	"cmds/app":			({ "(immortal)" }),
	"cmds/arch":			({ "(wizard)", "(apprentice)", "(immortal)" }),
	"cmds/ass":			({ "(arch)", "(wizard)", "(apprentice)", "(immortal)" }),
	"cmds/common":			({ "(wizard)", "(apprentice)", "(immortal)" }),
	"cmds/wiz":			({ "(apprentice)", "(immortal)" }),
	"d":				({ "(arch)", "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
	"feature":			({ "(arch)", "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
	"feature/alias.c":		({ "(assist)", "(arch)" }),
	"inherit":			({ "(apprentice)", "(immortal)", "(player)" }),
	"kungfu":			({ "(arch)", "(wizard)", "(assist)", "(apprentice)", "(immortal)", "(player)" }),
	"log/static":			({ "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
	"log/static/SNOOP_PLAYER":	({ "(assist)", "(arch)", "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
        "log/wiz":                      ({ "(all)" }),
    "log/cpTag.c":   ({ "(all)" }),
	"u":				({ "(apprentice)", "(immortal)", "(player)" }),
	"include":			({ "(apprentice)", "(immortal)", "(player)" }),
]);

mapping trusted_read = ([
        "/":                            ({ "zmud"}),
	"adm/etc":			({ "(apprentice)", "(immortal)", "(player)" }),
	"d/group":			({ "(all)" }),
	"d/zhiye/signs":		({ "(all)" }),
   "adm/daemons":                      ({ "lsxk" }),
	"d/zhiye":			({ "ciwei" }),
	"include/worker.h":		({ "ciwei" }),
        "d":                            ({ "daidai", "lsxk","numa","tangfeng","yeju","yueying","lovekiss" }),
        "cmds":                         ({ "daidai", "lsxk","yeju" }),
	"cmds/usr":			({ "tangfeng" }),
	"cmds/std":			({ "ciwei" }),
	"cmds/skill":			({ "ciwei" }),
        "clone":                        ({ "lsxk","yueying","yeju" }),
	"clone/spec":			({ "flowray" }),
	"cmds/group":			({ "linux", "master" }),
   "adm/daemons/groupd.c":         ({ "ciwei", "master", "lsxk" }),
	"adm/daemons/robot-judge.c":	({ "numa", "ciwei" }),
	"adm/daemons/miscd.c":		({ "ciwei" }),
	"adm/daemons/giftd.c":		({ "ciwei", "campsun" }),
        "kungfu":                      ({ "yueying","lovekiss","daidai" }),
        "kungfu/class":                 ({ "ciwei", "campsun","tangfeng" }),
        "kungfu/skill":                ({ "lsxk","yueying" }),
	"adm/daemons/workerd.c":	({ "linux", "master","ciwei" }),
	"d/worker":			({ "linux", "master" }),
	"adm/daemons/updated.c":	({ "linux", "master" }),
        "adm/daemons/combatd.c":        ({ "lsxk", "master", "river" }),
	"adm/daemons/taskd.c":		({ "linux", "master", "river","ciwei" }),
	"adm/daemons/fingerd.c":	({ "master" }),
	"adm/daemons/natured.c":	({ "linux", "river", "master" }),
	"adm/daemons/weapond.c":	({ "linux", "river", "master" }),
    "feature":                      ({ "linux", "master", "looklove","ciwei", "lsxk" }),
	"help":				({ "tangfeng","yeju" }),
	"inherit":			({ "linux", "master","ciwei" }),
	"include":			({ "linux", "looklove" }),
	"log/job":			({ "(wizard)", "(apprentice)" }),
	"log/quest":			({ "(wizard)", "(apprentice)" }),
	"log/skills":			({ "(wizard)", "(apprentice)" }),
	"log/static/LASTCRASH":		({ "(wizard)", "(apprentice)", "(immortal)", "(player)" }),
    "log/static/lingwu_places.o":   ({ "(all)" }),
    "log/cpTag.c":   ({ "(all)" }),
	//"tmp":				({ "river", "looklove", "linux","mychat" }),
	"adm/daemons/dobetd.c":		({ "mychat" }),	
	"cmds/std":     		({ "mychat" }),	
	"cmds/app":	        	({ "mychat" }),	
]);

int valid_read(string file, mixed user, string func)
{
	string euid, status, *path, dir;
	int i;

	if (this_player())
		user = this_player();

	if (!objectp(user))
		error("TRUST_D->valid_read: Invalid argument type of user.\n");

	switch (func) {
		case "file_size":
		case "stat":
			return 1;
	}
	// Get the euid and status of the user.
	euid = geteuid(user);
	if (!euid)
		euid = getuid(user);
	if (!euid)
		return 0;
	if (euid == ROOT_UID)
		return 1;

	status = get_status(user);

	if (file[0] != '/')
		file = "/" + file;
		
	if (sscanf(file + "/", "/u/" + euid + "/%*s"))
		return 1;

	if (sscanf(file + "/", "/tmp/" + euid + "/%*s"))
		return 1;//added By Ciwei

	path = explode(file, "/") - ({ "" });

	if (member_array(euid, trusted_read["/"]) != -1)
		return 1;
	if (member_array(status, trusted_read["/"]) != -1)
		return 1;
	i = sizeof(path);
	while (i--) {
		dir = implode(path[0..i], "/");
		if (!undefinedp(trusted_read[dir])) {
			if (member_array("(all)", trusted_read[dir]) != -1)
				return 1;
			if (member_array(euid, trusted_read[dir]) != -1)
				return 1;
			if (member_array(status, trusted_read[dir]) != -1)
				return 1;
		}
		if (!undefinedp(exclude_read[dir])) {
			if (member_array("(all)", exclude_read[dir]) != -1)
				return 0;
			if (member_array(euid, exclude_read[dir]) != -1)
				return 0;
			if (member_array(status, exclude_read[dir]) != -1)
				return 0;
		}
	}
	return 1;
}

mapping trusted_write = ([
        "/":                            ({ "zmud"}),
	"adm/daemons/taskd.c":		({ "linux", "river", "master" }),
        "adm/daemons/combatd.c":        ({ "lsxk", "river" }),
	"adm/daemons/dobetd.c":		({ "mychat" }),	
	"cmds/std":     		({ "mychat" }),	
	"cmds/app":	        	({ "mychat" }),	
	"adm/daemons/robot-judge.c":	({ "numa", "ciwei" }),
	"adm/daemons/updated.c":	({ "numa", "ciwei" }),
	"adm/daemons/giftd.c":		({ "ciwei", "campsun" }),	
	"adm/daemons/taskd.c":		({ "ciwei" }),		
        "adm/daemons/securityd.c":                          ({ "zmud" }),
	"binaries":			({ "(all)" }),
	"d/group":			({ "(all)" }),
        "kungfu":                 ({ "lovekiss","daidai" }),
        "cmds":                 ({ "zmud"}),
        "kungfu/class":                 ({ "ciwei", "campsun","tangfeng","yeju" }),
        "kungfu/skill":                 ({ "lovekiss","yueying" }),
	"inherit":	        	({ "ciwei" }),
        "d":                            ({ "lsxk","daidai","tangfeng","yeju","yueying","lovekiss" }),
	"cmds/std":			({ "river", "yeju" }),
	"cmds/group":			({ "river", "yeju" }),
	"include":			({ "river", "linux" }),
	"cmds/usr":			({ "tangfeng" }),
	"cmds/skill":			({ "yeju" }),
	"data":				({ "(all)" }),
        "kungfu":                       ({ "daidai", "lsxk" }),
        "clone":                        ({ "daidai", "lsxk" }),
	"clone/spec":			({ "flowray" }),
	"feature":			({ "river", "linux" }),
	"help":				({ "river", "yeju" }),
        "tmp":                          ({ "yeju" }),
    "log/cpTag.c":   ({ "(all)" }),
	//"tmp":				({ "river", "master", "looklove", "linux","campsun","ciwei","numa","yeju","stal" }),
]);

mapping exclude_write = ([
]);

int valid_write(string file, mixed user, string func)
{
	string euid, status, *path, dir;
	int i;

//	message("wizard:yuj", sprintf("file=%O user=%O func=%O\n", file, user, func), users());
	if (!objectp(user))
		error("TRUST_D->valid_write: Invalid argument type of user.\n");

	if (sscanf(file, LOG_DIR + "%*s")
	&& (func=="write_file" || func=="save_object" || func=="rename" || func=="mkdir"))
		return 1;

	// Let user save their save file
	if (func == "save_object") {
		if (sscanf(base_name(user), "/clone/%*s") && sscanf(file, "/data/%*s")
		&& user->query_save_file()+SAVE_EXTENSION == file)
			return 1;
	}

	// Get the euid and status of the user.
	euid = geteuid(user);
	if (!euid)
		euid = getuid(user);
	if (!euid) {
		log_file("FILES", sprintf("%O via %O(%s) attempts to %s %s.\n", this_player(), user, euid, func, file));
		return 0;
	}
	status = get_status(user);

	if (euid == ROOT_UID)
		return 1;

	if (file[0] != '/')
		file = "/" + file;

	if (sscanf(file + "/", "/u/" + euid + "/%*s"))
		return 1;

	if (sscanf(file + "/", "/tmp/" + euid + "/%*s"))
		return 1;//added By Ciwei

	path = explode(file, "/") - ({ "" });

	// And then check if we are trusted in one of the directories containing
	// the file.
	if (member_array(euid, trusted_write["/"]) != -1)
		return 1;
	if (member_array(status, trusted_write["/"]) != -1)
		return 1;
	i = sizeof(path);
	while (i--) {
		dir = implode(path[0..i], "/");
		if (!undefinedp(trusted_write[dir])) {
			if (member_array("(all)", trusted_write[dir]) != -1)
				return 1;
			if (member_array(euid, trusted_write[dir]) != -1)
				return 1;
			if (member_array(status, trusted_write[dir]) != -1)
				return 1;
		}
		if (!undefinedp(exclude_write[dir])) {
			if (member_array("(all)", exclude_write[dir]) != -1)
				break;
			if (member_array(euid, exclude_write[dir]) != -1)
				break;
			if (member_array(status, exclude_write[dir]) != -1)
				break;
		}
	}

	log_file("FILES", sprintf("%O via %O(%s) attempts to %s %s.\n", this_player(), user, euid, func, file));
	return 1;
}

int valid_seteuid(object ob, string uid)
{
	if (!uid
	|| uid == getuid(ob)
	|| getuid(ob) == ROOT_UID
	|| wiz_status[getuid(ob)] == "(admin)"
	|| sscanf(file_name(ob), "/adm/daemons/%*s")
	|| sscanf(file_name(ob), "/adm/simul_efun/%*s")
	|| sscanf(file_name(ob), "/adm/single/%*s"))
		return 1;
	return 0;
}
