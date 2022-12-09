#include "yatch_chart.h"

using namespace std;

//FOK �� �ִ��� Ȯ��, ����
int CheckFOK::SetValue(vector<int>dice_num)
{
	int result = 0;
	int check_value[6] = { 0, };
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
CheckFOK::CheckFOK(Chart* chart)
{
	this->chart = chart;
}

//Full House �� �ִ��� Ȯ��, ����
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
CheckFH::CheckFH(Chart* chart)
{
	this->chart = chart;
}


//Small Straight �� �ִ��� Ȯ��, ����
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
CheckSS::CheckSS(Chart* chart)
{
	this->chart = chart;
}


//Big Straight �� �ִ��� Ȯ��, ����
int CheckBS::SetValue(vector<int>dice_num)
{
	int result = 0;
	if ((accumulate(dice_num.begin(), dice_num.end(), 0) == 15 && dice_num.front() == 1 && dice_num.back() == 5))
		result = 40;
	if ((accumulate(dice_num.begin(), dice_num.end(), 0) == 20 && dice_num.front() == 2 && dice_num.back() == 6))
		result = 40;
	return result;
}
CheckBS::CheckBS(Chart* chart)
{
	this->chart = chart;
}


//yacht �� �ִ��� Ȯ��, ����
int CheckYacht::SetValue(vector<int>dice_num)
{
	int result = 50;
	if (dice_num[0] == dice_num[1] == dice_num[2] == dice_num[3] == dice_num[4])
		return 50;
	else return 0;
}
CheckYacht::CheckYacht(Chart* chart)
{
	this->chart = chart;
}


//choice �� �ִ��� Ȯ��, ����
int CheckChoice::SetValue(vector<int>dice_num)
{
	int result = 0;
	result = accumulate(dice_num.begin(), dice_num.end(), 0);
	return result;
}
CheckChoice::CheckChoice(Chart* chart)
{
	this->chart = chart;
}