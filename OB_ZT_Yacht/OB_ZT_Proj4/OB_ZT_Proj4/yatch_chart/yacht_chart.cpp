#include <iostream>
#include "yatch_chart.h"
using namespace std;

Chart::Chart() // ������ 
{
	this->player_name = "guest";
}

Chart::Chart(string name)// ������, �÷��̾� �̸� ���� ���� ��
{
	this->player_name = name;
}

void Chart::GetBonus() //subtotal �� ���� 63�̻��̸� bonus�� 35�� ����, bonus�� �⺻���� null
{
	if (*subtotal > 63)
	{
		*bonus = 35;
	}
}

void Chart::GetTotalSum() //���� ǥ ��, �ϴ� ǥ�� �� , ���ʽ� ������ �� ���ϱ�
{
	*this->totalvalue = *subtotal + *choice + *four_of_a_kind + *full_house + *s_straight + *b_straight + *totalvalue + *bonus;
}

void Chart::GetSubTotal() //��� ǥ ��
{
	*this->subtotal = *aces + *deuces + *threes + *fours + *fives + *sixes;
}

void Chart::GetDiceValue(vector<int>input) //�ֻ����κ��� ���� vector<int> ���·� ����
{
	this->dice_num.clear();//erase(dice_num.begin(), dice_num.end()); //���� �ֻ��� ����� �� �ʱ�ȭ
	for (int i = 0; i < input.size(); i++)
	{
		this->dice_num[i] = input[i]; //�Է¹��� �ֻ��� ���� dice_num (�ֻ��� �� �����) �� ����
	}
	sort(this->dice_num.begin(), this->dice_num.end()); //�ֻ��� ����� ����
}

// *subtotal = GetSuubtotal() �� ó��


//�÷��̾ ���� �ѱ� �� ���� ����� ǥ�� ���, vector<int>�� �����Ѵ�.
vector<int> Chart::GetRoundResult()
{
	vector<int>Result;
	Result.push_back(*this->aces);
	Result.push_back(*this->deuces);
	Result.push_back(*this->threes);
	Result.push_back(*this->fours);
	Result.push_back(*this->fives);
	Result.push_back(*this->sixes);
	Result.push_back(*this->bonus);
	Result.push_back(*this->subtotal);

	Result.push_back(*this->choice);
	Result.push_back(*this->four_of_a_kind);
	Result.push_back(*this->full_house);
	Result.push_back(*this->s_straight);
	Result.push_back(*this->b_straight);
	Result.push_back(*this->yacht);
	Result.push_back(*this->totalvalue);
	return Result;
}

/*
�÷��̾� ���� �Ǿ��� ��, ���꿡 �̿��� �ӽð��� ���� ��ϰ��� ���Ͽ� �ʱ�ȭ ���ش�
public ���� chart_value(�ӽð�) ���Ϳ� �����Ͽ� �� ����
*/
void Chart::SetDefaultValue() 
 {
	this->chart_value.clear();//erase(chart_value.egin(), chart_value.end());  //���� �� ����
	this->chart_value.push_back(*this->aces);		//1
	this->chart_value.push_back(*this->deuces);		//2		this->chart_value.push_back(*this->threes); //3
	this->chart_value.push_back(*this->fours);		//4
	this->chart_value.push_back(*this->fives);		//5
	this->chart_value.push_back(*this->sixes);		//6
	this->chart_value.push_back(*this->bonus);
	this->chart_value.push_back(*this->subtotal);

	this->chart_value.push_back(*this->choice);				//choice
	this->chart_value.push_back(*this->four_of_a_kind);		//4 of kind
	this->chart_value.push_back(*this->full_house);			// full house
	this->chart_value.push_back(*this->s_straight);			// small straight
	this->chart_value.push_back(*this->b_straight);			// large straight
	this->chart_value.push_back(*this->yacht);				// yacht
	this->chart_value.push_back(*this->totalvalue);
 }

 //�ӽð� ����(�� �� �ֻ����� ���� ������ �������ش�)
 vector<int> Chart::GetChartValue()
{
	 return this->chart_value;
}

 //ǥ�� ����ϱ�� ������ �� �Է����ֱ�
 void Chart::PushValue(int choose_num)
{
	 switch (choose_num)
	 {
	 case 1:
		 *this->aces = this->chart_value[0];
		 break;
	 case 2:
		 *this->deuces = chart_value[1];
		 break;
	 case 3:
		 *this->threes = chart_value[2];
		 break;
	 case 4:
		 *this->fours = chart_value[3];
		 break;
	 case 5:
		 *this->fives = chart_value[4];
		 break;
	 case 6:
		 *this->sixes = chart_value[5];
		 break;
	 case 7:
		 *this->choice = chart_value[6];
		 break;
	 case 8:
		 *this->four_of_a_kind = chart_value[7];
		 break;
	 case 9:
		 *this->full_house = chart_value[8];
		 break;
	 case 10:
		 *this->s_straight= chart_value[9];
		 break;
	 case 11:
		 *this->b_straight = chart_value[10];
		 break;
	 case 12:
		 *this->yacht = chart_value[11];
		 break;
	 }
}

 Chart ChartFactory::GetChart()
 {
	 return Chart();
 }

 Chart ChartFactory::GetChart(string name)
 {
	 return Chart(name);
 }

 void main()
 {

 }
 /*
//���� ����
int main()
{
	ChartFactory factory;
	vector<int>input; //�ֻ��� ���� �� ����
	Chart play1;
	Chart play2;

	int y = 12;
	play1 = factory.GetChart();
	play2 = factory.GetChart("me");

	while (y > 0)
	{
		play1.SetDefaultValue();		//1. �ӽ� ���Ͱ� �ʱ�ȭ
		play1.GetChartValue();		//2. chart_value �� ����
		play1.GetDiceValue(input);		//3. �ֻ��� ����� �޾ƿ���
		SetUpValue upvalue(&play1);    //���� class ����(command)
		CheckFOK fok(&play1);
		CheckFH fh(&play1);
		CheckSS ss(&play1);
		CheckBS bs(&play1);
		CheckYacht yatcht(&play1);
		CheckChoice choice(&play1);

		for (int i = 0; i < 6; i++)
		{
			if (upvalue.IsNullptr(&play1.chart_value[i]))
				play1.chart_value[i] = upvalue.SetValue(play1.dice_num, i);
		} //���� ǥ �� ���

		//for of kind ���� choice ���� null ���� Ȯ�� �� �� ���� ����(chart_value�� �����Ѵ�)
		if (fok.IsNullptr(&play1.chart_value[6])) //�Ʒ��� ǥ �� ���
			play1.chart_value[6] = fok.SetValue(play1.dice_num);

		if (fh.IsNullptr(&play1.chart_value[7]))
			play1.chart_value[7] = fh.SetValue(play1.dice_num);

		if (ss.IsNullptr(&play1.chart_value[8]))
			play1.chart_value[8] = ss.SetValue(play1.dice_num);

		if (bs.IsNullptr(&play1.chart_value[9]))
			play1.chart_value[9] = bs.SetValue(play1.dice_num);

		if (yatcht.IsNullptr(&play1.chart_value[10]))
			play1.chart_value[10] = yatcht.SetValue(play1.dice_num);

		if (choice.IsNullptr(&play1.chart_value[11]))
			play1.chart_value[11] = choice.SetValue(play1.dice_num);

		play1.GetChartValue(); //chart_value �� ����
	}


		play1.GetBonus();
		play1.GetSubTotal();
		play1.GetTotalSum();
		play1.GetRoundResult();
}*/