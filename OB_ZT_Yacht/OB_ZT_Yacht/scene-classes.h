#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"

class Draw // �߻�Ŭ����
{
public:	
	void gotoxy(int, int); // ����	
	COORD getxy();
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

class TableDraw : public Draw
{
public:
	TableDraw(); // ������
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
	vector<pair<int, int>> cursordice_pos = { {52, 15}, { 64, 15}, {76, 15}, {88, 15}, {100, 15} }; // �ϴ� �ֻ�����
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
	void DiceKeepDraw(int, int); // ���° �ֻ�������
	void DiceActivateDraw(int, int);
	int TableFixedDraw(); // ���õ� ǥ�� �� num
	void RollTurnRoundDraw(int, int, int); // ����, ��, ��
};

class EndSceneInputManager : public SceneInputManager
{
public:
	void KeyMovingControl();
};

#endif
