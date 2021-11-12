#ifndef FIGURE_H
#define FIGURE_H
#include "base_Sprite.h"
#include "base_Animation.h"

void Figure_Load();
void Figure_Init();
void Figure_Final();
void Figure_Update();



class Figure
{
public:
	Figure();
	~Figure();

	void Init();
	void Update();
	void SetFigure(float2D* vList, int count);
	void GoToTarget(float x, float y, int type = 0);
	
	void FigureDestroy();
	void SetFigurePos(float x, float y);

private:
	void PositionUpdate();
	void EnemyCollisionCheck();

	SpritePL* figure[8];
	AnimationMoveStraight* moveStraight[8];
	float2D Pos[8];
	float2D OldPos[8];
	bool active;
	float alpha[8];
	float posX;
	float posY;
	float oldX;
	float oldY;
};

Figure* Figure_GetFigure();


#endif // !FIGURE_H

