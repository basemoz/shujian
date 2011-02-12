// chuansong_fu.c

#include <ansi.h>

inherit ITEM;

static mapping address = ([
	"武馆":		"/d/xiangyang/damen",
	"wg":		"/d/xiangyang/damen",
	"wuguan":	"/d/xiangyang/damen",
	"桃花岛":	"/d/thd/jicui",
	"thd":		"/d/thd/jicui",
	"taohuadao":"/d/thd/jicui",
	"华山":		"/d/huashan/zhengqi",
	"hs":		"/d/huashan/zhengqi",
	"huashan":	"/d/huashan/zhengqi",
	"少林":		"/d/shaolin/pingtai",
	"sl":		"/d/shaolin/pingtai",
	"shaolin":	"/d/shaolin/pingtai",
	"星宿":		"/d/xingxiu/xxh",
	"xx":		"/d/xingxiu/xxh",
	"xingxiu":	"/d/xingxiu/xxh",
	"嵩山":		"/d/songshan/damen",
	"ss":		"/d/songshan/damen",
	"songshan":	"/d/songshan/damen",
	"武当":		"/d/wudang/sanqing",
	"wd":		"/d/wudang/sanqing",
	"wudang":	"/d/wudang/sanqing",
	"峨嵋":		"/d/emei/houdian",
	"em":		"/d/emei/houdian",
	"emei":		"/d/emei/houdian",
	"明教":		"/d/mingjiao/jyt",
	"mj":		"/d/mingjiao/jyt",
	"mingjiao":	"/d/mingjiao/jyt",
	"丐帮":		"/d/gb/pomiao",
	"gb":		"/d/gb/pomiao",
	"gaibang":	"/d/gb/pomiao",
	"古墓":		"/d/gumu/jqg/wshi",
	"gm":		"/d/gumu/jqg/wshi",
	"gumu":		"/d/gumu/jqg/wshi",
	"慕容":		"/d/mr/yanziwu/yanziwu",
	"mr":		"/d/mr/yanziwu/yanziwu",
	"murong":	"/d/mr/yanziwu/yanziwu",
	"铁掌":		"/d/tiezhang/wztang",
	"tz":		"/d/tiezhang/wztang",
	"tiezhang":	"/d/tiezhang/wztang",
	"神龙岛":	"/d/sld/dukou",
	"sld":		"/d/sld/dukou",
	"shenlongdao":	"/d/sld/dukou",
	"天龙寺":	"/d/dali/shanhou",
	"tls":		"/d/dali/shanhou",
	"tianlongsi":	"/d/dali/shanhou",
	"昆仑":		"/d/kunlun/guangchang",
	"kl":		"/d/kunlun/guangchang",
	"kunlun":	"/d/kunlun/guangchang",
	"雪山":		"/d/xueshan/guangchang",
	"xs":		"/d/xueshan/guangchang",
	"sueshan":	"/d/xueshan/guangchang",
	"扬州":		"/d/city/kedian",
	"yz":		"/d/city/kedian",
	"yangzhou":	"/d/city/kedian",
	"杭州":		"/d/hz/yuewangmiao",
	"hz":		"/d/hz/yuewangmiao",
	"hangzhou":	"/d/hz/yuewangmiao",
	"苏州":		"/d/suzhou/beidajie1",
	"sz":		"/d/suzhou/beidajie1",
	"suzhou":	"/d/suzhou/beidajie1",
	"嘉兴":		"/d/jiaxing/jiaxing",
	"jx":		"/d/jiaxing/jiaxing",
	"jiaxing":	"/d/jiaxing/jiaxing",
	"长安":		"/d/changan/zhonglou",
	"ca":		"/d/changan/zhonglou",
	"changan":	"/d/changan/zhonglou",
	"成都":		"/d/chengdu/center",
	"cd":		"/d/chengdu/center",
	"chengdu":	"/d/chengdu/center",
	"大理":		"/d/dali/kedian",
	"dl":		"/d/dali/kedian",
	"dali":		"/d/dali/kedian",
	"佛山":		"/d/foshan/guangchang",
	"fs":		"/d/foshan/guangchang",
	"foshan":	"/d/foshan/guangchang	",
	"福州":		"/d/fuzhou/zhongxin",
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
	set_name(HIY "传送符" NOR, ({"chuansong fu","fu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
		"一张黄灿灿的符，看上去金光闪闪，隐隐可见有烟雾在其上缭绕。\n"
		"你心中一动，这符似乎可以带你去任何地方。\n");
		set("value", 100);
		set("unit", "张");
	}
}

int do_fly(string arg)
{
	object me = this_player();
	object ob, where;
	string dest;

	if (!arg || arg == "")
		return notify_fail("你想传送到哪儿?\n");

	// 先判断是不是地名
	dest = address[arg];

	// 如果不是地名，判断是不是人名
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

	// 如果不是地名或人名，当作特殊地址来处理
	if (!dest)
		dest = arg;
	
	message_vision(HIG "$N将一张"
	+name()+
	HIG "贴在脑门上，口中念念有词，忽然一阵烟雾涌起，$N消失不见了。\n"
	NOR,me);

	return me->move(dest);
}

int do_roar(string arg)
{
	object me = this_player();
	object env;
	object ob;
	int	i, count = 0;

	// 判断是不是针对特点的人发出狮子吼
	if (arg)
	{
		ob = present(arg, environment(me));
		if (!ob || !living(ob))
			return notify_fail("你要对谁使用狮子吼?\n");
		
		message_vision(HIR "$N对着$n阴阴地一笑，嘴里念念有词，$n只觉得天旋地转，站立不稳，昏倒在地。\n"
			NOR,me, ob);
		ob->unconcious();
		return 1;
	}
	
	// 先统计这一声狮子吼能把多少人吼晕，显示不同的信息
	env = environment(me);
	foreach (ob in all_inventory(env))
	{
		if(!ob || ob == me || !living(ob))
			continue;
		
		count++;
	}
	
	if (count > 0)
	{
		message_vision(HIR "$N将一张"
			+name()+
			HIR "贴在脑门上，猛然发出一声惊天动地的大喝，风云为之变色，周围众人立足不稳，纷纷昏倒在地。\n"
			NOR,me);

		// 让活着的生物晕倒
		foreach (ob in all_inventory(env))
		{
			if(!ob || ob == me || !living(ob))
				continue;
			
			ob->unconcious(); 
		}
	}
	else
	{
		message_vision(HIB "$N将一张"
			+name()+
			HIB "贴在脑门上，猛然发出一声惊天动地的大喝，四野空旷，空山回音。\n"
			NOR,me);
	}

	return 1;
}

