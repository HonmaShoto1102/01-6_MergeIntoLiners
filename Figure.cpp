#include "Figure.h"
#include "PlayerData.h"
//#define FIGUREMAX (2)

static Figure* figureClass;

void Figure_Load()
{
	figureClass = new Figure();
}

void Figure_Init()
{
	figureClass->Init();
}

void Figure_Final()
{
	delete figureClass;
}

void Figure_Update()
{
	figureClass->Update();
}

Figure * Figure_GetFigure()
{
	return figureClass;
}

Figure::Figure()
{
	for (int i = 0; i < 8; i++)
	{
		figure[i] = new SpritePL("Asset/figure.png", 12);
		moveStraight[i] = new AnimationMoveStraight();
		alpha[i] = 0.0f;
		Pos[i] = { 0.0f,0.0f };
		OldPos[i] = { 0.0f,0.0f };
	}	
	
	active = false;
	posX = 0;
	posY = 0;
	oldX = 0;
	oldY = 0;
	
}

Figure::~Figure()
{
	for (int i = 0; i < 8; i++)
	{
		delete figure[i];
		delete moveStraight[i];
	}	
}

void Figure::Init()
{
	active = false;
	//alpha = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		figure[i]->InitPL();
		figure[i]->SetAnchorPoint(ANCHOR_CENTER);
		figure[i]->SetActive(active);
		figure[i]->SetAlpha(alpha[i]);
	}	
}

void Figure::Update()
{
	if (!active)return;

	

	for (int i = 0; i < 8; i++)
	{
		if (moveStraight[i]->GetPlayF()) {
			Pos[i].x = moveStraight[i]->GetPosX();
			Pos[i].y = moveStraight[i]->GetPosY();
			if (moveStraight[i]->GetTime() >= 300) {
				moveStraight[i]->End();
				FigureDestroy();
			}
		}

		if (figure[i]->GetActive()) {
			alpha[i] += 0.01f;
			if (alpha[i] >= 0.5f)alpha[i] = 0.5f;
			figure[i]->SetAlpha(alpha[i]);
		}
	}
	

	if (Player_GetState() == ps_default) {
		FigureDestroy();
	}

	EnemyCollisionCheck();
	PositionUpdate();
}

void Figure::SetFigure(float2D * vList, int count)
{
	
	active = true;
	for (int i = 0; i < 8; i++)
	{
		if (figure[i]->GetActive())continue;
		figure[i]->SetActive(active);
		figure[i]->SetAlpha(0.0f);
		alpha[i] = 0.0f;
		float minx = vList[0].x;
		float miny = vList[0].y;
		float maxx = vList[0].x;
		float maxy = vList[0].y;
		for (int i = 0; i < count; i++)
		{
			if (minx > vList[i].x)minx = vList[i].x;
			if (miny > vList[i].y)miny = vList[i].y;
			if (maxx < vList[i].x)maxx = vList[i].x;
			if (maxy < vList[i].y)maxy = vList[i].y;
		}
		Pos[i].x = (minx + maxx) / 2;
		Pos[i].y = (miny + maxy) / 2;
		figure[i]->SetPosition(Pos[i].x, Pos[i].y);
		figure[i]->SetPolygonPoint(vList, count);
		return;
	}	
}

void Figure::GoToTarget(float x, float y, int type)
{

	for (int i = 0; i < 8; i++)
	{
		if (!figure[i]->GetActive())continue;
		moveStraight[i]->Init(Pos[i].x, Pos[i].y, x, y, 10, type);
		moveStraight[i]->Play();
	}
	
}

void Figure::PositionUpdate()
{
	oldX = posX;
	oldY = posY;
	for (int i = 0; i < 8; i++)
	{
		OldPos[i] = Pos[i];
		figure[i]->SetPosition(OldPos[i].x, OldPos[i].y);
	}	
}

void Figure::EnemyCollisionCheck()
{
	
}

void Figure::FigureDestroy()
{
	active = false;
	for (int i = 0; i < 8; i++)
	{
		figure[i]->SetActive(false);
	}	
}

void Figure::SetFigurePos(float x, float y)
{
	for (int i = 0; i < 8; i++)
	{
		figure[i]->SetPosition(x, y);
	}	
}
