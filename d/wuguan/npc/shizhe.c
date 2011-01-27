// shizhe.c 天涯一号
#include <ansi.h>
#define Weapon_LEVEL            100
#define SKILLS_LEVEL            200
#define KNOWLEDGE_LEVEL 200
#define GIVE_EXP                800000
#define MAX_NEILI               3800
#define MAX_JINGLI              2500
#define HM_LEVEL				600
inherit NPC;
string ask_newbie();
string ask_xingxiu();
string ask_sld();
string ask_wudang();
string ask_ss();
string ask_emei();
string ask_shaolin();
string ask_xs();
string ask_mingjiao();
string ask_kl();
string ask_hs();
string ask_gb();
string ask_mur();
string ask_tttt();
string ask_thd();
string ask_tz();
string ask_tls();
string ask_hm();
object ob = this_object();
void create()
{
   set_name(HIR"书剑礼物使者"NOR, ({ "shizhe" }));
       set("nickname", HBCYN"书剑天下礼物使者"NOR);
    set("long", "你可以ask shizhe about newbie,在ask shizhe about 拜师,喜欢哪个门派就ask shizhe about ***,addoil all \n");
    set("gender", "男性");
    set("age", 70);
    set("per", 24);
    set("str", 40);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("qi",5000);
    set("jingli",6000);
    set("max_qi", 8000);
    set("max_jing", 5000);
    set("eff_jingli", 6000);
    set("jiali", 190);
    set("combat_exp", 9000000);
    set("shen", 25000);
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
(: exert_function, "taiji" :),
(: perform_action, "sword.chan" :),
(: perform_action, "cuff.zhen" :),
(: perform_action, "cuff.zhan" :),
(: perform_action, "cuff.ji" :)
      }));
    setup();
    set("inquiry", ([
"newbie" : (: ask_newbie :),
        "拜师" : "你要拜哪里？（ask shizhe about 〈门派名称〉）\n武当？少林？星宿？华山？丐帮？神龙岛？昆仑？铁掌？\n古墓？慕容？桃花岛？天龙寺？大轮寺？嵩山？明教？峨嵋?\n如果有 ask 后没有反应的，那么就是那个门派已经关闭了。\n",
"大轮寺" : (: ask_xs :),
"桃花岛" : (: ask_thd :),
"星宿" : (: ask_xingxiu :),
"武当" : (: ask_wudang :),
"峨嵋" : (: ask_emei :),
"明教" : (: ask_mingjiao :),
"少林" : (: ask_shaolin :),
"丐帮" : (: ask_gb :),
"古墓" : (: ask_tttt :),
"华山" : (: ask_hs :),
"嵩山" : (: ask_ss :),
"慕容" : (: ask_mur :),
"天龙寺" : (: ask_tls :),
"铁掌" : (: ask_tz :),
"神龙岛" : (: ask_sld :),
"昆仑" : (: ask_kl :),
"洪门" : (: ask_hm :),
      ]) );
}
string ask_newbie()
{ 
    mapping skill;
    string *skl;
    int i;
    object me = this_object();
    object ob = this_player();
    write ("请输入 ask shizhe about 拜师 来要技能。\n");
    ob->set_skill("dodge",1);
    skill = ob->query_skills();
    skl = keys(skill);
    i = sizeof(skl);
    while (i--) 
    {
		ob->delete_skill(skl[i]);              
    }
	message_vision(HBRED"$N废去了$n的所有武功！\n"NOR,me,ob);
	message_vision(HBRED"另外赠送你一周的贵宾服务！\n"NOR,me,ob);    
    ob->delete("double_attack");
	
	// 天赋
	this_player()->set("str", 100);
    this_player()->set("per", 100);
    this_player()->set("int", 100);
    this_player()->set("con", 100);
    this_player()->set("dex", 100);
    this_player()->set("kar", 100);
    this_player()->set("pur", 100);

	// 战斗经验
    this_player()->set("combat_exp", GIVE_EXP);

	// 身体素质
    this_player()->set("neili", 100000);
    this_player()->set("max_neili", 100000);
    this_player()->set("jingli", 100000);
    this_player()->set("max_jingli", 100000);
    this_player()->set("eff_jingli", 100000);
    this_player()->set("qi", 100000);
    this_player()->set("max_qi", 100000);
    this_player()->set("eff_qi", 100000);
    this_player()->set("jing", 100000);
    this_player()->set("max_jing", 100000);
    this_player()->set("eff_jing", 100000);

	// 职业技能
    this_player()->set_skill("nongsang", SKILLS_LEVEL);
    this_player()->set_skill("zhizao", SKILLS_LEVEL);
    this_player()->set_skill("duanzao", SKILLS_LEVEL);
    this_player()->set_skill("caikuang", SKILLS_LEVEL);

	// 杂学
    this_player()->set_skill("literate", SKILLS_LEVEL);
    this_player()->set_skill("medicine", SKILLS_LEVEL);
	this_player()->set_skill("jingmai-xue", SKILLS_LEVEL);
    this_player()->set_skill("trade", SKILLS_LEVEL);
    this_player()->set_skill("poison", SKILLS_LEVEL);
	this_player()->set_skill("stealing", SKILLS_LEVEL);
	this_player()->set_skill("beauty", SKILLS_LEVEL);
	
	// 基本武学
    this_player()->set_skill("unarmed", SKILLS_LEVEL);
    this_player()->set_skill("finger", SKILLS_LEVEL);
    this_player()->set_skill("force", SKILLS_LEVEL);
    this_player()->set_skill("dodge", SKILLS_LEVEL);
    this_player()->set_skill("parry", SKILLS_LEVEL);
   	this_player()->set_skill("sword", SKILLS_LEVEL);

	// 特殊招式
    this_player()->set_skill("dugu-jiujian", SKILLS_LEVEL);

	// 特殊招式激活
    this_player()->map_skill("sword", "dugu-jiujian");
    this_player()->map_skill("parry", "dugu-jiujian");
    this_player()->map_skill("dodge", "dugu-jiujian");
	
    ob->set("job_time/送信",1000);
    ob->set("job_time/丐帮",400);
    ob->set("shizhe_newbie",1);
    ob->set("registered", 3);    
	ob->set("vip/vip_time",time());
	ob->add("vip/vip_time",7*24*3600);
	ob->set("vip/vip_start_time",time());    
    ob->set("age",15);
    ob->set("mud_age",100000);
    ob->set("离馆",1);
    ob->delete("enter_wuguan");
    return "为鼓励newbie特此奖励!请用 ask shizhe about 拜师 来要技能。\n"; 
}
string ask_fanhui()
{
    mapping skill;
    string *skl;
    int i;
    object me = this_object();
    object ob = this_player();
    skill = ob->query_skills();
    skl = keys(skill);
    i = sizeof(skl);
    while (i--) 
    {
ob->delete_skill(skl[i]);              
    }
    message_vision(HBRED"$N废去了$n的所有武功！\n"NOR,me,ob);
    ob->delete("shizhe_newbie");
    ob->delete("shizhe_拜师");
    ob->delete("mishu_newbie");
    ob->delete("mishu_want");
    ob->set("family",0);
    return "请重新ask shizhe about newbie一次。\n";
}
string ask_xingxiu()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("星宿派", 2, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
     this_player()->move("/d/xingxiu/xxh");
     this_player()->set("job_time/星宿",500);
    this_player()->set_skill("huagong-dafa",SKILLS_LEVEL);
    this_player()->set_skill("chousui-zhang",SKILLS_LEVEL);
    this_player()->set_skill("sanyin-zhua",SKILLS_LEVEL);
    this_player()->set_skill("zhaixingshu",SKILLS_LEVEL);
    this_player()->set_skill("tianshan-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("staff",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
    this_player()->set_skill("poison",200);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("shen",-100000);
    return "hehe";
}
string ask_ss()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("嵩山派", 4, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/songshan/damen");
    this_player()->set_skill("songyang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("songyang-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("songshan-jian",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-shenzhang",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-zhenqi",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("zhongyuefeng",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("songshan_points",600);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_wudang()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("武当派", 2, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/wudang/sanqing");
    this_player()->set_skill("taiji-quan",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("taiji-jian",SKILLS_LEVEL);
    this_player()->set_skill("taoism",200);
    this_player()->set_skill("tiyunzong",SKILLS_LEVEL);
    this_player()->set_skill("yinyun-ziqi",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("zhenshan-mianzhang",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_emei()
{
    object ob;
    ob=this_player();
    if (ob->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("峨嵋派", 5, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/emei/houdian");
    this_player()->set_skill("anying-fuxiang",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("yanxing-daofa",SKILLS_LEVEL);
    this_player()->set_skill("dacheng-fofa",200);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("huifeng-jian",SKILLS_LEVEL);
    this_player()->set_skill("jieshou-jiushi",SKILLS_LEVEL);
    this_player()->set_skill("linji-jianzhen",200);

    this_player()->set_skill("sixiang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("linji-zhuang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_shaolin()
{
object ob;
ob=this_player();
if (ob->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!ob->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
if((string)ob->query("gender") == "女性" )
return "少林寺武功需要纯阳之体，小姑娘可不收啊! ";
message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
this_object()->create_family("少林派", 99, "弟子");
this_object()->recruit_apprentice(this_player());
this_object()->delete("title");       
    this_player()->move("/d/shaolin/smdian");
this_player()->set_skill("buddhism",180);
this_player()->set_skill("jingang-quan",SKILLS_LEVEL);//6高级
this_player()->set_skill("cuff",SKILLS_LEVEL);
this_player()->set_skill("banruo-zhang",SKILLS_LEVEL);
this_player()->set_skill("strike",SKILLS_LEVEL);
this_player()->set_skill("yizhi-chan",SKILLS_LEVEL);
this_player()->set_skill("finger",SKILLS_LEVEL);
this_player()->set_skill("longzhua-gong",SKILLS_LEVEL);
this_player()->set_skill("claw",SKILLS_LEVEL);
this_player()->set_skill("qianye-shou",SKILLS_LEVEL);
this_player()->set_skill("hand",SKILLS_LEVEL);
this_player()->set_skill("ruying-suixingtui",SKILLS_LEVEL);
this_player()->set_skill("leg",SKILLS_LEVEL);


        //3 weapon 但是不给三大武学只给基本自己选择
this_player()->set_skill("blade",SKILLS_LEVEL);
this_player()->set_skill("club",SKILLS_LEVEL);
this_player()->set_skill("whip",SKILLS_LEVEL);
this_player()->set_skill("yijin-jing",SKILLS_LEVEL);
this_player()->set_skill("shaolin-shenfa",SKILLS_LEVEL);

    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_mingjiao()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("明教", 37, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
     this_player()->move("/d/mingjiao/jyt");
    this_player()->set_skill("qishang-quan",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-mianzhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("yingzhua-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-lingfa",SKILLS_LEVEL);
    this_player()->set_skill("dagger",SKILLS_LEVEL);
    this_player()->set_skill("liehuo-jian",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("lieyan-dao",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-fumozhen",200);
    this_player()->set_skill("qiankun-danuoyi",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-shengong",SKILLS_LEVEL);
    this_player()->set_skill("piaoyi-shenfa",SKILLS_LEVEL);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_gb()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("丐帮", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");        
    this_player()->move("/d/gb/pomiao");
    this_player()->set_skill("xianglong-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("dagou-bang",SKILLS_LEVEL);
    this_player()->set_skill("stick",SKILLS_LEVEL);
    this_player()->set_skill("huntian-qigong",SKILLS_LEVEL);
    this_player()->set_skill("xiaoyaoyou",SKILLS_LEVEL);
    this_player()->set_skill("bangjue",SKILLS_LEVEL);
    this_player()->set_skill("dagou-zhen",SKILLS_LEVEL);
    this_player()->set_skill("checking",SKILLS_LEVEL);
    this_player()->set_skill("stealing",SKILLS_LEVEL);
    this_player()->set_skill("begging",SKILLS_LEVEL);
    this_player()->set("shen",100000);
// 删除特殊quest 记号
//    this_player()->set("dgb/wugou",1);
//    this_player()->set("xlz/kanglong",1);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_hs()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("华山派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/huashan/zhengqi");
    this_player()->set_skill("huashan-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
    this_player()->set_skill("huashan-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("zixia-gong",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("poyu-quan",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hunyuan-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("huashan-qigong",SKILLS_LEVEL);
    this_player()->set_skill("zhengqi-jue",SKILLS_LEVEL);
    this_player()->set_skill("dugu-jiujian",SKILLS_LEVEL);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_tttt()
{
//object suo
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    if (this_player()->query("per") < 25)
     return "你天生容貌欠佳, 恐怕今生难圆双剑合壁之美梦。\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("古墓派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
     this_player()->move("/d/gumu/jqg/wshi");
//鉴于GM 都是帅哥靓妹
    this_player()->set_skill("strike",SKILLS_LEVEL);    
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);    
    this_player()->set_skill("cuff",SKILLS_LEVEL);            
    this_player()->set_skill("yunu-xinjing",SKILLS_LEVEL);
    this_player()->set_skill("yunu-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("yunu-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("xuantie-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("meinu-quanfa",SKILLS_LEVEL);
    this_player()->set_skill("quanzhen-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("yinsuo-jinling",SKILLS_LEVEL);

    if (this_player()->query("gender")!="女性") {
this_player()->set_skill("tianluo-diwang",SKILLS_LEVEL);
this_player()->set_skill("quanzhen-jianfa",SKILLS_LEVEL);
this_player()->set_skill("anran-zhang",SKILLS_LEVEL);
    } else {
this_player()->set_skill("yunu-jianfa",SKILLS_LEVEL);
this_player()->set_skill("meinu-quanfa",SKILLS_LEVEL);
    }
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_mur()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("姑苏慕容", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");        
    this_player()->move("/d/mr/yanziwu/yanziwu");
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("murong-daofa",SKILLS_LEVEL);
    this_player()->set_skill("canhe-zhi",SKILLS_LEVEL);
    this_player()->set_skill("douzhuan-xingyi",SKILLS_LEVEL);
    this_player()->set_skill("finger",SKILLS_LEVEL);
    this_player()->set_skill("murong-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("shenyuan-gong",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("xingyi-zhang",SKILLS_LEVEL);
    this_player()->set_skill("yanling-shenfa",SKILLS_LEVEL);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_thd()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("桃花岛", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");   
    this_player()->move("/d/thd/jicui");
    this_player()->set("job_time/桃花岛",400);
    this_player()->set_skill("bihai-chaosheng", SKILLS_LEVEL);
    this_player()->set_skill("suibo-zhuliu", SKILLS_LEVEL);
    this_player()->set_skill("leg", SKILLS_LEVEL);
    this_player()->set_skill("strike", SKILLS_LEVEL);
    this_player()->set_skill("luoying-zhang", SKILLS_LEVEL);
    this_player()->set_skill("hand", SKILLS_LEVEL);
    this_player()->set_skill("finger", SKILLS_LEVEL);
    this_player()->set_skill("throwing", SKILLS_LEVEL);
    this_player()->set_skill("tanzhi-shentong", SKILLS_LEVEL);
    this_player()->set_skill("xuanfeng-tui",SKILLS_LEVEL);
    this_player()->set_skill("sword", SKILLS_LEVEL);
    this_player()->set_skill("yuxiao-jian", SKILLS_LEVEL);
    this_player()->set_skill("taoism", SKILLS_LEVEL);
    this_player()->set_skill("qimen-bagua", SKILLS_LEVEL);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_tz()
{
 if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
  if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("铁掌帮", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");   
    this_player()->move("/d/tiezhang/wztang");
    this_player()->set_skill("guiyuan-tunafa", SKILLS_LEVEL);
    this_player()->set_skill("tiezhang-xinfa", 200);
    this_player()->set_skill("axe", SKILLS_LEVEL);
    this_player()->set_skill("lietian-fu", SKILLS_LEVEL);
    this_player()->set_skill("shuishangpiao", SKILLS_LEVEL);
    this_player()->set_skill("strike", SKILLS_LEVEL);
    this_player()->set_skill("tiezhang-zhangfa", SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_sld()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("神龙教", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/sld/dukou");

    this_player()->set_skill("hook",SKILLS_LEVEL);
    this_player()->set_skill("canglang-goufa",SKILLS_LEVEL);
    this_player()->set_skill("huagu-mianzhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("lingshe-bianfa",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-tuifa",SKILLS_LEVEL);
    this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("tenglong-bifa",SKILLS_LEVEL);
    this_player()->set_skill("dagger",SKILLS_LEVEL);
    this_player()->set_skill("dulong-dafa",SKILLS_LEVEL);
    this_player()->set_skill("youlong-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("poison",200);
    this_player()->set_skill("shenlong-wudizhen",200);
    this_player()->set_skill("shenlong-yaoli",200);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_tls()
{
    object ob;
    ob=this_player();
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    if((string)ob->query("gender") == "女性" )
return "天龙寺武功需要纯阳之体，小姑娘可不收啊! ";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("天龙寺", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/dali/shanhou");
    this_player()->set_skill("qingyan-zhang",SKILLS_LEVEL);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("qiantian-yiyang",SKILLS_LEVEL);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("tianlong-xiang",SKILLS_LEVEL);
    this_player()->set_skill("finger",SKILLS_LEVEL);
    this_player()->set_skill("buddhism",180);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("duanjia-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("yiyang-zhi",SKILLS_LEVEL);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_xs()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("大轮寺", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/xueshan/guangchang");
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("huanxi-chan",180);
    this_player()->set_skill("huoyan-dao",SKILLS_LEVEL);
    this_player()->set_skill("longxiang-boruo",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("hammer",SKILLS_LEVEL);
    this_player()->set_skill("yuxue-dunxing",SKILLS_LEVEL);
    this_player()->set_skill("xuedao-jing",SKILLS_LEVEL);
    this_player()->set_skill("xiangfu-lun",SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_kl()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("昆仑派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
     this_player()->move("/d/kunlun/guangchang");
    this_player()->set_skill("xuantian-wuji",SKILLS_LEVEL);
    this_player()->set_skill("taxue-wuhen",SKILLS_LEVEL);
    this_player()->set_skill("chuanyun-tui",SKILLS_LEVEL);
    this_player()->set_skill("kunlun-zhang",SKILLS_LEVEL);
    this_player()->set_skill("zhentian-quan",SKILLS_LEVEL);
    this_player()->set_skill("liangyi-jian",SKILLS_LEVEL);
    this_player()->set_skill("xunlei-jian",SKILLS_LEVEL);
    this_player()->set_skill("mantian-huayu",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("art",200);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);

    return "hehe";
}
string ask_hm()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());

	// 天赋
	this_player()->set("str", 100);
    this_player()->set("per", 100);
    this_player()->set("int", 100);
    this_player()->set("con", 100);
    this_player()->set("dex", 100);
    this_player()->set("kar", 100);
    this_player()->set("pur", 100);

	// 战斗经验
    this_player()->set("combat_exp", 30000000);

	// 身体素质
    this_player()->set("neili", 100000);
    this_player()->set("max_neili", 100000);
    this_player()->set("jingli", 100000);
    this_player()->set("max_jingli", 100000);
    this_player()->set("eff_jingli", 100000);
    this_player()->set("qi", 100000);
    this_player()->set("max_qi", 100000);
    this_player()->set("eff_qi", 100000);
    this_player()->set("jing", 100000);
    this_player()->set("max_jing", 100000);
    this_player()->set("eff_jing", 100000);

	// 职业技能
    this_player()->set_skill("nongsang", 200);
    this_player()->set_skill("zhizao", 200);
    this_player()->set_skill("duanzao", 200);
    this_player()->set_skill("caikuang", 200);

	// 杂学
    this_player()->set_skill("medicine", HM_LEVEL);
	this_player()->set_skill("jingmai-xue", HM_LEVEL);
    this_player()->set_skill("literate", HM_LEVEL);
    this_player()->set_skill("buddhism", HM_LEVEL);
    this_player()->set_skill("daode-jing", HM_LEVEL);
    this_player()->set_skill("trade", HM_LEVEL);
    this_player()->set_skill("poison", HM_LEVEL);
	
	// 基本武学
    this_player()->set_skill("unarmed", HM_LEVEL);
    this_player()->set_skill("claw", HM_LEVEL);
    this_player()->set_skill("cuff", HM_LEVEL);
    this_player()->set_skill("finger", HM_LEVEL);
    this_player()->set_skill("hand", HM_LEVEL);
    this_player()->set_skill("strike", HM_LEVEL);
    this_player()->set_skill("leg", HM_LEVEL);
    this_player()->set_skill("force", HM_LEVEL);
    this_player()->set_skill("dodge", HM_LEVEL);
    this_player()->set_skill("parry", HM_LEVEL);
   	this_player()->set_skill("sword", HM_LEVEL);

	// 特殊招式
    this_player()->set_skill("beiming-shengong", HM_LEVEL);
    this_player()->set_skill("lingbo-weibu", HM_LEVEL);
    this_player()->set_skill("yiyang-zhi", HM_LEVEL);
    this_player()->set_skill("liumai-shenjian", HM_LEVEL);

	// 特殊招式激活
    this_player()->map_skill("parry", "yiyang-zhi");
    this_player()->map_skill("finger", "yiyang-zhi");
    this_player()->map_skill("force", "beiming-shengong");
    this_player()->map_skill("dodge", "lingbo-weibu");

    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);

    return "hehe";
}
