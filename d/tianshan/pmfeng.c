// Room: /d/tianshan/pmfeng.c
// By Linux

inherit ROOM;

void create()
{
	set("short", "��翷�");
	set("long", @LONG
��������ɽ���壬ɽ�������Ʒ����������켴����ããһƬ���վ�֮����
ԶԶ��ȥ���������ޣ���˽�����翷塣
LONG);
	 set("exits", ([
                "northdown" : __DIR__"dadao1",
		"southdown" : __DIR__"shanjin6",
        ]));        

	set("outdoors", "��ɽ");
	setup();
}
