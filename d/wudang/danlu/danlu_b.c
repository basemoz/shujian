// /clone/board/wudang_b.c

inherit BULLETIN_BOARD;

void create()
{
    set_name("制药留言板", ({ "board" }) );
    set("location", "/d/wudang/yaofang");
    set("board_id", "danlu_b");
    set("long", "如遇ＢＵＧ，请写在这。但请不要把药方公布于此，违者严惩！\n" );
	setup();
    set("capacity", 100);
}

