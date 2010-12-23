#include <ansi.h>

inherit NPC;

string *qian_type = 
({
        "��Ե","����","��Ե",
});

void create()
{
        set_name(HIC"�ƴ���"NOR, ({ "huang daxian", "daxian", "huang" }) );
        set("gender", "����" );
        set("age", 85);
        set("long","һλ��ǩ������������,�ƺ������Щ���¡�\n");
       
        set("attitude", "heroism");
        set("unique", 1);
        set("combat_exp", 100000);
        set("no_quest", 1);
        set("shen", 3000);
        set("str", 1000);
        set("int", 1000);
        set("con", 1000);
        set("dex", 1000);
        set("jiali", 200);
        set("max_qi", 900000);
        set("max_jing", 900000);
        set("eff_jingli", 900000);
        set("max_neili", 900000);
        set("startroom","/d/city/guangchang");
        set("chat_chance",4);
        set("chat_msg",({
               "�ƴ���˵��������ǩ,��ǩ.�޲�����!\n"NOR,
               (: random_move :)
        }));

        set("inquiry", ([

                "��ǩ" : "������������Ҳ֪���Ϸ���ǩҪ�ĳϣ�Ҫ��Ҫ����(qiuqian)��",
                "��ǩ" : "�������Υ����İ������ˣ��Ϸ������Ѹߣ�ʱ���޶࣬��Ͱ�ǩ���Ϸ򿴿���",
        ]));

        setup();
        carry_object("/clone/armor/cloth")->wear(); 
}

void init()
{
        add_action("do_qiuqian","qiuqian");
        add_action("do_answer","answer");
}

int do_qiuqian()
{
        object me,ob,qian;
        
        me = this_player();
        ob = this_object();

//      if (!wizardp(me) && time() - me->query("last_qiuqian_time") < 1800)
//             return notify_fail("����ǩ���ã�������ǩ���㵱������Ϸ����\n");

        if (present("zhu qian",me))
                return notify_fail("�����ϲ�����һ��ǩô���ú���ĥ��ĥ�ɡ�\n");

        command("look " + me->query("id"));
        command("consider");

        qian = new("/clone/misc/qian");
        qian->csh_qianwen();
        qian->set("owner",me->query("id"));

        if (!qian->move(me))
                return notify_fail("���ϴ���ô�ණ��������ǩ���㵱�Ǹϼ�����\n");

        message_vision("$N��һ��ǩͲ�ݸ�$n����ɫ���صĶ�����������ס���ĳ����飡��\n",ob,me);
        message_vision("$N΢��˫�ۣ�ĬĬ���棬�������ǩͲ��ҡƬ�̣�һ��ǩ���˳�����\n",me);
        message_vision("$N�Ͻ�����ǩͲ�������ǩ����������С����������뻳�С�\n",me);

        me->set("last_qiuqian_time",time());
        me->delete_temp("have_gived");
        me->delete_temp("can_answer");
        
        return 1;
}

int do_answer(string arg)
{
        object me,ob,obj;
        int i;
        string str,document,file;
        mapping qianwen;

        me = this_player();
        ob = this_object();

        if (!me->query_temp("can_answer"))
                return notify_fail("һ��ȥ������ʲô�ң�\n");

        if (!objectp(obj = me->query_temp("qian")))
        {
                me->delete_temp("can_anser");
                me->delete_temp("qian");
                return notify_fail("һ��ȥ������ʲô�ң�\n");
        }

        if (!arg || member_array(arg,qian_type) == -1)
        {
                str = HIC "�������кܶ���ǩ��" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "��";
                }
                str += "������������ǩ��\n";
                tell_object(me, str);
                tell_object(me, "����˾ͻش��ң�(answer ��)\n");
                return 1;
        }

        qianwen = obj->query("qianwen");

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        document = read_file(file) + "\n";
        tell_object(me,this_object()->name() + "���������дʣ�\n");
        command("walkby " + me->query("id"));
        tell_object(me,HIM + qianwen["doc"] + "\n" + NOR);
        tell_object(me,this_object()->name() + "����˵����" + HIW + qianwen["title"] + NOR + "��" + HIR + qianwen["type"] + NOR + "��\n");
        str = "ǩ�ĺ�����úü��ţ�\n";
        str += HIG + document + NOR;
        tell_object(me,str);
        tell_object(me,"�������" + HIW + arg + NOR + "�����Ϸ����룡\n");
        switch (arg)
        {
                case "��Ե":
                        str = qianwen["love_fate"];
                        break;
                case "��Ե":
                        str = qianwen["love_fate"];
                        break;
                case "����":
                        str = qianwen["love_fate"];
                        break;

                default:
                        
                        command("consider");
                        message_vision("$N����ǩѰ˼���ã���ɫ�������أ�\n",this_object(),me);                     
                        return 1;
                        break;
        }
        command("whisper " + me->query("id") + " about " + str);
        command("smile " + me->query("id"));        

        me->delete_temp("can_answer");
        me->delete_temp("qian");
        destruct(obj);
        return 1;        
}

int accept_object(object me, object ob)
{
        int i;
        string str,file;
        mapping qianwen;
        

        if (ob->query("money_id"))
        {
                if (!me->query_temp("have_gived"))
                {
                        command("say û�¸��Ϸ�Ǯ������Ϸ��ǽл���ô��");
                        return 0;
                }
                if (ob->value() < me->query_temp("have_gived"))
                {
                        command("say �����ǮҲ����Ū�Ϸ򣿵��Ϸ������ô��");
                        return 0;
                }
                command("nod " + me->query("id"));
                command("say ���ӿɽ�Ҳ���Ҹ�֪�Ϸ���������£�");
                str = HIC "��ǩ���ǿ����ʺܺܶ�����ģ�" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "��";
                }
                str += "������������ǩ��\n";
                tell_object(me,str);
                tell_object(me,"����˾͸����Ϸ�(answer ��)\n");
                me->set_temp("can_answer",1);
                me->delete_temp("have_gived");
                destruct(ob);
                return -1;
        }

        if (ob->query("id") != "zhu qian")
        {
                command("say ����ʲô�������Ϸ�Ҫ�����ã�");
                return 0;
        }

        if (!mapp(qianwen = ob->query("qianwen")) ||
            ob->query("owner") != me->query("id"))
        {
                command("haha");
                command("say ���������һ����ǩ��Ҳ����˼����Ū�ң�");
                return 0;
        }

        if (undefinedp(qianwen["id"]) ||
            !intp(qianwen["id"]) ||
            undefinedp(qianwen["title"]) ||
            !stringp(qianwen["title"]) ||
            qianwen["title"] == "" ) 
        {
              
                command("consider");
                message_vision("$N����ǩѰ˼���ã���ɫ�������أ�\n",this_object(),me);
                return -1;
        }

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        if (file_size(file) < 0)
        {
               
                command("consider");
                message_vision("$N����ǩѰ˼���ã���ɫ�������أ�\n",this_object(),me);
                return -1;
        }

        switch (qianwen["type"])
        {
                case "����ǩ":
                case "����ǩ":
                        command("heihei");
                        tell_object(me,"��ǩ���Ƿ�ͬС�ɣ��Ϸ�Ҳ��Ӧй©����������Ը�����ʮ���ƽ��пɿ��ǣ�\n");
                        me->set_temp("have_gived",100000);
                        break;
                default:
                        command("say");
                        tell_object(me,"��ǩ����������ף����ұ���δ�ؾ��ܽ������⣬�������便�������Ը����һƽ�������\n");
                        me->set_temp("have_gived",50000);
                        break;
        }
        me->set_temp("qian",ob);
        return 1;       
}


