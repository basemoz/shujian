// by lane@狗熊

#include <ansi.h>
inherit F_CLEAN_UP;

int sort_skill(string file)
{
	int i;
	if ( file[<2..<1] != ".c" ) return 0;
	if ( !sscanf(file, "%*s.c") )  return 0;
	if ( sscanf(file, "%*s_noshow.c") )  return 0;
	i = strlen(file);
	while(i--){
		if( file[i] == '.' ) continue;
		if( file[i] < 'a' || file[i] > 'z' )
			return 0;
	}

	return 1;
}

int sort_skill2(string sk) 
{
	return (SKILL_D(sk)->type() == "knowledge" && SKILL_D(sk)->type2() == "music");
}

int check_music(object me)
{
	int i, j, k;
	mapping music;

	music = me->query("music");
	if( !mapp(music) ) music = ([]);
	if( !arrayp(keys(music)) ) return 1;
	k = sizeof(keys(music));

	if( k > 0 ) {
		for( i=0; i < k; i++ ) {
			if( file_size("/d/music/book/"+keys(music)[i]+".c") < 0 ) {
				tell_object(me, HIY"你发现自己忘记了一首经典的乐谱。\n"NOR);
				me->delete("music/"+keys(music)[i]);
				return;
			}

			if( wizardp(me) ) tell_object(me, HIY"你的("+keys(music)[i]+")熟练度为："+me->query("music/"+keys(music)[i] )+"，学习时间为："+me->query("music_time/"+keys(music)[i] )+"，现在时间为："+time()+"。\n"NOR);

			if( !me->query("music_time/"+keys(music)[i] ) )
				me->set("music_time/"+keys(music)[i], time() );

// 鄙视 yeju@SJ 要求每天减熟练度 5 点 buy lane@none

			if( ( j = ( time() - me->query("music_time/"+keys(music)[i]) ) / 86400 ) >= 1 ) {
				me->add("music_time/"+keys(music)[i], j*86400 );
				if( wizardp(me) ) tell_object(me, HIY"你的("+keys(music)[i]+")熟练度下降了"+j*5+"点。\n"NOR);
				me->add("music/"+keys(music)[i], -j*5 );
				if( me->query("music/"+keys(music)[i]) < 1 )
					me->set("music/"+keys(music)[i], 0);
			}
		}
	} else return;

	return;
}

int main(object me,string arg)
{
	object ob;
	mapping book;
	mapping skl, lrn, map;
        
	string *sname, *mapped, *allskills, str = "", str2 = "", bname;
	int i, j, k, n;
	seteuid(getuid());

	if( !arg ) ob = me;
	else {
		ob = present(arg, environment(me));
		if( !ob ) ob = find_player(arg);
		if( !ob ) ob = find_living(arg);
		if( !ob ) ob = LOGIN_D->find_body(arg);
		if( !ob || !me->visible(ob) ) return notify_fail("你要察看谁的技能？\n");
		if( wiz_level(me) < wiz_level(ob) ) return notify_fail("你要察看谁的状态？\n");
	}

	skl = ob->query_skills();
	map = ob->query_skill_map();
	if( mapp(map) ) mapped = values(map);
	if( !mapped ) mapped = ({});
	
	lrn = ob->query_learned();
	if( !mapp(lrn) ) lrn = ([]);
	
	allskills  = sort_array( keys(skl), (: strcmp :) );	
	
	sname  = filter_array( allskills, (: sort_skill2 :) );
	allskills -= sname;
	j = sizeof(sname);

	if( j > 0 ) {
		str = HIW"【";
		str += (ob==me?"你":ob->name(1))+"的乐理技能表】"NOR"：\n";	
		str += "┌────────────────────────────────────────────┐\n";
		str += sprintf("%-90s", "│总共"+chinese_number(j)+"项技能");
		for(i=0; i < j; i++) {
			if( i % 2 == 0 ) str += "│\n│";
			else str += "  ";
			str += sprintf("%s%-8s%-14s"HIC"→"NOR"%s %3d/%6d",
				(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
				to_chinese(sname[i]), "(" + sname[i] + ")",
				"/cmds/skill/skills.c"->skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
				skl[sname[i]], (int)lrn[sname[i]],);
			if( i > j-2 && i % 2 == 0 )
				str +="                                             ";
		}
		str += "│\n└────────────────────────────────────────────┘\n";
	}
	else
		str += HIW+" "+(ob==me ? "你" : ob->name(1)) + "目前并没有学会任何乐理技能。\n"NOR;
	write (str);		       

// 乐谱标记为 (music/***)
	check_music(ob);

	book = ob->query("music");
	if( !mapp(book) ) book = ([]);
	if( !arrayp(keys(book)) ) return 1;
	k = sizeof(keys(book));

	if( k <= 0 ) str2 = HIW+" "+(ob==me ? "你" : ob->name(1))+"目前尚不会弹奏任何乐谱。\n"+NOR;

	else {
		str2 = HIW+"【"+(ob==me ? "你" : ob->name(1))+"目前熟练弹奏的乐谱有】"+NOR;
		str2 += "\n┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";

		for( i=0; i < k; i++ ) {
			if( file_size("/d/music/book/"+keys(book)[i]+".c") < 0 ) {
				if( wizardp(ob) ) tell_object(ob, HIY"你发现自己忘记了一首经典的乐谱("+keys(book)[i]+")。\n"NOR);
				ob->delete("music/"+keys(book)[i]);
				return;
			}
			bname = call_other("/d/music/book/" + keys(book)[i], "book_name");
			if( !bname ) bname = "无名曲";
			bname = "『"+bname+"』("+YEL+keys(book)[i]+NOR+")";
			str2 += sprintf(" %-58s", bname);

// 熟练度 10点为1个等级，10个等级封顶
// 如果熟练度 = 0 在使用时候显示 忘记
			n = ( ob->query("music/"+keys(book)[i]) + 9 ) / 10;
			if( n  < 1 ) str2 += HBRED"长期缺乏练习\n"NOR;
			if( n == 1 ) str2 += HBRED"☆\n"NOR;
			if( n == 2 ) str2 += HBRED"☆☆\n"NOR;
			if( n == 3 ) str2 += HBRED"☆☆☆\n"NOR;
			if( n == 4 ) str2 += HBRED"☆☆☆☆\n"NOR;
			if( n == 5 ) str2 += HBRED"☆☆☆☆☆\n"NOR;
			if( n == 6 ) str2 += HBRED"★☆☆☆☆\n"NOR;
			if( n == 7 ) str2 += HBRED"★★☆☆☆\n"NOR;
			if( n == 8 ) str2 += HBRED"★★★☆☆\n"NOR;
			if( n == 9 ) str2 += HBRED"★★★★☆\n"NOR;
			if( n >  9 ) str2 += HBRED"★★★★★\n"NOR;
		}
		str2 += "┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";
	}

	write( str2 );	
	return 1;
}

int help(object me)
{
	string *file,	str, bname;
	int i, j=0;

	file = get_dir("/d/music/book/");

	if( sizeof(file) > 0 ) {
		file  = filter_array(file, (: sort_skill :) );
		j = sizeof(file);
	}



	if( j > 0 ) {
		str = "\n┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n";
		for( i=0; i < j; i++ ) {
			bname = call_other("/d/music/book/" + file[i], "book_name");
			if( bname ) str += " 『"+bname+"』";
			else str +=" 『无名曲』";
			str += "("+YEL+replace_string(file[i], ".c", "")+NOR+")\n";
		}
	}

write(@HELP
指令格式 : music
这个指令可以让你显示目前的乐理技能等级和已经学会的弹奏乐谱。
目前开放的乐谱有：
HELP);
		write(str);
		write("┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n");

	return 1;
}