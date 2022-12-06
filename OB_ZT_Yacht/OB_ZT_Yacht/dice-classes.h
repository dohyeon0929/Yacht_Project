#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"
int RandRange(const int& min, const int& max);

// Dice의 상태 activate/keep
class DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state)=0; // 주사위 상태 토글
	virtual bool IsActivated()=0; // 주사위가 Activate인지 반환
};

// 다음 주사위 롤 때 굴릴 수 있는 상태
class DiceStateActivate : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return true; }
};

// 다음 주사위 롤 때 굴릴 수 없는 상태
class DiceStateKeep : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return false; }
};

// 주사위 관련 정보와 기능을 담는 클래스
class Dice
{
protected:
	int dice_num = 0; //주사위를 굴려서 나온 수
	vector<int> dice_num_set; //주사위 6면의 눈들의 집합
	DiceState* dice_state = new DiceStateActivate(); //주사위의 상태를 의미
public:		
	virtual void Roll(); //주사위를 굴려 임의의 값을 갖는다 
	virtual void Toggle(); //주사위의 상태를 바꾼다
	bool operator<(const Dice& dice) const;
	Dice& operator=(Dice& dice);
};

//평범한 주사위
class NormalDice : public Dice
{
public:
	NormalDice(); 
	bool isNormal() { return true; }
};

//특수능력을 통해 사용할 수 있는 숫자 2개로 이루어진 주사위
class TwoSideDice : public Dice
{
private:
	int side_count = 2;
public:
	TwoSideDice();
	void SetDiceNumSet();
};

// TwoSideDice를 쓸 때 사용할 두 개의 숫자를 고르고 넘겨주는 클래스
class SelectNums {
private:
	int count;
	vector<int> num_set; 
public:
	SelectNums(int count = 2) { this->count = count; }
	void Select(); //숫자 count개 입력받기
	vector<int> GetDiceNumSet() { return num_set; }
};

// 주사위들의 집합
class DiceSet {
protected:
	vector<Dice> dice_set;
public:
	virtual Dice GetDice(const int& idx); //idx 인덱스에 해당되는 주사위 반환
	virtual vector<Dice> GetDiceSet() { return dice_set; }
	virtual int Size() { return dice_set.size(); }// 주사위 집합의 크기를 반환
	virtual void Add(const Dice& dice); //주사위 집합 dices에 dice 추가
	virtual void Remove(const int& count); //주사위 집합에서 파라미터에 해당되는 종류의 dice 제거
	virtual void Clear(); //주사위 집합 비우기
};

// Activate 상태인 주사위들의 집합
class ActivateDiceSet : public DiceSet
{
private:
	multiset<Dice> dice_multiset;
public:
	virtual Dice GetDice(const int& idx); 
	virtual vector<Dice> GetDiceSet();
	virtual int Size() { return dice_multiset.size(); }
	virtual void Add(const Dice& dice) override;
	virtual void Remove(const int& idx) override; 
	virtual void Clear();
};

// DiceSet 생성하는 클래스
class DiceSetFactory 
{
private:
	DiceSet dice_set;
	DiceSet special_dice_set;
	int dice_count=5;
public:
	DiceSetFactory SetDiceCount(const int& count); // 생성할 DiceSet의 dice 개수 설정
	DiceSetFactory ChangeSpecialDice(const Dice& dice); // 생성할 DiceSet에서 normal_dice 하나를 제거하고 파라미터로 받은 dice 추가
	DiceSet GetDiceSet(); // 설정한 조건대로 DiceSet을 생성하고 반환함
};
#endif
