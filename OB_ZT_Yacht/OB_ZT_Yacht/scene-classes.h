#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"

class Draw // 추상클래스
{
public:	
	void gotoxy(int, int); // 공통	
	COORD getxy();
	virtual void EraseScene(); // 공통
	
private:
	
};

// 단일 scene 내부에서 작동하는 기능, scenemanager를 상속
class StartSceneDraw : public Draw
{
public:
	void Init(); // startscene
	void TitleDraw(); // startscene
	
};

class GameSceneDraw : public Draw
{
public:
	GameSceneDraw(); // 생성자
};

class EndSceneDraw : public Draw
{
public:
	EndSceneDraw();
};

class TableDraw : public Draw
{
public:
	TableDraw(); // 생성자
};

class DiceDraw : public Draw
{
public:
	DiceDraw();
};

class TableValueDraw : public Draw
{
public:
	TableValueDraw(vector<int>);
	//TableFixedDraw();

private:
	vector<pair<int, int>> table_pos = { {24, 5}, {36, 5} };
	
};

class CursorDraw : public Draw
{
public:
	int KeyMovingControl();
	vector<pair<int, int>> cursordice_pos = { {52, 15}, { 64, 15}, {76, 15}, {88, 15}, {100, 15} }; // 일단 주사위만
};

class DiceValueDraw : public Draw
{
public:
	DiceValueDraw(vector<int>);
private:
	pair<int, int> dice_pos = { 52, 15 };
};

class InfoSceneDraw : public Draw
{
public:
	InfoSceneDraw();
};


class SceneInputManager : public Draw// 추상클래스
{
public:
	//virtual void InputKeyBoard();
	int KeyControl();
	virtual void KeyMovingControl() = 0; // 공통
};

class StartSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl(); // 공통
};

class InfoSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl(); // 공통
};

class GameSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl();
	void DiceKeepDraw(int); // 몇번째 주사위인지
	void DiceActivateDraw(int);
	void TableFixedDraw(int); // 선택된 표의 행 num
	void RollTurnRoundDraw(int, int, int); // 라운드, 턴, 롤
};

class EndSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl();
};

#endif
