// glist.c  �����б�
// by augx@sj 4/11/2002
//modified by tangfeng@sj 8/7/2004

#include <ansi.h>
inherit F_CLEAN_UP;
#include <mudlib.h>

#if !defined(GROUP_D)
#define GROUP_D   "/adm/daemons/groupd"
#endif

int main(object me, string arg)
{
	mapping * groups, mp;
	mapping gmembers;
	string gid;
	string * sv, * sk, * option;
	object ob;
	int i,j,k,p=0;
  int opt_long,opt_inter;
  
  if( me->query_temp("command_busy"))
		return notify_fail("����æ���ء�\n");

	if(!arg )
	{
  	write("\n�� "+CHINESE_MUD_NAME+"("+INTERMUD_MUD_NAME+") �������а�\n");
	  write("�������ө������������ө��������ө������������������ө������ө������ө������ө��������ө���������\n");
	  write("��������  ��������  �����ɱ�ʶ��      ��  ��      ����������ʵ  ������  ������ǰվ�㩦Ǩ��վ�㩧\n");
	  write("�ĩ����ة������������ة��������ة������������������ة������ة������ة������ة��������ة���������\n");

	  groups = GROUP_D->get_sort_group();
	  for(i=0;i<sizeof(groups);i++) {
		  mp = GROUP_D->get_group(groups[i]["id"]);
		  write( sprintf("��%-4i  %-12s  %-8s  %-18s  %2i(%2i)  %-6i  %-6i  %-8s  %-8s��\n",
			  i+1,mp["name"],groups[i]["id"],mp["master1_name"]+"("+mp["master1"]+")",mp["members"],mp["max_members"],mp["power"],mp["score"],mp["site"],mp["site_next"]) );
	  }

	  write("������������������������������������������������������������������������������������������������\n");
	  write("��ǰ�վ�㲻�Ǳ�վ�İ��ɵ�ͳ������ÿ���糿����һ�Ρ�\n");
	  return 1;
	}
	else
	{
    //����who.c@sj
	  option = explode(arg, " ");
	  option -= ({ "" });	
	  //�������˼�ǣ�
	  i = sizeof(option);
	  while( i-- )
			switch(option[i]) {
				case "-l": opt_long = 1; break;
				case "-!": opt_inter = 1; break;
				default:
        /*
        //���Ǻ��˽���������
					if( option[i][0]=='@' ) {
						notify_fail("��·���鲢û�б����롣\n");
						if (find_object(DNS_MASTER) && RWHO_Q->send_rwho_q(option[i][1..<1],
							me, opt_long & wizardp(me), opt_inter)) {
							// ֻ����ʦ������ who @xx -l��Yu Jue@SJ 19990624
							write("����ѶϢ���ͳ������Ժ�\n");
							return 1;
						}
						return 0;
					}
        */
          if(!option[i])
		        return notify_fail("û��˵����Ҫ��ѯ�İ������ƣ�\n");	      
	        if( !GROUP_D->site_now(gid=option[i]) )
		        return notify_fail( GROUP_D->get_last_error() );
	        if( !(gmembers = GROUP_D->get_group(gid,2)) )
		        return notify_fail("û��������ɻ��߲������ô���\n");	      
			}
	  }
 
  	sk = keys(gmembers);
  	sv = values(gmembers);
    if (opt_inter)
    	write("\n�� "+CHINESE_MUD_NAME+"("+INTERMUD_MUD_NAME+") "+GROUP_D->get_group_name(gid)+"��Ա��("+HIG"��ɫ��ʾ�������ߡ�"NOR+")\n");
    else 
    	write("\n�� "+CHINESE_MUD_NAME+"("+INTERMUD_MUD_NAME+") "+GROUP_D->get_group_name(gid)+"���߳�Ա"NOR+"\n"); 
  	write("��������������������������������������������������������������������������������������������\n");
  
    if (opt_long)
    {
      j = sizeof(gmembers);		
	    for(i=0;i<j;i++) {
		     write("��");
  	     if(find_player(sk[i])) p++;
		     if(opt_inter && !(ob=find_player(sk[i]))) continue;
		     write( sprintf("%12s%s%s\n",GROUP_D->get_member_class(sk[i]),find_player(sk[i])?	HIG"*"NOR:" ",ob->short(1)));
		     //�����Լ�������Ҫ��ʾ�����ݣ�������ʾ���ɵļ��𣬰����򸱰���
		     write("��\n");		
		  }
	    if(p=0 && opt_inter)
      {
        write(HIG+GROUP_D->get_group_name(gid)+"�����ܹ��г�Ա"+chinese_number(j)+"��;ȴ�������ߣ�\n");
   	    write("��������������������������������������������������������������������������������������������\n");
      }
      else  
	    {
	      write("��������������������������������������������������������������������������������������������\n");
	      write(HIG+GROUP_D->get_group_name(gid)+"�����ܹ��г�Ա"+chinese_number(j)+"��;"+chinese_number(p)+"���ߣ�\n");
      } 
    }
    else 
    {
	    j = sizeof(gmembers);
	    for(i=0,k=1;i<j;i++) {
		    if( k == 1 ) write("��");
		    if(find_player(sk[i])) p++;
		    if(opt_inter && !(ob=find_player(sk[i]))) continue;
		    write( sprintf("  %-18s  ",(find_player(sk[i])?HIG:NOR)+sv[i]+"("+capitalize(sk[i])+")"+NOR) );
		    k++;
		    if( k > 4 ) {
			     write("��\n");
			     k = 1;
		    }
	   }
     if(p=0 && opt_inter)
     {
        write(HIG+GROUP_D->get_group_name(gid)+"�����ܹ��г�Ա"+chinese_number(j)+"��;ȴ�������ߣ�\n");
   	    write("��������������������������������������������������������������������������������������������\n");
     }
     else  
	   {
	     if( k>1 && k<5 ) write( sprintf("%"+((5-k)*22+2)+"s\n","��") );
	     write("��������������������������������������������������������������������������������������������\n");
	     write(HIG+GROUP_D->get_group_name(gid)+"�����ܹ��г�Ա"+chinese_number(j)+"��;"+chinese_number(p)+"���ߣ�\n");
     }
  }
	
	me->set_temp("command_busy", 1);
	call_out("remove_busy", 3, me);
	return 1;
}

void remove_busy(object me)
{
	if (me) me->delete_temp("command_busy");
}
int help(object me)
{
	write(@HELP
ָ���ʽ :
glist �г����еİ��ɵ������
glist [����id] �鿴�˰��ɵĳ�Ա��
glist -l �鿴��ϸ������ݡ�
glist -! �鿴���߰������ˡ�
HELP
	);
	return 1;
}
