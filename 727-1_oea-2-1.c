#include<stdio.h>
int main (){
   int n,k=0,x;
   scanf("%d", &n);
   for(int i=1; i<=n; ++i)
   {
      scanf("%d", &x);
      if(x>=0)
	{k++;}
   }
   printf("%d\n", k);
   return 0;
}
