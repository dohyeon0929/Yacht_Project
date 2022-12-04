#include "dice-classes.h"
int RandRange(const int& min, const int& max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

//DiceState
void DiceStateActivate::Toggle(DiceState* dice_state) {
	dice_state = new DiceStateKeep();
}

void DiceStateKeep::Toggle(DiceState* dice_state) {
	dice_state = new DiceStateActivate();
}

//Dice
void Dice::Roll() {
	dice_num = dice_num_set[RandRange(0, dice_num_set.size() - 1)];
}

void Dice::Toggle() {
	dice_state->Toggle(dice_state);
}

bool Dice::operator<(const Dice& dice)const {
	return this->dice_num > dice.dice_num;
}

Dice& Dice::operator=(Dice& dice) {
	this->dice_num = dice.dice_num;
	this->dice_num_set = dice.dice_num_set;
	this->dice_state = dice.dice_state;
	return *this;
}
//Dice-NormalDice
NormalDice::NormalDice() {
	dice_num_set = { 1,2,3,4,5,6 };
}


//Dice-TwoSideDice
void TwoSideDice::SetDiceNumSet() {
	SelectNums select_nums(side_count);
	select_nums.Select();
	dice_num_set = select_nums.GetDiceNumSet();
}

//SelectNums
void SelectNums::Select() {
	//UI 어떻게 구현할지에 따라 달린 듯?
	int num;
	for (int i = 0; i < count; i++) {
		cin >> num;
		num_set.push_back(num);
	}
}

//DiceSet
Dice DiceSet::GetDice(const int& idx) {
	auto iter = dice_set.begin();
	for (int i = 0; i < idx; i++)iter++;
	return *iter;
}

void DiceSet::Add(const Dice& dice) {
	dice_set.push_back(dice);
}

void DiceSet::Remove(const int& count) {
	auto iter = dice_set.begin();
	for (int i = 0; i < count; i++) iter++;
	Dice dice; *iter = dice;
}

void DiceSet::Clear() {
	dice_set.clear();
}

//DiceSet - ActivateDiceSet
Dice ActivateDiceSet::GetDice(const int& idx) {
	auto iter = dice_multiset.begin();
	for (int i = 0; i < idx; i++)iter++;
	return *iter;
}

vector<Dice> ActivateDiceSet::GetDiceSet() {
	dice_set.clear();
	for (auto i : dice_multiset) {
		dice_set.push_back(i);
	}
	return dice_set;
}

void ActivateDiceSet::Add(const Dice& dice) {
	dice_multiset.insert(dice);
}

void ActivateDiceSet::Remove(const int& count) {
	auto iter = dice_multiset.begin();
	for (int i = 0; i < count; i++) iter++;
	dice_multiset.erase(iter);
	Dice dice;
}

void ActivateDiceSet::Clear() {
	dice_multiset.clear();
}

//DiceSetFactory
DiceSetFactory DiceSetFactory::SetDiceCount(const int& count) {
	dice_count = count;
	return *this;
}

DiceSetFactory DiceSetFactory::ChangeSpecialDice(const Dice& dice) {
	special_dice_set.Add(dice);
	return *this;
}

DiceSet DiceSetFactory::GetDiceSet() {
	dice_set.Clear();
	int cnt = 0;
	for (auto i : special_dice_set.GetDiceSet()) {
		dice_set.Add(i);
		cnt++;
	}

	special_dice_set.Clear();

	for (int i = 0; i < dice_count - cnt; i++) {
		Dice* dice = new NormalDice();
		dice_set.Add(*dice);
	}
	return dice_set;
}
