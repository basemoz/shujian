// dig.c

#include <ansi.h>
#define BOOK    "/clone/gift/book"      //��
#define MIC     "/clone/gift/danwan"    //ҩ
#define MON     "/clone/gift/money"     //Ǯ
#define JADE    "/d/zhiye/obj/othermaterial" //��
#define DAZAO   "/clone/gift/imbue"     //�������

int main(object me, string arg)
{
	object *player,gift;
	int i,level,p;
	string str;
			/*
		���ǵ����������������
        
		ÿ�����±�����Ҷ����ܶ����ã�����ս������ȫ����ģ�û���±�����ң�û�ж��⽱����
		ÿ��JOB��1/2������������½����е�һ�
		1��200 GOLD��
		2��500 EXP��	
		3��һ����1-4������������
		4��һ�����ܲ�ƪ��
		5��Τ��������
		
        
		���⣺��ڼ䣬ÿ�λ�ô��ǵ����������ͷ�ε�ID�����Ի��һ��߼�4��������/������(1/50)��
		���� 4 6 �������������
		*/
	if(arg) return notify_fail("��Test��ʲô����Ҫ�ӡ�\n");
	if(!wizardp(me) ) return notify_fail("������ʦ���\n");
	if(me->query("id")!="tangfeng"&& me->query("id")!="linux") return notify_fail("лл����ʹ�á�\n");
	player = all_inventory(environment(me));
	p=sizeof(player);
	if(p<2) return notify_fail("��̫���˰ɡ�\n");

	for (p = 0; p < sizeof(player); p++) {
		if (!living(player[p]) || !player[p]->query_temp("quest/gift/mid-autumn/yuebing")) continue;

		if(player[p]->query_temp("quest/gift/mid-autumn/yuebing"))
			tell_object(me,HIW"����������ʼ�鿴�±�С��"+player[p]->query("name")+"�Ľ��������\n"NOR);

		if(player[p]->query_temp("quest/gift/mid-autumn/yuebing")
			&& random(2))//ֻ��һ�����н���
		{
			
			//���ʤ�����л�����һ�θ߼�����
			//���˾��ǰ�
			if(player[p]==me && !player[p]->query("quest/gift/mid-autumn/winner") &&!random(150))//��������²��ܻ��
			{
				level=3;
				if(!random(2)) level+=1;//4���Ŀ����Ժܴ�
				if(!random(20)) level+=1;//���ǰ���Ѿ�һ��random(50)�ˣ����ﻹ�еĻ�����Ŀ����в���
				gift = new(JADE);
				gift->set_level(level);
				player[p]->add("quest/gift/mid-autumn/winner",1);
				if(player[p]->query("registered")<3)
					log_file("quest/yuebing", sprintf("��VIP %s(%s)��ʤ���%d���±����%d������%s��ʤ�����ռ����\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 level,
												 gift->query("name")) );
				else
					log_file("quest/yuebing", sprintf("VIP %s(%s)��ʤ���%d���±����%d������%s��\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 level,
												 gift->query("name")) );
			}
			//������Ŀ��ܻ�������ֽ��������������������С������
			else if(player[p]->query("quest/gift/mid-autumn/special")>=2|| random(150))
			{
				i=random(3);
				if(random(60))
				{                    
					switch(i)
					{
					case 0: 
						gift = new (BOOK);					
						break;
					case 1: 
						gift = new (MIC);
						if(!random(8)) gift->set("secret_obj",1);
						gift->set("bonus","combat_exp");
						break;
					case 2:         
						gift = new (MON);
						break;
					//default:return;
					}
				}
				else
				{
					gift = new(JADE);
					gift->set_level(1+random(2));
				}
				gift->set("gift_target",player[p]->query("id"));
				gift->set("owner",player[p]->query("id"));
				if(player[p]->query("registered")<3)
					log_file("quest/yuebing", sprintf("��VIP %s(%s)���%d���±����%s�����б�����%d�Ρ�\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 gift->query("name"),
												 player[p]->query("quest/gift/mid-autumn/special")) );
				else
					log_file("quest/yuebing", sprintf("VIP %s(%s)���%d���±����%s�����б�����%d�Ρ�\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 gift->query("name"),
												 player[p]->query("quest/gift/mid-autumn/special")) );
			}
			else
			{
				level=1;
				i = random(2);//���������������ܲ�ƪû�м���
				if(!random(5)) level+=1;
				if(!random(7)) level+=1;
				if(!random(9)) level+=1;//��ļ���1-4
				switch(i)
				{
			    case 0:
					gift = new(DAZAO);
					break;
				case 1:
					gift = new(JADE);
					gift->set_level(level);
					break;
				//default:return;              			
				}
				player[p]->add("quest/gift/mid-autumn/special",1);
				if(player[p]->query("registered")<3)
					log_file("quest/yuebing", sprintf(HIR"��VIP %s(%s)���%d���±���%d�λ�ñ���%s��\n"NOR, 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 player[p]->query("quest/gift/mid-autumn/special"),
												 gift->query("name")) );
				else
					log_file("quest/yuebing", sprintf(HIR"VIP %s(%s)���%d���±���%d�λ�ñ���%s��\n"NOR, 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 player[p]->query("quest/gift/mid-autumn/special"),
												 gift->query("name")) );
			}
			gift->set("gift_target",player[p]->query("id"));
			gift->set("owner",player[p]->query("id"));
			gift->move(player[p]);
			tell_object(me,HIW"���������±�С��"+player[p]->query("name")+"��ý���"+gift->query("name")+HIW"��\n"NOR);

			str="�㻹����ػ��"+gift->query("name")+"�Ľ�����\n"NOR;
			tell_object(player[p],str);
		}
		player[p]->delete_temp("quest/gift/mid-autumn/yuebing");//ȫ��ȥ����־
		
	}
	return 1;
}
	
int help(object me)
{
	write(@HELP
ָ���ʽ : test
 
 
HELP
    );
    return 1;
}
