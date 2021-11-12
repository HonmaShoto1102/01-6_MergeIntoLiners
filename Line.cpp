#include "Line.h"

#include "FairyVH.h"
#include "Heart.h"
#include "PlayerData.h"
#include "Effect.h"
#include "Stage.h"
#include "SoundManager.h"

typedef struct HeartData{
	float posX;
	float posY;
	int l1;
	int l2;
	HeartType ht;
	bool flag;
}HDATA;

void LineCreate(LINE* p_line, float sx, float sy, float ex, float ey, FAIRY_LINEe fl);
void HeartCreate();
void LineCross(LINE* pl1, LINE* pl2);
void SetLineStrong(LINE* p);
void SetLineDefalt(LINE* p);
void SetFLchange(LINE* p, FAIRY_LINEe fl);
void SetLineSD(LINE* p, FAIRY_LINEe fl);
void LineUpdate(LINE* pl);
void SetColorChange(LINE* pl, LINECOLOR lc);
void DeleteCoverLine(int id);

int ltimeCount = 0;
int theEndLineCount = LINENULL;
int theOldLineCount = LINENULL;

static LINE line_Vertica[FMAX];
static LINE line_Horizy[FMAX];
static LINE line_Map[LINEMAX];
static HDATA HeartDates[HEARTMAX];

void Create_hDate(float x, float y, int L1, int L2, HeartType ht);
void Delete_hDate(int lineNumber);
void Update_hDate();

//static CollisionCircle c_v= { {0,0},0 };
//static CollisionCircle c_h = { {0,0},0 };
//static CollisionCircle c_null = { {0,0},0 };

void Line_Load()
{
	for (int i = 0; i < FMAX; i++)
	{
		line_Vertica[i].sp = new SpritePA("Asset/line.png", 12);
		line_Horizy[i].sp = new SpritePA("Asset/line.png", 12);
	}
	
	for (int i = 0; i < LINEMAX; i++)
	{
		line_Map[i].sp = new SpritePA("Asset/line.png", 12);
	}
}

void Line_Init()
{
	for (int i = 0; i < HEARTMAX; i++)
	{
		HeartDates[i].flag = false;
		HeartDates[i].l1 = LINENUMBER_INV;
		HeartDates[i].l2 = LINENUMBER_INV;
	}

	for (int i = 0; i < FMAX; i++)
	{
		line_Vertica[i].sp->Init();
		line_Vertica[i].startPos = { 0,0 };
		line_Vertica[i].endPos = { 0,0 };
		line_Vertica[i].currentEpos = { 0,0 };
		line_Vertica[i].sp->SetActive(false);
		line_Vertica[i].sp->SetScale(1.0f, 0.5f);
		line_Vertica[i].angle = 0;
		line_Vertica[i].Num = LINEMAX + FMAX + i;
		line_Vertica[i].lintType = l_lvert;
		line_Vertica[i].sp->SetAnchorPoint(ANCHOR_LC);
		line_Vertica[i].sp->SetPartialAnchorPoint(ANCHOR_LC);
		line_Vertica[i].age = 0;
		line_Vertica[i].lc = lc_pink;
		line_Vertica[i].st = ls_off;
		line_Vertica[i].lineCreater = lineCreater_Fairy;
		line_Vertica[i].contextID = LINENULL;
		line_Vertica[i].rlineID = LINENULL;
		SetColorChange(&line_Vertica[i], lc_pink);

		line_Horizy[i].sp->Init();
		line_Horizy[i].startPos = { 0,0 };
		line_Horizy[i].endPos = { 0,0 };
		line_Horizy[i].currentEpos = { 0,0 };
		line_Horizy[i].sp->SetActive(false);
		line_Horizy[i].sp->SetScale(1.0f, 0.5f);
		line_Horizy[i].angle = 0;
		line_Horizy[i].Num = LINEMAX + i;
		line_Horizy[i].lintType = l_lvert;
		line_Horizy[i].sp->SetAnchorPoint(ANCHOR_LC);
		line_Horizy[i].sp->SetPartialAnchorPoint(ANCHOR_LC);
		line_Horizy[i].age = 0;
		line_Horizy[i].lc = lc_blue;
		line_Horizy[i].st = ls_off;
		line_Horizy[i].lineCreater = lineCreater_Fairy;
		line_Horizy[i].contextID = LINENULL;
		line_Horizy[i].rlineID = LINENULL;
		SetColorChange(&line_Horizy[i], lc_blue);
	}

	

	for (int i = 0; i < LINEMAX; i++)
	{
		line_Map[i].sp->Init();
		line_Map[i].sp->SetActive(false);
		line_Map[i].sp->SetScale(1.0f, 0.5f);
		line_Map[i].startPos = { 0,0 };
		line_Map[i].endPos = { 0,0 };
		line_Map[i].currentEpos = { 0,0 };
		line_Map[i].angle = 0;
		line_Map[i].Num = i;
		line_Map[i].lintType = l_lvert;
		line_Map[i].sp->SetAnchorPoint(ANCHOR_LC);
		line_Map[i].sp->SetPartialAnchorPoint(ANCHOR_LC);
		line_Map[i].age = 0;
		line_Map[i].st = ls_off;
		line_Map[i].contextID = LINENULL;
		line_Map[i].rlineID = LINENULL;
	}

	//Line_CreateLineMap(300.0f, 600.0f, 900.0f, 600.0f);
	//Line_CreateLineMap(500.0f, 300.0f, 500.0f, 900.0f);
}

void Line_Update()
{
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Vertica[i].sp->GetActive()) {
			LineUpdate(&line_Vertica[i]);
		}

		if (line_Horizy[i].sp->GetActive()) {
			LineUpdate(&line_Horizy[i]);
		}
	}
	

	for (int i = 0; i < LINEMAX; i++)
	{
		if (line_Map[i].sp->GetActive()) {
			LineUpdate(&line_Map[i]);
		}
	}

	HeartCreate();
	ltimeCount++;
	//if (ltimeCount % 1000 == 0) {
	//	Line_CreateLineMap(300.0f, 600.0f, 600.0f, 600.0f);
	//	Line_CreateLineMap(500.0f, 400.0f, 500.0f, 800.0f);
	//}
}

void Line_Final()
{
	for (int i = 0; i < FMAX; i++)
	{
		delete line_Vertica[i].sp;
		delete line_Horizy[i].sp;
	}
	
}

void Line_CreateLineV(int count,float sx,float sy,float ex,float ey,FAIRY_LINEe fl)
{
	LineCreate(&line_Vertica[count], sx, sy, ex, ey,fl);
	theOldLineCount = theEndLineCount;
	theEndLineCount = line_Vertica[count].Num;
	SoundManager_PlaySE(SL_line_drawn_up);
	
}

void Line_CreateLineStrongV(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl)
{
	LineCreate(&line_Vertica[count], sx, sy, ex, ey, fl);
	line_Vertica[count].contextID = context;
	theOldLineCount = theEndLineCount;
	theEndLineCount = line_Vertica[count].Num;
	SoundManager_PlaySE(SL_line_drawn_up);
}

void Line_DeleteLineV(int count)
{
	//float offx = line_Vertica.sp->GetWidth() / 2;
	//float offy = line_Vertica.sp->GetHeight() / 2;
	if (line_Vertica[count].st != ls_off)
	ActivateLineEffect("effect_delete_vertica_line", { (line_Vertica[count].startPos.x + line_Vertica[count].currentEpos.x)/2,(line_Vertica[count].startPos.y + line_Vertica[count].currentEpos.y)/2}, { 0.2f,0.0015f*line_Vertica[count].length },line_Vertica[count].angle + 3.1415f*0.5f);
	//line_Vertica[count].sp->SetActive(false);
	//Delete_hDate(line_Vertica[count].Num);
	//Heart_DeleteHeart(line_Vertica[count].Num);
	//theEndLineCount = theOldLineCount;
}

void Line_CreateLineH(int count, float sx, float sy, float ex, float ey, FAIRY_LINEe fl)
{
	LineCreate(&line_Horizy[count], sx, sy, ex, ey,fl);
	theOldLineCount = theEndLineCount;
	theEndLineCount = line_Horizy[count].Num;
	SoundManager_PlaySE(SL_line_drawn_up);
}

void Line_CreateLineStrongH(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl)
{
	LineCreate(&line_Horizy[count], sx, sy, ex, ey, fl);
	line_Horizy[count].contextID = context;
	theOldLineCount = theEndLineCount;
	theEndLineCount = line_Horizy[count].Num;
	SoundManager_PlaySE(SL_line_drawn_up);
}

void Line_DeleteLineH(int count)
{ 
	//float offx = line_Horizy.sp->GetWidth() / 2;
	//float offy = line_Horizy.sp->GetHeight() / 2;
	if(line_Horizy[count].st != ls_off)
	ActivateLineEffect("effect_delete_horizy_line", { (line_Horizy[count].startPos.x + line_Horizy[count].currentEpos.x) / 2, (line_Horizy[count].startPos.y + line_Horizy[count].currentEpos.y) / 2 }, { 0.0015f*line_Horizy[count].length,0.2f }, line_Horizy[count].angle);
	//line_Horizy[count].sp->SetActive(false);
	//Delete_hDate(line_Horizy[count].Num);
	//Heart_DeleteHeart(line_Horizy[count].Num);
	//theEndLineCount = theOldLineCount;
}

LINE * Line_GetLineMessageV(int num)
{
	return &line_Vertica[num];
}

LINE * Line_GetLineMessageH(int num)
{
	return &line_Horizy[num];
}

int Line_CreateLineMap(float sx, float sy, float ex, float ey,  LINECOLOR lc, LINE_CREATERe creater, FAIRY_LINEe fl)
{
	for (int i = 0; i < LINEMAX; i++)
	{
		if (line_Map[i].sp->GetActive() || line_Map[i].st == ls_str)continue;
		SetColorChange(&line_Map[i], lc);
		line_Map[i].lc = lc;
		line_Map[i].lineCreater = creater;
		LineCreate(&line_Map[i], sx, sy, ex, ey,fl);
		line_Map[i].Num = i;
		theOldLineCount = theEndLineCount;
		theEndLineCount = i;
		return i;
	}
}

int Line_CreateLineMap(float sx, float sy, float ex, float ey, int reline, LINECOLOR lc, LINE_CREATERe creater, FAIRY_LINEe fl)
{
	for (int i = 0; i < LINEMAX; i++)
	{
		if (line_Map[i].sp->GetActive() || line_Map[i].st == ls_str)continue;
		SetColorChange(&line_Map[i], lc);
		line_Map[i].lc = lc;
		line_Map[i].lineCreater = creater;
		LineCreate(&line_Map[i], sx, sy, ex, ey, fl);
		line_Map[i].Num = i;
		theOldLineCount = theEndLineCount;
		theEndLineCount = i;
		line_Map[i].rlineID = reline;
		return i;
	}
}


void Line_DeleteLineMap(int Number)
{
	if (Number >= LINEMAX + FMAX) {
		int coID = line_Vertica[Number - LINEMAX - FMAX].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Vertica[Number - LINEMAX - FMAX].contextID = LINENULL;
		line_Vertica[Number - LINEMAX - FMAX].sp->SetActive(false);
		Line_DeleteLineV(Number - LINEMAX - FMAX);
		line_Vertica[Number - LINEMAX - FMAX].st = ls_off;
		line_Vertica[Number - LINEMAX - FMAX].rlineID = LINENULL;
		
		Delete_hDate(line_Vertica[Number - LINEMAX - FMAX].Num);
		Heart_DeleteHeart(line_Vertica[Number - LINEMAX - FMAX].Num);
	}
	else if (Number >= LINEMAX) {
		int coID = line_Horizy[Number - LINEMAX].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Horizy[Number - LINEMAX].contextID = LINENULL;
		line_Horizy[Number - LINEMAX].sp->SetActive(false);
		Line_DeleteLineH(Number - LINEMAX);
		line_Horizy[Number - LINEMAX].st = ls_off;
		line_Horizy[Number - LINEMAX].rlineID = LINENULL;
		
		Delete_hDate(line_Horizy[Number - LINEMAX].Num);
		Heart_DeleteHeart(line_Horizy[Number - LINEMAX].Num);
	}
	else {
		int coID = line_Map[Number].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Map[Number].contextID = LINENULL;
		line_Map[Number].sp->SetActive(false);
		line_Map[Number].st = ls_off;
		line_Map[Number].rlineID = LINENULL;
		Delete_hDate(line_Map[Number].Num);
		Heart_DeleteHeart(line_Map[Number].Num);
	}
	theEndLineCount = theOldLineCount;
}

void Line_BecomeStrongLineMap(int Number)
{
	if (Number >= LINEMAX + FMAX) {
		line_Vertica[Number - LINEMAX - FMAX].sp->SetActive(false);
		line_Vertica[Number - LINEMAX - FMAX].st = ls_str;
		Delete_hDate(line_Vertica[Number - LINEMAX - FMAX].Num);
		Heart_DeleteHeart(line_Vertica[Number - LINEMAX - FMAX].Num);
	}
	else if (Number >= LINEMAX) {
		line_Horizy[Number - LINEMAX].sp->SetActive(false);
		line_Horizy[Number - LINEMAX].st = ls_str;
		Delete_hDate(line_Horizy[Number - LINEMAX].Num);
		Heart_DeleteHeart(line_Horizy[Number - LINEMAX].Num);
	}
	else {
		line_Map[Number].sp->SetActive(false);
		line_Map[Number].st = ls_str;
		Delete_hDate(line_Map[Number].Num);
		Heart_DeleteHeart(line_Map[Number].Num);
	}
	theEndLineCount = theOldLineCount;
}

void Line_DeleteLineAll()
{
	for (int i = 0; i < LINEMAX; i++)
	{
		Line_DeleteLineMap(i);
	}
	for (int i = 0; i < FMAX; i++)
	{
		Line_DeleteLineMap(LINEMAX + i);
		Line_DeleteLineMap(LINEMAX + i + FMAX);
		//Line_DeleteLineV(i);
		//Line_DeleteLineH(i);
	}
	theEndLineCount = LINENULL;
	theOldLineCount = LINENULL;
}

int Line_GetAllNumber()
{
	int lineCount = 0;
	for (int i = 0; i < LINEMAX; i++)
	{
		if (line_Map[i].sp->GetActive()) {
			lineCount = i;
		}
	}
	return lineCount;
}

CollisionLine Line_GetLine(int lineNum)
{
	CollisionLine li = { 0,0,0,0 };
	if (line_Map[lineNum].sp->GetActive()) {
		li = { line_Map[lineNum].startPos.x,line_Map[lineNum].startPos.y,line_Map[lineNum].endPos.x,line_Map[lineNum].endPos.y };
		return li;
	}
	return li;
}

CollisionLine Line_GetLineV(int count)
{
	CollisionLine li = { 0,0,0,0 };
	if (line_Vertica[count].sp->GetActive()) {
		li = { line_Vertica[count].startPos.x,line_Vertica[count].startPos.y,line_Vertica[count].endPos.x,line_Vertica[count].endPos.y };
	}
	return li;
}

CollisionLine Line_GetLineH(int count)
{
	CollisionLine li = { 0,0,0,0 };
	if (line_Horizy[count].sp->GetActive()) {
		li = { line_Horizy[count].startPos.x,line_Horizy[count].startPos.y,line_Horizy[count].endPos.x,line_Horizy[count].endPos.y };
	}
	return li;
}

CollisionLine Line_GetCurrentLineV()
{
	CollisionLine li = { 0,0,0,0 };
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Vertica[FMAX - i - 1].sp->GetActive()) {
			li = { line_Vertica[FMAX - i - 1].startPos.x,line_Vertica[FMAX - i - 1].startPos.y,line_Vertica[FMAX - i - 1].endPos.x,line_Vertica[FMAX - i - 1].endPos.y };
			return li;
		}
	}
	return li;
}

CollisionLine Line_GetCurrentLineH()
{
	CollisionLine li = { 0,0,0,0 };
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Horizy[FMAX - i - 1].sp->GetActive()) {
			li = { line_Horizy[FMAX - i - 1].startPos.x,line_Horizy[FMAX - i - 1].startPos.y,line_Horizy[FMAX - i - 1].endPos.x,line_Horizy[FMAX - i - 1].endPos.y };
			return li;
		}
	}
	return li;
}

CollisionLine Line_GetCollisionLineForNumberAll(int lineNum)
{
	CollisionLine cl = { 0,0,0,0 };

	if (lineNum >= LINEMAX+FMAX) {
		if (line_Vertica[lineNum - LINEMAX - FMAX].sp->GetActive()) {
			cl.sx = line_Vertica[lineNum - LINEMAX - FMAX].startPos.x;
			cl.sy = line_Vertica[lineNum - LINEMAX - FMAX].startPos.y;
			cl.ex = line_Vertica[lineNum - LINEMAX - FMAX].endPos.x;
			cl.ey = line_Vertica[lineNum - LINEMAX - FMAX].endPos.y;
			return cl;
		}
	}else if (lineNum >= LINEMAX) {
		if (line_Horizy[lineNum - LINEMAX].sp->GetActive()) {
			cl.sx = line_Horizy[lineNum - LINEMAX].startPos.x;
			cl.sy = line_Horizy[lineNum - LINEMAX].startPos.y;
			cl.ex = line_Horizy[lineNum - LINEMAX].endPos.x;
			cl.ey = line_Horizy[lineNum - LINEMAX].endPos.y;
			return cl;
		}
	}
	else {
		if (line_Map[lineNum].sp->GetActive()) {
			cl.sx = line_Map[lineNum].startPos.x;
			cl.sy = line_Map[lineNum].startPos.y;
			cl.ex = line_Map[lineNum].endPos.x;
			cl.ey = line_Map[lineNum].endPos.y;
			return cl;
		}
	}
	return cl;
}

//void Line_DeleteLineForNumberAll(int lineNum)
//{
//	if (lineNum == 0) {
//		Line_DeleteLineV();
//	}
//	else if (lineNum == 1) {
//		Line_DeleteLineH();
//	}
//	else if(lineNum>1){
//		Line_DeleteLineMap(lineNum - 2);
//	}
//}
//
//LINE * Line_GetLineForNumberAllOBJ(int lineNum)
//{
//	if (lineNum == 0) {
//		if (line_Vertica.sp->GetActive()) {
//			return &line_Vertica;
//		}
//	}
//	else if (lineNum == 1) {
//		if (line_Horizy.sp->GetActive()) {
//			return &line_Horizy;
//		}
//	}
//	else {
//		if (line_Map[lineNum - 2].sp->GetActive()) {
//			return &line_Map[lineNum -2];
//		}
//	}
//	return NULL;
//}

LINE * Line_GetLineForNumberAllMAP(int lineNum)
{
	if (lineNum >= LINEMAX+FMAX) {
		if (line_Vertica[lineNum - LINEMAX - FMAX].sp->GetActive()) {
			return &line_Vertica[lineNum - LINEMAX - FMAX];
		}
	}
	else if (lineNum >= LINEMAX) {
		if (line_Horizy[lineNum - LINEMAX].sp->GetActive()) {
			return &line_Horizy[lineNum - LINEMAX];
		}
	}
	else {
		if (line_Map[lineNum].sp->GetActive()) {
			return &line_Map[lineNum];
		}
	}
	return NULL;
}

LINE * Line_GetEndLine()
{
	if (theEndLineCount >= 0) {
		return 	Line_GetLineForNumberAllMAP(theEndLineCount);
	}
	return NULL;
}

bool Line_GetActiveLineV(int count)
{
	/*for (int i = 0; i < FMAX; i++)
	{
		if (line_Vertica[i].sp->GetActive()) {
			return true;
		}
	}*/
	return line_Vertica[count].sp->GetActive();
}

bool Line_GetActiveLineH(int count)
{
	/*for (int i = 0; i < FMAX; i++)
	{
		if (line_Vertica[i].sp->GetActive()) {
			return true;
		}
	}*/
	return line_Horizy[count].sp->GetActive();
}

bool Line_GetActiveLineV()
{
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Vertica[i].sp->GetActive()) {
			return true;
		}
	}
	return false;
}

bool Line_GetActiveLineH()
{
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Horizy[i].sp->GetActive()) {
			return true;
		}
	}
	return false;
}


void LineCreate(LINE* p_line, float sx, float sy, float ex, float ey, FAIRY_LINEe fl) {
	//if (p_line->sp->GetActive())return;

	if (p_line->sp->GetActive())return;
	p_line->fl = fl;
	p_line->sp->SetActive(true);
	p_line->length = 0.0f;
	p_line->angle = atan2f(ey - sy, ex - sx);
	p_line->sp->SetAngle(p_line->angle);
	p_line->age = 0;
	p_line->st = ls_ing;
	if (ey - sy == 0) {
		p_line->lenghtMax = fabsf(ex - sx);
		p_line->lintType = l_lvert;
	}
	else if (ex - sx == 0) {
		p_line->lenghtMax = fabsf(ey - sy);
		p_line->lintType = l_lhory;
	}
	else {
		if ((ey - sy) / (ex - sx) > 0) {
			p_line->lintType = l_oleft;
		}
		else
		{
			p_line->lintType = l_oright;
		}
		p_line->lenghtMax = fabsf((ex - sx) / cosf(p_line->angle));
	}

	CollisionLine cl = { sx,sy,ex,ey };
	for (int i = 0; i < LINEMAX; i++)
	{
		if (line_Map[i].sp->GetActive() == false)continue;
		if (line_Map[i].lintType == p_line->lintType && (&line_Map[i] != p_line)) {
			if (Collision_LineAndLineDistance(line_Map[i].GetColl(), cl, 48)) {
				Line_BecomeStrongLineMap(i);
				p_line->contextID = i;
				p_line->fl = fl_strong;
			}
		}
	}
	for (int i = 0; i < FMAX; i++)
	{
		if (line_Horizy[i].sp->GetActive()) {
			if (line_Horizy[i].lintType == p_line->lintType && (&line_Horizy[i] != p_line)) {
				if (Collision_LineAndLineDistance(line_Horizy[i].GetColl(), cl, 48)) {
					Line_BecomeStrongLineMap(LINEMAX + i);
					p_line->contextID = LINEMAX + i;
					p_line->fl = fl_strong;
				}
			}
		}
		if (line_Vertica[i].sp->GetActive()) {
			if (line_Vertica[i].lintType == p_line->lintType && (&line_Vertica[i] != p_line)) {
				if (Collision_LineAndLineDistance(line_Vertica[i].GetColl(), cl, 48)) {
					Line_BecomeStrongLineMap(LINEMAX + FMAX + i);
					p_line->contextID = LINEMAX + FMAX + i;
					p_line->fl = fl_strong;
				}
			}
		}
	}


	if (fl == fl_strong) {
		SetLineStrong(p_line);
	}
	else if (fl == fl_defalt) {
		SetLineDefalt(p_line);
	}
	
	//p_line->sp->SetWidth(0.0f);
	p_line->sp->SetPartialWidth(0.0f);
	p_line->startPos = { sx,sy };
	p_line->endPos = { ex,ey };
	p_line->currentEpos = { sx,sy };
	p_line->sp->SetPosition(p_line->startPos.x, p_line->startPos.y);

	
}

void HeartCreate() {


	for (int i = 0; i < FMAX; i++)
	{
		for (int j = i + 1; j < FMAX; j++)
		{
			LineCross(&line_Vertica[i], &line_Vertica[j]);
			LineCross(&line_Horizy[i], &line_Horizy[j]);
		}
	}

	for (int i = 0; i < FMAX; i++)
	{
		for (int j = 0; j < FMAX; j++)
		{
			LineCross(&line_Vertica[i], &line_Horizy[j]);
		}
	}	
	for (int i = 0; i < LINEMAX; i++)
	{
		for (int j = 0; j < FMAX; j++)
		{
			LineCross(&line_Vertica[j], &line_Map[i]);
			LineCross(&line_Horizy[j], &line_Map[i]);
		}		
	}
	for (int i = 0; i < LINEMAX; i++)
	{
		for (int j = i + 1; j < LINEMAX; j++)
		{
			LineCross(&line_Map[i], &line_Map[j]);
		}
	}

	Update_hDate();
}

void LineCross(LINE* pl1, LINE* pl2) {

	if (pl1->Num == pl2->Num)return;
	if (pl1->sp->GetActive()) {
		float vx1 = pl1->startPos.x;
		float vy1 = pl1->startPos.y;
		float vx2 = (pl1->endPos.x - pl1->startPos.x)*(pl1->length / pl1->lenghtMax) + pl1->startPos.x;
		float vy2 = (pl1->endPos.y - pl1->startPos.y)*(pl1->length / pl1->lenghtMax) + pl1->startPos.y;
		CollisionLine L1 = { vx1,vy1,vx2,vy2 };
		if (pl2->sp->GetActive()) {
			float hx1 = pl2->startPos.x;
			float hy1 = pl2->startPos.y;
			float hx2 = (pl2->endPos.x - pl2->startPos.x)*(pl2->length / pl2->lenghtMax) + pl2->startPos.x;
			float hy2 = (pl2->endPos.y - pl2->startPos.y)*(pl2->length / pl2->lenghtMax) + pl2->startPos.y;
			CollisionLine L2 = { hx1,hy1,hx2,hy2 };
			if (pl1->rlineID == pl2->Num || pl1->Num == pl2->rlineID)return;
			Cross_imf cif = Collision_LineAndLineHit(L1, L2);
			if (cif.flag) {
				float an = pl1->angle - pl2->angle;
				HeartType ht;
				if (fabsf(cosf(an)) < 0.1f) {
					ht = RightAngle;
				}
				else
				{
					ht = Diagonal;
				}
				//Heart_CreateHeart(cif.interX, cif.interY, pl1->Num, pl2->Num, ht);
				Create_hDate(cif.interX, cif.interY, pl1->Num, pl2->Num, ht);
			}
		}
	}
}

void SetLineSD(LINE* p, FAIRY_LINEe fl) {
	switch (fl)
	{
	case fl_defalt:
		SetLineDefalt(p);
		break;
	case fl_strong:
		SetLineStrong(p);
		break;
	default:
		break;
	}
}

void SetLineStrong(LINE* p) {
	p->sp->SetColor(255, 0, 0);
	p->sp->SetScale(1.0f, 1.0f);
}


void SetLineDefalt(LINE* p) {
	//p->sp->SetColor(255, 255, 255);
	SetColorChange(p, p->lc);
	p->sp->SetScale(1.0f, 0.5f);
}

void SetFLchange(LINE* p ,FAIRY_LINEe fl) {
	if (p->fl == fl) return;
	p->fl = fl;
	p->age = 0;
	SetLineSD(p, fl);
}

void LineUpdate(LINE* pl) {
	if (pl->length < pl->lenghtMax) {
		pl->length += 20.0f;
		if (pl->length >= pl->lenghtMax) {
			pl->length = pl->lenghtMax;
			pl->st = ls_on;
		}
		//pl->sp->SetWidth(pl->length);
		pl->sp->SetPartialWidth(pl->length / 1600.0f);
		float x = pl->startPos.x + (pl->length / pl->lenghtMax)*(pl->endPos.x - pl->startPos.x);
		float y = pl->startPos.y + (pl->length / pl->lenghtMax)* (pl->endPos.y - pl->startPos.y);
		pl->currentEpos.x = x;
		pl->currentEpos.y = y;
		int lb = Stage_GetNumberOfBlock(bl_lineBox);
		for (int i = 0; i < lb; i++)
		{
			
			M_lineCreateBox* lbx = Stage_lineBox_hit(x, y, i);
			if (lbx != NULL) {
				lbx->OnTrigger();
				SoundManager_PlaySE(SL_break_crystal);
				Line_DeleteLineMap(pl->Num);
				return;
			}
		}

		int mb = Stage_GetNumberOfBlock(bl_mirrorBox);
		for (int i = 0; i < mb; i++)
		{
			/*float x = pl->startPos.x + (pl->length / pl->lenghtMax)*(pl->endPos.x - pl->startPos.x);
			float y = pl->startPos.y + (pl->length / pl->lenghtMax)* (pl->endPos.y - pl->startPos.y);
			pl->currentEpos.x = x;
			pl->currentEpos.y = y;*/
			CollisionPoint po;
			po.point.x = x;
			po.point.y = y;
			M_mirorrBox* mrr = Stage_GetMirrorBox_byNumber(i);
			CollisionRectangle cr_mr = mrr->GetColl();
			if (Collision_RectangleAndPointHit(&cr_mr, &po)) {
				if (mrr->GetMirType() == M_mirorrBox::mirorr_OFF) {
					Line_DeleteLineMap(pl->Num);
					return;
				}
				int mrFlag = mrr->LineReflex(pl);
				if (mrFlag == 1) {
					pl->lenghtMax = pl->length;
					pl->lenghtMax = pl->length;
					pl->endPos.x = pl->currentEpos.x;
					pl->endPos.y = pl->currentEpos.y;
				}
				if (mrFlag == 2) {
					pl->lenghtMax = pl->length;
					pl->lenghtMax = pl->length;
					pl->endPos.x = pl->currentEpos.x;
					pl->endPos.y = pl->currentEpos.y;
				}
			}
		}
	}
	pl->sp->SetAlpha(1.0f);
	SetLineSD(pl, pl->fl);
	if (Player_GetState() == ps_default) {
		pl->age++;
		if (pl->fl == fl_defalt) {
			if (pl->age >= 300) {

				//if(pl->Num == LINEMAX + 1)ActivateEffect(Effect_DeleteVerticaLine, { line_Vertica.startPos.x,line_Vertica.startPos.y }, { 1,0.5f }, 10);
				//if(pl->Num == LINEMAX + 2)ActivateEffect(Effect_DeleteHorizyLine, { line_Horizy.startPos.x,line_Horizy.startPos.y }, { 1,0.5f }, 10);
				/*pl->sp->SetActive(false);
				Delete_hDate(pl->Num);
				Heart_DeleteHeart(pl->Num);*/
				Line_DeleteLineMap(pl->Num);
				//if (pl->fl == fl_strong)SetFLchange(pl, fl_defalt);
			}
			if (pl->age >= 200) {
				if (pl->age % 14 > 7) {
					pl->sp->SetAlpha(1.0f);
				}
				else {
					pl->sp->SetAlpha(0.0f);
				}
			}
		}

		if (pl->fl == fl_strong) {
			if (pl->age >= 300) {
				SetFLchange(pl, fl_defalt);
			}
			if (pl->age >= 200) {
				if (pl->age % 14 > 7) {
					SetLineDefalt(pl);
				}
				else {
					SetLineStrong(pl);
				}
			}
		}

	}
}

void SetColorChange(LINE* pl, LINECOLOR lc) {
	switch (lc)
	{
	case lc_red:
		pl->sp->SetColor(255, 0, 0);
		break;
	case lc_blue:
		pl->sp->SetColor(0, 0, 255);
		break;
	case lc_green:
		pl->sp->SetColor(0, 255, 0);
		break;
	case lc_yellow:
		pl->sp->SetColor(255, 255, 0);
		break;
	case lc_black:
		pl->sp->SetColor(0, 0, 0);
		break;
	case lc_pink:
		pl->sp->SetColor(255, 20, 147);
		break;
	default:
		break;
	}
}

void Create_hDate(float x, float y, int L1, int L2, HeartType ht) {
	int MinL = min(L1, L2);
	int MaxL = max(L1, L2);

	for (int i = 0; i < HEARTMAX; i++)
	{
		if (MinL == HeartDates[i].l1&&MaxL == HeartDates[i].l2) {
			return;
		}
	}

	for (int i = 0; i < HEARTMAX; i++)
	{
		if (HeartDates[i].flag)continue;
		HeartDates[i].l1 = MinL;
		HeartDates[i].l2 = MaxL;
		HeartDates[i].posX = x;
		HeartDates[i].posY = y;
		HeartDates[i].ht = ht;
		HeartDates[i].flag = true;
		return;
	}
}

void Delete_hDate(int lineNumber) {
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (HeartDates[i].l1 == lineNumber || HeartDates[i].l2 == lineNumber) {
			HeartDates[i].flag = false;
			HeartDates[i].l1 = LINENUMBER_INV;
			HeartDates[i].l2 = LINENUMBER_INV;
			//HeartDates[i].active = false;
		}
	}
}

void Update_hDate() {
	for (int i = 0; i < HEARTMAX; i++)
	{
		if (HeartDates[i].flag) {
			LINE* pl1 = Line_GetLineForNumberAllMAP(HeartDates[i].l1);
			LINE* pl2 = Line_GetLineForNumberAllMAP(HeartDates[i].l2);
			//if (pl1 == NULL || pl2 == NULL)continue;
			if (pl1->sp->GetActive() && pl1->length >= pl1->lenghtMax&&
				pl2->sp->GetActive() && pl2->length >= pl2->lenghtMax) {
				Heart_CreateHeart(HeartDates[i].posX, HeartDates[i].posY, HeartDates[i].l1, HeartDates[i].l2, HeartDates[i].ht);
			}
		}		
	}
}


void DeleteCoverLine(int id) {
	if (id >= LINEMAX + FMAX) {
		int coID = line_Vertica[id - LINEMAX - FMAX].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Vertica[id - LINEMAX - FMAX].contextID = LINENULL;
		line_Vertica[id - LINEMAX - FMAX].sp->SetActive(false);
		line_Vertica[id - LINEMAX - FMAX].st = ls_off;
		line_Vertica[id - LINEMAX - FMAX].rlineID = LINENULL;
		Delete_hDate(line_Vertica[id - LINEMAX - FMAX].Num);
		Heart_DeleteHeart(line_Vertica[id - LINEMAX - FMAX].Num);
	}
	else if (id >= LINEMAX) {
		int coID = line_Horizy[id - LINEMAX].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Horizy[id - LINEMAX].contextID = LINENULL;
		line_Horizy[id - LINEMAX].sp->SetActive(false);
		line_Horizy[id - LINEMAX].st = ls_off;
		line_Horizy[id - LINEMAX].rlineID = LINENULL;
		Delete_hDate(line_Horizy[id - LINEMAX].Num);
		Heart_DeleteHeart(line_Horizy[id - LINEMAX].Num);
	}
	else {
		int coID = line_Map[id].contextID;
		if (coID != LINENULL) {
			DeleteCoverLine(coID);
		}
		line_Map[id].contextID = LINENULL;
		line_Map[id].sp->SetActive(false);
		line_Map[id].st = ls_off;
		line_Map[id].rlineID = LINENULL;
		Delete_hDate(line_Map[id].Num);
		Heart_DeleteHeart(line_Map[id].Num);
	}
	theEndLineCount = theOldLineCount;
}