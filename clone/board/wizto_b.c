// /clone/board/wizto_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("管理员处理玩家事务公告板", ({ "board" }) );
        set("location", "/d/city/chmiao");
	set("board_id", "wizto_b");
	set("long", "这是一个管理员处理玩家事务的公告留言板，玩家不能留言。\n" );
	setup();
	set("capacity", 500);
}

int do_post(string arg)
{
	if (!wizardp(this_player()))
		return notify_fail("只有巫师才可以在这里留言。\n");

	return ::do_post(arg);
}
void auto_post(string title,string text) {
        mapping note;
        object POSTER;
        if( objectp(POSTER=load_object("/clone/board/wizto_b")) )
        {
                 note=([]);
                 note["title"] = title;;
                 note["author"] = sprintf("%s(%s)",this_player()->query("name"),this_player()->query("id"));
                 note["time"] = time();
                 POSTER->done_post2(this_player(),note,text);
          }
       return;
 }
 void done_post2(object me, mapping note, string text)
{
        mapping *notes;

        note["time"] = time();
        note["msg"] = text;
        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                notes = ({ note });
        else
                notes += ({ note });

        // Truncate the notes if maximum capacity exceeded.
        if( sizeof(notes) > query("capacity") )
                notes = notes[query("capacity")/ 2 .. query("capacity")];

        set("notes", notes);
        save();
        note = copy(note);
        note["msg"] = "来自 " + ::short() + "\n" + text;
        "/clone/board/post_b"->done_post(me, note);
        tell_object(me,"处罚记录已经发布到管理员处理玩家事务公告板。\n");
}
