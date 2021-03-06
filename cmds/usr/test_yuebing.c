// dig.c

#include <ansi.h>
#define BOOK    "/clone/gift/book"      //书
#define MIC     "/clone/gift/danwan"    //药
#define MON     "/clone/gift/money"     //钱
#define JADE    "/d/zhiye/obj/othermaterial" //玉
#define DAZAO   "/clone/gift/imbue"     //打造机会

int main(object me, string arg)
{
	object *player,gift;
	int i,level,p;
	string str;
			/*
		大智岛上增加随机奖励。
        
		每个带月饼的玩家都可能额外获得，不论战绩，完全随机的，没有月饼的玩家，没有额外奖励。
		每次JOB的1/2玩家随机获得如下奖励中的一项：
		1、200 GOLD存款。
		2、500 EXP。	
		3、一块玉（1-4级随机随机）。
		4、一本技能残篇。
		5、韦兰铁锤。
		
        
		另外：活动期间，每次获得大智岛最后生存者头衔的ID，可以获得一块高级4级玉（密玉/香凝玉）(1/50)。
		但是 4 6 奖励最多获得三次
		*/
	if(arg) return notify_fail("就Test，什么都不要加。\n");
	if(!wizardp(me) ) return notify_fail("这是巫师命令。\n");
	if(me->query("id")!="tangfeng"&& me->query("id")!="linux") return notify_fail("谢谢你来使用。\n");
	player = all_inventory(environment(me));
	p=sizeof(player);
	if(p<2) return notify_fail("人太少了吧。\n");

	for (p = 0; p < sizeof(player); p++) {
		if (!living(player[p]) || !player[p]->query_temp("quest/gift/mid-autumn/yuebing")) continue;

		if(player[p]->query_temp("quest/gift/mid-autumn/yuebing"))
			tell_object(me,HIW"【奖励】开始查看月饼小子"+player[p]->query("name")+"的奖励情况！\n"NOR);

		if(player[p]->query_temp("quest/gift/mid-autumn/yuebing")
			&& random(2))//只有一半人有奖励
		{
			
			//如果胜利者有机会获得一次高级宝玉
			//本人就是吧
			if(player[p]==me && !player[p]->query("quest/gift/mid-autumn/winner") &&!random(150))//这个概率下才能获得
			{
				level=3;
				if(!random(2)) level+=1;//4级的可能性很大
				if(!random(20)) level+=1;//玩家前面已经一个random(50)了，这里还行的话，真的可以中彩了
				gift = new(JADE);
				gift->set_level(level);
				player[p]->add("quest/gift/mid-autumn/winner",1);
				if(player[p]->query("registered")<3)
					log_file("quest/yuebing", sprintf("非VIP %s(%s)获胜因第%d个月饼获得%d级宝玉%s。胜利者终极宝物。\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 level,
												 gift->query("name")) );
				else
					log_file("quest/yuebing", sprintf("VIP %s(%s)获胜因第%d个月饼获得%d级宝玉%s。\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 level,
												 gift->query("name")) );
			}
			//大多数的可能获得这三种奖励，另外特殊礼物必须小于两次
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
					log_file("quest/yuebing", sprintf("非VIP %s(%s)因第%d个月饼获得%s。其中宝物获得%d次。\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 gift->query("name"),
												 player[p]->query("quest/gift/mid-autumn/special")) );
				else
					log_file("quest/yuebing", sprintf("VIP %s(%s)因第%d个月饼获得%s。其中宝物获得%d次。\n", 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 gift->query("name"),
												 player[p]->query("quest/gift/mid-autumn/special")) );
			}
			else
			{
				level=1;
				i = random(2);//最后的倚天屠龙技能残篇没有加入
				if(!random(5)) level+=1;
				if(!random(7)) level+=1;
				if(!random(9)) level+=1;//玉的级别1-4
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
					log_file("quest/yuebing", sprintf(HIR"非VIP %s(%s)因第%d个月饼第%d次获得宝物%s。\n"NOR, 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 player[p]->query("quest/gift/mid-autumn/special"),
												 gift->query("name")) );
				else
					log_file("quest/yuebing", sprintf(HIR"VIP %s(%s)因第%d个月饼第%d次获得宝物%s。\n"NOR, 
				                                 player[p]->name(1),
												 player[p]->query("id"),
												 player[p]->query("quest/gift/mid-autumn/yuebing"),
												 player[p]->query("quest/gift/mid-autumn/special"),
												 gift->query("name")) );
			}
			gift->set("gift_target",player[p]->query("id"));
			gift->set("owner",player[p]->query("id"));
			gift->move(player[p]);
			tell_object(me,HIW"【奖励】月饼小子"+player[p]->query("name")+"获得奖励"+gift->query("name")+HIW"！\n"NOR);

			str="你还意外地获得"+gift->query("name")+"的奖励。\n"NOR;
			tell_object(player[p],str);
		}
		player[p]->delete_temp("quest/gift/mid-autumn/yuebing");//全部去掉标志
		
	}
	return 1;
}
	
int help(object me)
{
	write(@HELP
指令格式 : test
 
 
HELP
    );
    return 1;
}
