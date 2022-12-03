#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"

// 주사위 관련 정보와 기능을 담는 클래스
class Dice
{
private:
	int dice_num = 0; //주사위를 굴려서 나온 수
	DiceNumSet dice_num_set; //주사위 6면의 눈들의 집합
	DiceState* dice_state = new DiceStateActivate(); //주사위의 상태를 의미
public:		
	virtual void Roll(); //주사위를 굴려 임의의 값을 갖는다 
	virtual void Toggle(); //주사위의 상태를 바꾼다
};

//평범한 주사위
class NormalDice : public Dice
{
public:
	NormalDice(); 
};

//특수능력을 통해 사용할 수 있는 숫자 2개로 이루어진 주사위
class TwoSideDice : public Dice
{
public:
	TwoSideDice();
	void SetDiceNumSet();
};

// TwoSideDice를 쓸 때 사용할 두 개의 숫자를 고르고 넘겨주는 클래스
class SelectNums {
private:
	DiceNumSet dice_num_set; 
public:
	void Select();
	DiceNumSet GetDiceNumSet();
};

// Dice의 각 면에 적혀있는 수들의 집합
class DiceNumSet {
private: 
	vector<int> dice_num_set;
public:
	vector<int> GetDiceNumSet();
	void add(); //dice_num_set에 새로운 수를 추가
	void remove(int num); //dice_num_set에서 수를 삭제
};

// Dice의 상태 activate/keep
class DiceState
{
private:
public:
	virtual void Toggle()=0; // 주사위 상태 토글
	virtual void IsActivated()=0; // 주사위가 Activate인지 반환
};

// 다음 주사위 롤 때 굴릴 수 있는 상태
class DiceStateActivate : public DiceState{
private:
public:
	virtual void Toggle();
	virtual void IsActivated();
};

// 다음 주사위 롤 때 굴릴 수 없는 상태
class DiceStateKeep : public DiceState{
private:
public:
	virtual void Toggle();
	virtual void IsActivated();
};

// 주사위들의 집합
class DiceSet {
private:
	vector<Dice> dices;
public:
	virtual int size(); // 주사위 집합의 크기를 반환
	virtual void add(); //주사위 집합 dices에 dice 추가
	virtual void remove(Dice dice); //주사위 집합에서 파라미터에 해당되는 종류의 dice 제거
};

// Keep 상태인 주사위들의 집합
class KeepDiceSet : public DiceSet{
};

// Activate 상태인 주사위들의 집합
class ActivateDiceSet : public DiceSet{
	int GetSize();
};

// Dice를 생성하는 클래스
class DiceSetFactory {
private:
	DiceSet dice_set;
	int dice_count;
public:
	DiceSetFactory SetDiceCount(); // 생성할 DiceSet의 dice 개수 설정
	DiceSetFactory ChangeSpecialDice(Dice dice); // 생성할 DiceSet에서 normal_dice 하나를 제거하고 파라미터로 받은 dice 추가
	DiceSet GetDiceSet(); // 설정한 조건대로 DiceSet을 생성하고 반환함
};
#endif
