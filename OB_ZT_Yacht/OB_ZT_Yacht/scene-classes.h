#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"


//여러 씬들을 관리하는 SceneManager
class SceneInputManager // 인터페이스
{
public:	
	void gotoxy(int, int); // 공통
	int KeyControl(); // 공통
	void EraseScene(); // 공통
	
private:
	
};

// 단일 scene 내부에서 작동하는 기능, scenemanager를 상속
class StartScene : public SceneInputManager 
{
public:
	void Init(); // startscene
	void TitleDraw(); // startscene
	int MenuDraw(); // startscene
};

class InfoScene : public SceneInputManager
{
public:
	void InfoDraw(); // infoscene
};

class GameSceneDraw : public SceneInputManager
{
public:
	GameSceneDraw(); // 생성자
	//void GameDraw(); // 게임화면 그리기
};

class TableDraw : public SceneInputManager
{
public:
	TableDraw(); // 생성자
};

class DiceDraw : public SceneInputManager
{
public:
	DiceDraw();
};

class TableValueDraw : public SceneInputManager
{
public :
	TableValueDraw(vector<int>);

private:
	
	vector<pair<int, int>> table_pos = { {24, 5}, {36, 5} };
};

class DiceValueDraw : public SceneInputManager
{
public:
	DiceValueDraw(vector<int>);
private:
	pair<int, int> dice_pos = { 52, 15 };
};

class CursorDraw : public SceneInputManager
{
public:

};
#endif
