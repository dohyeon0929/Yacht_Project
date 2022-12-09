#pragma once
#ifndef SYSTEM_CLASSES_H
#define SYSTEM_CLASSES_H
#include "essential.h"
#include "dice-classes.h"
#include "chart-classes.h"


class Scene {
public:
	void gotoxy(int, int); // 공통	
	COORD getxy();
	virtual void EraseScene(); // 공통
	int KeyControl();
	virtual void KeyMovingControl();// 공통
};

class StartScene : public Scene {
private:
	
public:
	StartScene();
	void Init(); // startscene
	void TitleDraw(); // startscene
	void KeyMovingControl();
};

class InfoScene : public Scene {
private:
public:
	InfoScene();
	void InfoDraw();
	void KeyMovingControl();
};

class GameScene : public Scene {
private:
	int round=1; int max_round = 12;
	int turn=1; int max_turn = 2;
	int roll=1; int max_roll = 3;

	pair<int,int> table_pos_set[3][12];
	map<pair<int,int>,bool> table_can_go;
	bool table_fixed[3][12];
	DiceSet dice_set;
	vector<int> dice_num_set;
	Chart player[3];
	Chart tmp_player[3];
	vector<pair<int, int>> table_pos = { {0,0}, {24, 5}, {36, 5} };
	vector<int> table_y_pos = { 5,7,9,11,13,15,19,21,23,25,27,29 };
	vector<int> table_total_y_pos = { 17,31 };
	pair<int, int> dice_pos = { 52, 15 };

public:
	GameScene();
	void RollTurnRoundDraw();
	int KeyMovingControlReturn();
	void MakeDiceNumSet();
	void TableDraw();
	void DiceDraw();
	void TableValueDraw(const vector<int>& table_value);
	void TableValueDraw(const int& who, const vector<int>& table_value);
	void DiceValueDraw(const vector<int>& dice_value);
	void WhosWinner();
	void DiceKeepDraw(const int& x, const int& y);
	void DiceActivateDraw(const int& x, const int& y);
};
class EndScene : public Scene {
private:
public:
	EndScene();
	void EndSceneDraw();
};

class GameManager {
private:
	Scene* now_scene = new StartScene();
	friend Scene;
	int winner=-1;
public:
	GameManager() {}
	void SetScene(const string& usage);
	void SetWinner(const int& winner);
	int GetWinner() { return winner; }
};
#endif
