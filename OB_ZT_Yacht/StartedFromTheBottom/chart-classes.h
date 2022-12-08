#pragma once
#ifndef CHART_CLASSES_H
#define CHART_CLASSES_H
#include "dice-classes.h"

class Command
{
protected:
	vector<Dice> dice_set;
	vector<int> dice_num_set;
public:
	Command() {}
	virtual void SetDiceNumSet(const vector<int>& dice_num_set);
	virtual int GetPoint() { return 0; }
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

class Chart {
private:
	vector<int> chart_nums;
	vector<int> dice_num_set;
	int sub_total = 0;
	int total = 0;
	//static const Ones ones; static const Twoes twoes; static const Threes threes; static const Fours fours; static const Fives fives; static const Sixes sixes;
	//static const Choice choice; static const FourOfKind fok; static const FullHouse fh; static const SmallStraight ss; static const LargeStraight ls; static const Yacht yacht;
	//static  Ones ones; static  Twoes twoes; static  Threes threes; static  Fours fours; static Fives fives; static  Sixes sixes;
	//static  Choice choice; static  FourOfKind fok; static  FullHouse fh; static  SmallStraight ss; static  LargeStraight ls; static  Yacht yacht;
	vector<Command*> command_set;
public:
	Chart();
	Chart(const vector<int>& dice_num_set);
	void SetDiceNumSet(const vector<int>& dice_num_set);
	void FillValues();

	void SetChartNum(const int& idx, const int& val);
	vector<int> GetChartNum();
	int GetSubTotal() { return sub_total; }
	int GetTotal() { return total; }
	Chart& operator=(Chart& chart);
};

#endif
