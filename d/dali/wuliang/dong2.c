// dong2.c
// bbb 1997/07/16
//COOL@SJ,9808
//tangfeng@SJ,2004

#include <ansi.h>
inherit ROOM;

#define QUESTDIR "quest/�����˲�/"
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR4 "quest/�����˲�/���ɾ�Ԯƪ/"
#define QUESTDIR5 "quest/�����˲�/��������ƪ/"
#define QUESTDIR6 "quest/�����˲�/�书/"

string look_yuxiang();
string look_zi();
string look_shoe();
string look_left();
string look_right();
void dy(object me);

void create()
{
    set("short", "����");
	set("long", @LONG
��ǰͻȻһ����һ����װ��Ů���ֳֳ����������׼��������š�ϸ��֮
�£�ԭ����һ������(yuxiang)������д�������(zi)���ʷ�Ʈ�ݣ����Լ�ǿ
����������д�ɣ��������������ˮ����ˮ������ˮ������ӳ��ʯ���бȵ�һ
��ʯ������������
LONG
	);

	set("exits", ([
		"out" : __DIR__"dong1",
	]));

	set("valid_startroom",1);
	
	set("item_desc",([
		"left"		:	(: look_left :),
		"right"	:		(: look_right :),
		"zi"		:	(: look_zi :),
		"yuxiang"	:	(: look_yuxiang :),

	]));

	setup();
}


void init()
{
	object me;
    me = this_player();
    
    //ͨ�������ɶ���������ͨ������������϶�����ʦ��æ
    if(me->query_condition("killer"))
    {
       message_vision(HIC"\nͻȻ����֪�������ﴫ��һ�������������ﲻ��ӭ$N��\n"NOR,me); 
       tell_object(me,HIR"���ţ���֪����������һֻ��ŷ���һ�ţ�����һ���߷ɳ�ȥ��\n"NOR);
       tell_room(environment(me),HIR"\n��֪����������һֻ��ŷ���һ�ţ���"+ me->name()+ "�߷ɳ�ȥ��\n"NOR, ({ me }));
       if(random(2)) me->move("/d/dali/wuliang/xiaoxi");
       else me->move("/d/xiangyang/conglin3");
       tell_room(environment(me), HIR"\nֻ��"+ me->name()+ "���һ���ɹ�����ˤ�˸�����ʺ����˧Ŷ~~~~~~~~\n"NOR, ({ me }));
       me->start_busy(1);
       return;
    }
	if (me->query(QUESTDIR1+"start") 
	      && !me->query(QUESTDIR1+"wuliangover")
	      && me->query_temp(QUESTDIR1+"jianying")
	      && !me->query_temp(QUESTDIR1+"see_duanyu1"))
    {      
  	  me->start_busy(2);
  	  remove_call_out("dy");
  	  call_out("dy",1,me);
  	}
  	add_action("do_ketou", "ketou");
  	add_action("do_ketou", "kneel");
}
void dy(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) return;
  if(present("duan yu",this_object()))
  {
  	obj=present("duan yu",this_object());
  	destruct(obj); 
  }
  if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& me->query_temp(QUESTDIR1+"jianying") && !me->query_temp(QUESTDIR1+"see_duanyu1"))
  {
      tell_object(me,HIG"\n���������ţ���ǰ��Ȼһ����ʧ������������Ӵ������ǰһ����װ��Ů���ֳֳ����������׼�������š��㶨����ʱ������Ů����\n"
                          "����̬�򷽣�ȴ�Ʋ��ǻ��ˣ����ŵ�������ϸ�������Ƴ�����һ�������ɵ�����������������һ���С������һ������ɫ����\n"
                          "΢΢�������������һ������ӨȻ�й⣬��ʷ������ֵ���һ���������Ժڱ�ʯ��ɣ�ֻ��Խ��Խ����������й����ת��\n"
                          "�����������Ƽ��˻��ˣ��������۹��鶯֮�ʡ� \n"NOR);
     obj=new(__DIR__"npc/dy");
     if(!present("qingnian nanzi",this_object()) && !present("duan yu",this_object()))
            obj->move(environment(me)); 
  }  
}
int do_ketou(string arg)
{      
       int time;
	object me,obj;
	me=this_player();
  if(present("duan yu",this_object())) return 0;

	if( !arg || arg != "yuxiang" ) return 0;
	
	if( arg=="yuxiang" ) {
		message_vision("$N�������ţ��������������������ͷ����\n", this_player());
		if (!me->query_temp(QUESTDIR1+"lbwb/left")|| !me->query_temp(QUESTDIR1+"lbwb/right"))
		{
			tell_object(me,"���������һ��ͷ����ȥ���ƺ�������������(left)���ҽ�(right)������֡� \n");
			return 1; 
		}
		me->add_temp(QUESTDIR1+"ketou_trigger", 1);
	}
	if( me->query_temp(QUESTDIR1+"ketou_trigger")==16 ) {
		me->delete_temp(QUESTDIR1+"lbwb1");
		me->delete_temp(QUESTDIR1+"ketou_trigger");
		if(me->query(QUESTDIR1+"start")
		   &&me->query_temp(QUESTDIR1+"see_duanyu1")
		   &&!me->query(QUESTDIR1+"wuliangover"))
		{
		   message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
                  if(!me->query(QUESTDIR6+"yuxiang"))  log_file("quest/TLBB", sprintf("%s(%s) ���񴦿�ͷ����书��־1�����飺%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
           me->set(QUESTDIR6+"yuxiang",1);
           return 1;	
	     }
		if(me->query(QUESTDIR1+"start")
		   &&me->query(QUESTDIR1+"wuliangover")
		   &&!me->query(QUESTDIR1+"over"))
		{
		   message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
		   tell_object(me,HIG"��Ȼʲô��û�У����̲�ס��ס�ؿ�ͷ���������Ѿ����Ƴտ�\n"NOR);
		   return 1;
		}
		if(me->query(QUESTDIR1+"start")
		   &&me->query(QUESTDIR6+"yuxiang")
		   &&me->query(QUESTDIR1+"over"))
		{
			if(me->query(QUESTDIR6+"pass"))
			{
				message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
				tell_object(me,HIG"����Ȼ�Ѿ��������貨΢���������̲�ס�ص�����������Ѿ����Ƴտ�\n"NOR);
				return 1;
			}

       //����ʱ����һ��
	     if(me->query(QUESTDIR6+"time")&& time()-me->query(QUESTDIR6+"time")<86400)
	     {
		       message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
	         return 1;
		 }
       //by Spiderii@ty �����±��,ֻΪ��ֹ��ǰ��lbwb����ҿ�������fan bojuan
       time = time() - me->query("quest/�����˲�/�书/time");
       if ( me->query("quest/�����˲�/�书/time") && time < 86400 ) 
          {
		       message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
	         return 1;
		 }


       if(present("bo juan",me))
	     {
		       message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
	         return 1;	
		 }
       //�κ��˶������õ��貨΢���ؼ��������ܲ�������ȴֻ�����λ��ᣨ��VIP��
       
       obj=unew("/d/dali/obj/dodge_book");
         if(!clonep(obj)){
		       message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
              return 1;
         }
         if(clonep(obj) && obj->violate_unique()){
            destruct(obj);
		       message_vision("$N���������ϵı����������ѣ��������ֽ�ȥ������ʲôҲû�У������Ѿ���ȡ���ˡ�\n", me);
            return 1;
         } 

	   message_vision(HIR"$N���������ϵı����������ѣ��������ֽ�ȥ���������ʲôҲû�У�$N������������һ�ᣬ��Ȼ�ҳ�һ������\n"NOR, me);
	   log_file("quest/TLBB", sprintf("%s(%s) ���񴦿�ͷ��ò���\n", me->name(1),me->query("id")) );
          obj->set("owner", me->query("id"));//By Spiderii@ty �Ӹ����,��ֹBUG
	   obj->move(me);	
          me->set("quest/�����˲�/�书/time", time()); //�Ӹ����ơ���ֹ������,ֻΪ������ǰ��lbwb����� By Spiderii@ty
	   return 1;
	  }	  
	}
	return 1;
}


string look_left()
{ 
     object me;  
     me=this_player();
     me->set_temp(QUESTDIR1+"lbwb/left",1);
	return
	 HIC"���װٱ飬�������ߡ�\n"NOR;
}

string look_right()
{ 
     object me;  
     me=this_player();
    me->set_temp(QUESTDIR1+"lbwb/right",1);
	return
	HIY"���������������޻ڡ� \n"NOR;
}

string look_zi()
{
	return
	HIW"���������£��˼�����Ҳ -- ��ң��Ϊ��ˮ���顣\n"NOR;
}

string look_yuxiang()
{    
     object me;  
     me=this_player();
     me->set_temp(QUESTDIR1+"lbwb/yuxiang",1); 
  	return
	HIR"����һ�������ɵ�����������һ���С�����ϵ��Ƴ���΢΢�������������һ������ӨȻ�й⣬��ɷ��\n"NOR;
}
