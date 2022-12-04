#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"

class Draw // 추상클래스
{
public:	
	void gotoxy(int, int); // 공통	
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

class TableDraw : public GameSceneDraw
{
public:
	TableDraw(); // 생성자
};

class DiceDraw : public GameSceneDraw
{
public:
	DiceDraw();
};

class TableValueDraw : public GameSceneDraw
{
public:
	TableValueDraw(vector<int>);

private:
	vector<pair<int, int>> table_pos = { {24, 5}, {36, 5} };
};

class DiceValueDraw : public GameSceneDraw
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

class CursorDraw : public GameSceneDraw // ??
{
public:

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
};

class EndSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl();
};

#endif
