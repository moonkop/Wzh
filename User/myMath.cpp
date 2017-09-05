#include "MyMath.h"
#include "preProcesser.h"
#include "stm32f4xx.h"
int MED_FIL_ITEM_int = 0;
int med_fil_cnt_int;
int med_filter_tmp_int[5][MED_WIDTH_NUM];

void FillFitter(int data,int item)
{
	for (int i = 0; i < MED_WIDTH_NUM; i++)
	{
		med_filter_tmp_int[item][i] = data;

	}
}

int Moving_Median_int(int in_int, int item) //ÖÐÎ»Êý
{
	u8 i, j;
	int width_num = 5;
	int t_int;
	int tmp[MED_WIDTH_NUM];

	//        if( ++med_fil_cnt_int >= width_num )
	//            med_fil_cnt_int = 0;
	//        med_filter_tmp_int[ med_fil_cnt_int ] = in_int;
	//				

	if (med_fil_cnt_int + 1 >= width_num)
	{
		for (i = 1; i < width_num; i++)
		{
			med_filter_tmp_int[item][i - 1] = med_filter_tmp_int[item][i];
		}
		med_filter_tmp_int[item][width_num - 1] = in_int;

	}
	else
	{
		med_fil_cnt_int++;
		med_filter_tmp_int[item][med_fil_cnt_int] = in_int;
	}
	for (i = 0; i < width_num; i++)
		tmp[i] = med_filter_tmp_int[item][i];
	for (i = 0; i < width_num - 1; i++)
	{
		for (j = 0; j < (width_num - 1 - i); j++)
		{
			if (tmp[j] > tmp[j + 1])
			{
				t_int = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = t_int;
			}
		}
	}

	return (tmp[(u16)width_num / 2]);

}


int remap(int val, int minVal, int maxVal, int minOut, int maxOut)
{
	return  ((long)val - minVal)*(maxOut - minOut) / (maxVal - minVal) + minOut;
}

int getmax(int* nums, int count)
{
	int max = *nums++;
	while (count--)
	{
		if (*nums>max)
		{
			max = *nums;
		}
		nums++;
	}
	return max;
}
