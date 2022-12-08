#include "essential.h"
#include "chart-classes.h"

//Command
void Command::SetDiceNumSet(const vector<int>& dice_num_set) {
	this->dice_num_set.clear();
	for (int i = 0; i < 5; i++) {
		this->dice_num_set.push_back(dice_num_set[i]);
	}
	sort(this->dice_num_set.begin(), this->dice_num_set.end());
}
int Ones::GetPoint() {
	int num = 0;
	int point_per_num = 1;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Twoes::GetPoint() {
int num = 0;
	int point_per_num = 2;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Threes::GetPoint() {
int num = 0;
	int point_per_num = 3;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Fours::GetPoint() {
int num = 0;
	int point_per_num = 4;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Fives::GetPoint() {
int num = 0;
	int point_per_num = 5;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Sixes::GetPoint() {
	int num = 0;
	int point_per_num = 6;
	for (auto i : dice_num_set) {
		if (i== point_per_num)num++;
	}
	return num * point_per_num;
}
int Choice::GetPoint() {
	int num = 0;
	for (auto i : dice_num_set) {
		num += i;
	}
	return num;
}
int FullHouse::GetPoint() {
	map<int, int> m;
	for (auto i : dice_num_set) {
		m[i]++;
	}
	int isThree=0, isTwo=0;
	for (int i = 1; i <= 6; i++) {
		if (m[i] == 3)isThree = i;
		else if (m[i] == 2)isTwo = i;
	}
	if (isThree && isTwo)return isThree * 3 + isTwo * 2;
	else return 0;
}
int SmallStraight::GetPoint() {
	int dp[5];
	dp[0] = 1;
	int ans = 1;
	sort(dice_num_set.begin(), dice_num_set.end());
	for (int i = 1; i < 5; i++) {
		if (dice_num_set[i] == dice_num_set[i - 1] + 1) {
			dp[i] = dp[i - 1] + 1;
			ans = max(ans, dp[i]);
		}
		else if (dice_num_set[i] == dice_num_set[i - 1]) {
			dp[i] = dp[i - 1];
		}
		else dp[i] = 1;
	}
	if (ans >= 4)return 15;
	else return 0;
}
int LargeStraight::GetPoint() {
	int dp[5];
	dp[0] = 1;
	sort(dice_num_set.begin(), dice_num_set.end());
	int ans = 1;
	for (int i = 1; i < 5; i++) {
		if (dice_num_set[i] == dice_num_set[i - 1] + 1) {
			dp[i] = dp[i - 1] + 1;
			ans = max(ans, dp[i]);
		}
		else if (dice_num_set[i] == dice_num_set[i - 1]) {
			dp[i] = dp[i - 1];
		}
		else dp[i] = 1;
	}
	if (ans >= 5)return 30;
	else return 0;
}
int FourOfKind::GetPoint() {
	map<int, int> m;
	int sum = 0;
	for (auto i : dice_num_set) {
		m[i]++;
		sum += i;
	}
	int isFour = 0;
	for (int i = 1; i <= 6; i++) {
		if (m[i] == 4)isFour = i;
	}
	if (isFour)return sum;
	else return 0;
}
int Yacht::GetPoint() {
	map<int, int> m;
	for (auto i : dice_num_set) {
		m[i]++;
	}
	int isFive = 0;
	for (int i = 1; i <= 6; i++) {
		if (m[i] == 5)isFive = i;
	}
	if (isFive)return 50;
	else return 0;
}

//Chart
Chart::Chart() {
	for (int i = 0; i < 12; i++) {
		chart_nums.push_back(-1);
	}
	command_set.push_back(new Ones());
	command_set.push_back(new Twoes());
	command_set.push_back(new Threes());
	command_set.push_back(new Fours());
	command_set.push_back(new Fives());
	command_set.push_back(new Sixes);
	command_set.push_back(new Choice);
	command_set.push_back(new FourOfKind);
	command_set.push_back(new FullHouse);
	command_set.push_back(new SmallStraight);
	command_set.push_back(new LargeStraight);
	command_set.push_back(new Yacht);
}
Chart::Chart(const vector<int>& dice_num_set) {
	for (int i = 0; i < 12; i++) {
		chart_nums.push_back(-1);
	}
	command_set.push_back(new Ones());
	command_set.push_back(new Twoes());
	command_set.push_back(new Threes());
	command_set.push_back(new Fours());
	command_set.push_back(new Fives());
	command_set.push_back(new Sixes);
	command_set.push_back(new Choice);
	command_set.push_back(new FourOfKind);
	command_set.push_back(new FullHouse);
	command_set.push_back(new SmallStraight);
	command_set.push_back(new LargeStraight);
	command_set.push_back(new Yacht);
	this->SetDiceNumSet(dice_num_set);
}
void Chart::SetDiceNumSet(const vector<int>& dice_num_set) {
	this->dice_num_set = dice_num_set;
}
void Chart::FillValues() {
	for (int i = 0; i < 12; i++) {
		command_set[i]->SetDiceNumSet(dice_num_set);
		chart_nums[i] = command_set[i]->GetPoint();
	}
}
void Chart::SetChartNum(const int& idx, const int& val) {
	chart_nums[idx] = val;
	sub_total = 0; total += val;
	for (int i = 0; i < 6; i++) {
		if(chart_nums[i]!=-1)
			sub_total += chart_nums[i];
	}
	if (sub_total >= 63)total += 35;
}
vector<int> Chart::GetChartNum() {
	vector<int> tmp;
	for (int i = 0; i < 12; i++) {
		tmp.push_back(chart_nums[i]);
	}
	return tmp;
}
Chart& Chart::operator=(Chart& chart) {
	this->chart_nums = chart.chart_nums;
	this->sub_total = chart.sub_total;
	this->total = chart.total;
	return *this;
}
