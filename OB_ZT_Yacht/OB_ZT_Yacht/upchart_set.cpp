#include "yatch_chart.h"

using namespace std;

// yatch_chart�� ������ null���� Ȯ��, null�� �ƴ϶��,, setValue ����


bool CalChart::IsNullptr(int* value)
{
	int result = 0;
	if (*value)
	{
		return false;
	}
	else return true;
}
int CalChart::SetValue(vector<int>dicenum)
{
	return 0;
}


CheckUpValue::CheckUpValue(Chart* chart)
{
	this->chart = chart;
}

int CheckUpValue::SetValue(vector<int>dice_num, int number)
{
	int result = 0;
	for (int i = 0; i < dice_num.size(); i++)
	{
		if (dice_num[i] == number)
			result += number;
	}
	return result;
}


/*
int setValue::ResultValue(vector<int>cal_value)
{

}
*/


