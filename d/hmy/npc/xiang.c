// xiang.c ������

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("������", ({ "xiang wentian", "xiang", "wentian"}));
        set("long", "ֻ������ò���ݣ����θߴ������������һ�Ի��׳��룬������ǰ��\n"+
		"���ϸ���һ���������ٿ�������ʱ��ȴ���䵶��\n");
        set("title",HIY"������� "HIW"������ʹ"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 2200);
        set("eff_jingli", 2500);
        set("jiali", 100);
        set("combat_exp", 2000000);

        set_skill("finger", 220);
        set_skill("parry", 220);
        set_skill("dodge", 220);
        set_skill("force", 220);
        set_skill("literate", 160);

        set_skill("yiyang-zhi",220);
        set_skill("ding-dodge",220);
        set_skill("huntian-qigong",220);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "yiyang-zhi");
        map_skill("dodge", "ding-dodge");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger", "yiyang-zhi");
        
        set("chat_chance", 3);
        set("chat_msg", ({
		"����������ƺ�������һ��ڣ��������þƣ���\n",
        }));
        setup();

        carry_object(MISC_D("cloth"))->wear();        
}
