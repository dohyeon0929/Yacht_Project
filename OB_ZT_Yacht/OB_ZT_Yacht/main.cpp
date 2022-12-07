#include "essential.h"
#include "dice-classes.h"
#include "scene-classes.h"
#include "yatch_chart.h"

int main() {
	StartSceneDraw startscene;
	startscene.Init();
	startscene.TitleDraw();	
	StartSceneInputManager startsceneinputmanager;
	startsceneinputmanager.KeyMovingControl();
	GameManage game_manage;

}