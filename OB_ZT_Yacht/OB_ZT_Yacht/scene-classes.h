#ifndef SCENE_CLASSES_H
#define SCENE_CLASSES_H

#include "essential.h"


//���� ������ �����ϴ� SceneManager
class SceneInputManager // �������̽�
{
public:	
	void gotoxy(int, int); // ����
	int KeyControl(); // ����
	void EraseScene(); // ����
	
private:
	
};

// ���� scene ���ο��� �۵��ϴ� ���, scenemanager�� ���
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
	GameSceneDraw(); // ������
	//void GameDraw(); // ����ȭ�� �׸���
};

class TableDraw : public SceneInputManager
{
public:
	TableDraw(); // ������
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
