#pragma once
#ifndef CHART_CLASSES_H
#define CHART_CLASSES_H
#include "dice-classes.h"

class Command // 표의 12가지 항목을 주사위 값에 따라 판단할 객체들의 부모 추상 클래스. 
{
protected:
	vector<Dice> dice_set; 
	vector<int> dice_num_set; // 주사위의 값들만 저장한 벡터
public:
	Command() {}
	virtual void SetDiceNumSet(const vector<int>& dice_num_set); // 주사위 셋 설정
	virtual int GetPoint() = 0; // 해당 주사위 셋에서 해당 항목은 몇 점인지 반환
};

class Ones : public Command {
public:
	virtual int GetPoint();
};
class Twoes : public Command {
public:
	virtual int GetPoint();
};
class Threes : public Command {
public:
	virtual int GetPoint();
};
class Fours : public Command {
public:
	virtual int GetPoint();
};
class Fives : public Command {
public:
	virtual int GetPoint();
};
class Sixes : public Command {
public:
	virtual int GetPoint();
};
class Choice : public Command {
public:
	virtual int GetPoint();
};
class FullHouse : public Command {
public:
	virtual int GetPoint();
};
class SmallStraight : public Command {
public:
	virtual int GetPoint();
};
class LargeStraight : public Command {
public:
	virtual int GetPoint();
};
class FourOfKind : public Command {
public:
	virtual int GetPoint();
};
class Yacht : public Command {
public:
	virtual int GetPoint();
};

class Chart { // 표 객체
private:
	vector<int> chart_nums; // 표에 들어갈 숫자 집합
	vector<int> dice_num_set; // 표에 적용되는 주사위 수 집합
	int sub_total = 0; // ones~sixes 까지의 합을 저장할 변수
	int total = 0; // 전체 숫자들의 합 저장할 변수
	vector<Command*> command_set; // ones~yacht까지 커맨드들을 저장할 벡터
public:
	Chart();
	Chart(const vector<int>& dice_num_set);
	void FillValues(); // 주사위 셋 바탕으로 값 채우기

	void SetDiceNumSet(const vector<int>& dice_num_set); 
	void SetChartNum(const int& idx, const int& val); // 표의 특정 인덱스의 숫자만 수정
	vector<int> GetChartNum(); // 차트의 숫자 전체 집합을 반환
	int GetSubTotal() { return sub_total; } 
	int GetTotal() { return total; }
	Chart& operator=(Chart& chart);
};

#endif
