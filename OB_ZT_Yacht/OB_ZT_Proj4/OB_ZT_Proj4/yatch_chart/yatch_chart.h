#pragma once
#include "chart_needs.h"
using namespace std;
//ǥ class
class Chart
{
	private:
				//�ϴ� ��Ʈ ��� Ŭ���� ����
		Chart();
		Chart(string name);
		string player_name = "";
		int *aces = nullptr;	//1  
		int *deuces = nullptr;	//2
		int *threes = nullptr;	//3
		int *fours = nullptr;	//4
		int *fives = nullptr;	//5
		int *sixes = nullptr;	//6
		int* bonus = nullptr;				//���ʽ� ����
		int* subtotal = nullptr;			//���� ��Ż

		int *choice = nullptr;				//choice				7
		int *four_of_a_kind = nullptr;		//4�� ������			8
		int *full_house = nullptr;			//Ǯ �Ͽ콺(2�� 3��)	9
		int *s_straight = nullptr;			//���ӵ� 4��			10
		int *b_straight = nullptr;			//���ӵ� 5��			11
		int *yacht = nullptr;				//������ 5��			12
		int* totalvalue = nullptr;
	public:
		friend class ChartFactory;  //��Ʈ ���丮 ����
		vector<int> dice_num;		//�ֻ��� ��
		vector<int> chart_value;	//�ӽ� ��
		void SetDefaultValue(); //���� �ʱ�ȭ(chart_value)
		vector<int> GetChartValue(); //chart_value �� ���� 
		vector<int>GetRoundResult(); // ���� ����� ����

		void GetTotalSum();						//��ü �� ��
		void GetSubTotal();						//���� ǥ �� ���ϱ�
		void PushValue(int choose_num);			//�ӽð� ��� ����� ������ �� Ȯ������
		void GetBonus();						//���ʽ� ���� Ȯ��
		void GetDiceValue(vector<int>input);	//�ֻ����κ��� �Է¹��� �� ����
		
};


// ���� ǥ, command
class UpChart //: public ISetValue
{
public:
	//virtual ~UpChart();
	virtual bool IsNullptr(int* values);
	virtual int SetValue(vector<int>dice_num);
};


//�ֻ��� ���� ���� ǥ �� ����
class SetUpValue : public UpChart
{
private:
	Chart* chart;
public:
	//SetUpValue(Chart& chart);
	int SetValue(vector<int>cal_value, int number);
};



//�Ʒ��� ǥ, command

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




