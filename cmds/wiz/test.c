// test.c

inherit F_CLEAN_UP;
#include <mudlib.h>
#include <job_mul.h>

int main(object me, string arg)
{
	int qua;
	int i,j,max;
	int q1,q2,q3,q4,q5;
  if (sscanf(arg, "%d", max)!=1 ){
		return notify_fail("����������\n");
	}
	q1 = 0;
	q2 = 0;
	q3 = 0;
	q4 = 0;
	q5 = 0;
	for (j=1;j<max;j++)
	{
	qua = 1;
	i = random(100);
	if(i>30 && !random(3)) qua+=1;
	if(i>60 && !random(4)) qua+=1;
	if(i>80 && !random(5)) qua+=1;
	if(i>90 && !random(6)) qua+=1;
	switch (qua) {
		case 1:
			q1+=1;
			break;
		case 2:
			q2+=1;
			break;
		case 3:
			q3+=1;
			break;
		case 4:
			q4+=1;
			break;
		case 5:
			q5+=1;
			break;	
	}
	write(qua + "\n");
	}
	write("q1="+q1+"\nq2="+q2+"\nq3="+q3+"\nq4="+q4+"\nq5="+q5+"\n");
	return 1;
}



int help(object me)
{
write(@HELP
ָ���ʽ : test <ĳ��>
 
���������书���ܵ�ǿ����
HELP
    );
    return 1;
}

