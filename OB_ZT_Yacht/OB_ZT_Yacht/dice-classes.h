#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"

//// Dice�� �� �鿡 �����ִ� ������ ����
//class DiceNumSet {
//private: 
//	vector<int> dice_num_set;
//public:
//	vector<int> GetDiceNumSet();
//	void add(); //dice_num_set�� ���ο� ���� �߰�
//	void remove(int num); //dice_num_set���� ���� ����
//};

// Dice�� ���� activate/keep
class DiceState
{
private:
public:
	virtual void Toggle()=0; // �ֻ��� ���� ���
	virtual void IsActivated()=0; // �ֻ����� Activate���� ��ȯ
};

// ���� �ֻ��� �� �� ���� �� �ִ� ����
class DiceStateActivate : public DiceState{
private:
public:
	virtual void Toggle();
	virtual void IsActivated();
};

// ���� �ֻ��� �� �� ���� �� ���� ����
class DiceStateKeep : public DiceState{
private:
public:
	virtual void Toggle();
	virtual void IsActivated();
};

// �ֻ��� ���� ������ ����� ��� Ŭ����
class Dice
{
private:
	int dice_num = 0; //�ֻ����� ������ ���� ��
	vector<int> dice_num_set; //�ֻ��� 6���� ������ ����
	DiceState* dice_state = new DiceStateActivate(); //�ֻ����� ���¸� �ǹ�
public:		
	virtual int Roll(); //�ֻ����� ���� ������ ���� ���´� 
	virtual void Toggle(); //�ֻ����� ���¸� �ٲ۴�
};

//����� �ֻ���
class NormalDice : public Dice
{
public:
	NormalDice(); 
};

//Ư���ɷ��� ���� ����� �� �ִ� ���� 2���� �̷���� �ֻ���
class TwoSideDice : public Dice
{
public:
	TwoSideDice();
	void SetDiceNumSet();
};

// TwoSideDice�� �� �� ����� �� ���� ���ڸ� ���� �Ѱ��ִ� Ŭ����
class SelectNums {
private:
	vector<int> dice_num_set; 
public:
	void Select();
	vector<int> GetDiceNumSet();
};

// �ֻ������� ����
class DiceSet {
private:
public:
	virtual int Size(); // �ֻ��� ������ ũ�⸦ ��ȯ
	virtual void Add(); //�ֻ��� ���� dices�� dice �߰�
	virtual void Remove(Dice dice); //�ֻ��� ���տ��� �Ķ���Ϳ� �ش�Ǵ� ������ dice ����
};

// Keep ������ �ֻ������� ����
class KeepDiceSet : public DiceSet{
private:
	vector<Dice> dices;
};

// Activate ������ �ֻ������� ����
class ActivateDiceSet : public DiceSet{
private:
	multiset<Dice> dices;
	int GetSize();
};

// Dice�� �����ϴ� Ŭ����
class DiceSetFactory {
private:
	DiceSet dice_set;
	int dice_count;
public:
	DiceSetFactory SetDiceCount(); // ������ DiceSet�� dice ���� ����
	DiceSetFactory ChangeSpecialDice(Dice dice); // ������ DiceSet���� normal_dice �ϳ��� �����ϰ� �Ķ���ͷ� ���� dice �߰�
	DiceSet GetDiceSet(); // ������ ���Ǵ�� DiceSet�� �����ϰ� ��ȯ��
};
#endif
