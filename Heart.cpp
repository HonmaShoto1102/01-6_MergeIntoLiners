#include "Heart.h"

#include "FairyVH.h"
#include "Figure.h"
#include "Stage.h"
#include "Line.h"
#include "playerCollision.h"
#include "drawNumber.h"

//#include <vector>

//using namespace std;


static Heart hearties[HEARTMAX];
//static SpritePL* tePl;
static int CurrentHeartNumber = 0;
static int uiNumberCount = 0;
static int lineCount = 0;

static float2D pointList[4];
static int pCount = 0;

bool Heart_Compare(Heart* heart);
void FigureCreate(Heart* heart);
bool bjHeart(Heart* h1, Heart* h2, Heart* ph);
Heart* GetHeartByLine(Heart* h, int ln, int c);
Heart* WriteHeart(Heart* pOut, Heart* pIn, Heart* ph);
int LifeOrRight(Heart* h, Heart* th);
void plistInit();
void DrawFigure();
void AddpList(float x, float y);

void Heart_Load()
{
	for (int i = 0; i < HEARTMAX; i++)
	{
		hearties[i].sp = new SpriteC("Asset/heart.png", 14);		
	}
	//tePl = new SpritePL("Asset/ds.jpg", 12);
	DrawNumber_Load();
}

void Heart_Init()
{
	for (int i = 0; i < HEARTMAX; i++)
	{
		hearties[i].sp->Init();
		hearties[i].sp->SetAnchorPoint(ANCHOR_CENTER);
		hearties[i].sp->SetScale(1.0f, 1.0f);
		hearties[i].sp->SetActive(false);
		hearties[i].l1 = LINENUMBER_INV;
		hearties[i].l2 = LINENUMBER_INV;
		hearties[i].active = false;
	}
	DrawNumber_Init();
}

void Heart_Update()
{
	DrawNumber_ReSet();
	bool bra = false;
	int fcount = 0;
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (hearties[i].sp->GetActive()) {

			
			if (i+1 >= CurrentHeartNumber) {
				if (hearties[i].ht == RightAngle&&CurrentHeartNumber<i+1) {
					fcount++;
				}
				if (fcount) {
					bra = true;
				}
				//bra = true;
				DrawNumber_SetDraw(hearties[i].sp->GetPosX(), hearties[i].sp->GetPosY(), hearties[i].uiNumber, bra, i);
			}
			

			int bc = Stage_GetNumberOfBlock(bl_heartBox);
			for (int j = 0; j < bc; j++)
			{
				M_heartBox* mhb = Stage_heartBox_hitWithPoint(hearties[i].sp->GetPosX(), hearties[i].sp->GetPosY(), j);
				if (mhb != NULL&&hearties[i].ht== RightAngle&&mhb->GetActive()) {

					int Ln1 = hearties[i].l1;
					int Ln2 = hearties[i].l2;
					Line_DeleteLineMap(Ln1);
					Line_DeleteLineMap(Ln2);
					CurrentHeartNumber--;
					mhb->SetHeartActive(true);
					SetTeleport(mhb->GetPosCn().x, mhb->GetPosCn().y);										
				}				
			}

			int be = Stage_GetNumberOfBlock(bl_stageTransBox);
			for (int j = 0; j < be; j++)
			{
				CollisionRectangle co = { hearties[i].sp->GetPosX(),hearties[i].sp->GetPosY(),5,5 };
				M_stageTransBox* mhbe = Stage_transBox_hit(&co, j);
				if (mhbe != NULL && hearties[i].ht == RightAngle&&mhbe->GetActive()) {

					int Ln1 = hearties[i].l1;
					int Ln2 = hearties[i].l2;
					Line_DeleteLineMap(Ln1);
					Line_DeleteLineMap(Ln2);
					CurrentHeartNumber--;
					mhbe->SetAreahActive(true);
					SetAreaport(mhbe->GetPosCn().x, mhbe->GetPosCn().y);
				}
			}

			int gb = Stage_GetNumberOfBlock(bl_goalBox);
			for (int j = 0; j < gb; j++)
			{
				CollisionRectangle co = { hearties[i].sp->GetPosX(),hearties[i].sp->GetPosY(),5,5 };
				M_goalBox* mgbe = Stage_GetGoalBox_byNumber(j);
				CollisionRectangle cr_g = mgbe->GetColl();
				if (mgbe != NULL && hearties[i].ht == RightAngle) {
					if (Collision_RectangleAndRectangleHit(&co, &cr_g)) {
						int Ln1 = hearties[i].l1;
						int Ln2 = hearties[i].l2;
						Line_DeleteLineMap(Ln1);
						Line_DeleteLineMap(Ln2);
						CurrentHeartNumber--;
						mgbe->SetAreahActive(true);
						PlayerCollision_StageClear(mgbe->GetPosCn().x, mgbe->GetPosCn().y);
					}
					
				}
			}
		}
	}

	DrawNumber_Update();
}

void Heart_Final()
{
	DrawNumber_Final();
	for (int i = 0; i < HEARTMAX; i++)
	{
		delete hearties[i].sp;
	}
}

//int Heart_SetHeart(float x, float y)
//{
//	for (int i = 0; i < HEARTMAX; i++)
//	{
//		if (hearties[i].sp->GetActive())continue;
//		hearties[i].sp->SetPosition(x, y);
//		hearties[i].sp->SetActive(true);
//		return i;
//	}
//	return 0;
//}

bool Heart_GetFlag()
{
	for (int i = CurrentHeartNumber; i < HEARTMAX; i++)
	{
		if (hearties[i].sp->GetActive()) {
			if (hearties[i].ht == RightAngle) {
				return true;
			}
		}
	}
	return false;
}

void Heart_HeartDestory(int heartNumber)
{
	hearties[heartNumber].sp->SetActive(false);
}

Heart * Heart_GetHeart()
{
	for (int i = CurrentHeartNumber; i < HEARTMAX; i++)
	{
		if (hearties[i].sp->GetActive())
		{
			CurrentHeartNumber = i;
			CurrentHeartNumber++;
			return &hearties[i];
		}
	}
	
	return &hearties[CurrentHeartNumber];
}

int Heart_CreateHeart(float x, float y, int L1, int L2,HeartType HT)
{
	int MinL = min(L1, L2);
	int MaxL = max(L1, L2);

	for (int i = 0; i < HEARTMAX; i++) {
		if (MinL == hearties[i].l1&&MaxL == hearties[i].l2) {
			return i;
		}
	}

	for (int i = 0; i < HEARTMAX; i++)
	{
		if (hearties[i].active) {
			continue;
		}
		else
		{
			hearties[i].l1 = MinL;
			hearties[i].l2 = MaxL;
			hearties[i].sp->SetPosition(x, y);
			hearties[i].sp->SetActive(true);
			hearties[i].active = true;		
			hearties[i].ht = HT;
			bool succ = Heart_Compare(&hearties[i]);
			if (HT == Diagonal) {
				hearties[i].sp->SetAlpha(0.0f);
				if (succ) {
					lineCount++;
					uiNumberCount++;
				}			
				hearties[i].uiNumber = uiNumberCount;
				
			}
			if (HT == RightAngle) {
				hearties[i].sp->SetAlpha(1.0f);
				if (succ) {
					uiNumberCount = 1;
					//uiNumberCount++;
					lineCount++;
				}		
				hearties[i].uiNumber = uiNumberCount;

			}		
			FigureCreate(&hearties[i]);
			return i;
		}	
	}
	return HEARTNULL;
}

void Heart_DeleteHeart(int lineNum)
{
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (hearties[i].l1 == lineNum||hearties[i].l2 == lineNum) {
			hearties[i].sp->SetActive(false);
			hearties[i].l1 = LINENUMBER_INV;
			hearties[i].l2 = LINENUMBER_INV;
			hearties[i].active = false;
		}
	}
}

void Heart_ReSet()
{
	CurrentHeartNumber = 0;
	//uiNumberCount = 0;
	lineCount = 0;
}

bool Heart_isEndHeart()
{
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (hearties[i].sp->GetActive()) {
			if (i >= CurrentHeartNumber)return false;
		}
	}
	return true;
}

void Heart_CreateFigure()
{
	int hc = Heart_GetHeartCount();
	float2D* vlist = new float2D[hc];
	int hvc = 0;

	for (int i = 0; i < hc; i++)
	{
		if (hearties[i].sp->GetActive()) {
			vlist[hvc].x = hearties[i].sp->GetPosX();
			vlist[hvc].y = hearties[i].sp->GetPosY();
			hvc++;
		}		
	}
	
	if (hvc < 3)return;
	Figure_GetFigure()->SetFigure(vlist, hvc);
	delete[] vlist;
	vlist = NULL;
}

void Heart_MoveFigure(float x, float y)
{
	Figure_GetFigure()->GoToTarget(x, y, 1);
}

int Heart_GetHeartCount()
{
	return lineCount;
}

Heart * Heart_GetHeart(int hNumber)
{	
	if (hearties[hNumber].sp->GetActive()) {
		return &hearties[hNumber];
	}
	return NULL;
}

int Heart_GetCurrentHeartNum()
{
	return CurrentHeartNumber;
}


bool Heart_Compare(Heart* heart) {
	CollisionCircle c1;
	c1.center.x = heart->sp->GetPosX();
	c1.center.y = heart->sp->GetPosY();
	c1.radius = 4.0f;
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (hearties[i].sp->GetActive()&& heart!=&hearties[i]) {

			CollisionCircle c2;
			c2.center.x = hearties[i].sp->GetPosX();
			c2.center.y = hearties[i].sp->GetPosY();
			c2.radius = 4.0f;
			if (Collision_CircleAndCircleHit(&c1, &c2)) {
				if (heart->ht == RightAngle&& hearties[i].ht!=RightAngle) {
					hearties[i].sp->SetActive(false);
				}
				if (hearties[i].ht == RightAngle) {
					heart->sp->SetActive(false);
					return false;
				}
			}
		}
	}
	return true;
}


void FigureCreate(Heart* heart) {

	plistInit();
	AddpList(heart->sp->GetPosX(), heart->sp->GetPosY());
	Heart* h1 = GetHeartByLine(heart, heart->l2,0);
	Heart* h2 = GetHeartByLine(heart, heart->l1,0);

	if (bjHeart(h1, h2, heart)) {
		DrawFigure();
		return;
	}

	plistInit();
	AddpList(heart->sp->GetPosX(), heart->sp->GetPosY());
	h1 = GetHeartByLine(heart, heart->l2, 1);
	h2 = GetHeartByLine(heart, heart->l1, 0);

	if (bjHeart(h1, h2, heart)) {
		DrawFigure();
		return;
	}

	plistInit();
	AddpList(heart->sp->GetPosX(), heart->sp->GetPosY());
	h1 = GetHeartByLine(heart, heart->l2, 0);
	h2 = GetHeartByLine(heart, heart->l1, 1);

	if (bjHeart(h1, h2, heart)) {
		DrawFigure();
		return;
	}

	plistInit();
	AddpList(heart->sp->GetPosX(), heart->sp->GetPosY());
	h1 = GetHeartByLine(heart, heart->l2, 1);
	h2 = GetHeartByLine(heart, heart->l1, 1);

	if (bjHeart(h1, h2, heart)) {
		DrawFigure();
		return;
	}
	
}

bool bjHeart(Heart* h1, Heart* h2,Heart* ph) {
	
	if (h1 == NULL || h2 == NULL)return false;
	int L1, L2;
	if (ph->l2 == h1->l1)L1 = h1->l2;
	if (ph->l2 == h1->l2)L1 = h1->l1;
	if (ph->l1 == h2->l1)L2 = h2->l2;
	if (ph->l1 == h2->l2)L2 = h2->l1;

	if (L2 == L1)return true;
	
	int minL = min(L1, L2);
	int maxL = max(L1, L2);
	for (int i = 0; i < lineCount; i++)
	{
		Heart* th = Heart_GetHeart(i);
		if (th == NULL)continue;
		if (th->l1 == minL && th->l2 == maxL) {
			AddpList(th->sp->GetPosX(), th->sp->GetPosY());
			return true;
		}
	}
	return false;
}


Heart* GetHeartByLine(Heart* h,int ln,int c) {
	Heart* reth = NULL;
	for (int i = 0; i < lineCount; i++)
	{
		Heart* th = Heart_GetHeart(i);
		if (th == NULL || th == h) continue;
		if (th->l1 == ln || th->l2 == ln) {
			int b = LifeOrRight(h, th);
			if (b == c) {
				reth = WriteHeart(reth, th, h);
				int b = 2;
			}
		}
	}
	if (reth != NULL) {
		AddpList(reth->sp->GetPosX(), reth->sp->GetPosY());
	}

	return reth;
}

Heart* WriteHeart(Heart* pOut, Heart* pIn, Heart* ph) {
	if (pOut == NULL) {
		//pOut = pIn;
		return pIn;
	}
	float Ox = pOut->sp->GetPosX();
	float Oy = pOut->sp->GetPosY();
	float Ix = pIn->sp->GetPosX();
	float Iy = pIn->sp->GetPosY();
	float Hx = ph->sp->GetPosX();
	float Hy = ph->sp->GetPosY();
	float okoru = (Ox - Hx)*(Ox - Hx) + (Oy - Hy) * (Oy - Hy);
	float ikoru = (Ix - Hx)*(Ix - Hx) + (Iy - Hy) * (Iy - Hy);
	if (okoru <= ikoru)return pOut;
	if (okoru > ikoru) {
		return pIn;
	}
}

int LifeOrRight(Heart* h, Heart* th) {
	if (h->sp->GetPosX() > th->sp->GetPosX()) {
		return 0;
	}
	else if (h->sp->GetPosX() < th->sp->GetPosX()) {
		return 1;
	}
	else {
		if (h->sp->GetPosY() > th->sp->GetPosY()) {
			return 0;
		}
		else {
			return 1;
		}
	}
	return 0;
}

void plistInit() {
	for (int i = 0; i < 4; i++)
	{
		pointList[i].x = 0;
		pointList[i].y = 0;
	}
	pCount = 0;
}

void DrawFigure() {
	if (pCount < 3)return;
	Figure_GetFigure()->SetFigure(pointList, pCount);
}

void AddpList(float x, float y) {
	pointList[pCount].x = x;
	pointList[pCount].y = y;
	pCount++;
}


