// user list

inherit F_CLEAN_UP;


int main(object me)
{
        object obj;
        obj = new("/d/zhiye/obj/kuangshi.c");
        if(!obj) return 1;
        obj->set_level(random(10));
        obj->set("findby",me->query("id"));
        if( !obj->move(me) ) destruct(obj);
        return 1;

}

int help(object me)
{
write(@HELP
ָ���ʽ : ulist

������������ҵ�/obj/user number ��ʾ������
HELP
    );
    return 1;
}
