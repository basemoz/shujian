//by spiderii@ty�����Ա��˳ŵ���Ū��������
#include <ansi.h>

inherit F_DBASE;
int random_place(string dirss,object bs);

string *dirs = ({
"/d/baituo",
"/d/city",
"/d/cangzhou",
"/d/changan",
"/d/changle",
"/d/chengdu",
"/d/dali",
"/d/emei",
"/d/foshan",
"/d/fuzhou",
"/d/gb",
"/d/gumu",
"/d/hengshan",
"/d/hj",
"/d/hmy",
"/d/huanghe",
"/d/huashan",
"/d/hz",
"/d/jiaxing",
"/d/jingcheng",
"/d/kunlun",
"/d/lanzhou",
"/d/meizhuang",
"/d/miaojiang",
"/d/mingjiao",
"/d/mr",
"/d/nanyang",
"/d/ningbo",
"/d/sld",
"/d/songshan",
"/d/suzhou",
"/d/taishan",
"/d/tanggu",
"/d/thd",
"/d/tiezhang",
"/d/tls",
"/d/wudang",
"/d/xiangyang",
"/d/xingxiu",
"/d/xueshan",
});

string *dirname = ({
"����ɽ",
"����",
"����",
"����",
"���ְ�",
"�ɶ�",
"����",
"����ɽ",
"��ɽ",
"����",
"ؤ��",
"��Ĺ",
"��ɽ",
"��ԭ",
"��ľ��",
"�ƺ�",
"��ɽ",
"����",
"����",
"����",
"����",
"����",
"÷ׯ",
"�置",
"����",
"Ľ��",
"����",
"����",
"������",
"��ɽ",
"����",
"̩ɽ",
"����",
"�һ���",
"����ɽ",
"������",
"�䵱",
"����",
"����",
"ѩɽ",

});


void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "�ڴ澫��");
        CHANNEL_D->do_channel( this_object(), "sys", "�콵��ʯϵͳ�Ѿ�������\n"); 
        set("name","");
        remove_call_out("choose_baoshi");
        call_out("choose_baosi",10);
}

void choose_baosi()
{
        int i, j ,k,ppl,rd;
        object *list,newob;
        string str,m_name;
        string smp;
        
        j = random(sizeof(dirs));
        rd = random(7);
        if(rd==0) 
        {
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==1) 
        {
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==2)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==3)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==4)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==5)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "��";
        }
        if(rd==6)
        { 
                 newob = new("/quest/obj/baoshi");
                 str = "ˮ��";
        }
                
        if(random_place(dirs[j],newob)== 1 )
        message("channel:chat",HIG"��"+HIR"�콵��ʯ"+HIG"��"+HIW"ͻȻ���д��˸�ը��,һ�������ճ���,����һ��"+str+"����"+dirname[j]+"�ķ�����ȥ!\n"+NOR,users());
        remove_call_out("choose_baosi");
  call_out("choose_baosi",1800);
}

int random_place(string dirss,object bs)
{
        int  j, k;
        object  newob,ob;
        mixed*  file, exit;
        string id_name;
        file = get_dir( dirss+"/npc/*.c", -1 );
        
        if( !sizeof(file) ) return 0;

        for(k=0;k<50;k++) { // try 50 times
           j = random(sizeof(file));
           if( file[j][1] > 0 ) {
             newob=load_object(dirss+"/npc/"+file[j][0]);
             if(!newob) continue;
             id_name = newob->query("id");
             destruct(newob);
             if(!id_name) continue;
             if(!objectp(ob=find_living(id_name))) continue; //���npc���ǻ�� 
                     if(bs->move(ob)) {
                    CHANNEL_D->do_channel( this_object(), "sys", "��ʯ�䵽��"+ob->query("name")+"("+ob->query("id")+")�����ϡ�\n"); 
                     return 1;
                    }
             }
           }
         CHANNEL_D->do_channel( this_object(), "sys", "���α�ʯ����ʧ��\n");        
        return 0;
}
