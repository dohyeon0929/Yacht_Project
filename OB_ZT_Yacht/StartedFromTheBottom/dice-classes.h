#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H
#include "essential.h"

//Dice
class Dice
{
protected:
	int dice_num ; 
	vector<int> dice_num_set; 
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
#endif
