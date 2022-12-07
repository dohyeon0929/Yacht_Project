#pragma once
#include "chart_needs.h"
using namespace std;
//표 class
class Chart
{
	private:
				//하단 차트 담당 클래스 선언
		Chart();
		Chart(string name);
		string player_name = "";
		int *aces = nullptr;	//1  
		int *deuces = nullptr;	//2
		int *threes = nullptr;	//3
		int *fours = nullptr;	//4
		int *fives = nullptr;	//5
		int *sixes = nullptr;	//6
		int* bonus = nullptr;				//보너스 점수
		int* subtotal = nullptr;			//서브 토탈

		int *choice = nullptr;				//choice				7
		int *four_of_a_kind = nullptr;		//4개 같은수			8
		int *full_house = nullptr;			//풀 하우스(2개 3개)	9
		int *s_straight = nullptr;			//연속된 4개			10
		int *b_straight = nullptr;			//연속된 5개			11
		int *yacht = nullptr;				//같은수 5개			12
		int* totalvalue = nullptr;
	public:
		friend class ChartFactory;  //차트 팩토리 생성
		vector<int> dice_num;		//주사위 값
		vector<int> chart_value;	//임시 값
		void SetDefaultValue(); //벡터 초기화(chart_value)
		vector<int> GetChartValue(); //chart_value 값 리턴 
		vector<int>GetRoundResult(); // 라운드 결과값 리턴

		void GetTotalSum();						//전체 값 합
		void GetSubTotal();						//위쪽 표 값 더하기
		void PushValue(int choose_num);			//임시값 계산 결과중 저장할 값 확정짓기
		void GetBonus();						//보너스 점수 확인
		void GetDiceValue(vector<int>input);	//주사위로부터 입력받은 값 저장
		
};


// 위쪽 표, command
class UpChart //: public ISetValue
{
public:
	//virtual ~UpChart();
	virtual bool IsNullptr(int* values);
	virtual int SetValue(vector<int>dice_num);
};


//주사위 값에 따른 표 값 설정
class SetUpValue : public UpChart
{
private:
	Chart* chart;
public:
	//SetUpValue(Chart& chart);
	int SetValue(vector<int>cal_value, int number);
};



//아래쪽 표, command

class DownChart //: public ISetValue
{
public:
	//virtual ~DownChart();
	virtual bool IsNullptr(int* values);
	virtual int SetValue(vector<int>dice_num);
};


class CheckFOK : public DownChart
{
private:
	Chart* chart;
public:
	//CheckFOK(Chart& chart);
	int SetValue(vector<int>dice_num);
};

class CheckFH : public DownChart
{
private:
	Chart* chart;
public:
	//CheckFH(Chart& chart);
	int SetValue(vector<int>dice_num);
};

class CheckSS : public DownChart
{
private:
	Chart* chart;
public:
	//CheckSS(Chart& chart);
	int SetValue(vector<int>dice_num);
};

class CheckBS : public DownChart
{
private:
	Chart* chart;
public:
	//CheckBS(Chart& chart);
	int SetValue(vector<int>dice_num);
};


class CheckYacht : public DownChart
{
private:
	Chart* chart;
public:
	//CheckYacht(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckChoice : public DownChart
{
private:
	Chart* chart;
public:
	//CheckChoice(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class ChartFactory
{
	public:
		Chart GetChart();
		Chart GetChart(string name);
};



class Scene
{
public:
	virtual vector<int> DrawScene(Chart &player) = 0;
};

class StartScene : Scene
{
public:
	vector<Chart> setChart();
	//void game_scene();
};


class GameScene : Scene
{
private:
	int game_round = 12;
public:
	virtual void SetGameRound(int &game_round);
	virtual int GetGameRound(vector<Chart>& player, int& game_round);
	virtual vector<int> DrawScene(Chart & player) = 0;
};


class GameScenePrev : GameScene
{
public:
	vector<int> DrawScene(Chart &player);
};

class GameSceneCal : GameScene
{
public:
	vector<int> DrawScene(Chart &player);
};

class GameSceneResult : GameScene
{
public:
	vector<int> DrawScene(Chart &player);
};


/*
class EndScene : Scene
{
private:

public:
	vector<int> DrawScene(Chart player);
};*/




