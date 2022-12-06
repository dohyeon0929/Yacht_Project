#include "yatch_chart.h"

using namespace std;

bool DownChart::IsNullptr(int* value)
{
	int result = 0;
	if (*value)
	{
		return false;
	}
	else return true;
}
int DownChart::SetValue(vector<int>dice_num)
{
	return 0;
}

//FOK 값 있는지 확인, 대입
int CheckFOK::SetValue(vector<int>dice_num)
{
	int result = 0;
	int check_value[6] = {0,};
	for (int i = 0; i < dice_num.size(); i++)
	{
			check_value[dice_num[i]] += 1;
	}
	for (int i = 0; i < dice_num.size(); i++)
	{
		if ((check_value[i] >= 4))
			result = accumulate(dice_num.begin(), dice_num.end(), 0);
	}
	return result;
}

//Full House 값 있는지 확인, 대입
int CheckFH::SetValue(vector<int>dice_num)
{
	int result = 0;
	int check_value[6] = { 0, };
	for (int i = 0; i < dice_num.size(); i++)
	{
		check_value[dice_num[i]] += 1;
	}
	for (int i = 0; i < dice_num.size(); i++)
	{
		if ((check_value[i] == 3))
			for (int j = 0; j < 5; j++)
			{
				if (i == j) continue;
				if (check_value[j] == 3) {
					result = (i + 1) * 3 + (j + 1) * 2;
					break;
				}
			}
	}
	return result;
}

//Small Straight 값 있는지 확인, 대입
int CheckSS::SetValue(vector<int>dice_num)
{
	int result = 0;
	if ((accumulate(dice_num.begin(), dice_num.begin() + 3, 0) == 14 && dice_num.front() == 1) ||
		(accumulate(dice_num.begin() + 1, dice_num.end(), 0) == 14 && dice_num.back() == 4))
		result = 30;

	else if ((accumulate(dice_num.begin(), dice_num.begin() + 3, 0) == 14 && dice_num.front() == 2) ||
		(accumulate(dice_num.begin() + 1, dice_num.end(), 0) == 14 && dice_num.back() == 5))
		result = 30;
	else if ((accumulate(dice_num.begin(), dice_num.begin() + 3, 0) == 18 && dice_num.front() == 3) ||
		(accumulate(dice_num.begin() + 1, dice_num.end(), 0) == 18 && dice_num.back() == 6))
		result = 30;

	return result;
}

//Big Straight 값 있는지 확인, 대입
int CheckBS::SetValue(vector<int>dice_num)
{
	int result = 0;
	if ((accumulate(dice_num.begin(), dice_num.end(), 0) == 15 && dice_num.front() == 1 &&dice_num.back() == 5)) 
		result = 40;
	if ((accumulate(dice_num.begin(), dice_num.end(), 0) == 20 && dice_num.front() == 2 && dice_num.back() == 6))
		result = 40;
	return result;
}

//yacht 값 있는지 확인, 대입
int CheckYacht::SetValue(vector<int>dice_num)
{
	int result = 50;
	if (dice_num[0] == dice_num[1] == dice_num[2] == dice_num[3] == dice_num[4])
		return 50;
	else return 0;
}

//choice 값 있는지 확인, 대입
int CheckChoice::SetValue(vector<int>dice_num)
{
	int result = 0;
	result = accumulate(dice_num.begin(), dice_num.end(), 0);
	return result;
}