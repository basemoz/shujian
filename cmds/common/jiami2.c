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
	if (!arg) return notify_fail("ָ���ʽ��jiami <�ļ���>\n");	
	src = arg;
	src = resolve_path(me->query("cwd"), src);
	if (file_size(src) == -2 && src[<1] != '/') src += "/";
	if (src[<1] == '/') src += "*";	
	file = get_dir(src, -1);
	i = sizeof(file);
	if (!i) return notify_fail("û�� "+src+"��\n");	
	src = "/" + implode(explode(src, "/")[0..<2], "/") + "/";
	while (i--) {
		if (file[i][1] >= 0) {
			tmps = src + file[i][0];			
			switch(do_jiami(tmps)){
				case 1:	j++;
					write("����"+tmps+"�ɹ���\n");
					break;
				case 0: write("��û�ж�"+tmps+"��дȨ�ޡ�\n");
					break;
				case -4: write("�ļ������� .c �� .h ��β��\n");
					 break;
				case -3: write("û��"+tmps+"����ļ���\n");
					 break;
				case -2: write("��û�ж�"+tmps+"�Ķ�Ȩ�ޡ�\n");
					 break;
				case -1: write(tmps+"�Ѿ��������ˡ�\n");
					 break;
				default:
					write("����\n");
			}
		}
	}
	write("\n"+j+" ���ļ����ܳɹ���\n");
	return 1;
}
/*
-4 
notify_fail("�ļ������� .c �� .h ��β��\n")
-3
notify_fail("û������ļ���\n")
-2
notify_fail(file + " ����Ϊ�㡣\n");
-1
notify_fail(file + " �Ѿ��������ˡ�\n")
0
дʧ��
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
