// Room: /d/meizhuang/jiushi.c
// By Lklv

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������һ����ң�����ƿ�������һ���˱Ǿ��㡣����������˸�ɫ����
�ľƺ���Ͱ����ɫ�ƾߣ��������硣
LONG
	);

	set("exits", ([
		"east" : __DIR__"huilang4",
	]));
	setup();
}