#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"

// �ֻ��� ���� ������ ����� ��� Ŭ����
class Dice
{
private:
	int dice_num = 0; //�ֻ����� ������ ���� ��
	DiceNumSet dice_num_set; //�ֻ��� 6���� ������ ����
	DiceState* dice_state = new DiceStateActivate(); //�ֻ����� ���¸� �ǹ�
public:		
	virtual void Roll(); //�ֻ����� ���� ������ ���� ���´� 
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
	DiceNumSet dice_num_set; 
public:
	void Select();
	DiceNumSet GetDiceNumSet();
};

// Dice�� �� �鿡 �����ִ� ������ ����
class DiceNumSet {
private: 
	vector<int> dice_num_set;
public:
	vector<int> GetDiceNumSet();
	void add(); //dice_num_set�� ���ο� ���� �߰�
	void remove(int num); //dice_num_set���� ���� ����
};

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

// �ֻ������� ����
class DiceSet {
private:
	vector<Dice> dices;
public:
	virtual int size(); // �ֻ��� ������ ũ�⸦ ��ȯ
	virtual void add(); //�ֻ��� ���� dices�� dice �߰�
	virtual void remove(Dice dice); //�ֻ��� ���տ��� �Ķ���Ϳ� �ش�Ǵ� ������ dice ����
};

// Keep ������ �ֻ������� ����
class KeepDiceSet : public DiceSet{
};

// Activate ������ �ֻ������� ����
class ActivateDiceSet : public DiceSet{
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
