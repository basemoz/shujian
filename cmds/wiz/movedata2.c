// movedata.c
// By River@SJ 2002.4.5
// YUJ@SJ 2002-04-08
// Ciwei@SJ string SITE_NAME = "LN" ת������վ��ʱ ���޸Ĵ˱��� ���±༭ʹ��

#include <ansi.h>

inherit F_CLEAN_UP;

#define NID_PATH "/log/ln/newdata/"
#define ID_PATH "/log/ln/data/"
#define ODB "/clone/user/olduser"
//#define SITE_NAME "LN"
/*
��΢�� ˵��
����movedata��ʱ��ͬʱ��ȡ lnmud��������ʹ�ͬʱ���� Users
��΢�� ˵��
�����Alivedays���ڲ���mudvips�� at discuz
*/

string SITE_NAME = "LN";

mapping olddb, newdb;

int help(object me);

varargs void dup(string key)
{
	newdb[key] = olddb[key];
}

int savedata(string id)
{
	string nid;
	string status;
	string email;
	string passwd;
	string* jobs;
	
	mapping job;	
	mixed ret;

	int i,j,exp;

	seteuid(ROOT_UID);

	nid = id;

	ODB->restore(ID_PATH + "user/" + id[0..0] + "/" + id);
	olddb = ODB->query_dbase();
	newdb = ([ ]);
	//Ӧ�÷ֿ�ln cq��ִ�е� lnִ�е� ������
	//������ת�� -> ���ò��� ^_^
	// Job time
	//һЩ��job_time��ת��
	if(olddb["job_time"]) newdb["job_time"] = copy(olddb["job_time"]);
	else newdb["job_time"] =([]);
	if (olddb["dali_job"])
		newdb["job_time"]["����"] += olddb["dali_job"];
	if (olddb["gb_job"])
		newdb["job_time"]["ؤ��"] += olddb["gb_job"];
	if (olddb["gb_job2"])
		newdb["job_time"]["��Ч����"] += olddb["gb_job2"];
	if (olddb["gf_job"])
		newdb["job_time"]["�ٸ�"] += olddb["gf_job"];
	if (olddb["hs_job"])
		newdb["job_time"]["��ɽ"] += olddb["hs_job"];
	if (olddb["mingjiao_job"])
		newdb["job_time"]["����"] += olddb["mingjiao_job"];
	if (olddb["mr_job"])
		newdb["job_time"]["Ľ��"] += olddb["mr_job"];
	if (olddb["sl_job"])
		newdb["job_time"]["���־�Ԯ"] += olddb["sl_job"];
	if (olddb["snake_job"])
		newdb["job_time"]["ץ��"] += olddb["snake_job"];
	if (olddb["songshan_points"])
		newdb["job_time"]["��ɽ"] += olddb["songshan_points"];
	if (olddb["thd_job"])
		newdb["job_time"]["�һ���"] += olddb["thd_job"];
	if (olddb["wd_job"])
		newdb["job_time"]["�䵱"] += olddb["wd_job"];
	//if (olddb["xs_job"])
		//newdb["job_time"]["ѩɽ"] = olddb["xs_job"];ln cq code ���Ѿ�������xs_job �������
	if (olddb["xx_job4"])
		newdb["job_time"]["���ް�ҩ"] += olddb["xx_job4"];
	if (olddb["xx_job5"])
		newdb["job_time"]["������ͽ"] += olddb["xx_job5"];
	if (olddb["xx_points"])
		newdb["job_time"]["����"] += olddb["xx_points"];
	if (olddb["zhao_job"])
		newdb["job_time"]["����"] += olddb["zhao_job"];
	//һЩ����job_name������
	if (job = newdb["job_time"]) {
			jobs = keys(job);
			for(i=0;i<sizeof(jobs);i++)
			{
				if(jobs[i]=="�һ�����Ĺ"){
					job["�һ���"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="Ľ��͵ѧ"){
					job["Ľ��"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="wd_job"){
					job["�䵱"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="ؤ����"){
					job["ؤ��"] = job[jobs[i]];
					map_delete(job,jobs[i]);
				}
			}
	}
	//��Ϊlnת������cut exp �ķ�������job_last_gift�Ͳ�����
	if(SITE_NAME =="CQ"){
	if (mapp(olddb["job_last_gift"]))
		newdb["job_last_gift"] = copy(olddb["job_last_gift"]);
	if (job = newdb["job_last_gift"]) {
			jobs = keys(job);
			for(i=0;i<sizeof(jobs);i++)
			{
				if(jobs[i]=="�һ�����Ĺ"){
					job["�һ���"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="Ľ��͵ѧ"){
					job["Ľ��"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="wd_job"){
					job["�䵱"] = job[jobs[i]];
					map_delete(job,jobs[i]);
					continue;
				}
				if(jobs[i]=="ؤ����"){
					job["ؤ��"] = job[jobs[i]];
					map_delete(job,jobs[i]);
				}
			}
	}			
	}			
	//job���ֽ���
	// hp ����, max_jing max_qi eff_jingli ��ϵͳ�Զ����� ���ò���
	dup("jing");
	dup("eff_jing");

	dup("jingli");
	dup("max_jingli");

	dup("qi");
	dup("eff_qi");

	dup("neili");
	dup("max_neili");
	dup("shen");

	dup("food");
	dup("potential");
	dup("water");
	dup("combat_exp");

	// score ����
	if ( olddb["class"] && olddb["class"] != "eunuch")
		dup("class");
	dup("title");
	dup("str");
	dup("con");
	dup("name");
	newdb["id"] = nid;
//	dup("id");
	dup("dex");
	dup("int");

	dup("nickname");
	dup("mud_age");
	dup("birthday");

	dup("gender");
	if (newdb["gender"] != "Ů��")
		newdb["gender"] = "����";
		
	dup("PKS");
	dup("MKS");
	dup("BKS");
	dup("GKS");
	dup("death_count");
	dup("death_times");
	dup("balance");
	
	dup("per");
	dup("kar");
	dup("pur");

	newdb["oldsj"] = 1;
	newdb["from_site"] = SITE_NAME;
	dup("name");
	newdb["mud_time"] = olddb["mud_age"];
	//newdb["name"] = "���ִ���";
	//about party���кܶ�Ŷ~~~
	//���������
	//�ֿ����� һ���� �������Ƿ��ܵ������� Ϊ�˱�������ظ��õ����� ������һ����copy
	//         һ���� ֻ����cq ln������ ����quest ���   
	
	//for all	
	if (mapp(olddb["marry"]))
		newdb["marry"] = copy(olddb["marry"]);
	if ( olddb["luohan_winner"] )
		newdb["luohan_winner"] = 1;
	if ( olddb["muren_winner"] )
		newdb["muren_winner"] = 1;
	if ( olddb["tls"] )
		newdb["tls"] = 1;
	if ( olddb["xie_qishang"] )
		newdb["xie_qishang"] = 1;	
	if ( olddb["gb_bags"] )
		newdb["gb_bags"] = copy(olddb["gb_bags"]);	
	if ( olddb["gb_pass"] )
		newdb["gb_pass"] = 1;
	if (mapp(olddb["family"]))
		newdb["family"] = copy(olddb["family"]);
	if (stringp(olddb["last_death"]))
		newdb["last_death"] = copy(olddb["last_death"]);
	if (stringp(olddb["last_killer"]))
		newdb["last_killer"] = copy(olddb["last_killer"]);
	if (olddb["gf_gives"])
		newdb["gf_gives"] = copy(olddb["gf_gives"]);
	//ss
	if (mapp(olddb["ss"]))
		newdb["ss"] = copy(olddb["ss"]);
	//gb
	if (mapp(olddb["gb"]))
		newdb["gb"] = copy(olddb["gb"]);
	if (mapp(olddb["htqg"]))
		newdb["htqg"] = copy(olddb["htqg"]);		
	///wd
	if (olddb["wudang_given"])
		newdb["wudang_given"] = copy(olddb["wudang_given"]);
	if (olddb["taiji_zsf"])
		newdb["taiji_zsf"] = copy(olddb["taiji_zsf"]);
	if (olddb["taiji_quest"])
		newdb["taiji_quest"] = copy(olddb["taiji_quest"]);
	//tls
	if (olddb["dudan_given"])
		newdb["dudan_given"] = copy(olddb["dudan_given"]);
	if (olddb["fenglu"])
		newdb["fenglu"] = copy(olddb["fenglu"]);
	if (olddb["kr_add"])
		newdb["kr_add"] = copy(olddb["kr_add"]);	
	//sl
	if (mapp(olddb["yjj"]))
		newdb["yjj"] = copy(olddb["yjj"]);
	//mj
	if (mapp(olddb["mjling"]))
		newdb["mjling"] = copy(olddb["mjling"]);
	//hs
	//if (olddb["fengset"])
		//newdb["fengset"] = copy(olddb["fengset"]);
	if (mapp(olddb["hs"]))
		newdb["hs"] = copy(olddb["hs"]);
	//gm
	if (olddb["gmpass"])
		newdb["gmpass"] = copy(olddb["gmpass"]);
	//mr	
	//em
	if (olddb["emsujia"])
		newdb["emsujia"] = copy(olddb["emsujia"]);
	//dls
	if (olddb["join_age"])
		newdb["join_age"] = copy(olddb["join_age"]);
	if (olddb["ryl_add"])
		newdb["ryl_add"] = copy(olddb["ryl_add"]);
	if(SITE_NAME =="CQ"){
	//just fo cq
	//gm	
	if (olddb["gmsanwu"])
		newdb["gmsanwu"] = copy(olddb["gmsanwu"]);
	if (olddb["ygpass"])
		newdb["ygpass"] = copy(olddb["ygpass"]);
	//quest	
	if (olddb["hanshui_food"])
		newdb["hanshui_food"] = copy(olddb["hanshui_food"]);
	if (olddb["menggu"])
		newdb["menggu"] = copy(olddb["menggu"]);
	//tls
	if (olddb["liumai_pass"])
		newdb["liumai_pass"] = copy(olddb["liumai_pass"]);
	if (mapp(olddb["liumai-shenjian"]))
		newdb["liumai-shenjian"] = copy(olddb["liumai-shenjian"]);
	//sl
	if (olddb["fenwo"])
		newdb["fenwo"] = copy(olddb["fenwo"]);
	if (olddb["pass_xin"])
		newdb["pass_xin"] = copy(olddb["pass_xin"]);
	//if (mapp(olddb["wxz"]))
		//newdb["wxz"] = copy(olddb["wxz"]);
	//thd
	if (mapp(olddb["thd"]))
		newdb["thd"] = copy(olddb["thd"]);				
	//else
	if (mapp(olddb["forging"]))
		newdb["forging"] = copy(olddb["forging"]);
	if (arrayp(olddb["friend_user"]))
		newdb["friend_user"] = copy(olddb["friend_user"]);
	if (mapp(olddb["env"]))
		newdb["env"] = copy(olddb["env"]);
	if (stringp(olddb["color"]))
		newdb["color"] = copy(olddb["color"]);	
	if (olddb["color_time"])
		newdb["color_time"] = copy(olddb["color_time"]);	
	if (olddb["name_modify"])
		newdb["name_modify"] = copy(olddb["name_modify"]);
	if (olddb["rules"])
		newdb["rules"] = copy(olddb["rules"]);
	}
	/*	
	if (mapp(olddb[""]))
		newdb[""] = copy(olddb[""]);
	*/			
	//LN��վ��һЩ����
	if(SITE_NAME =="LN"){
	
	if (olddb["color_time"])
		newdb["color_time"] = copy(olddb["color_time"])/2;
	if (olddb["name_modify"])
		newdb["name_modify"] = copy(olddb["name_modify"])/2;
	if (olddb["rules"])
		newdb["rules"] = copy(olddb["rules"])/2;
	//����	
	if ( newdb["mud_age"] > 7840000 )
		newdb["mud_age"] = 7840000;
	if ( olddb["max_neili"] > 8500 )
		newdb["max_neili"] = 8500;
	if (olddb["balance"] > 10000000)
		newdb["balance"] = 10000000;
// �������������������ת�� just for ln
	if ((exp = newdb["combat_exp"]) > 3000000) {
		float scale = 3000000.0 / exp;
		
		newdb["combat_exp"] = 3000000;
		newdb["mud_age"] = to_int(newdb["mud_age"] * scale);
		newdb["PKS"] = to_int(newdb["PKS"] * scale);
		newdb["BKS"] = to_int(newdb["BKS"] * scale);
		newdb["GKS"] = to_int(newdb["GKS"] * scale);
		newdb["MKS"] = to_int(newdb["MKS"] * scale);
		newdb["death_count"] = to_int(newdb["death_count"] * scale);
		newdb["death_times"] = to_int(newdb["death_times"] * scale);
		if (job = newdb["job_time"]) {
			jobs = keys(job);
			i = sizeof(jobs);
			for (j = 0; j < i; j ++)
				job[jobs[j]] = to_int(job[jobs[j]] * scale);
		}
	}
	}
	//about skill and master change
	ODB->delete_skill("jingmai-xue");
	ODB->delete_skill("lingbo-weibu");
	ODB->delete_skill("jiuyin-zhengong");
	ODB->delete_skill("jiuyin-shenfa");
	ODB->delete_skill("jiuyin-shenzhua");
	ODB->delete_skill("jiuyin-baiguzhua");
	ODB->delete_skill("jiuyin-shenzhang");
	ODB->delete_skill("cuixin-zhang");
	ODB->delete_skill("dafumo-quan");
	ODB->delete_skill("xuanyin-jian");
	ODB->delete_skill("xuanming-shenzhang");
	ODB->delete_skill("yinlong-bian");
	ODB->delete_skill("daode-jing");
	if ( ODB->query_skill("jiuyang-shengong") > ODB->query_skill("shenghuo-shengong"))
		ODB->set_skill("shenghuo-shengong", ODB->query_skill("jiuyang-shengong"));
	ODB->delete_skill("jiuyang-shengong");
	ODB->delete_skill("hamagong");
	ODB->delete_skill("jinshe-jianfa");
	ODB->delete_skill("jinshe-zhangfa");
	if ( ODB->query_skill("dugu-jiujian") > ODB->query_skill("huashan-jianfa"))
		ODB->set_skill("huashan-jianfa", ODB->query_skill("dugu-jiujian"));
	ODB->delete_skill("dugu-jiujian");
	ODB->delete_skill("hamabu");
	ODB->delete_skill("baituo-shezhang");
	ODB->delete_skill("liumai-shenjian");
	ODB->delete_skill("kongming-quan");
	ODB->delete_skill("wuxiang-zhi");
	ODB->delete_skill("lanhua-shou");
	ODB->delete_skill("pixie-jian");
	ODB->delete_skill("hunyuan-zhang");
	ODB->delete_skill("qianzhu-wandushou");
	ODB->delete_skill("xiantian-gong");
	
	//ODB->set_skill("duanzao", ODB->query_skill("forging"));
	//ODB->delete_skill("forging");
	
	if(mapp(newdb["family"]) && newdb["family"]["master_name"]){
	switch(newdb["family"]["master_name"])
	{
		case "���޼�":		newdb["title"] = HIR"���̽����״�����"NOR;	break;	// ����
		case "������ɮ":	newdb["title"] = "�����ɵ���ʮ�������";		break;	// ������
		case "���":
		case "С��Ů":		newdb["title"] = HIW"��Ĺ��������´���"NOR;	break;	// ��Ĺ��
		case "������":		newdb["title"] = "�䵱�ɵڶ�������";		break;	// �䵱��
		case "���ַ���":	newdb["title"] = HIY"�����½��ַ������µ���"NOR;	break;
		case "�Ħ��":		newdb["title"] = HIY"�������������µ���"NOR;	break;
		case "Ѫ������":	newdb["title"] = HIR"������Ѫ�������״�����"NOR;	break;	// ������
		case "�鰲ͨ":		newdb["title"] = "�����̵ڶ�������";		break;	// ������
		case "������":		newdb["title"] = "�����ɵڶ�������";		break;	// ������
		case "Ľ�ݲ�":		newdb["title"] = "����Ľ�ݵڶ�������";		break;	// ����Ľ��
		case "�Ϲٽ���":	newdb["title"] = HIM"���ư��Ϲٰ�������"NOR;	break;	// ���ư�
		case "���ٳ���":	newdb["title"] = "�����µ�ʮ��������";		break;	// ������
		case "����ʦ̫":
		case "�º���":		newdb["title"] = "�����ɵ���������";		break;	// ������
		case "������":		newdb["title"] = HIC"���������״�����"NOR;	break;	// ��ɽ��
		case "��ҩʦ":		newdb["title"] = "�һ����ڶ�������";		break;	// �һ���
		case "������":		newdb["title"] = "��ɽ�ɵ�ʮ��������";		break;
		case "������":		newdb["title"] = "��ɽ�ɵ�ʮ��������";
					newdb["family"]["master_name"]    =  "������";
					newdb["family"]["master_id"]      =  "mu renqing";
					break;
		case "����Ⱥ":
		case "������":		newdb["title"] = "��ɽ�ɵ�ʮ�Ĵ�����";		break;	// ��ɽ��
		case "���߹�":
					newdb["family"]["master_name"]    =  "������";
					newdb["family"]["master_id"]      =  "liang zhanglao";
					newdb["family"]["generation"]     =  19;
					newdb["gb"]["fenduo"]             =  "�ܶ�";
					newdb["class"]                    =  "beggar";
					if(newdb["gb"]["bags"]) newdb["gb"]["bags"] = 1;
					newdb["title"]                    = sprintf("ؤ���ܶ�%s������",
                								chinese_number(newdb["gb"]["bags"]));
                			break;
		}
		//default :		title = "none";				break;			
	}
	//������
	if(olddb["registered"]>1) newdb["registered"]= 2;	
	//if(SITE_NAME =="LN") newdb["startroom"] = "/d/city/kedian/bonus_room";
	//else 
	newdb["startroom"] = "/d/city/kedian";
	dup("startroom");
		
	ODB->set_dbase(newdb);
	
	status = read_file(ID_PATH +"login/"+ id[0..0] +"/"+ id + SAVE_EXTENSION);

	sscanf(status, "%*s\"email\":\"%s\",", email);

	sscanf(status, "%*s\"password\":\"%s\",", passwd);
	
	ret = dbquery("SELECT Alivedays FROM Users "
		"WHERE U_Username=" + save_variable(nid));
	if (!ret) {write(sprintf("%-8s���ݿ����ʧ�� for Serch Users\n",nid));return 0;}
	if(sizeof(ret)>0)
	{
		log_file("static/MOVEDATA", sprintf("%-8s ���� %-4s ��Ϊ���ݱ� Users �Ѿ�����%-8s���ϣ�ת��ʧ��", 
			nid, SITE_NAME,nid));
		write(capitalize(id) +" ����ʧ�ܡ�\n");
		return 1;
	}	
	//ȷ��Users��û�����ݲ�save ���ᷢ�� Users��ô  Data�е��°ɣ�fear
	
	if ( !ODB->save(NID_PATH +"user/" + nid[0..0] +"/"+nid + SAVE_EXTENSION))
		{write(sprintf("%-8s���ݿ����ʧ�� for Data's User\n",nid));return 0;}
	write_file(NID_PATH +"login/" + nid[0..0] +"/"+nid + SAVE_EXTENSION,status, 1);
		
	ret = dbquery("SELECT alivedays,question,answer,mail "
			"FROM "+lower_case(SITE_NAME)+"_qa_users WHERE id=" + save_variable(nid));
	if(ret && sizeof(ret)==1){
	
	if(ret[0][0]>0)
		{
		string site_name2 = lower_case(SITE_NAME);
		if(site_name2=="ln") site_name2 = sprintf("ln%d",2);
		dbquery("INSERT INTO mudvips "
			"(username,regtimelimit,updatetime,regemail) "
			"VALUES ('"+nid+"@"+site_name2+"','"+(time()+ret[0][0]*24*60*60)+"','"+time()+"','"+ret[0][3]+"')"
			);
		//regtimelimit alivedays*24*60*60+time() 
		//updatetime time()
		//regtimelimit  updatetime 
		//
		}		
	//ret = dbquery("replace into "+SITE_NAME+"_Users set "	
	ret = dbquery("replace into Users set "
		"U_Username='"+nid+"',"
		"U_Name='"+newdb["name"]+"',"
		"U_Password='"+passwd+"',"
		"U_Email='"+email+"',"
		"U_Site='CQ',"
		//"U_Site='" + SITE_NAME + "',"
		"Mud_Site='CQ',"
		//"Mud_Site='" + SITE_NAME + "',"
		"U_Registered='" + time() + "',"
		"U_Extra='" + newdb["gender"] + "',"
		"U_Online='N',"
		//"Alivedays='"+ret[0][0]+"',"
		"Question='"+ret[0][1]+"',"
		"Answer='"+ret[0][2]+"'"
		);		
	}
	else {
	//ret = dbquery("replace into "+SITE_NAME+"_Users set "	
	ret = dbquery("replace into Users set "
		"U_Username='"+nid+"',"
		"U_Name='"+newdb["name"]+"',"
		"U_Password='"+passwd+"',"
		"U_Email='"+email+"',"
		"U_Site='CQ',"
		//"U_Site='" + SITE_NAME + "',"
		"Mud_Site='CQ',"
		//"Mud_Site='" + SITE_NAME + "',"
		"U_Registered='" + time() + "',"
		"U_Extra='" + newdb["gender"] + "',"
		"U_Online='N',"
		"Alivedays='0'");
	}
	if (!ret) {write(sprintf("%-8s���ݿ����ʧ�� for Users\n",nid));return 0;}
			
	status = replace_string(status, "", "");
	status = replace_string(status, "\\", "");
	status = replace_string(status, "\"", "");
	status = replace_string(status, "'", "");
	//ret = dbquery("REPLACE "+SITE_NAME+"_Data SET "	
	ret = dbquery("REPLACE Data SET "
		"U_ID=" + save_variable(sprintf(DATA_DIR "login/%c/%s%s", nid[0], nid,SAVE_EXTENSION)) + ","
		"U_Time=" + save_variable(time()) + ","
		"U_Data=" + save_variable(status));	
	if (!ret) {write(sprintf("%-8s���ݿ����ʧ�� for Data's Login\n",nid));return 0;}
	
	write(capitalize(id) +" ������ϡ�\n");
	return 1;
}

int iso(string str)
{
	if(!str) return 0;
	return sscanf(str+"$","%s.o$", str)==1;
}

int main(object me, string arg)
{
	string uid;
	string dir;
	string *files;

	int count = 0;
	int dix = 0;
	int j = 1;
	
	if (!arg)
	{
		return help(me);
	}
	sscanf(arg,"%s %d %d",arg,dix,j);
	dir = ID_PATH + "login/" + arg + "/";
	files = get_dir(dir);
	files = filter_array(files,(:iso:));
	write(dir + " ����ʼ��\n");	
	if(!dix) dix = sizeof(files)-1;
	else dix += j-2;
	if(dix<0) return notify_fail("��������/\n");
	if(dix>sizeof(files)-1) dix= sizeof(files)-1;
	for (j-=1; j<=dix; j++)
	{
		if (sscanf(files[j]+"$", "%s.o$", uid)==1 )
		{
			savedata(uid);
			count++;
		}
	}
	if(dix==sizeof(files)-1) write(dir + " ���������\n");
	else write(sprintf("%s ������δ������\n�� %d ��ʼ������� %d ��¼��\n",dir,dix+2,sizeof(files)-dix-1));
	write("\n�������� " + count + " λ�û���\n");
		
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ��movedata2 <a|b|c|...> [<numa> <numb>]
	numa ��ʾһ�δ����������,
	numb ��ʾ�����￪ʼ����
	
	���磺movedata2 a 100 1
	˵�����ӵ�һ����¼��ʼ����100������
		Ȼ�����movedata2 a 100 101....
	
HELP
	);
	return 1;
}