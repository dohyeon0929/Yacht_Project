#ifndef DICE_CLASSES_H
#define DICE_CLASSES_H

#include "essential.h"
int RandRange(const int& min, const int& max);

// Dice�� ���� activate/keep
class DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state)=0; // �ֻ��� ���� ���
	virtual bool IsActivated()=0; // �ֻ����� Activate���� ��ȯ
};

// ���� �ֻ��� �� �� ���� �� �ִ� ����
class DiceStateActivate : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return true; }
};

// ���� �ֻ��� �� �� ���� �� ���� ����
class DiceStateKeep : public DiceState
{
private:
public:
	virtual void Toggle(DiceState* dice_state);
	virtual bool IsActivated() { return false; }
};

// �ֻ��� ���� ������ ����� ��� Ŭ����
class Dice
{
protected:
	int dice_num = 0; //�ֻ����� ������ ���� ��
	vector<int> dice_num_set; //�ֻ��� 6���� ������ ����
	DiceState* dice_state = new DiceStateActivate(); //�ֻ����� ���¸� �ǹ�
public:		
	virtual void Roll(); //�ֻ����� ���� ������ ���� ���´� 
	virtual void Toggle(); //�ֻ����� ���¸� �ٲ۴�
	bool operator<(const Dice& dice) const;
	Dice& operator=(Dice& dice);
};

//����� �ֻ���
class NormalDice : public Dice
{
public:
	NormalDice(); 
	bool isNormal() { return true; }
};

//Ư���ɷ��� ���� ����� �� �ִ� ���� 2���� �̷���� �ֻ���
class TwoSideDice : public Dice
{
private:
	int side_count = 2;
public:
	TwoSideDice();
	void SetDiceNumSet();
};

// TwoSideDice�� �� �� ����� �� ���� ���ڸ� ����� �Ѱ��ִ� Ŭ����
class SelectNums {
private:
	int count;
	vector<int> num_set; 
public:
	SelectNums(int count = 2) { this->count = count; }
	void Select(); //���� count�� �Է¹ޱ�
	vector<int> GetDiceNumSet() { return num_set; }
};

// �ֻ������� ����
class DiceSet {
protected:
	vector<Dice> dice_set;
public:
	virtual Dice GetDice(const int& idx); //idx �ε����� �ش�Ǵ� �ֻ��� ��ȯ
	virtual vector<Dice> GetDiceSet() { return dice_set; }
	virtual int Size() { return dice_set.size(); }// �ֻ��� ������ ũ�⸦ ��ȯ
	virtual void Add(const Dice& dice); //�ֻ��� ���� dices�� dice �߰�
	virtual void Remove(const int& count); //�ֻ��� ���տ��� �Ķ���Ϳ� �ش�Ǵ� ������ dice ����
	virtual void Clear(); //�ֻ��� ���� ����
};

// Activate ������ �ֻ������� ����
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

// DiceSet �����ϴ� Ŭ����
class DiceSetFactory 
{
private:
	DiceSet dice_set;
	DiceSet special_dice_set;
	int dice_count=5;
public:
	DiceSetFactory SetDiceCount(const int& count); // ������ DiceSet�� dice ���� ����
	DiceSetFactory ChangeSpecialDice(const Dice& dice); // ������ DiceSet���� normal_dice �ϳ��� �����ϰ� �Ķ���ͷ� ���� dice �߰�
	DiceSet GetDiceSet(); // ������ ���Ǵ�� DiceSet�� �����ϰ� ��ȯ��
};
#endif
