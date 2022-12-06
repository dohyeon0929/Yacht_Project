#pragma once
#include "chart_needs.h"
#include "yatch_chart.h"
class Scene
{
public:
	virtual vector<int> DrawScene(Chart& player) = 0;
};

class StartScene : Scene
{
public:
	vector<Chart> setChart();
	//void game_scene();
};


class GameScene : Scene
{
private:
	int game_round = 12;
public:
	//virtual void SetGameRound(int &game_round);
	int GetGameRound(vector<Chart>& player, int& game_round);
	virtual vector<int> DrawScene(Chart& player) = 0;
};


class GameScenePrev : GameScene
{
public:
	vector<int> DrawScene(Chart& player);
};

class GameSceneCal : GameScene
{
public:
	vector<int> DrawScene(Chart& player);
};

class GameSceneResult : GameScene
{
public:
	vector<int> DrawScene(Chart& player);
};


/*
class EndScene : Scene
{
private:

public:
	vector<int> DrawScene(Chart player);
};*/

