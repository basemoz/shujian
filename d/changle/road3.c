// Room: /d/changle/road1.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵ����̣����Ŵ�
������������������ǳ����֡���ʱ����������������߷ɳ۶���������
һ·���������ϵ��˸������ž�װ���¼��������еĻ���������ŵ���������
����Щϰ��Ľ����ˡ���·��������������������֡�
LONG
	);

	set("exits", ([
		"southwest" : __DIR__"road1",
               "north" : "/cmds/leitai/bwdh/zongtai",
	]));

	set("outdoors", "���ְ�");
	setup();
}
