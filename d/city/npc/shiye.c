// shiye.c modified by Lklv 2002.1.29

#include <ansi.h>
inherit NPC;
int ask_me(object who);
void create()
{
	set_name("����ˮ", ({ "wang huaishui", "wang" }));
	set("title", "�Ӿ�Ʒʦү");
	set("gender", "����");
	set("age", 57);
	set("combat_exp", 30000);
	set_skill("unarmed", 50);
	set_skill("dodge", 60);
	set_temp("apply/attack",  20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage",  20);
	set("shen", -1);
	set("inquiry", ([
		"ٺ»" : (: ask_me :),
	]));
	setup();
	carry_object("/clone/armor/cloth")->wear();
	carry_object("/clone/armor/shoes")->wear();
}

int ask_me(object who)
{
        object me = this_player();
        int times;
        times = (int)me->query("job_time/�ٸ�",1);

        if ( times<=1 ){
		command("say ��ûΪ��͢����ʲ����������Ҫٺ»��\n");
		return 1;
	}
	if ( times > 4000 ){
		command("say ���²����Ǹ�֪��ʦү�����ỹ�Ҹ�����ٺ»�أ�\n");
		command("flatter " + me->query("id"));
		return 1;
        }
	if( (int)me->query("gf_gives") < (int)me->query("age")) {
		if (me->query_temp("mark/huilu")){
			command("hehe " + me->query("id"));
			message_vision("����ˮ��ͷ������˵������λ"+RANK_D->query_respect(me)+"�����ˣ��������Ĺ�ٺ��"
			"�Ժ������������¡�\n",me);
			who->add_money("gold",10+times/10);
			command("give "+me->query("id")+" gold");
			me->delete_temp("mark/huilu");
			me->set("gf_gives",(int)me->query("age"));
			return 1;
		}
		command("look " + me->query("id"));
		command("say �����������ȥ�ɣ�\n");
		who->add_money("gold",times/20);
		command("give "+me->query("id")+" gold");
		write(WHT"����Լ����Ǯ����Ŀ���󲻴�԰���\n"NOR);
		me->set("gf_gives",(int)me->query("age"));
		return 1;
	}

        command("say û��ʱ���أ���ʲ��ٺ»��!\n");
        return 1;
}

int accept_object(object me, object obj)
{
        int times;
        times=me->query("job_time/�ٸ�",1);

        if (!me->query("job_time/�ٸ�")){
		command("say ��Ե�޹��������¸�ң�\n");
		return 1;
        }
        if(obj->query("money_id")){
		if(obj->value() >= times*100){
			command("hehe "+me->query("id"));
			command("whisper "+me->query("id")+" ��ͷ��İɣ���ͷ�һ�úù�����ģ�");
			me->set_temp("mark/huilu",1);
			return 1;
		}
		command("say ��ô��Ǯ�ܸ�ʲ�᣿��������ȥһ������Ժ���أ�");
		return 1;
        }
	command("say �����"+obj->name()+"�����ң���ʲ���ã���");
	return 0;
}

void destroy (object obj)
{
	destruct(obj);
	return;
}
