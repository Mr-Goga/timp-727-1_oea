#include<stdio.h>
#include<stdlib.h>
int sorting_shell(int *arr, int arr_len) 
{
	int tmp,shet=0,j;
	for (int d = arr_len / 2; d > 0; d=d/2)
	{
		for (int i = d; i < arr_len; ++i)
		{
			tmp = arr[i];
			
			for ( j = i; j >= d; j = j - d)
			{
				shet++;
				if (tmp < arr[j - d])
				{
					//shet++;
					arr[j] = arr[j - d];
				}
				else
					break;
			}	
			shet++;
			arr[j] = tmp;
		}		
	}
	return shet;
}
int main()
{
	int shet,n,*arr;
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}
	sorting_shell(arr, n);
	for (int i = 0; i < n-1; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[n-1]);
	free(arr);
	return 0;	
}
