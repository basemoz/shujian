#include <ansi.h>

inherit ITEM;

int save_room_file(string yn, string file, string str);
int do_mkroom (string file);
int init_var();
int save_file();
int do_saveroom(string arg);

mapping tmp = ([
  "no_fight"            :       0,
  "no_clean_up"         :       0,
  "valid_startroom"     :       0,
  "file_name"           :       "",
  "short"               :       "",
  "long"                :       "",
  "outdoors"            :       "",
  "g_name"				:		"",
  "hard"				:		"",
  "damage"				:		"",
  "combat_exp"			:		"",
  "skill_lvl"			:		"",
  "item_desc"           :       ([]),
  "exits"               :       ([]),
  "objects"             :       ([]),
]);

string *special_props = ({
        "short", "long", "file_name" });


void create()
{
    set_name(RED "灵牌" NOR, ({ "ling pai", "pai" }) );
    set("long", "这是前任历代帮主的灵牌。相信如果有人毁坏这些灵牌(huiling)，\n"
    	+		"将会被视为本帮的最大仇人。为了保证灵牌的安稳，现任帮主经常希望\n"
    	+		"常希望能够招募更加有力的人手来守卫灵牌(shouling)。\n" );
    set("unit","块");
    set("no_get", "这样做对死人太不尊重了吧？");
    set("no_drop", 1);
    set("no_put", 1);
    set("no_give", 1);      
    set("material", "wood");
    set_weight(1);
    setup();
}

void init()
{
	object me=this_player();
	object env = environment(this_player());
	
	if( me->query_condition("killer")
		 && me->query("g_name")+me->query("g_type") == env->query("g_name") )
	{
	    message_vision(HIY "$N一进总坛，...只听几声大喝，如同炸雷般在大殿里回响。"
            "$N不禁浑身发抖，再也站立不住，腿一软，扑通一声跪了下来。\n\n" NOR, me);
        message_vision(HIY "只听得一声大喝：$N！你在外杀人越货，胡作非为，"
            "现在倒来总坛藏身，岂有此理？！执法弟子何在！\n\n" NOR, me);
        message_vision(HIR "执法弟子一涌而上，乱棒齐下，$N痛得昏了过去......\n" NOR, me);

        me->move("/data/group/zongtan");
        me->unconcious();
	}
	
	
    add_action("do_huiling", "huiling");
    add_action("do_shouling", "shouling");
}

int do_shouling()
{
    object me = this_player();
    object ob;
    object ob1 = environment(me);
	int lvl;

	if( !me->query( "g_level" ) )
		return notify_fail( "你还是先建立了自己的帮派再说吧。\n" );
	if( me->query( "g_name" ) + me->query( "g_type" ) != ob1->query( "g_name" ) )
		return notify_fail( "怎么？替别人招人？\n" );
	if( me->query( "g_level" ) > 1 )
		return notify_fail( "只有帮主才能招募总坛护法。\n" );
	if( me->is_busy() )
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("你等打完架再说吧。\n");
		
	if( me->query( "balance" ) < 2000000 )
		return notify_fail( "你已经没有财力招募高手了。\n" );
		
	if( me->query( "combat_exp" ) * 3 / 2 < ob1->query( "combat_exp" ) )
		return notify_fail( "以你目前的功力，恐怕无法招募到更厉害的总坛护法。\n" );

	message_vision( HIC"$N不惜耗费巨资，想要招募几位武功更加高强的总坛护法。\n"NOR, me );
	
	me->add( "balance", -2000000 );
	me->start_busy( 2 );
	
	if( random(10) < 4 )
	{
		message_vision( HIC"很遗憾，$N没有找到合适的人选。\n"NOR, me );
	}
	else
	{
		message_vision( HIC"成功了，$N找到了两位新的总坛护法，总坛的防御加强了。\n"NOR, me );
		ob1->add("combat_exp", 100000);
		ob1->add("hard",100);
		lvl=ob1->query("skill_lvl");
		if((lvl+10)*(lvl+10)*(lvl+10)<=ob1->query("combat_exp") * 10)
			ob1->add("skill_lvl",10);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    call_out("newhufa",1,ob1);
		do_saveroom("");
	}

	return 1;

}

int newhufa(object ob1)
{
	    new("/data/group/npc/hufa.c")->move(ob1);
	    new("/data/group/npc/hufa.c")->move(ob1);
}

int do_huiling()
{
    object me = this_player();
    object ob;
    object ob1 = environment(me);
    int i;
    
	if( me->is_busy() )
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("你等打完架再说吧。\n");
	if( me->query("g_name") + me->query("g_type") == ob1->query("g_name") )
		return notify_fail("你没有搞错吧？\n");
		    
    message_vision( HIR"$N冷笑一声，走上前去，飞起一脚，正好踢在灵牌上\n"NOR,me);
    
    ob1->add("damage",1);
    if( ob1->query("damage") < 200 )
    {
    	message_vision( HIC"\n灵牌上留下了一个灰扑扑的脚印。\n"NOR,me );
    }
    else if( ob1->query("damage") < 500 )
    {
    	message_vision( HIC"\n灵牌轻轻地晃动了几下。\n"NOR,me );
    }
    else if( ob1->query("damage") < 1000 )
    {
    	message_vision( HIC"\n灵牌猛烈地前后晃动起来。\n"NOR,me );
    }
    else
    {
    	message_vision( HIR"\n灵牌摇摇欲坠，眼看就要倒下了。\n"NOR,me );
    }
    
    if( ob1->query("damage") >= ob1->query("hard") )
    {
    	message_vision( HIY"\n只听得一声巨响，前任历代帮主的灵牌被人捣毁了。\n"NOR,me );
	    message("channel:chat", HIC "【江湖传闻】：" HIR + ob1->query("g_name")
	    	+ HIG "总坛" HIC + "被捣毁了。\n" NOR,users());
	    message("channel:chat", HIC "【江湖传闻】：" HIR + ob1->query("g_name")
	    	+ HIC "人心涣散，被迫解散。\n" NOR,users());
write_file("/log/group",sprintf("%s %s 解散，原因：总坛被捣毁。\n",ctime(time())[4..19],ob1->query("g_name")));
		ob1->set("short", HIR "" + ob1->query("g_name") + HIG "总坛废墟" NOR );
		ob1->set("long", "这里曾经是" + ob1->query("g_name") + "的总坛，但是现在已经被别人捣毁了。\n");
		ob1->delete("combat_exp");
		ob1->delete("skill_lvl");
		ob1->delete("g_name");
		ob1->delete("damage");
		ob1->delete("hard");
		ob1->delete("objects");		
do_saveroom("");

	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("ling pai", ob1) ) )
	    	destruct(ob);
	    	

    	return 1;
    }

	me->start_busy( 4 );
        
    i = 1;
    while( (ob = present("hufa zhanglao "+sprintf("%d",i), ob1) ) )
    {
    	ob->kill_ob(me);
    	i++;
	}
        
    return 1;
}



int save_room_file(string yn, string file, string str)
{
	if( strlen(yn)<1 || yn[0]!='y' )
		return 1;

	if ( write_file(file, str, 1) ) 
	{
	    return 1;
	}
	else 
	{
	    write ("Mudos 尝试写入("+file+")失败!!\n");
		return 0;
	}
}

int init_var ()
{
	tmp["no_fight"]               =       0;
	tmp["no_clean_up"]            =       0;
	tmp["valid_startroom"]        =       0;
	tmp["file_name"]              =       "";
	tmp["short"]                  =       "";
	tmp["long"]                   =       "";
	tmp["outdoors"]               =       "";
	tmp["g_name"]					=		"";
	tmp["hard"]					=		"";
	tmp["damage"]					=		"";
	tmp["combat_exp"]				=		"";
	tmp["skill_lvl"]				=		"";
	tmp["item_desc"]              =       ([]);
	tmp["exits"]                  =       ([]);
	tmp["objects"]                =       ([]);
}


int do_saveroom(string arg)
{
        object env;
        string str, *name, file, pre, suc;
        mapping prop;
        int i;

        env = environment(this_player());
        file = file_name(env) + ".c";

        if (file_size(file) <= 0) return
          notify_fail ("没有这房间的档案: "+file+"\n");

        name = explode (read_file (file), "\n");
        pre = "";
        for (i=0; i<sizeof (name); i++)
          if (strsrch (name[i], "void create") != 0)
            pre += name[i] + "\n";
          else break;
        pre += "void create ()\n{\n";

        i += 2;
        while (name && name[i][0..0] != "}") i++;
        suc = ""; i++;
        while (i<sizeof(name)) suc += name[i++]+"\n";

        prop = env->query_entire_dbase();

        str = pre;
        str = sprintf ("%s  set (\"short\", \"%s\");\n"
               "  set (\"long\", @LONG\n%sLONG);\n\n",
             str, prop["short"], prop["long"]);

        name = keys(prop);
        for(i=0; i<sizeof(name); i++) {
          if( member_array(name[i], special_props)!=-1 ) continue;
          if ( (intp(prop[name[i]]) && prop[name[i]]>0) ||
                (stringp(prop[name[i]]) && prop[name[i]] != "" ) ||
                (mapp(prop[name[i]]) && prop[name[i]] == ([])) ||
                sizeof (prop[name[i]]) > 0)
                    str += sprintf("  set(\"%s\", %O);\n",
                                   name[i], prop[name[i]] );
        }
        if (sizeof (suc) < 5)
         str += "\n  setup();\n}\n";
        else
         str += "\n  setup();\n}\n"+suc;

        return save_room_file("y", file, str);
}
