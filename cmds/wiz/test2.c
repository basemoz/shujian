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
指令格式 : ulist

将线上所有玩家的/obj/user number 显示出来。
HELP
    );
    return 1;
}
