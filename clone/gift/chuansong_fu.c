// chuansong_fu.c

#include <ansi.h>

inherit ITEM;

static mapping address = ([
	"���":		"/d/xiangyang/damen",
	"wg":		"/d/xiangyang/damen",
	"wuguan":	"/d/xiangyang/damen",
	"�һ���":	"/d/thd/jicui",
	"thd":		"/d/thd/jicui",
	"taohuadao":"/d/thd/jicui",
	"��ɽ":		"/d/huashan/zhengqi",
	"hs":		"/d/huashan/zhengqi",
	"huashan":	"/d/huashan/zhengqi",
	"����":		"/d/shaolin/pingtai",
	"sl":		"/d/shaolin/pingtai",
	"shaolin":	"/d/shaolin/pingtai",
	"����":		"/d/xingxiu/xxh",
	"xx":		"/d/xingxiu/xxh",
	"xingxiu":	"/d/xingxiu/xxh",
	"��ɽ":		"/d/songshan/damen",
	"ss":		"/d/songshan/damen",
	"songshan":	"/d/songshan/damen",
	"�䵱":		"/d/wudang/sanqing",
	"wd":		"/d/wudang/sanqing",
	"wudang":	"/d/wudang/sanqing",
	"����":		"/d/emei/houdian",
	"em":		"/d/emei/houdian",
	"emei":		"/d/emei/houdian",
	"����":		"/d/mingjiao/jyt",
	"mj":		"/d/mingjiao/jyt",
	"mingjiao":	"/d/mingjiao/jyt",
	"ؤ��":		"/d/gb/pomiao",
	"gb":		"/d/gb/pomiao",
	"gaibang":	"/d/gb/pomiao",
	"��Ĺ":		"/d/gumu/jqg/wshi",
	"gm":		"/d/gumu/jqg/wshi",
	"gumu":		"/d/gumu/jqg/wshi",
	"Ľ��":		"/d/mr/yanziwu/yanziwu",
	"mr":		"/d/mr/yanziwu/yanziwu",
	"murong":	"/d/mr/yanziwu/yanziwu",
	"����":		"/d/tiezhang/wztang",
	"tz":		"/d/tiezhang/wztang",
	"tiezhang":	"/d/tiezhang/wztang",
	"������":	"/d/sld/dukou",
	"sld":		"/d/sld/dukou",
	"shenlongdao":	"/d/sld/dukou",
	"������":	"/d/dali/shanhou",
	"tls":		"/d/dali/shanhou",
	"tianlongsi":	"/d/dali/shanhou",
	"����":		"/d/kunlun/guangchang",
	"kl":		"/d/kunlun/guangchang",
	"kunlun":	"/d/kunlun/guangchang",
	"ѩɽ":		"/d/xueshan/guangchang",
	"xs":		"/d/xueshan/guangchang",
	"sueshan":	"/d/xueshan/guangchang",
	"����":		"/d/city/kedian",
	"yz":		"/d/city/kedian",
	"yangzhou":	"/d/city/kedian",
	"����":		"/d/hz/yuewangmiao",
	"hz":		"/d/hz/yuewangmiao",
	"hangzhou":	"/d/hz/yuewangmiao",
	"����":		"/d/suzhou/beidajie1",
	"sz":		"/d/suzhou/beidajie1",
	"suzhou":	"/d/suzhou/beidajie1",
	"����":		"/d/jiaxing/jiaxing",
	"jx":		"/d/jiaxing/jiaxing",
	"jiaxing":	"/d/jiaxing/jiaxing",
	"����":		"/d/changan/zhonglou",
	"ca":		"/d/changan/zhonglou",
	"changan":	"/d/changan/zhonglou",
	"�ɶ�":		"/d/chengdu/center",
	"cd":		"/d/chengdu/center",
	"chengdu":	"/d/chengdu/center",
	"����":		"/d/dali/kedian",
	"dl":		"/d/dali/kedian",
	"dali":		"/d/dali/kedian",
	"��ɽ":		"/d/foshan/guangchang",
	"fs":		"/d/foshan/guangchang",
	"foshan":	"/d/foshan/guangchang	",
	"����":		"/d/fuzhou/zhongxin",
	"fz":		"/d/fuzhou/zhongxin",
	"fuzhou":	"/d/fuzhou/zhongxin",
	"attack":		"zzzzzz",
	"attack":		"zzzzzz",
	"attack":	"zzzzzz",

]);

void init()
{
	if (environment() == this_player()) {
		add_action("do_fly", "fly");
		add_action("do_roar", "roar");
	}
}

void create()
{
	set_name(HIY "���ͷ�" NOR, ({"chuansong fu","fu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"һ�ŻƲӲӵķ�������ȥ��������������ɼ����������������ơ�\n"
		"������һ��������ƺ����Դ���ȥ�κεط���\n");
		set("value", 100);
		set("unit", "��");
	}
}

int do_fly(string arg)
{
	object me = this_player();
	object ob, where;
	string dest;

	if (!arg || arg == "")
		return notify_fail("���봫�͵��Ķ�?\n");

	// ���ж��ǲ��ǵ���
	dest = address[arg];

	// ������ǵ������ж��ǲ�������
	if (!dest)
	{
		ob = find_player(arg);
		if (!ob)
			ob = find_living(arg);
		if (ob)
			where = environment(ob);
		if (where)
			dest = (string)file_name(where);
	}

	// ������ǵ��������������������ַ������
	if (!dest)
		dest = arg;
	
	message_vision(HIG "$N��һ��"
	+name()+
	HIG "���������ϣ����������дʣ���Ȼһ������ӿ��$N��ʧ�����ˡ�\n"
	NOR,me);

	return me->move(dest);
}

int do_roar(string arg)
{
	object me = this_player();
	object env;
	object ob;
	int	i, count = 0;

	// �ж��ǲ�������ص���˷���ʨ�Ӻ�
	if (arg)
	{
		ob = present(arg, environment(me));
		if (!ob || !living(ob))
			return notify_fail("��Ҫ��˭ʹ��ʨ�Ӻ�?\n");
		
		message_vision(HIR "$N����$n������һЦ�����������дʣ�$nֻ����������ת��վ�����ȣ��赹�ڵء�\n"
			NOR,me, ob);
		ob->unconcious();
		return 1;
	}
	
	// ��ͳ����һ��ʨ�Ӻ��ܰѶ����˺��Σ���ʾ��ͬ����Ϣ
	env = environment(me);
	foreach (ob in all_inventory(env))
	{
		if(!ob || ob == me || !living(ob))
			continue;
		
		count++;
	}
	
	if (count > 0)
	{
		message_vision(HIR "$N��һ��"
			+name()+
			HIR "���������ϣ���Ȼ����һ�����춯�صĴ�ȣ�����Ϊ֮��ɫ����Χ�������㲻�ȣ��׷׻赹�ڵء�\n"
			NOR,me);

		// �û��ŵ������ε�
		foreach (ob in all_inventory(env))
		{
			if(!ob || ob == me || !living(ob))
				continue;
			
			ob->unconcious(); 
		}
	}
	else
	{
		message_vision(HIB "$N��һ��"
			+name()+
			HIB "���������ϣ���Ȼ����һ�����춯�صĴ�ȣ���Ұ�տ�����ɽ������\n"
			NOR,me);
	}

	return 1;
}

