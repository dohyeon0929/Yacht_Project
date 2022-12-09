#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"

//DiceState Keep/Activate
//class DiceState
//{
//private:
//public:
//	virtual void Toggle(DiceState* dice_state)=0;  
//	virtual bool IsActivated()=0; 
//};
//
//class DiceStateActivate : public DiceState
//{
//private:
//public:
//	virtual void Toggle(DiceState* dice_state);
//	virtual bool IsActivated() { return true; }
//};
//
//
//class DiceStateKeep : public DiceState
//{
//private:
//public:
//	virtual void Toggle(DiceState* dice_state);
//	virtual bool IsActivated() { return false; }
//};

//Dice
class Dice
{
protected:
	int dice_num ; 
	vector<int> dice_num_set; 
	//DiceState* dice_state = new DiceStateActivate(); 
	bool is_activated=true;
public:		
	Dice();
	virtual void Roll(); // 주사위 굴리기
	virtual void Toggle(); // 주사위 상태 전환
	bool IsActivated(); // 주사위 상태 묻기
	bool operator<(const Dice& dice) const;  
	bool operator==(const Dice& dice) const;
	operator int() { return dice_num; }
	Dice& operator=(Dice& dice);
	int GetDiceNum(); // 주사위 수 반환
	void SetDiceNum(const int& num); // 주사위 수 설정
	void SetActivated(); // 주사위 상태 activated로 변경
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
	virtual Dice GetDice(const int& idx); // 특정 인덱스의 주사위 반환
	virtual vector<Dice>& GetDiceSet() { return dice_set; } // 주사위 벡터 반환
	virtual int Size() { return dice_set.size(); } // 주사위셋 크기 반환
	virtual void Add(const Dice& dice); // 주사위 셋에 주사위 추가
	virtual void Remove(const int& count);  // 특정 인덱스 주사위 제거
	virtual void Clear(); // 주사위 셋 비우기
	void DefaultValue(); // 주사위들 디폴트 값으로 설정
	void Roll(); // 주사위 셋 전체 굴리기
	void Toggle(const int& num); // 특정 주사위 상태 토글
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
