#include<stdio.h>
#include<stdlib.h>

int sift_arr(int *arr, int arr_len, int i, int shet) //Ïèðîìèäàëüíàÿ ñîðòèðîâêà
{
	int  max_elem= arr_len,tmp;
	for (;;)
	{
		if ((2 * i > arr_len)||(max_elem==0))
		{
			break;
		}
		if (2 * i == arr_len)
		{
			max_elem = arr_len;
		}
		else
		{
			shet++;
			if (arr[2 * i] > arr[2 * i + 1])
			{
				max_elem = 2 * i;
			}
			else if (arr[2 * i] <= arr[2 * i + 1])
			{
				shet++;
				max_elem = 2 * i + 1;
			}
		}
		shet++;
		if (arr[i] < arr[max_elem])
		{
			shet++;
			tmp = arr[i];
			arr[i] = arr[max_elem];
			arr[max_elem] = tmp;
		}
		i = max_elem;
	}
	return shet;
}
int heap_sort(int *arr, int arr_len) 
{
	int i, shet=0,tmp;
	for (i = (arr_len) / 2; i >= 0; i--)
	{
		sift_arr(arr, arr_len, i, shet);
	}
	while(arr_len>0)
	{
		shet++;
		tmp = arr[0];
		arr[0]=arr[arr_len];
		arr[arr_len] = tmp;
		arr_len--;
		sift_arr(arr, arr_len, 0, shet);
	}
	return shet;
}



int main()
{
	int n,*arr;
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}
	heap_sort(arr, n-1);
	for (int i = 0; i < n-1; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[n-1]);
	free(arr);
	return 0;	
}
