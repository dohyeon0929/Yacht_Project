#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"

int RandRange(const int& min, const int& max);

//DiceState Keep/Activate
class DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state)=0;  
	virtual bool IsActivated()=0; 
};

class DiceStateActivate : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return true; }
};


class DiceStateKeep : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return false; }
};

//Dice
class Dice
{
protected:
	int dice_num ; 
	vector<int> dice_num_set; 
	DiceState* dice_state = new DiceStateActivate(); 
	bool is_activated=true;
public:		
	Dice();
	virtual void Roll(); 
	virtual void Toggle(); 
	bool IsActivated();
	bool operator<(const Dice& dice) const;
	bool operator==(const Dice& dice) const;
	operator int() { return dice_num; }
	int GetDiceNum();
	Dice& operator=(Dice& dice);
	void SetDiceNum(const int& num);
	void SetActivated();
};


//class NormalDice : public Dice
//{
//public:
//	NormalDice(); 
//	bool isNormal() { return true; }
//};
//
//class TwoSideDice : public Dice
//{
//private:
//	int side_count = 2;
//public:
//	TwoSideDice();
//	void SetDiceNumSet();
//};

// For TwoSideDice
//class SelectNums {
//private:
//	int count;
//	vector<int> num_set; 
//public:
//	SelectNums(int count = 2) { this->count = count; }
//	void Select();
//	vector<int> GetDiceNumSet() { return num_set; }
//};

class DiceSet {
protected:
	vector<Dice> dice_set;
public:
	DiceSet();
	virtual Dice GetDice(const int& idx); 
	virtual vector<Dice>& GetDiceSet() { return dice_set; }
	virtual int Size() { return dice_set.size(); }
	virtual void Add(const Dice& dice); 
	virtual void Remove(const int& count); 
	virtual void Clear(); 
	void DefaultValue();
	void Roll();
	void Toggle(const int& num);
};

//class ActivateDiceSet : public DiceSet
//{
//private:
//	multiset<Dice> dice_multiset;
//public:
//	virtual Dice GetDice(const int& idx); 
//	virtual vector<Dice>& GetDiceSet();
//	virtual int Size() { return dice_multiset.size(); }
//	virtual void Add(const Dice& dice) override;
//	virtual void Remove(const int& idx) override; 
//	virtual void Clear();
//};
//
//class DiceSetFactory 
//{
//private:
//	DiceSet dice_set;
//	DiceSet special_dice_set;
//	int dice_count=5;
//public:
//	DiceSetFactory SetDiceCount(const int& count); 
//	DiceSetFactory ChangeSpecialDice(const Dice& dice); 
//	DiceSet GetDiceSet(); 
//};
#endif
