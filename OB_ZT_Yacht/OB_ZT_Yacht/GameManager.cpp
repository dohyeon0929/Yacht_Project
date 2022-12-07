#include "yatch_chart.h"
#include "Scene.h"



vector<Chart> StartScene::setChart()
{
	ChartFactory factory;
	vector<Chart>playerchart;
	playerchart[0] = factory.GetChart();
	playerchart[1] = factory.GetChart("me");
	return playerchart;
}

/*
void GameScene::SetGameRound(int& game_round)
{
	game_round--;
}*/
/*
vector<int> GameScene::DrawScene(Chart& player)
{
	return player.GetRoundResult();
}*/
int GameScene::GetGameRound(vector<Chart>& player, int& game_round)
{
	GameScenePrev prev;
	GameSceneCal cal;
	GameSceneResult result;

	while (game_round > 0) //12라운드 반복
	{
		for (int i = 0; i < player.size(); i++) //chart 벡터 player의 수 만큼 , 즉 플레이어의 수 만큼 반복
		{
			int roll_count = 3;
			prev.DrawScene(player[i]); 			//맨 처음 턴이 넘어오면 이전 값 먼저 리턴하여 출력

			//최대 3회 반복
			while (roll_count > 3)
			{
				//1 .dice 실행 , 주사위 값 가져오기
				vector<int>dice;  //수정 필요 ..... 주사위 돌리고

				//2. chart_value 값 초기화 후 연산 수행
				player[i].SetDefaultValue(); //chart_value 값 초기화
				player[i].SetDiceValue(dice); //주사위 값 가져와서 dice_num 초기화
				cal.DrawScene(player[i]); //연산 결과값 리턴
				roll_count--;

				//수정필요, UI에서 select 했을 때 select한 칸 번호 읽어와서 끝내기
				if (1)  //UI에서 선택한 값이 표 값인 경우
				{
					player[i].PushValue(1); //예시값
					break;
				}
				else continue;
			}
			result.DrawScene(player[i]);
		}
		/*
			 // 연산에 이용할 vector<int> chart_value 초기화
			 // 주사위 값 vector<int> dice_num 에 저장

			cal.DrawScene(player[i]);
			DrawScene(player[i].chart_value); //연산 후 계산 값 보여주기


			display에서 선택한 위치 입력받아서 최종 입력값 데이터 저장해놓기
			player[i].PushValue();

			player[i].GetRoundResult();
			DrawScene(player[i].GetRoundResult());
		}*/
	}
	return 0;
}


vector<int>GameScenePrev::DrawScene(Chart& player)
{
	player.SetDefaultValue();
	return player.GetRoundResult(); //vector<int>Result 값 리턴
}

vector<int>GameSceneCal::DrawScene(Chart& player)
{
	player.SetDefaultValue();
	SetUpValue upvalue(&player);
	//SetUpValue upvalue(&player);
	CheckFOK fok(&player);
	CheckFH fh(&player);
	CheckSS ss(&player);
	CheckBS bs(&player);
	CheckYacht yatcht(&player);
	CheckChoice choice(&player);
	for (int i = 0; i < 6; i++)
	{
		if (upvalue.IsNullptr(&player.chart_value[i]))
			player.chart_value[i] = upvalue.SetValue(player.dice_num, i);
	} //위쪽 표 값 계산

		//for of kind 부터 choice 까지 null 여부 확인 후 값 대입 연산(chart_value에 저장한다)
	if (fok.IsNullptr(&player.chart_value[6])) //아래쪽 표 값 계산
		player.chart_value[6] = fok.SetValue(player.dice_num);

	if (fh.IsNullptr(&player.chart_value[7]))
		player.chart_value[7] = fh.SetValue(player.dice_num);

	if (ss.IsNullptr(&player.chart_value[8]))
		player.chart_value[8] = ss.SetValue(player.dice_num);

	if (bs.IsNullptr(&player.chart_value[9]))
		player.chart_value[9] = bs.SetValue(player.dice_num);

	if (yatcht.IsNullptr(&player.chart_value[10]))
		player.chart_value[10] = yatcht.SetValue(player.dice_num);

	if (choice.IsNullptr(&player.chart_value[11]))
		player.chart_value[11] = choice.SetValue(player.dice_num);
	return player.chart_value; //vector<int>chart_value 값 리턴
}

vector<int>GameSceneResult::DrawScene(Chart& player)
{
	player.SetSubTotal(); //위 표 값 계산
	player.SetBonus(); //
	player.SetTotalSum();
	return player.GetRoundResult();
}






