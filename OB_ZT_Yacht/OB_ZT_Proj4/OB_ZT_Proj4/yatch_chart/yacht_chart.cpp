#include <iostream>
#include "yatch_chart.h"
using namespace std;

Chart::Chart() // 생성자 
{
	this->player_name = "guest";
}

Chart::Chart(string name)// 생성자, 플레이어 이름 값을 넣을 때
{
	this->player_name = name;
}

void Chart::GetBonus() //subtotal 의 값이 63이상이면 bonus를 35로 설정, bonus의 기본값은 null
{
	if (*subtotal > 63)
	{
		*bonus = 35;
	}
}

void Chart::GetTotalSum() //위쪽 표 합, 하단 표의 합 , 보너스 점수의 합 더하기
{
	*this->totalvalue = *subtotal + *choice + *four_of_a_kind + *full_house + *s_straight + *b_straight + *totalvalue + *bonus;
}

void Chart::GetSubTotal() //상단 표 값
{
	*this->subtotal = *aces + *deuces + *threes + *fours + *fives + *sixes;
}

void Chart::GetDiceValue(vector<int>input) //주사위로부터 받은 vector<int> 형태로 리턴
{
	this->dice_num.clear();//erase(dice_num.begin(), dice_num.end()); //이전 주사위 저장된 값 초기화
	for (int i = 0; i < input.size(); i++)
	{
		this->dice_num[i] = input[i]; //입력받은 주사위 값을 dice_num (주사위 눈 결과값) 에 저장
	}
	sort(this->dice_num.begin(), this->dice_num.end()); //주사위 결과값 정렬
}

// *subtotal = GetSuubtotal() 로 처리


//플레이어가 턴을 넘길 때 최종 결과값 표에 기록, vector<int>값 리턴한다.
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
플레이어 턴이 되었을 때, 연산에 이용할 임시값에 이전 기록값을 더하여 초기화 해준다
public 변수 chart_value(임시값) 벡터에 복사하여 값 전달
*/
void Chart::SetDefaultValue() 
 {
	this->chart_value.clear();//erase(chart_value.egin(), chart_value.end());  //이전 값 정리
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

 //임시값 리턴(한 번 주사위를 던질 때마다 리턴해준다)
 vector<int> Chart::GetChartValue()
{
	 return this->chart_value;
}

 //표에 기록하기로 결정한 값 입력해주기
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
//실행 예시
int main()
{
	ChartFactory factory;
	vector<int>input; //주사위 리턴 값 가정
	Chart play1;
	Chart play2;

	int y = 12;
	play1 = factory.GetChart();
	play2 = factory.GetChart("me");

	while (y > 0)
	{
		play1.SetDefaultValue();		//1. 임시 벡터값 초기화
		play1.GetChartValue();		//2. chart_value 값 리턴
		play1.GetDiceValue(input);		//3. 주사위 결과값 받아오기
		SetUpValue upvalue(&play1);    //연산 class 선언(command)
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
		} //위쪽 표 값 계산

		//for of kind 부터 choice 까지 null 여부 확인 후 값 대입 연산(chart_value에 저장한다)
		if (fok.IsNullptr(&play1.chart_value[6])) //아래쪽 표 값 계산
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

		play1.GetChartValue(); //chart_value 값 리턴
	}


		play1.GetBonus();
		play1.GetSubTotal();
		play1.GetTotalSum();
		play1.GetRoundResult();
}*/