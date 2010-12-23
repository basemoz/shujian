// By Spiderii 加入tb奖励。新人赛1m
inherit NPC;
#include <ansi.h>
#include <mudlib.h>

int ask_clear_divorce();
int ask_gender();
int ask_divorce();
int ask_new_gift();
int ask_new_pks();
int ask_gift();
mixed change_gift(string gift);

void create()
{
        set_name("巫师精灵", ({"fairy"}));
        set("long","一个可爱的小精灵，传说遇到她的人可以实现内心的一些愿望。\n");

        set("gender", "女性");
        set("attitude", "friendly");
        set("age", 18);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 30);
        set("no_quest", 1);
        set("combat_exp", 100000);
        set("inquiry", ([

		  "调整属性" : (: ask_gift :),
                "更改姻缘" : (: ask_clear_divorce :),
                "恢复性别" : (: ask_gender :),
                "离婚"     : (: ask_divorce :),
                "新站礼物" : (: ask_new_gift :),
                "十恶不赦" : (: ask_new_pks :),
        ]));
        carry_object("/clone/misc/cloth")->wear();
        setup();
}
void init()
{
	object me = this_player();
	me->set_temp("exp",me->query("combat_exp"));
	add_action("do_change", "change");
}

int ask_gift()
{
	object me, ob;
	me = this_player(1);
	ob = me->query_temp("link_ob");

	if( !ob )
		return 0;
	while( ob && ob->is_character() )
		ob = ob->query_temp("link_ob");

	if (me->query("gift_changed"))
	{
		command("say 你已经调整过一次属性了，不要贪得无厌嘛。\n");
		return 1;
	}
	if (me->query_temp("gift_change"))
	{
		command("say 别问了，想换就快点换吧。\n");
		return 1;
	}
        if (! me->query("relife/times") )
    	{
	        command("say 您不是转世重修的玩家，不可以调整属性。\n");
	        return 1;
    	}
	command("say 想调整属性呀？倒是不难，转世一次只有一次额外的机会哦，一定要慎重啊！\n");
	write("确定的话请输入您的登陆密码：");

	input_to("check_answer", 1, me, 1);
	return 1;
}

private int check_answer(string passwd, object me)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("password");
	if( crypt(passwd, old_pass)!=old_pass )
	{
		tell_object(me, "密码错误，你放弃了修改属性！\n");
		return;
	}
	command("say 既然你决定了，就请转换你的属性吧。\n");
       command("say 指令格式：change <数值> <欲减属性> to <欲加属性>\n");
	me->set_temp("gift_change",1);
	return 1;
}

int do_change(string arg)
{
	object me = this_player();
	int i;
	string old_gift, new_gift;

	if (!arg || arg == "" || (sscanf(arg, "%d %s to %s", i, old_gift, new_gift) != 3))
		return notify_fail("指令格式：change <数值> <欲减属性> to <欲加属性>\n");
	if (!me->query_temp("gift_change"))
		return notify_fail("不可以随便调整属性！\n");
	if (!change_gift(old_gift) || !change_gift(new_gift))
		return notify_fail("你要调整什么属性？\n");
	if (i < 1)
		return notify_fail("你要调整几点属性？\n");
	if (me->query(change_gift(old_gift)) - i < 10 || me->query(change_gift(new_gift)) + i >30)
		return notify_fail("这么极端？太狠了点把？\n");
	me->add(change_gift(old_gift),-i);
    	me->add(change_gift(new_gift),i);
    	me->set("gift_changed",1);
    	if (INTERMUD_MUD_NAME == "SHTX")
                return notify_fail(HIR"属性调整完毕！此次调整共转换" + chinese_number(i) + "点"
                      + old_gift + "为" + new_gift + "。\n"NOR);
	me->setup();
	log_file("quest/gift_change", sprintf("[%s] %s转换%d点%s为%s.\n",
           	ctime(time())[0..15], geteuid(this_player(1)), i, old_gift, new_gift));
	return notify_fail(HIR"属性调整完毕！此次调整共转换" + chinese_number(i) + "点" + old_gift + "为" + new_gift +
	"。\n"NOR);
}

mixed change_gift(string gift)
{
	if (gift == "臂力")
		return "str";
	if (gift == "根骨")
		return "con";
	if (gift == "身法")
		return "dex";
	if (gift == "悟性")
		return "int";
	return 0;
}



int ask_clear_divorce()
{
        int exp;
        object me = this_player();
        if (!me->query("divorce"))
        {
                command("say 你好像并没有离婚过吧？\n");
                return 1;
        }
        exp = me->query("combat_exp") * me->query("divorce") * 5 / 1000;
        if (exp > 300000)
                exp = 300000;
        command("say 如果想清除离婚记录，你将要被惩罚" + chinese_number(exp) + "点经验。\n");
        command("say 你确定要清除离婚记录吗(yes or no)?");
        input_to("confirm_clear_divorce", 1, me, exp);
        return 1;
}

int confirm_clear_divorce(string arg, object me, int exp)
{
        if (arg != "yes")
        {
                write("你放弃了清除离婚记录的想法。\n");
                return 1;
        }
        command("say 好吧，既然你决定了，我就帮你清除掉吧，以后记得要专一啊。\n");
        command("sigh " + me->query("id"));
        command("lover fairy");
        log_file("quest/clear_divorce", sprintf("[%s] %s清除离婚记录%d次，减少经验%d点.\n",
                ctime(time())[0..15], geteuid(this_player(1)), me->query("divorce"), exp));
        me->delete("divorce");
        me->add("combat_exp", -exp);
        me->setup();
        write(HIR"离婚记录清除完毕！共减少经验" + chinese_number(exp) + "点。\n"NOR);
        return 1;
}

int ask_gender()
{
        int exp;
        object me = this_player();
        if (me->query("gender") != "无性")
        {
                command("say 你身体十分健全，难道是脑子出了问题？\n");
                return 1;
        }
        exp = me->query("combat_exp");
        if (exp < 100000)
        {
                command("say 你经验太少了，高点再来吧。\n");
                return 1;
        }
        exp = exp * 5 / 100;
        if (exp > 300000)
                exp = 300000;
        command("say 如果想恢复性别，你将要被惩罚" + chinese_number(exp) + "点经验。\n");
        command("say 你确定要恢复性别吗(yes or no)?");
        input_to("confirm_gender", 1, me, exp);
        return 1;
}

int confirm_gender(string arg, object me, int exp)
{
        if (arg != "yes")
        {
                write("你放弃了恢复性别的想法。\n");
                return 1;
        }
        command("say 好吧，既然你决定了，我就帮你恢复吧，这种法术难度是非常大的，唉。\n");
        command("poor fairy");
        command("sweat fairy");
        me->delete_skill("pixie-jian");
        me->set("class", me->query("class_old"));
        me->set("gender", "男性");
        me->add("combat_exp", -exp);
        me->setup();
        log_file("quest/clear_divorce", sprintf("[%s] %s恢复性别为男性，减少经验%d点.\n",
                ctime(time())[0..15], geteuid(this_player(1)), exp));
        write(HIR"性别恢复完毕！共减少经验" + chinese_number(exp) + "点。\n"NOR);
        return 1;
}

int ask_divorce()
{
        object me = this_player();
        string id = me->query("marry/id");
        int last_on = FINGER_D->get_last_on(id);

        if (!me->query("marry"))
        {
                command("say 你没有结婚，来问什么？\n");
                return 1;
        }
        if (!last_on)
        {
                command("say 你的" + (me->query("gender") == "男性"?"娇妻":"夫君") + "呢？\n");
                return 1;
        }
        if ((time() - last_on) / 86400 < 30)
        {
                command("say 你的" + (me->query("gender") == "男性"?"娇妻":"夫君") + "最近才登陆过，这样不好吧？\n");
                return 1;
        }
        command("say 你真的想离婚吗(yes or no)?");
        input_to("confirm_divorce", 1, me);
        return 1;
}

int confirm_divorce(string arg, object me)
{
        if (arg != "yes")
        {
                write("你放弃了离婚的想法。\n");
                return 1;
        }
        command("say 好吧，既然你决定了，我就成全你吧。\n");
        command("sigh " + me->query("id"));
        command("lover fairy");
        me->delete("marry");
        me->add("divorce", 1);
        return 1;
}

int ask_new_gift()
{
        object me = this_player();
        

        if (me->query("ty_gift") )
        {
                command("say 你不是领了吗？\n");
                return 1;
        }
        if (me->query("combat_exp") < 1500000 )
        {
                command("say 你还是等经验高点再来吧。\n");
                command("addoil " + me->query("id"));
                return 1;
        }

        if ( me->query("combat_exp") >= 1500000 )
        {
                me->add("balance", 5000000);
                me->set("ty_gift", 1);
        }
        command("say 好吧，就给你一份巫师的祝福吧。\n");
        command("addoil " + me->query("id"));
        return 1;
}
int ask_new_pks()
{
        object me = this_player();
        

        if (me->query("ty_pks") )
        {
                command("say 你不已经是恶人了么？\n");
                return 1;
        }
            if ((int)me->query_skill("jiuyin-baiguzhua",1) < 1)
        {
                command("say 你还没研究九阴真经下卷武学。\n");
                command("addoil " + me->query("id"));
                return 1;
        }

            if ((int)me->query_skill("jiuyin-baiguzhua",1) > 1 )
        {
                me->add("PKS", 50);
                me->set("ty_pks", 1);
        }
        command("say 好吧，你去做恶人去吧。\n");
        command("sigh " + me->query("id"));
        return 1;
}
