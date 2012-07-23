#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#define mem(x,y)		(x*)malloc(sizeof(x)*(y))

#define TLEN		8

int table[TLEN] = {1,7,11,13,17,19,23,29};
int inv[TLEN][2] = {{0,1},{-3,13},{-4,11},{-3,7},{4,-7},{7,-11},{10,-13},{1,-1}};

void memsetex(void* dst,void* data,size_t nmemb,size_t size)
{
	if(size == 1)
	{
		memcpy(dst,data,nmemb);
	}
	else
	{
		size_t half = size/2;
		memsetex(dst,data,nmemb,half);
		memcpy((char*)dst+half*nmemb,dst,half*nmemb);
		if(size%2)
		{
			memcpy((char*)dst+(size-1)*nmemb,data,nmemb);
		}
	}
}

int main()
{
	int n;
	const int lendiv8;
	const int len;
	int *list;
	int i,j,k,l;
	int one = 1;
	scanf("%d",&n);
	lendiv8 = n/30+1;
	len = lendiv8*8;
	list = mem(int,len*8);
	memsetex(list,&one,sizeof(int),len);
	for(i = 0;i < lendiv8;i++)
	{
		for(j = 0;j < 8;j++)
		{
			const int p;
			const int invp;
			const int loop;
			if(!i && !j)continue;
			p = i*30+table[j];
			invp = inv[j][0] - i * inv[j][1];
			loop = lendiv8 / p;
			for(k = 0;k < 8;k++)
			{
				int depth = -table[k]*invp;
				if(depth < 0)
					depth = p-(-depth%p);
				else
					depth %= p;
				if(j != k)
					for(l = 0;l <= loop;l++)
					{
						if(8*(depth+p*l)+k < len)
							list[8*(depth+p*l)+k] = 0;
					}
				else
				{
					for(l = 1;l <= loop;l++)
					{
						if(8*(depth+p*l)+k < len)
							list[8*(depth+p*l)+k] = 0;
					}
				}
			}
		}
	}
	printf("2 3 5 7 11 13 17 19 23 29");
	for(i = 1;i < lendiv8-1;i++)
	{
		for(j = 0;j < 8;j++)
		{
			if(list[i*TLEN+j])
				printf(" %d",i*30+table[j]);
		}
	}
	for(j = 0;j < 8;j++)
	{
		if(i*30+table[j] > n)break;
		if(list[i*TLEN+j])
			printf(" %d",i*30+table[j]);
	}
	putchar('\n');
	return 0;
}
