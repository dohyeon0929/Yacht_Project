#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"

class Draw // �߻�Ŭ����
{
public:	
	void gotoxy(int, int); // ����	
	virtual void EraseScene(); // ����
	
private:
	
};

// ���� scene ���ο��� �۵��ϴ� ���, scenemanager�� ���
class StartSceneDraw : public Draw
{
public:
	void Init(); // startscene
	void TitleDraw(); // startscene
	
};

class GameSceneDraw : public Draw
{
public:
	GameSceneDraw(); // ������
};

class EndSceneDraw : public Draw
{
public:
	EndSceneDraw();
};

class TableDraw : public GameSceneDraw
{
public:
	TableDraw(); // ������
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

class SceneInputManager : public Draw// �߻�Ŭ����
{
public:
	//virtual void InputKeyBoard();
	int KeyControl();
	virtual void KeyMovingControl() = 0; // ����
};

class StartSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl(); // ����
};

class InfoSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl(); // ����
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
