#include <iostream>
#include "yatch_chart.h"


Chart::Chart() // ������ 
{
	this->player_name = "guest";
}


Chart::Chart(string name)// ������, �÷��̾� �̸� ���� ���� ��
{
	this->player_name = name;
}


void Chart::SetBonus() //subtotal �� ���� 63�̻��̸� bonus�� 35�� ����, bonus�� �⺻���� null
{
	if (*subtotal > 63)
	{
		*bonus = 35;
	}
}


void Chart::SetTotalSum() //���� ǥ ��, �ϴ� ǥ�� �� , ���ʽ� ������ �� ���ϱ�
{
	*this->totalvalue = *subtotal + *choice + *four_of_a_kind + *full_house + *s_straight + *b_straight + *totalvalue + *bonus;
}


void Chart::SetSubTotal() //��� ǥ ��
{
	*this->subtotal = *aces + *deuces + *threes + *fours + *fives + *sixes;
}


void Chart::SetDiceValue(vector<int>input) //�ֻ����κ��� ���� vector<int> ���·� ����
{
	this->dice_num.clear();//erase(dice_num.begin(), dice_num.end()); //���� �ֻ��� ����� �� �ʱ�ȭ
	for (int i = 0; i < input.size(); i++)
	{
		this->dice_num[i] = input[i]; //�Է¹��� �ֻ��� ���� dice_num (�ֻ��� �� �����) �� ����
	}
	sort(this->dice_num.begin(), this->dice_num.end()); //�ֻ��� ����� ����
}
int Chart::Winner(Chart player2)
{
	if (*this->totalvalue > *player2.totalvalue) return 1;
	else if (*this->totalvalue > *player2.totalvalue) return 2;
	else return 0;
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
		if (!this->aces)
			*(this->aces) = this->chart_value[0];
		break;
	case 2:
		if (!this->deuces)
			*this->deuces = chart_value[1];
		break;
	case 3:
		if (!this->threes)
			*this->threes = chart_value[2];
		break;
	case 4:
		if (!this->fours)
			*this->fours = chart_value[3];
		break;
	case 5:
		if (!this->fives)
			*this->fives = chart_value[4];
		break;
	case 6:
		if (!this->sixes)
			*this->sixes = chart_value[5];
		break;
	case 7:
		if (!this->choice)
			*this->choice = chart_value[6];
		break;
	case 8:
		if (!this->four_of_a_kind)
			*this->four_of_a_kind = chart_value[7];
		break;
	case 9:
		if (!this->full_house)
			*this->full_house = chart_value[8];
		break;
	case 10:
		if (!this->s_straight)
			*this->s_straight = chart_value[9];
		break;
	case 11:
		if (!this->b_straight)
			*this->b_straight = chart_value[10];
		break;
	case 12:
		if (!this->yacht)
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

void Chart::CalSet()
{
	CheckUpValue upvalue(this);
	CheckFOK fok(this);
	CheckFH fh(this);
	CheckSS ss(this);
	CheckBS bs(this);
	CheckYacht yatcht(this);
	CheckChoice choice(this);

	for (int i = 0; i < 6; i++)
	{
		if (upvalue.IsNullptr(&this->chart_value[i]))
			this->chart_value[i] = upvalue.SetValue(this->dice_num, i);
	} //���� ǥ �� ���

	//for of kind ���� choice ���� null ���� Ȯ�� �� �� ���� ����(chart_value�� �����Ѵ�)
	if (fok.IsNullptr(&this->chart_value[6])) //�Ʒ��� ǥ �� ���
		this->chart_value[6] = fok.SetValue(this->dice_num);

	if (fh.IsNullptr(&this->chart_value[7]))
		this->chart_value[7] = fh.SetValue(this->dice_num);

	if (ss.IsNullptr(&this->chart_value[8]))
		this->chart_value[8] = ss.SetValue(this->dice_num);

	if (bs.IsNullptr(&this->chart_value[9]))
		this->chart_value[9] = bs.SetValue(this->dice_num);

	if (yatcht.IsNullptr(&this->chart_value[10]))
		this->chart_value[10] = yatcht.SetValue(this->dice_num);

	if (choice.IsNullptr(&this->chart_value[11]))
		this->chart_value[11] = choice.SetValue(this->dice_num);
}



