// Room: /d/city/guangchangnan.c

inherit ROOM;

void create()
{
	set("short", "�㳡��");
	set("long", @LONG
���ǹ㳡���ϲࡣ�ϱ���һ�Ҵ���̣���ǰ�����������д��һ�������
�������֣���ϸ��������������ѹ�͵��ּۻ��۵��������������ǵ����Ƽ���
������ˡ�
LONG
	);
	set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"dongdajie3",
		"west" : __DIR__"nandajie3",
		"north" : __DIR__"guangchang",
		"south" : __DIR__"dangpu",
	]));
	set("incity",1);
	setup();
}
