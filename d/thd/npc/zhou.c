// Modify By River@SJ about jieyi and hubo
// Modify by Darken for taohua quest 2k
// Modify By River@Sj for jiuyin quest
// Update by lsxk@hsbbs addͨ����Ʒ��߽�quest����. 2007/7/20
//by spiderii@ty ȡ�����Եı�̬��������
inherit NPC;

#include <skill.h> 
#include <ansi.h>
#include "question.h"



int ask_jieyi();
int do_answer(string arg);
int questions(object me);
int ask_jiuyin();
int ask_hubo();
int do_fangyuan();
int do_learn(string arg);
int ask_story();
int ask_skill();
int ask_story2();
void waiting(object ob);
void create()
{
	set_name("�ܲ�ͨ", ({ "zhou botong", "zhou", "botong" }) );
	set("nickname", "����ͯ");
	set("long", "����ͷ������ֱ�����أ���ü���룬������Ͷ�������ס�ˡ�\n"
		"���뷢��Ȼ����δȫ�ף�ֻ�ǲ�֪�ж����겻�꣬����Ұ��һ��ë���׵��������ˡ�\n"
		"���ľ�ֹ���红ͯһ����\n");
	set("gender", "����" );
	set("age", 48);
	set("attitude", "peaceful");
	set("apprentice", 1);

	set("str",28);
	set("int",25);
	set("con",30);
	set("dex",29);
	set("unique", 1);
	set("pur", 30);
	set("per", 24);

	set("no_get", "�ܲ�ͨ�������̫���ˡ�\n");

	set("max_qi", 12000);
	set("max_jing", 10000);
	set("max_neili", 21000);
	set("jiali", 150);
	set("combat_exp", 5600000);
	set("eff_jingli", 9500);
	set("double_attack", 1);
	set("score", 5000);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.qixing" :),
		(: perform_action, "sword.sanqing" :),
		(: perform_action, "cuff.kong" :),
		(: perform_action, "cuff.ming" :),
	}));

	set_skill("force", 380);
	set_skill("xiantian-gong", 380);
	set_skill("dodge", 390);
	set_skill("tiyunzong", 390);
	set_skill("cuff", 380);
	set_skill("kongming-quan", 380);
	set_skill("parry", 380);
	set_skill("sword", 380);
	set_skill("quanzhen-jianfa", 380);
	set_skill("taoism", 200);
	set_skill("literate", 260);

	map_skill("force", "xiantian-gong");
	map_skill("dodge", "tiyunzong");
	map_skill("cuff", "kongming-quan");
	map_skill("sword", "quanzhen-jianfa");
	map_skill("parry", "quanzhen-jianfa");
	prepare_skill("cuff", "kongming-quan");

	set("rank_info/respect", "����ͯ");
	set("shen_type", 1);
	create_family("ȫ���", 2, "����");
	set("class", "taoist");

	set("inquiry", ([
		"name": "�����ܲ�ͨ�ͺ��ˡ�",
		"rumors": "�ұ��Ǹ�����а��������ʮ���꣬ÿ�����һ���������ͷ���",
		"here": "�������һ����������Ǹ�С������������������ģ�������������ܲ�����ȫ�ˡ�",
		"��а": "�ǻ�ҩʦ����޳ܵļһƭ���ҵľ�....ȥ����",
		"��ҩʦ": "����޳ܵļһƭ���ҵľ�....ȥ����",
		"����ͨ": "�ҵ�ʦ���������书��ߵģ���һ�λ�ɽ�۽�ʱ����Ϊ��һ���֡�",
		"������": "�ҵ�ʦ���������书��ߵģ���һ�λ�ɽ�۽�ʱ����Ϊ��һ���֡�",
		"�ܲ�ͨ": "������ʲô����",
		"����": "���Ż���ԧ��֯����˫��....",
		"����": "���Ż���ԧ��֯����˫��....",
		"�λ�ү": "����ͯ���¶Բ�������û���ټ����ˡ�",
		"������": "����ͯ���¶Բ�������û���ټ����ˡ�",
		"�ϵ�": "����ͯ���¶Բ�������û���ټ����ˡ�",
		"����ͯ": "�Ҿ��ǰ���������ʲô����",
		"����ȭ": "����ȭ����ʮ��·���ھ��ǣ��������ɡ���ͨ���Ρ�������Ū��ͯӹ���档",
		"kongming-quan": "����ȭ����ʮ��·���ھ��ǣ��������ɡ���ͨ���Ρ�������Ū��ͯӹ���档",
		"����": "�Ǽ�����ǰ������������Ǹ�С������",
		"����": "�����ҵĽ����ֵܣ�����Ȼɵ���ĳ����á�",
		"����": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
		"jpei": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
		"�һ���": "��������һ����������Ǹ�С������������������ģ�������������ܲ�����ȫ�ˡ�",
		"��": "��Ҫ������",
		"fang": "��Ҫ������",
		"Բ": "ԲҪ��Բ��",
		"yuan": "ԲҪ��Բ��",
		"�����澭": (: ask_jiuyin :),
		"˫�ֻ���": (: ask_hubo :),
		"���һ���": (: ask_hubo :),
		"����": (: ask_jieyi :),
		"���": (: ask_jieyi :),
		"����": (: ask_story :),
		"��������": (: ask_story2 :),
		"�书": (: questions :),
		"����": (: ask_skill :),
	]));

	setup();

	if(random(2))
		carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
	object ob = this_player();
	add_action("do_fangyuan","fangyuan");
	add_action("do_draw","draw");
	add_action("do_draw","hua");
	add_action("do_answer","answer");
	add_action("do_learn","learn");
	add_action("do_learn","xue");
	::init();
	if (ob->query("family/family_name") == "ȫ���") {
		command("angry " + ob->query("id"));
		command("say ��ô�㵽����������ң��������Ҿ�ȥ�ʹ���˵��������ƨ�ɡ�");
	}
}

void kill_ob(object me)
{
        command("chat* crazy " + me->query("id"));
        ::kill_ob(me);
}

void unconcious()
{
        command("chat* ̾��������ͯ������Ҫ�����ˣ�������������ֻ���ܣ���Щ��ͷ���޳���һ���Ƶ�Ī�������ɫ��䡣");
        ::unconcious();
}


int ask_story()
{
        object me = this_player();
        string msg;
        msg = CYN"�ܲ�ͨ����$NҪ�������£���ʱ�˸߲��ҡ�\n"NOR;
        msg+= CYN"�ܲ�ͨ��ʼ��������澭�ͻ��ѵĹ��¡�\n"NOR;
        msg+= CYN"�ܲ�ͨ��$N���ʺ����������������˵�ˡ�\n"NOR;
        message_vision(msg, me);
        me->set_temp("thd/story",1);
        return 1;
}

int ask_story2()
{
        object me = this_player();
        string msg;
        if (me->query_temp("thd/story") == 1){
                msg = CYN"�ܲ�ͨһ��$N���������������ֿ�ĭ��ɵ�˵������\n";
                msg+= CYN"�ܲ�ͨ�����ֿ�ʼ��$N˵������ȫ��̵Ĺ��¡�\n";
                msg+= CYN"$N���ţ�Ҳѧ����Щȫ���������Ƥë��\n"NOR;
                msg+= HIW"�ܲ�ͨ˵����£������ĵ��ʵ������ֵܣ���ʲô������书ô��\n"NOR;
                message_vision(msg, me);
                me->set_temp("thd/story",2);
                return 1;
        }
        message_vision(CYN"�ܲ�ͨ��ֵ��ʵ�����ʲô������������\n"NOR, me);
        return 1;
}

int ask_jieyi()
{
	object ob=this_player();
	int i, time;

	i = ob->query("combat_exp") - 1000000;
	i /= 1000000;

	time = time() - ob->query("quest/jiebai/time");

	if (ob->query("quest/jiebai/pass")) {
		command("? " + ob->query("id"));
		command("say �������ǽ�ݹ�����");
		return 1;
	}
	if (ob->query("quest/jiebai/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say �Ҳ���˵�ˣ���û��Ȥ�����ݰ���");
		return 1;
	}
	if ( ob->query("quest/jiebai/time") && time < 86400 ) {
		command("shake");
		command("say �����ڿ�û�գ���æ�����ء�");
		return 1;
	}
	if ( ob->query("quest/jiebai/fail") >= i ){
		command("shake");
		command("say �����ڿ�û�գ���æ�����ء�");
		return 1;
	}
/*
	if (!wizardp(ob) && ob->query("age") > 48 ){
		command("shake");
		command("say ������ֻͯϲ�����������棬�����ݣ�û��˼��û��˼��");
		return 1;
	}
*/
	if (ob->query("gender") != "����" && ob->query("gender") != "Ů��") {
		if (ob->query("age") > 48) 
			command("say �ұ���Ҳ�������ݣ����ǲ�֪���ֵ���ƻ��ǽ����ƣ�");
		else
			command("say �ұ���Ҳ�������ݣ����ǲ�֪���ֵ���ƻ���������ƣ�");
		command("laugh");
		return 1;
	}
	if ( ob->query("class") =="bonze" || ob->query("class") == "huanxi"){
		command("monk "+ ob->query("id"));
		command("say "+RANK_D->query_respect(ob)+"������ͯ�ҿ�û����Ȥ�����ݡ�");
		return 1;
	}
	if ( ob->query("int") > 25) {
		command("shake");
		command("say ������˹��龫������׼����ʲô�����ء�");
		return 1;
	}
	if ( ob->query("shen") <= -1) {
		command("shake");
		command("say ����Ȼ������㣬��ʦ��̻岻����������а֮������Ҫ����ġ�");
		return 1;
	}
	if ( ob->query("combat_exp") < 1000000) {
		command("shake "+ ob->query("id"));
		command("say ��λ"+RANK_D->query_respect(ob)+"�������ʵ��̫����ˣ��ҿ�û��Ȥ�����ݡ�");
		return 1;
	}
	if (random(ob->query("kar")) < 20 || random(ob->query_int(1)) < 30){
		command("shake");
		command("say ������û�пգ�Ҫ�������������棿");
		ob->add("quest/jiebai/fail", 1);
		ob->set("quest/jiebai/time", time());
		log_file("quest/jiebai",
			sprintf("%-18s�����ܲ�ͨ��ݣ�ʧ��%s�Ρ�\n",
				ob->name(1)+"("+capitalize(getuid(ob))+")",
				chinese_number(ob->query("quest/jiebai/fail")) 
			), ob
		);
		return 1;
	}
	command("nod " + ob->query("id"));
	if (ob->query("gender") == "����") {
		command("say �ðɣ����Ҿͽ��Ϊ�ֵܰɡ�");
	}
	else if (ob->query("gender") == "Ů��") {
		if (ob->query("age") > 48)
			command("say �ðɣ����Ҿͽ��Ϊ��ܰɡ�");
		else
			command("say �ðɣ����Ҿͽ��Ϊ���ðɡ�");
	}
	message_vision("�ܲ�ͨ��$N�����������˵����������ͯ�ܲ�ͨ��������" + ob->name(1) +"���������պ��и��������ѹ�����\n"+
			"����Υ�����ģ������书ȫʧ����С��СèҲ�򲻹�����\n", ob);
	log_file("quest/jiebai",
		sprintf("%-18sʧ��%s�κ󣬳ɹ����ܲ�ͨ��ݣ�����%d����%d��\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",
			chinese_number(ob->query("quest/jiebai/fail")), 
			ob->query("kar"), 
			ob->query_int(1)
		), ob
	);
	ob->set("quest/jiebai/pass", 1);
	ob->set("quest/jiebai/exp", ob->query("combat_exp"));
	return 1;
}

int ask_jiuyin()
{
	object ob=this_player();
	object zhou = this_object();
	object book;
	int i,time;

	i = ob->query("combat_exp") - 2000000;
	i /= 1000000;
	time = time()- ob->query("quest/jiuyin1/time");

	if(present("jiuyinzhenjing shangjuan", ob)) {
		command("faint");
		command("say �㲻������ô��");
		return 1;
	}
	if( zhou->is_busy() || zhou->is_fighting()){
		command("hmm");
		command("say ��û��������æ��ô��");
		return 1;
	}
	if( ob->query("quest/jiuyin1/fail") >= 3 && ob->quest("registered") < 3 && !ob->query("quest/jiuyin1/pass")){
		command("say ����æ���ء�");
		return 1;
	}
	if ( !ob->quest("quest/jiuyin1/pass") && time < 86400) {
		command("say ����æ���ء�");
		return 1;
	}
	if ( ob->query("quest/jiuyin1/fail") >= i) {
		command("say ����æ���ء�");
		return 1;
	}
	if (ob->query("quest/jiuyin1/pass")){
		book = unew("/d/thd/obj/jiuyin-book1");
		if(!clonep(book)){
			command("pat");
			command("say ������û�пգ��������澭�Ͼ���Ȼ�����Ҫ�ɡ�");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("pat");
			command("say ������û�пգ��������澭�Ͼ���Ȼ�����Ҫ�ɡ�");
			return 1;
		}
		command("consider");
		command("say ��Ҫ�ٳ�һ�ݣ�");
		message_vision(HIW"$N���³�¼��һ�ݾ����澭���Ͼ�\n"NOR,ob);
		book->set("owner", ob->query("id"));
		book->move(ob);
		return 1;
	}
	if (ob->query_temp("jyquest") != 3) {
                command("? " + ob->query("id"));
                return 1;
	}
	command("say �����澭���Ǹ���������ʦ��ģ����Ǹ�����а��������ƭ��ȥ��");
	command("say �������Ÿ��������Ͼ��ȱ��ȫ���¾��ֱ����Լ�ͽ��͵�ˣ�����ͽб�Ӧ��");
	command("laugh zhou");
	ob->set_temp("jyquest", 4);
	command("say ���������������������ѵ��и������ң���������ˡ�");
	message_vision(HIY"�ܲ�ͨ����$N˵�������ԹԵ�����˵���°ɡ���\n"NOR,ob);
	command("grin");
	ob->move("/d/thd/neidong");
	zhou->move("/d/thd/neidong");
	call_out("waiting", 120, ob);
	return 1;
}

int ask_skill()
{
	object me=this_player();
	object ob = this_object();
	object book;
	object* ppl;
	int i, j =0;
        
	if (me->query_temp("jyquest") != 5) {
		command("? " + ob->query("id"));
		return 1;
	}
	command("hehe zhou");
	command("say ��Щ���������Լ��Ĵ������������ĺܰ���");
	message_vision(CYN"�ܲ�ͨȴֻ�Ǹ���$N���ʩչ����ȫ��������$N����\n"NOR,me);
	i = sizeof(ppl);
	while(i--) {
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("quest/jiuyin1/pass"))
		j++;
	} 
	if( me->query("combat_exp") > 2000000
	 && random(me->query_int(1)) > 35
	 && random(me->query("kar")) > 25
	 && random(me->query("pur")) > 25
	 && j < 1){ 
		message_vision(HIW"\n�ܲ�ͨ��$N��ϰ�����ᣬͻȻ������Ц������\n"NOR,me);
		command("haha");
		command("laugh");
		command("say ��Щ�����书����ô�����Լ��Ĺ����Ǿ��Ǿ����澭����");
		command("say ���������㿴�����⹦���������������Ҳ�Ŀ�ˡ�");
		book=unew("/d/thd/obj/jiuyin-book1");
		log_file("quest/jiuyin",
			sprintf("%-18sʧ��%s�κ󣬵õ������澭�ϲᣬ��%d������%d������%d��\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/jiuyin1/fail")),
				me->query_int(1), 
				me->query("kar"), 
				me->query("pur") 
			), me
		);
		me->delete_temp("jyquest");
		me->set("quest/jiuyin1/pass",1);
		if(!clonep(book)){
			command("hungry");
			command("say ���ˣ��������ˣ����Ӷ����ˣ���Ҫ�Է�ȥ�ˡ�");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("hungry");
			command("say ���ˣ��������ˣ����Ӷ����ˣ���Ҫ�Է�ȥ�ˡ�");
			return 1;
		}                 
		command("say �������Ѿ�ѧ���ˣ�������澭�Ͼ����㳭¼һ��ȥ�ɡ�");
		message_vision(HIW"$N�������澭���Ͼ�С�ĵĳ�¼������\n"NOR,me);
		book->set("owner", me->query("id"));
		book->move(me);
		return 1;
	}
	message_vision(CYN"$N������ô��ϰ�����޷��ɹ���\n"NOR,me);
	command("sigh");
	command("say ��������书�����ű���ѧ�˰ɡ�");
	command("disapp");
	me->add("quest/jiuyin1/fail", 1);
	me->set("quest/jiuyin1/time", time());
	log_file("quest/jiuyin",
		sprintf("%-18s����ܲ�ͨ���õ������澭�ϲᣬʧ��%s�Ρ�\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/jiuyin1/fail"))
		), me
	);
	me->delete_temp("jyquest");
	return 1;
}

void waiting(object ob)
{
	if( ob->query_temp("thd/story")==2 
	 && ob->query_temp("jyquest") == 4
	 && ob->query_temp("jiuyin/question") > 3){
		command("say ������������ô�ã�һ�������İɣ�");
		command("hmm");
		command("ah zhou");
		command("say �����ɣ��ҽ�������Ĺ���");
		command("grin");
		ob->set_temp("jyquest",5);
		ob->move("/d/thd/cave");
		this_object()->move("/d/thd/cave");
	}
	else {
		command("yawn");
		command("say ��������ֱ������ģ���ȥ����ȥ��");
		ob->delete_temp("jyquest");
		ob->add("jiuyin/failed", 1);
		ob->move("/d/thd/cave");
		destruct(this_object());
	}
}

int ask_hubo()
{
	object ob=this_player();
	int hubo,i,time;

	i = ob->query("combat_exp") - ob->query("quest/jiebai/exp");
	i /= 500000;
	time = time()- ob->query("quest/hubo/time");

	if(!ob->query("quest/jiebai/pass")){
		tell_object(ob,"�ܲ�ͨ�������㿴����֪����Щʲô���⡣\n");
		command("say ����˭������ôĪ�����������˫�ֻ������°���");
		return 1;
	}               
	if (ob->query("double_attack")) {
		command("? " + ob->query("id"));
		command("say �㲻���Ѿ�ѧ������");
		return 1;
	}
	if(ob->query("quest/hubo/fail") >= 3 && ob->query("registered")< 3){
		command("disapp " + ob->query("id"));
		command("say �Ѿ�������ô��Σ�������һ����Ҳ���������Ź����ˡ�");
		return 1;
	}
	if ( ob->query("quest/hubo/miss")) {
		command("disapp " + ob->query("id"));
		command("say �Ѿ�������ô��Σ�������һ����Ҳ���������Ź����ˡ�");
		return 1;
	}
	if ( ob->query("quest/hubo/fail") >= i ) {
		command("shake " + ob->query("id"));
		command("say ���������ڻ����ʺ�ѧ���Ź���");
		return 1;
	}
	if ( ob->query("quest/hubo/time") && time < 86400) {
		command("shake " + ob->query("id"));
		command("say ���������ڻ����ʺ�ѧ���Ź��������ʱ���������԰ɡ�");
		return 1;
	}
	hubo = ob->query_temp("zuoyou_hubo");
	if (hubo == 22) {
		command("say ��������һ�Σ�");
		return 1;
	}
	if (hubo == 1) {
		command("say ��������Ϳ����");
		return 1;
	}
	if (hubo > 1 && hubo <= 21) {
		command("say ��ô����������ɣ����������Ů����������͸��һ���Ķ�������ʮ�߰˸��ϣ��������Ź�������ʼ��ѧ���ᣡ");
		return 1;
	}
	if (ob->query_skill("force") < 100 || ob->query("max_neili") < 500 || ob->query("combat_exp") < 50000) {
		command("say �㻹���ȴ����ѧ������˵�ɡ�");
		return 1;
	}
	command("say ���Ź��������ڶ�������֮ʱ��������������˵�����ѵ�������˵����Ҳ����֮����\n"+
		"�е���һѧ��ᣬ�е���һ����Ҳѧ���ˣ�Խ�Ǵ�����Խ�ǲ��ɡ�");
	command("say �����������һ�Σ����ֻ���(fang)�����ֻ�Բ(yuan)��");
	ob->set_temp("zuoyou_hubo", 1);
	return 1;
}

int do_fangyuan()
{
	object ob=this_player();
	int hubo;

	if (ob->is_busy() || ob->is_fighting())
		return notify_fail("����æ���أ�\n");

	hubo = ob->query_temp("zuoyou_hubo");
	if (!hubo) return 0;
	if (hubo < 21) {
		message_vision("$N�������ʳָ�ڵ��ϻ��������������ķ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 21) {
		message_vision("$N�������ʳָ�ڵ��ϻ��������������ķ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
		command("haha " + ob->query("id"));
		command("say ��ô������һ�±�첻����");
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 22) {
		if ( ob->query("pur") > 27 ){
                   if( (ob->query_temp("sj_credit/quest/public/hubo")&&random(ob->query("pur"))>18) || random(ob->query("pur")) > 25 ){
				message_vision("$N΢΢һЦ��������һ���ĵؿ���������������˫����ָ�����ֻ���һ�����飬���ֻ���һ��ԲȦ��\n"+
					"����������Բ�߻�Բ��\n", ob);
				say("�ܲ�ͨ���һ�������˰��βŵ������ⶨ�������̥��ѧ���ı��죬�Ǳ��װ��ˡ���\n");
				message_vision("�ܲ�ͨ����������������������ޱȵ��湦��һ���Զ����̸���$N��\n", ob);
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->delete_temp("zuoyou_hubo");
				log_file("quest/jiebai",
					sprintf("%-18sʧ��%s�κ󣬴��ܲ�ͨ������˫�ֻ���������%d��\n",
						ob->name(1)+"("+capitalize(getuid(ob))+")",
						chinese_number(ob->query("quest/hubo/fail")),
						ob->query("pur") 
					), ob
				);
				ob->set("double_attack", 1);
				ob->set("quest/hubo/pass", 1);
				return 1;
			}
			else {
				ob->delete_temp("zuoyou_hubo");
				message_vision("$N���������ʳָ�ڵ��ϻ����������������Ծ��Ƿ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
				write("������������ô�򵥡�\n");
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->add("quest/hubo/fail", 1);
				ob->set("quest/hubo/time", time());
				log_file("quest/jiebai",sprintf("%-18s����ܲ�ͨ������˫�ֻ�����ʧ��%s�Ρ�\n",
					ob->name(1)+"("+capitalize(getuid(ob))+")",chinese_number(ob->query("quest/hubo/fail")) ), ob);
				return 1;
			}
		}
		message_vision("$N���������ʳָ�ڵ��ϻ����������������Ծ��Ƿ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
		message_vision("$N���ڷ����Լ���һ����Ҳ���������Ź����ˡ�\n", ob);
		ob->delete_temp("zuoyou_hubo");
               ob->set("quest/hubo/miss", 1);
		log_file("quest/jiebai",sprintf("%-18s���ܲ�ͨ������˫�ֻ������������ʲ������޷��ɹ�������%d��\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",ob->query("pur") ),ob);
		command("disapp " + ob->query("id"));
		return 1;
	}
	return 0;
}

int do_draw(string arg)
{
	object ob=this_player();

	if (!ob->query_temp("zuoyou_hubo")) return 0;
	if (arg == "fang" || arg == "��" || arg == "yuan" || arg == "Բ") 
		return notify_fail("�ܲ�ͨŭ��������ͬʱ����Բ��\n");
	if (arg == "fang yuan" || arg == "��Բ") return do_fangyuan();
	return 0;
}

int accept_object(object who, object ob)
{
	if (ob->id("skin") && ob->query("material") == "paper") {
		if ((who->query_temp("thd/onquest") == 7)&&(who->query_temp("thd/story")==2)) {
			message_vision(CYN"�ܲ�ͨ����Ƥ��ϸ�鿴�������Ǿ����澭��\n"NOR, who);
			message_vision(CYN"��������ȥ������ҩʦ��ȴ���ܲ�ͨ��ס��\n"NOR, who);
			command("say ����ȵ���˵����������ɣ�");
			command("sing");
			command("say �þ�û������������������������ɣ�");
			command("hit " + who->query("id"));
			call_out("finish",5, who);
			return notify_fail("");
		}
		else {
			command("? " + who->query("id"));
			command("say ���������ʲô��\n");
			return notify_fail("");
		}
	}
	else if (who->query_temp("jyquest")==2 && ob->id("fan he") && ob->query("material") == "wood") {
		command("ah " + who->query("id"));
		command("say �ǻ���а��СѾͷ�����æ�ͷ���ô��");
		message_vision(CYN"�ܲ�ͨ����$N�ش��Ѿ���ʼ��ʳ���������С�\n"NOR,who);
		message_vision(CYN"�ܲ�ͨ���꣬��Ц��һ�£��Ŷ�$N�ʵ�������֪����Թ���û�У���\n"NOR,who);
		who->set_temp("jyquest", 3);
		command("say ����а��Ҫ�ҵľ����澭�����ҹ���ʮ��������");
		command("sing3");
		return 1;
	}
	return 0;
}

int prevent_learn(object ob, string skill)
{
	if (skill == "kongming-quan")
		return 0;
	return 1;
}
 
int is_apprentice_of(object ob)
{
	return 1;
}
 
int recognize_apprentice(object ob)
{
	return 1;
}

void finish(object who)
{
	string msg;
	msg = HIC"�ܲ�ͨ˵����������û��ϵ��������ϰ�������þ�û���˴���ˡ���\n";
	msg+= HIY"�ܲ�ͨ˵��������$N������\n";
	msg+= HIC"�ܲ�ͨ���˵ĵ������컹�ְ�����\n";
	msg+= HIR"$N���书�����������ڳ��ܲ��ˣ����˹�ȥ��\n"; 

	message_vision(msg, who); 
	who->set_temp("thd/onquest",8);
	who->unconcious();
}
