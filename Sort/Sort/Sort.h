#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Stack.h"
#include <string.h>

void ArrayPrint(int *arr, int n)
{
	int i = 0;
	for (i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//ʵ����������
void InsertSort(int *arr, int n)
{
	int end = 0;
	int tmp = 0;
	for (end = 0; end < n - 1; ++end)
	{
		tmp = arr[end + 1];
		while (end >= 0)
		{
			//���ڲŽ��������ڲ�����
			if (arr[end] > tmp)
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = tmp;
	}
}

void ShellSort(int *arr, int n)
{
	int gap = n;
	while (gap >= 1)  //����gap�Ĵ�С
	{
		//һ������gapΪ��
		gap = gap / 3 + 1; //����С��ֱ��1
		int i = 0;
		//��������
		for (i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = 0;
			tmp = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > tmp)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
		if (gap == 1)
			break;
	}
}

void SelectSort(int *arr, int n)
{
	int min = 0;
	int max = n-1;
	//ÿ��ѡһ����ġ�һ��С��
	while (min < max)
	{
		for (int i = min; i <= max; ++i)
		{
			//��maxʱ������ȵ�����������һ����Ϊmax�����������
			if (arr[i] >= arr[max])
			{
				Swap(&arr[i], &arr[max]);
			}
			//��minʱ������ȵ�������ǰ��һ����Ϊmin��������ǰ��
			if (arr[i] < arr[min])
			{
				Swap(&arr[i], &arr[min]);
			}
		}

		min++;
		max--;
	}
	
}

void AdjustDown(int *arr, int n, int i)
{
	//һ�����µ������豣֤�����������Ǵ��
	int parent = i;
	int child = 2 * i + 1;
	while (child < n)
	{
		//�����Ԫ��������
		if (arr[child] < arr[child + 1] && child+1 < n)
		{
			++child;
		}
		//�������С�����ӣ�������������
		if (arr[parent] < arr[child])
		{
			Swap(&arr[parent], &arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *arr, int n)
{
	int root = (n - 1 - 1) / 2;
	//�������
	while (root >= 0)
	{
		AdjustDown(arr, n, root);
		root--;
	}
	//���Ѷ�Ԫ�������һ��Ԫ�ؽ���������������ɷ��ʳ��ȣ����浽ĩβ�����Ԫ�ز����ٱ�����
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDown(arr, end, 0);
		end--;
	}
}

void BubbleSort(int *arr, int n)
{
	int end = n;
	while (end > 1)
	{
		int flag = 0;
		for (int cur = 0; cur < end - 1; ++cur)
		{
			//����ʱ�������������ȶ���
			if (arr[cur] > arr[cur + 1])
			{
				flag = 1;
				Swap(&arr[cur], &arr[cur + 1]);
			}
		}
		if (flag == 0)
			break;
	}
}

//����ȡ�з�
int GetMid(int *arr, int begin, int end)
{
	int mid = begin + ((end - begin) >> 1);
	if (arr[begin] > arr[mid])
	{
		if (arr[mid] > arr[end])
			return mid;
		else if (arr[begin] > arr[end])
			return end;
		else
			return begin;
	}
	else
	{
		if (arr[begin] > arr[end])
			return begin;
		else if (arr[end] > arr[mid])
			return mid;
		else
			return end;
	}
}

/*
PartSort()���������д���key�ķ���key���ұߣ�С��key�ķ���key�����
keyͨ������ȡ�з���GetMid����ã�ʹ��key�Ĵ�С�����ӽ���λ��
*/
int PartSort1(int *arr, int begin, int end)
{
	int mid = GetMid(arr, begin, end);
	Swap(&arr[begin], &arr[mid]);

	int ret = begin;
	int key = arr[begin];
	while (begin < end)
	{
		//�ȴ��ҿ�ʼ��С
		while (begin < end && arr[end] >= key)
		{
			--end;
		}
		//�ٴ���ʼ�Ҵ�
		while (begin < end && arr[begin] <= key)
		{
			++begin;
		}
		//����
		if (begin < end)
			Swap(&arr[begin], &arr[end]);
	}
	//��ǰֵ����ʼλ��
	arr[ret] = arr[begin];
	//�м�ֵ���ڵ�ǰλ��(������)
	arr[begin] = key;

	return begin;
}

int PartSort2(int *arr, int begin, int end)
{
	int mid = GetMid(arr, begin, end);
	Swap(&arr[begin], &arr[mid]);

	int key = arr[begin];
	//��ʼbeginΪ��
	while (begin < end)
	{
		//����ʼ�ұ�keyС�ģ��������ŵ���ǰ���У���λ�ñ�Ϊ��
		while (begin < end && arr[end] >= key)
		{
			--end;
		}
		arr[begin] = arr[end];

		//�ٴ��ҿ�ʼ�ұ�key��ģ��������ŵ���ǰ���У���λ�ñ�Ϊ��
		while (begin < end && arr[begin] <= key)
		{
			++begin;
		}
		arr[end] = arr[begin];
	}

	arr[begin] = key;
	return begin;
}

//ǰ��ָ�뷨
int PartSort3(int *arr, int begin, int end)
{
	int mid = GetMid(arr, begin, end);
	Swap(&arr[begin], &arr[mid]);

	int key = arr[begin];
	int prev = begin;
	int cur = prev + 1;
	//cur�ҵ�С��key�ľ���prev����
	while (cur <= end)
	{
		//prev�߹��Ķ���С��key��
		if (arr[cur] < key)
		{
			++prev;
			if (prev != cur)
			{
				Swap(&arr[prev], &arr[cur]);
			}
		}
		++cur;
	}
	//������prev������ʼ��(key)����
	Swap(&arr[prev], &arr[begin]);
	return prev;
}

void QuickSort(int *arr, int left, int right)
{
	if (left >= right)
		return;
	int mid;
	
	if (left < right)
	{
		if (right - left > 5)
		{
			mid = PartSort3(arr, left, right);

			QuickSort(arr, left, mid - 1);
			QuickSort(arr, mid + 1, right);
		}
		//���ٵݹ��Σ�С����ֱ��ʹ�ò�������
		else
		{
			InsertSort(arr + left, right - left + 1);
		}
	}
}

//�ǵݹ�ʵ�ֿ���
void QuickSortNonR(int *arr, int left, int right)
{
	Stack *st = (Stack *)malloc(sizeof(Stack));
	StackInit(st);
	//���������˵�ѹջ��ע��˳��һ�£�ѹջ�ͳ�ջ���
	StackPush(st, right);
	StackPush(st, left);
	while (StackEmpty(st) != 0)
	{
		int begin = StackTop(st);
		StackPop(st);
		int end = StackTop(st);
		StackPop(st);
		int div = PartSort1(arr, begin, end);

		//[begin, div-1]
		if (begin < div-1)
		{
			StackPush(st, div - 1);
			StackPush(st, begin);
		}

		//[div+1, end]
		if (div+1 < end)
		{
			StackPush(st, end);
			StackPush(st, div + 1);
		}
	}
}

void _MergeSort(int *arr, int left, int right, int *tmp)
{
	if (left >= right)
		return;
	int mid = left + ((right - left) >> 1);

	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid + 1, right, tmp);

	//[left, mid]  [mid+1, right]
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	int ret = left;
	//�����ź��������鲢
	while (begin1 <= end1 && begin2 <= end2)
	{
		//����ʱΪ��֤�ȶ��ԣ��Ȳ���ǰ��һ��
		if (arr[begin1] <= arr[begin2])
		{
			tmp[left++] = arr[begin1];
			begin1++;
		}
		else
		{
			tmp[left++] = arr[begin2];
			begin2++;
		}
	}
	//������һ����������꣬����һ��������ʣ��Ԫ�ض�������tmp��
	while (begin1 <= end1)
	{
		tmp[left++] = arr[begin1];
		begin1++;
	}
	while (begin2 <= end2)
	{
		tmp[left++] = arr[begin2];
		begin2++;
	}
	//��tmp�й鲢�õ��������п���ԭ����
	while (ret <= right)
	{
		arr[ret] = tmp[ret];
		ret++;
	}
}

void MergeSort(int *arr, int n)
{
	//��Ҫ�¿���һ��ͬ�ȴ�С�Ŀռ�������������Ĺ鲢
	int *tmp = (int *)malloc(sizeof(int)*n);
	_MergeSort(arr, 0, n - 1, tmp);
	free(tmp);
}

void CountSort(int *arr, int n)
{
	int max = arr[0];
	int min = arr[0];
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}
	int size = max - min + 1;
	int *tmp = (int *)malloc(sizeof(int)* size);
	memset(tmp, 0, sizeof(int) * size);
	int begin = 0;
	while (begin < n)
	{
		tmp[arr[begin] - min]++;
		++begin;
	}
	begin = 0;
	int left = 0;
	while (begin < size)
	{
		while (tmp[begin]-- > 0)
		{
			arr[left++] = begin+1;
		}
		begin++;
	}
}

void SortTest()
{
	/*srand(time(0));
	int size = 10000;
	int *arr = (int *)malloc(sizeof(int)* size);
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}*/
	//int arr[] = { 5, 9, 2, 6, 5, 7, 3, 8, 4, 1 };
	//int arr[] = { 5, 8, 7, 6, 9, 5, 4, 3, 2, 1 };
	int arr[] = { 6, 5 };

	int size = sizeof(arr) / sizeof(arr[0]);
	//int begin = clock();
	//ShellSort(arr, size);
	////InsertSort(arr, size);
	//int end = clock();
	//printf("%d\n", end - begin);
	SelectSort(arr, size);
	//HeapSort(arr, size);
	//BubbleSort(arr, size);
	//QuickSort(arr, 0, size - 1);
	//QuickSortNonR(arr, 0, size - 1);
	//MergeSort(arr, size);
	//CountSort(arr, size);

	//PartSort(arr, 0, size - 1);
	ArrayPrint(arr, size);
	//printf("%d\n", GetMid(arr, 0, size - 1));
}
