#include "dice-classes.h"

//Dice
Dice::Dice() {
	dice_num_set = { 1,2,3,4,5,6 };
	dice_num = 0;
}
void Dice::Roll() {
	//dice_num = dice_num_set[RandRange(0, dice_num_set.size() - 1)];
}
void Dice::Toggle() {
	if (is_activated)is_activated = false;
	else is_activated = true;
}
bool Dice::IsActivated() {
	return is_activated;
}
bool Dice::operator<(const Dice& dice)const {
	return this->dice_num > dice.dice_num;
}
bool Dice::operator==(const Dice& dice)const {
	return this->dice_num == dice.dice_num;
}
int Dice::GetDiceNum() {
	return dice_num;
}
Dice& Dice::operator=(Dice& dice) {
	this->dice_num = dice.dice_num;
	this->dice_num_set = dice.dice_num_set;
	return *this;
}
void Dice::SetDiceNum(const int& num) {
	dice_num = num;
}
void Dice::SetActivated() {
	is_activated = true;
}

//DiceSet
DiceSet::DiceSet() {
	vector<Dice> v(5);
	dice_set = v;
}
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
void DiceSet::DefaultValue(){
	for (int i = 0; i < 5; i++) {
		dice_set[i].SetDiceNum(0);
		dice_set[i].SetActivated();
	}
}
void DiceSet::Roll() { 
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++) {
		if(dice_set[i].IsActivated())
			dice_set[i].SetDiceNum(rand() % 6 + 1);
	}
}
void DiceSet::Toggle(const int& num) {
	dice_set[num].Toggle();
}
