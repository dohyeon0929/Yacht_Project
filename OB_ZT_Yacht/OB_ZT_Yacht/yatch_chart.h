#pragma once
#pragma once

#include "chart_needs.h"
using namespace std;
//ǥ class
class Chart
{
private:
	Chart();
	Chart(string name);
	string player_name = "";
	int* aces = nullptr;	//1  
	int* deuces = nullptr;	//2
	int* threes = nullptr;	//3
	int* fours = nullptr;	//4
	int* fives = nullptr;	//5
	int* sixes = nullptr;	//6
	int* bonus = nullptr;				//���ʽ� ����
	int* subtotal = nullptr;			//���� ��Ż

	int* choice = nullptr;				//choice				7
	int* four_of_a_kind = nullptr;		//4�� ������			8
	int* full_house = nullptr;			//Ǯ �Ͽ콺(2�� 3��)	9
	int* s_straight = nullptr;			//���ӵ� 4��			10
	int* b_straight = nullptr;			//���ӵ� 5��			11
	int* yacht = nullptr;				//������ 5��			12
	int* totalvalue = nullptr;
public:

	friend class ChartFactory;		//��Ʈ ���丮 ����
	friend class CalSet;
	vector<int> dice_num;			//�ֻ��� ��
	vector<int> chart_value;		//�ӽ� ��


	vector<int> GetChartValue();	//chart_value �� ���� 
	vector<int> GetRoundResult();	// ���� ����� ����
	void SetDefaultValue();					//chart_value �ʱ�ȭ �� ����� �� ����

	int Winner(Chart Player2);//���� ����ߴ���
	void SetTotalSum();						//��ü �� ��
	void SetSubTotal();						//���� ǥ �� ���ϱ�
	void CalSet();							//���갪 �ӽ� ����

	void PushValue(int choose_num);			//�ӽð� ��� ����� ������ �� Ȯ������
	void SetBonus();						//���ʽ� ���� Ȯ��
	void SetDiceValue(vector<int>input);	//�ֻ����κ��� �Է¹��� �� ����
};


class GameManage
{
public:
	GameManage();
};

//�ֻ��� ���� ���� ǥ �� ����
class CalChart //: public ISetValue
{
private:
	Chart* chart;
public:
	virtual bool IsNullptr(int* values);
	virtual int SetValue(vector<int>dice_num);
};


// ���� ǥ, command
class CheckUpValue : public CalChart
{
private:
	Chart* chart;
public:
	CheckUpValue(Chart* chart);
	int SetValue(vector<int>dice_num, int number);
};

//�Ʒ��� ǥ, command
class CheckFOK : public CalChart
{
private:
	Chart* chart;
public:
	CheckFOK(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckFH : public CalChart
{
private:
	Chart* chart;
public:
	CheckFH(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckSS : public CalChart
{
private:
	Chart* chart;
public:
	CheckSS(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckBS : public CalChart
{
private:
	Chart* chart;
public:
	CheckBS(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckYacht : public CalChart
{
private:
	Chart* chart;
public:
	CheckYacht(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class CheckChoice : public CalChart
{
private:
	Chart* chart;
public:
	CheckChoice(Chart* chart);
	int SetValue(vector<int>dice_num);
};

class ChartFactory
{
public:
	Chart GetChart();
	Chart GetChart(string name);
};







