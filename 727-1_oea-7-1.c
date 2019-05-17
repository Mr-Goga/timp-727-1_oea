#include<stdio.h>
#include<stdlib.h>
int kostul(int *arr, int left, int right, int shet )
{
	int opor,tmp_left,tmp_right,tmp;
	
		opor = arr[(left + right) / 2];
		tmp_left = left;
		tmp_right = right;
		do
		{
			shet++;
			while (arr[tmp_left] < opor) 
			{
				shet++;
				tmp_left++;
			}
			shet++;
			while (arr[tmp_right] > opor)
			{
				shet++;
				tmp_right--;
			}	
			if (tmp_left <= tmp_right)
			{
				shet++;
				if (arr[tmp_left] > arr[tmp_right])
				{
					shet++;
					tmp = arr[tmp_left];
					arr[tmp_left] = arr[tmp_right];
					arr[tmp_right] = tmp;
				}
				tmp_right--;
				tmp_left++;
			}		
		} while (tmp_left <= tmp_right);

		if(tmp_left<right)
		shet= shet+kostul(arr, tmp_left, right, shet);
		if (left < tmp_right)
		shet =shet+ kostul(arr, left, tmp_right, shet);
		return shet;
}


int quickSort(int *arr, int arr_len) 
{
	int shet = 0;
	shet=kostul(arr, 0, arr_len-1,shet);
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
	shet= quickSort(arr, n);
	for (int i = 0; i < n-1; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[n-1]);
	free(arr);
	return 0;	
}
