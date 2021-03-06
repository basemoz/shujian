#pragma no_save_binary

buffer buf;

int do_jiami(string file);

int main(object me, string arg)
{
	string src,tmps;
	int i,j = 0;
	mixed file;
	
	if(!wizardp(me)) return 0;	
	seteuid(getuid(me));
	if (!arg) return notify_fail("指令格式：jiami <文件名>\n");	
	src = arg;
	src = resolve_path(me->query("cwd"), src);
	if (file_size(src) == -2 && src[<1] != '/') src += "/";
	if (src[<1] == '/') src += "*";	
	file = get_dir(src, -1);
	i = sizeof(file);
	if (!i) return notify_fail("没有 "+src+"。\n");	
	src = "/" + implode(explode(src, "/")[0..<2], "/") + "/";
	while (i--) {
		if (file[i][1] >= 0) {
			tmps = src + file[i][0];			
			switch(do_jiami(tmps)){
				case 1:	j++;
					write("加密"+tmps+"成功！\n");
					break;
				case 0: write("你没有对"+tmps+"的写权限。\n");
					break;
				case -4: write("文件必须以 .c 或 .h 结尾。\n");
					 break;
				case -3: write("没有"+tmps+"这个文件。\n");
					 break;
				case -2: write("你没有对"+tmps+"的读权限。\n");
					 break;
				case -1: write(tmps+"已经被加密了。\n");
					 break;
				default:
					write("错误！\n");
			}
		}
	}
	write("\n"+j+" 个文件加密成功。\n");
	return 1;
}
/*
-4 
notify_fail("文件必须以 .c 或 .h 结尾。\n")
-3
notify_fail("没有这个文件。\n")
-2
notify_fail(file + " 长度为零。\n");
-1
notify_fail(file + " 已经被加密了。\n")
0
写失败
*/
int do_jiami(string file)
{
	int size, i;
	switch (file[<2..<1]) {
		case ".c":
		case ".h":
			break;
		default:
			return -4;
	}
	if (file_size(file) < 0) return -3;	
	buf = read_buffer(file);
	size = sizeof(buf);	
	if (!size) return -2;
	if (buf[0] & 0x80) return -1;	
	for (i = 0; i < size; i++) buf[i] = ((buf[i] ^ ((i+128) & 0xD5)) * 257) >> (i & 7);	
	write_buffer(file, 0, buf);
	buf = read_buffer(file);
	size = sizeof(buf);
	if (buf[0] & 0x80) return 1;	
	return 0;
}
