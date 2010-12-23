// named.c
// By snowman@SJ 10/06/2000
//modified by campsun 2003/09/25
//�޸����ݣ��޸ĺ���get_random_name,���ڿ���ָ��������ֵ��ַ������ˡ�
//����ָ��ȡ��������1-4�������֣������벻Ҫ����4������

mapping get_random_name(int,int);
mapping random_name(int,int);

string* f_name = ({
"��", "��",
"��", "��", "��", "��", "��",
"��", "�", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "�",
"��",
"��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "¬", "³", "��", "��",
"��", "é", "ë", "��", "��", "��", "ī", "Ĳ", "��",
"��", "��",
"��", "��", "��", "Ƥ", "ƽ",
"��", "��", "��", "Ǯ", "��", "��", "��", "��", "��",
"��",
"ɵ", "��", "��", "��", "��", "ʩ", "ʯ", "ʱ", "ʷ", "��", "˧", "ˮ", "��", "��", "��",
"̸", "��", "��", "��", "��", "١",
"��", "��", "��", "Τ", "κ", "��", "��", "��", "��", "��",
"��", "��", "Ф", "л", "��", "��", "��", "Ѧ",
"��", "��", "��", "��", "Ҧ", "��", "��", "��", "Ӣ", "ӯ", "��", "��", "��", "��", "��", "��", "Ԫ", "Ԭ", "��", "��", "��",
"��", "տ", "��", "��", "��", "֣", "֧", "��", "��", "��", "ף", "��", "��", "��", "��",

"����", "����",
"����", "����", "����",
"����", "����", "����", "��ľ", "��ǧ",
"����", "����", "����", "����", "��ұ", "����", "�麣",
"����", "����", "�ʸ�",
"�й�",
"����", "���",
"Ľ��",
"�Ϲ�", "�Ϲ�",
"ŷ��",
"���",
"���",
"��۳",
"�Ϲ�", "����", "ʦ��", "˾��", "˾ͽ",
"̫��", "�̨", "Ϳ��", "��ֺ",
"΢��", "����", "����",
"����", "�ĺ�", "����", "��ԯ",
"�ַ�", "����", "ξ��", "����", "����",
"�׸�", "����", "����", "����", "���", "��", "����", "����",
});

string* f_id = ({
"ai", "an",
"bo", "bao", "bei", "bian", "bo",
"cao", "cen", "chang", "chang", "chen", "cheng",
"dai", "dai", "deng", "di", "di", "dong", "dou",
"er",
"fan", "fan", "fang", "fei", "feng", "feng", "fu", "fu", "fu",
"ge", "gou", "gu", "guan", "guan",
"ha", "han", "hao", "he", "he", "he", "hou", "hou", "hu", "hua", "hua", "hua", "huang", "huo",
"ji", "ji", "jiang", "jiang", "jin", "jiu",
"kang", "kang", "ke", "kong", "kuai", "kuang",
"lang", "lei", "li", "lian", "liang", "lin", "ling", "liu", "lu", "lu", "lv", "luo",
"ma", "mao", "mao", "mi", "miao", "ming", "mo", "mou", "mu",
"ni", "nian",
"pan", "pang", "peng", "pi", "ping",
"qi", "qi", "qi", "qian", "qiao", "qin", "qin", "qiu", "qu",
"ren",
"sha", "shang", "shao", "she", "shen", "shi", "shi", "shi", "shi", "shu", "shuai", "shui", "song", "su", "sun",
"tan", "tang", "tang", "tao", "teng", "tong",
"wan", "wang", "wang", "wei", "wei", "wei", "wu", "wu", "wu", "wu",
"xi", "xiang", "xiao", "xie", "xiong", "xu", "xu", "xue",
"yan", "yan", "yang", "yang", "yao", "yi", "yin", "yin", "ying", "ying", "you", "you", "yu", "yu", "yu", "yu", "yuan", "yuan", "yue", "yue", "yun",
"zang", "zhan", "zhang", "zhang", "zhao", "zheng", "zhi", "zhong", "zhou", "zhu", "zhu", "zong", "zhou", "zhu", "zu",

"baili", "baishang",
"chujin", "chunyu", "chanyu",
"dongfang", "dongguo", "dongmen", "duanmu", "duanqian",
"gongliang", "gongsun", "gongxi", "gongyang", "gongye", "guliang", "guihai",
"helian", "huyan", "huangpu",
"jiagu",
"liangqiu", "linghu",
"murong",
"nangong", "nanguo",
"ouyang",
"puyang",
"qidiao",
"ruyan",
"shangguan", "shentu", "shikong", "sima", "situ",
"taishu", "tantai", "tuqin", "tuozhi",
"weisheng", "wenren", "wuma",
"ximen", "xiahou", "xiangsi", "xuanyuan",
"yanfa", "yangshe", "yuchi", "yuwen", "yuezheng",
"zaifu", "zhangsun", "zhongli", "zhongsun", "zhuge", "zhuankong", "zongzheng", "zuoqiu",
});

string* name_m = ({
"��",
"��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��",
"��", "�»�", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "�", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��",
"��", "�", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "¡", "»",
"��", "��", "��", "��",
"��",
"��", "��",
"��", "��", "ǿ", "��",
"��", "��", "��", "��",
"ɽ", "ʢ", "ʤ", "ʱ", "��", "��", "��", "˳",
"̩", "��", "��", "��", "ͦ", "ͬ",
"��", "Ϊ", "ΰ", "��", "��",
"��", "��", "��", "��", "��", "��", "С", "Т", "��", "��", "��", "ѧ��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�", "��",
"��", "�", "֮", "־", "��", "��", "��", "��", "��", "��",
});

string* id_m = ({
"an",
"ba", "bai", "ban", "bi", "bin", "bin", "bo",
"cai", "cai", "chang", "chang", "chao", "cheng", "chuan",
"da", "dehua", "ding", "ding", "dong", "dou", "duo",
"fa", "fa", "fei", "feng", "feng", "fu", "fu", "fu", "fu",
"gang", "gang", "gao", "gong", "guan", "guang", "guo",
"hai", "hao", "he", "hong", "hu", "hua", "hui",
"ji", "ji", "jian", "jian", "jian", "jian", "jiang", "jie", "jin", "jin", "jin", "jing", "jun", "jun",
"kang", "ke", "ke", "kuang",
"lang", "li", "liang", "liang", "lin", "ling", "long", "long", "lu",
"man", "min", "ming", "ming",
"ning",
"pei", "pei",
"qi", "qi", "qiang", "qing",
"ren", "ren", "rong", "ruo",
"shan", "sheng", "sheng", "shi", "shi", "shou", "shu", "shun",
"tai", "tao", "tian", "tie", "ting", "tong",
"wan", "wei", "wei", "wen", "wu",
"xi", "xi", "xian", "xiang", "xiang", "xiao", "xiao", "xiao", "xiong", "xiong", "xu", "xueyou",
"yang", "yi", "yi", "yi", "yi", "yong", "yong", "you", "yu", "yu", "yu", "yue",
"zhen", "zheng", "zhi", "zhi", "zhi", "zhong", "zhou", "zhou", "zi", "zi",
});

string* name_g = ({     //Ů��ר��
"��",
"����", "��",
"��", "��",
"��", "����", "��",
"��", "��", "��", "ܽ",
"��",
"��", "��", "��", "��", "��",
"��", "��", "��", "��", "��",
"��",
"��", "�", "��", "��", "��", "��", "��",
"��", "��",
"Ƽ",
"ٻ", "��", "��", "��", "��",
"��",
"�", "��",
"��",
"��",
"ϼ", "��", "��", "����",
"��Ȼ", "��", "��", "Ӣ", "��", "ӫ", "ӯ", "ӱ", "��", "��",
"��", "��", "��",
});

string* id_g = ({
"ai",
"baochai", "bi",
"chun", "cui",
"dai", "daiyu", "dan",
"fang", "fen", "feng", "fu",
"gu",
"hong", "hong", "hua", "hui", "hui",
"jiao", "jing", "jing", "ju", "juan",
"ke",
"lan", "lan", "li", "li", "lian", "lin", "ling",
"mei", "min",
"ping",
"qian", "qin", "qin", "qing", "qing",
"rong",
"shan", "shu",
"ting",
"wan",
"xia", "xian", "xiang", "xiangyun",
"yanran", "yan", "yan", "ying", "ying", "ying", "ying", "ying", "yu", "yuan",
"zhen", "zhen", "zhu",
});

mapping random_name(int gender,int num)
{
	string *ids,*f_id1,*f_id2;
	mapping name;
	string f_n1,f_n2;
	int i;
	string *group_name,*group_id;
	if (gender)																					//�ж��л�Ů����
	{
		group_name=f_name;
		group_id=f_id;
	}
	else
	{
		group_name=name_g;
		group_id=id_g;
	}
	f_n2="";
	f_id2=({});
	i=random(sizeof(group_name));
	f_n1=group_name[i];
	f_id1=({ group_id[i] });
	while(strlen(f_n1)>num)																		//�����õ��ַ���������Ҫ�ģ�����Ѱ��
	{
		name=random_name(gender,num);

		f_n1=name["name"];
		f_id1=name["id"];
	}
	if(strlen(f_n1)<num)																		//����ַ�������������еݹ�Ѱ��
	{
		name=random_name(gender,num-strlen(f_n1));
     	f_n2=name["name"];
     	f_id2=name["id"];
	}
    f_n1=f_n1+f_n2;
	f_id1=f_id1+f_id2;
	ids=f_id1;
	
		
	return ([
		"name" : f_n1,
		"id" : ids,
	]);
}

mapping get_random_name(int gender,int num)																//�����ֵ�id��������
{
	mapping name;
	string *ids;
	int char_num=num*2;
	name=random_name(gender,char_num);																	//����random_name����������
	ids=name["id"];
	
	switch(sizeof(ids))
	{

		case 4:
			ids = ({ids[0]+ids[1]+" "+ids[2]+ids[3]})+({ids[0]+ids[1]})+({ids[2]+ids[3]});					//��4���ֵ����ֵ�id������������
		break;
		case 3:
			ids =({ids[0]+" "+ids[1]+ids[2]})+({ids[0]})+({ids[1]+ids[2]});									//��3���ֵ����ֵ�id����
		break;
		case 2:
            ids =({ids[0]+" "+ids[1]})+({ids[0]})+({ids[1]});												//�����ֵ����ֵ�id����
		break;


	}

	return ([
		"name" : name["name"],
		"id" : ids,
	]);
	


}