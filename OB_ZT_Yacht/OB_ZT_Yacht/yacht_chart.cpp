#include <iostream>
#include "yatch_chart.h"

// 생성자
Chart::Chart()
{
	this->player_name = "guest";
}


//생성자, 플레이어 이름 값을 넣을 때
Chart::Chart(string name)
{
	this->player_name = name;
}


//subtotal 의 값이 63이상이면 bonus를 35로 설정, bonus의 기본값은 null
void Chart::SetBonus() 
{
	if (subtotal > 63)
	{
		bonus = 35;
	}
}


//위쪽 표 합, 하단 표의 합 , 보너스 점수의 합 더하기
void Chart::SetTotalSum() 
{
	this->totalvalue = subtotal + choice + four_of_a_kind + full_house + s_straight + b_straight + totalvalue + bonus;
}


//상단 표 값
void Chart::SetSubTotal() 
{
	this->subtotal = aces + deuces + threes + fours + fives + sixes;
}


//주사위로부터 받은 vector<int> 형태로 리턴
void Chart::SetDiceValue(vector<int>input) 
{
	this->dice_num.clear();//erase(dice_num.begin(), dice_num.end()); //이전 주사위 저장된 값 초기화
	for (int i = 0; i < input.size(); i++)
	{
		this->dice_num.push_back(input[i]); //입력받은 주사위 값을 dice_num (주사위 눈 결과값) 에 저장
	}
	sort(this->dice_num.begin(), this->dice_num.end()); //주사위 결과값 정렬
}


//승자 결정 this 와 파라미터로 받은 chart 객체의 totalvalue 값 비교
int Chart::Winner(Chart player2)
{
	if (this->totalvalue > player2.totalvalue) return 1;
	else if (this->totalvalue > player2.totalvalue) return 2;
	else return 0;
}

// *subtotal = GetSuubtotal() 로 처리


//플레이어가 턴을 넘길 때 최종 결과값 표에 기록, vector<int>값 리턴한다.
vector<int> Chart::GetRoundResult()
{
	this->aces = 10;

	cout << "test\n";
	vector<int>Result;
	Result.push_back(this->aces);
	Result.push_back(this->deuces);
	Result.push_back(this->threes);
	Result.push_back(this->fours);
	Result.push_back(this->fives);
	Result.push_back(this->sixes);
	Result.push_back(this->bonus);
	Result.push_back(this->subtotal);

	Result.push_back(this->choice);
	Result.push_back(this->four_of_a_kind);
	Result.push_back(this->full_house);
	Result.push_back(this->s_straight);
	Result.push_back(this->b_straight);
	Result.push_back(this->yacht);
	Result.push_back(this->totalvalue);
	return Result;
}

vector<int>Chart::GetDiceNum()
{
	return this->dice_num;
}
/*
플레이어 턴이 되었을 때, 연산에 이용할 임시값에 이전 기록값을 더하여 초기화 해준다
public 변수 chart_value(임시값) 벡터에 복사하여 값 전달
*/
void Chart::SetDefaultValue()
{
	this->chart_value.clear();//erase(chart_value.egin(), chart_value.end());  //이전 값 정리
	this->chart_value.push_back(this->aces);		//1
	this->chart_value.push_back(this->deuces);		//2		this->chart_value.push_back(*this->threes); //3
	this->chart_value.push_back(this->fours);		//4
	this->chart_value.push_back(this->fives);		//5
	this->chart_value.push_back(this->sixes);		//6
	this->chart_value.push_back(this->bonus);
	this->chart_value.push_back(this->subtotal);

	this->chart_value.push_back(this->choice);				//choice
	this->chart_value.push_back(this->four_of_a_kind);		//4 of kind
	this->chart_value.push_back(this->full_house);			// full house
	this->chart_value.push_back(this->s_straight);			// small straight
	this->chart_value.push_back(this->b_straight);			// large straight
	this->chart_value.push_back(this->yacht);				// yacht
	this->chart_value.push_back(this->totalvalue);
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
		if (this->aces != -1)
			this->aces = this->chart_value[0];
		break;
	case 2:
		if (this->deuces != -1)
			this->deuces = chart_value[1];
		break;
	case 3:
		if (this->threes != -1)
			this->threes = chart_value[2];
		break;
	case 4:
		if (this->fours != -1)
			this->fours = chart_value[3];
		break;
	case 5:
		if (this->fives != -1)
			this->fives = chart_value[4];
		break;
	case 6:
		if (this->sixes != -1)
			this->sixes = chart_value[5];
		break;
	case 7:
		if (this->choice != -1)
			this->choice = chart_value[6];
		break;
	case 8:
		if (this->four_of_a_kind != -1)
			this->four_of_a_kind = chart_value[7];
		break;
	case 9:
		if (this->full_house != -1)
			this->full_house = chart_value[8];
		break;
	case 10:
		if (this->s_straight != -1)
			this->s_straight = chart_value[9];
		break;
	case 11:
		if (this->b_straight != -1)
			this->b_straight = chart_value[10];
		break;
	case 12:
		if (this->yacht != -1)
			this->yacht = chart_value[11];
		break;
	}
	
}


/* 
<ChartFactory>
Chart() ==> 차트 생성
Chart(string) ==> 차트 생성, 이름 설정
*/
Chart ChartFactory::GetChart()
{
	return Chart();
}

Chart ChartFactory::GetChart(string name)
{
	return Chart(name);
}


/*
* CalSet()
* 주사위값 (dice_num)을 받아온 뒤
* 연산할 수 있는 모든 경우 수의 클래스를 생성
* 연산 결과값 chart_value에 저장
*/
void Chart::CalSet()
{
	CheckUpValue upvalue(this);
	CheckFOK fok(this);
	CheckFH fh(this);
	CheckSS ss(this);
	CheckBS bs(this);
	CheckYacht yatcht(this);
	CheckChoice choice(this);
	//위쪽 표 값 계산
	if (upvalue.IsAble(this->aces) == false) {
		this->chart_value[0] = upvalue.SetValue(this->dice_num, 0);
		cout <<"aces : "<< this->aces << " / input";
	}
	if (upvalue.IsAble(this->deuces == false)){
		this->chart_value[1] = upvalue.SetValue(this->dice_num, 1);
		cout << "aces : " << this->deuces << " / input";
	}
	if (upvalue.IsAble(this->threes)){
		this->chart_value[2] = upvalue.SetValue(this->dice_num, 2);
		cout << "aces : " << this->threes << " / input";
	}
	if (upvalue.IsAble(this->fours)){
		this->chart_value[3] = upvalue.SetValue(this->dice_num, 3);
		cout << "aces : " << this->fours << " / input";
	}
	if (upvalue.IsAble(this->fives)){
		this->chart_value[4] = upvalue.SetValue(this->dice_num, 4);
		cout << "aces : " << this->fives << " / input";
	}
	if (upvalue.IsAble(this->sixes)){
		this->chart_value[5] = upvalue.SetValue(this->dice_num, 5);
		cout << "aces : " << this->sixes << " / input";
	}
	//for of kind 부터 choice 까지 null 여부 확인 후 값 대입 연산(chart_value에 저장한다)
	if (fok.IsAble(this->choice))
		this->chart_value[6] = fok.SetValue(this->dice_num);

	if (fh.IsAble(this->four_of_a_kind))
		this->chart_value[7] = fh.SetValue(this->dice_num);

	if (ss.IsAble(this->full_house))
		this->chart_value[8] = ss.SetValue(this->dice_num);

	if (bs.IsAble(this->s_straight))
		this->chart_value[9] = bs.SetValue(this->dice_num);

	if (yatcht.IsAble(this->b_straight))
		this->chart_value[10] = yatcht.SetValue(this->dice_num);

	if (choice.IsAble(this->yacht))
		this->chart_value[11] = choice.SetValue(this->dice_num);
}



