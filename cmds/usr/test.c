
int main(object me,string arg)
{
	mixed ret;
	
	ret = dbquery("SELECT content FROM test WHERE 'id'=0");
	
	if(ret && sizeof(ret)>0)
	{
		write("back "+ret[0][0]+"\n");
		return 1;
	}
	return notify_fail("failed\n");
}