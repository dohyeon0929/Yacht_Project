#include "essential.h"
#include "dice-classes.h"
#include "scene-classes.h"
#include "yatch_chart.h"
#include <io.h>
#include <fcntl.h>

int main() {
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//Console.OutputEncoding = Encoding.UTF8;
	StartSceneDraw startscene;
	startscene.Init();
	startscene.TitleDraw();	
	StartSceneInputManager startsceneinputmanager;
	startsceneinputmanager.KeyMovingControl();
	GameManage game_manage;

}