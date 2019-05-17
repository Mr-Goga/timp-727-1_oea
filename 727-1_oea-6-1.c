#include<stdio.h>
#include<stdlib.h>
int sorting_comb(int *arr, int arr_len) //ñîðòèðîâêà ðàñ÷åñòêîé
{
	int shet=0,s = arr_len;
	int tmp = 0;
	for (int i = 0; i < arr_len; i++)
	{
		s = s/ 1.247f;
		for (int j = 0; j+s < arr_len ; ++j)
		{
			shet++;
			if (arr[j] > arr[j + s])
			{
				tmp = arr[j + s];
				arr[j + s] = arr[j];
				arr[j] = tmp;
				shet++;
			}
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
	sorting_comb(arr, n);
	for (int i = 0; i < n-1; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[n-1]);
	free(arr);

	return 0;	
}
