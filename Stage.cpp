#include "Stage.h"
#include "playerCollision.h"
#include "tinyxml2.h"
#include "GM.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include <vector>
#include "Event.h"
#include "InputManager.h"

using namespace std;


static char stageName[STAGEMAX][10]{
	"stage1_A",
	"stage1_B",
	"stage2_A",
	"stage2_B",
	"stage2_C",
	"stage3_A",
	"stage3_B",
	"stage3_C",
    "stage3_D"
};

static char eventName[EVENTTYPE_MAX][30]{
	"EVENTTYPE_WALK",
	"EVENTTYPE_DRAW_HORIZY",
	"EVENTTYPE_DRAW_VERTICA",
	"EVENTTYPE_CROSS_LINE",
	"EVENTTYPE_TALK"
};

void BGMInit();
void BGMFinal();

static int Now_StageNumber = SET_START_STAGE;
static int Next_StageNumber = SET_START_STAGE;
static int StageSizeWidth = 0;
static int StageSizeHeight = 0;
static int StartPosX = 300;
static int StartPosY = 500;

//static M_collsionBOX* mboxes;
//static int mboxCount;
//static M_textureBOX* t_blockes;
//static int tboxCount;

static vector<M_textureBOX*> textureBoxes;
static vector<M_collsionBOX*> collisionBoxes;
static vector<M_heartBox*> heartBoxes;
//static vector<M_heartBox*> hiddenHeartBoxes;
//static vector<M_invisibleBox*> invisibleBoxes;
static vector<M_damegeBox*> damegeBoxes;
static vector<M_stageTransBox*> stageTransBoxes;
static vector<M_goalBox*> goalBoxes;
static vector<M_lineCreateBox*> lineBoxes;
static vector<M_enemyBox*> enemyBoxes;
static vector<M_diagonalCollisionBox*> diagonalBoxes;
static vector<M_enemy2Box*> enemy2Boxes;
static vector<M_startBox*> startBoxes;
static vector<M_eventBox*> eventBoxes;
static vector<M_mirorrBox*> mirrorBoxes;

//プロトタイプ宣言
bool loadMapXML(int mapNumber);
void StageTransCheck();
int eventNumberGet(const char* name);

void Stage_Load()
{
	loadMapXML(Now_StageNumber);
	//mboxCount = 4;
	//mboxes = new M_collsionBOX[mboxCount];	
	//mboxes[0].LoadData(   0, 930, 2560,  300);
	//mboxes[1].LoadData(   0,-100, 2560,  100);
	//mboxes[2].LoadData(-100,   0,  100,  1080);
	//mboxes[3].LoadData(2560,   0,  100,  1080);

	/*M_heartBox* hvb = new M_heartBox((char*)"Asset/key_heart_box.png",1400,1600, 128, 128,7);
	heartBoxes.push_back(hvb);

	M_stageTransBox* stb = new M_stageTransBox((char*)"Asset/Stage/area_heart_box.png",2060, 1860, 128, 128, 7,3);
	stageTransBoxes.push_back(stb);
*/
	/*M_mirorrBox* mir = new M_mirorrBox("Asset/Stage/mirror_slant_left.png", 1400, 1990, 256, 256, M_mirorrBox::mirorr_ON);
	mirrorBoxes.push_back(mir);
	

	M_mirorrBox* mir1 = new M_mirorrBox("Asset/Stage/mirror_vertical_right.png", 2200, 1990, 256, 256, M_mirorrBox::mirorr_ON);
	mirrorBoxes.push_back(mir1);*/

	////M_damegeBox* dab = new M_damegeBox(NULL, 600, 1, 1280, 30, 7);
	////damegeBoxes.push_back(dab);
	//M_lineCreateBox* lcb = new M_lineCreateBox((char*)"Asset/target_cursor.png", 800, 670, 128, 128, 7);
	//lcb->LoadParameta(0, 100);
	//lineBoxes.push_back(lcb);

	//M_diagonalCollisionBox* dib = new M_diagonalCollisionBox(800, 700, 1000, 400,M_diagonalCollisionBox::ld_ru);
	//diagonalBoxes.push_back(dib);

	//M_textureBOX* nnm = new M_textureBOX("Asset/nnm.png", 800, 700, 1000, 400, 7);
	//textureBoxes.push_back(nnm);

	//M_heartBox* htb = new M_heartBox("Asset/key_heart_box.png", 800, 500, 128, 128, 7);
	//htb->LoadState(false);
	//heartBoxes.push_back(htb);
	//int hiddenCount = (int)heartBoxes.size() - 1;
	//M_enemy2Box* en2b = new M_enemy2Box("enemy2", 800, 500, hiddenCount, "walk_left");
	//enemy2Boxes.push_back(en2b);

	//tboxCount = 40;
	//t_blockes = new M_textureBOX[tboxCount];
	//for (int i = 0; i < tboxCount; i++)
	//{
	//	t_blockes[i].LoadData("Asset/ground.png", i * 64, 930, 11);
	//}
}

void Stage_Init()
{
	if (Now_StageNumber == 6) {
		SetInCaves(true);
	}
	else {
		SetInCaves(false);
	}
	for (size_t i = 0; i < textureBoxes.size(); i++)
	{
		textureBoxes[i]->Init();
	}
	for (size_t i = 0; i < collisionBoxes.size(); i++)
	{
		collisionBoxes[i]->Init();
	}
	for (size_t i = 0; i < heartBoxes.size(); i++)
	{
		heartBoxes[i]->Init();		
	}
	for (size_t i = 0; i < damegeBoxes.size(); i++)
	{
		damegeBoxes[i]->Init();
	}
	for (size_t i = 0; i < stageTransBoxes.size(); i++)
	{
		stageTransBoxes[i]->Init();
	}
	for (size_t i = 0; i < goalBoxes.size(); i++)
	{
		goalBoxes[i]->Init();
	}
	for (size_t i = 0; i < lineBoxes.size(); i++)
	{
		lineBoxes[i]->Init();
		//lineBoxes[i]->LoadParameta({ 0,1 }, 300);
	}
	for (size_t i = 0; i < diagonalBoxes.size(); i++)
	{
		diagonalBoxes[i]->Init();
	}

	for (size_t i = 0; i < startBoxes.size(); i++)
	{
		startBoxes[i]->Init();
		StartPosX = startBoxes[i]->GetColl().x;
		StartPosY = startBoxes[i]->GetColl().y;
	}

	for (size_t i = 0; i < eventBoxes.size(); i++)
	{
		eventBoxes[i]->Init();
	}

	for (int i = 0; i < mirrorBoxes.size(); i++)
	{
		mirrorBoxes[i]->Init();
	}

	//BGMInit();
	Player_PositionReSet(StartPosX, StartPosY);
}

void Stage_Update()
{
	for (size_t i = 0; i < lineBoxes.size(); i++)
	{
		lineBoxes[i]->Update();
	}
	for (size_t i = 0; i < heartBoxes.size(); i++)
	{
		if (Player_GetState() == ps_goHeart||Player_GetState() == ps_default) {
			heartBoxes[i]->SetHeartActive(false);
		}
	}
	for (size_t i = 0; i < mirrorBoxes.size(); i++)
	{
		mirrorBoxes[i]->Update();
	}

	StageTransCheck();
}

void Stage_Final()
{
	//delete[] t_blockes;
	//t_blockes = 0;
	//delete[] mboxes;
	//mboxCount = 0;
	//BGMFinal();

	for (size_t i = 0; i < textureBoxes.size(); i++)
	{
		delete textureBoxes[i];
	}
	for (size_t i = 0; i < collisionBoxes.size(); i++)
	{
		delete collisionBoxes[i];
	}
	for (size_t i = 0; i < heartBoxes.size(); i++)
	{
		delete heartBoxes[i];
	}
	for (size_t i = 0; i < stageTransBoxes.size(); i++)
	{
		delete stageTransBoxes[i];
	}
	for (size_t i = 0; i < goalBoxes.size(); i++)
	{
		delete goalBoxes[i];
	}
	for (size_t i = 0; i < damegeBoxes.size(); i++)
	{
		delete damegeBoxes[i];
	}
	for (size_t i = 0; i < lineBoxes.size(); i++)
	{
		delete lineBoxes[i];
	}
	for (size_t i = 0; i < enemyBoxes.size(); i++)
	{
		delete enemyBoxes[i];
	}
	for (size_t i = 0; i < diagonalBoxes.size(); i++)
	{
		delete diagonalBoxes[i];
	}
	for (size_t i = 0; i < enemy2Boxes.size(); i++)
	{
		delete enemy2Boxes[i];
	}

	for (size_t i = 0; i < startBoxes.size(); i++)
	{
		delete startBoxes[i];
	}

	for (size_t i = 0; i < eventBoxes.size(); i++)
	{
		delete eventBoxes[i];
	}

	for (size_t i = 0; i < mirrorBoxes.size(); i++)
	{
		delete mirrorBoxes[i];
	}

	mirrorBoxes.clear();
	eventBoxes.clear();
	startBoxes.clear();
	enemy2Boxes.clear();
	diagonalBoxes.clear();
	enemyBoxes.clear();
	lineBoxes.clear();
	collisionBoxes.clear();
	textureBoxes.clear();
	heartBoxes.clear();
	stageTransBoxes.clear();
	goalBoxes.clear();
	damegeBoxes.clear();

}

void Stage_heartBoxCreate(int id)
{
	if (id < 500) {
		heartBoxes[id]->SetActive(true);
	}
	else {
		stageTransBoxes[id - 500]->SetActive(true);
	}
}

int Stage_GetNowStageNumber()
{
	return Now_StageNumber;
}



void Stage_Translation(int stageNumber)
{
	if (stageNumber < 0)return;
	if (Next_StageNumber == stageNumber)return;
	Next_StageNumber = stageNumber;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

int Stage_GetNumberOfBlock(BL_TYPE bl_type)
{
	switch (bl_type)
	{
	case bl_collisionBox:
		return (int)collisionBoxes.size();
	case bl_textureBox:
		return (int)textureBoxes.size();
	case bl_heartBox:
		return (int)heartBoxes.size();
	case bl_stageTransBox:
		return (int)stageTransBoxes.size();
	case bl_damegeBox:
		return (int)damegeBoxes.size();
	case bl_goalBox:
		return (int)goalBoxes.size();
	case bl_lineBox:
		return (int)lineBoxes.size();
	case bl_enemyBox:
		return (int)enemyBoxes.size();
	case bl_diagonalBox:
		return (int)diagonalBoxes.size();
	case bl_enemy2Box:
		return (int)enemy2Boxes.size();
	case bl_eventBox:
		return (int)eventBoxes.size();
	case bl_mirrorBox:
		return (int)mirrorBoxes.size();
	default:
		break;
	}
	return 0;
}

//-------------------------------------------------------------------------------------
//                        当たり判定がplayer自身が処理した場合
//-------------------------------------------------------------------------------------
//type1:M_collisioBOXを取得。
M_collsionBOX * Stage_collisionBOX_hit(CollisionRectangle* PayerBOX,int boxNum)
{
	CollisionRectangle coll = collisionBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndRectangleHit(PayerBOX, &coll)) {
		return collisionBoxes[boxNum];
	}
	return NULL;
}
M_textureBOX * Stage_textureBOX_hit(CollisionRectangle * PlayerBOX, int boxNum)
{
	CollisionRectangle coll = textureBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndRectangleHit(PlayerBOX, &coll)) {
		return textureBoxes[boxNum];
	}
	return NULL;
}
M_collsionBOX * Stage_collisionBOX_hitWithLine(CollisionLine Lc, int boxNum)
{
	CollisionRectangle coll = collisionBoxes[boxNum]->GetColl();
	if (Collision_LineAndRectangleHit(&Lc, &coll)) {
		return collisionBoxes[boxNum];
	}
	return NULL;
}
M_collsionBOX * Stage_collisionBOX_Get(int boxNum)
{
	return collisionBoxes[boxNum];
}

M_heartBox * Stage_heartBox_hitWithPoint(float x, float y, int boxNum)
{
	CollisionPoint po;
	po.point.x = x;
	po.point.y = y;
	CollisionRectangle coll = heartBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndPointHit(&coll, &po)) {
		return heartBoxes[boxNum];
	}
	return NULL;
}

M_damegeBox * Stage_damegeBox_hit(CollisionRectangle pB, int boxNum)
{
	CollisionRectangle coll = damegeBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndRectangleHit(&pB, &coll)) {
		return damegeBoxes[boxNum];
	}
	return NULL;
}

M_lineCreateBox* Stage_lineBox_hit(float x,float y, int boxNum) {


	if (lineBoxes[boxNum]->GetTrigger())return NULL;
	CollisionPoint po;
	po.point.x = x;
	po.point.y = y;
	CollisionRectangle coll = lineBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndPointHit(&coll, &po)) {
		return lineBoxes[boxNum];
	}
	return NULL;
}

M_stageTransBox * Stage_transBox_hit(CollisionRectangle * playerBOX, int boxNum)
{
	CollisionRectangle coll = stageTransBoxes[boxNum]->GetColl();
	if (Collision_RectangleAndRectangleHit(playerBOX, &coll)) {
		return stageTransBoxes[boxNum];
	}
	return NULL;
}

M_enemyBox* Stage_enemyBox_byNumber(int boxNum) {

	return enemyBoxes[boxNum];
}

M_diagonalCollisionBox * Stage_diagonalBox_byNumber(int boxNum)
{
	return diagonalBoxes[boxNum];
}

M_enemy2Box * Stage_GetEnemy2Box_byNumber(int boxNum)
{
	return enemy2Boxes[boxNum];
}

M_eventBox * Stage_GetEventBox_byNumber(int boxNum)
{
	return eventBoxes[boxNum];
}

M_mirorrBox * Stage_GetMirrorBox_byNumber(int boxNum)
{
	return mirrorBoxes[boxNum];
}

M_goalBox * Stage_GetGoalBox_byNumber(int boxNum)
{
	return goalBoxes[boxNum];
}

void Stage_SetMirrorON_or_OFF(int trigger)
{
	for (int i = 0; i < mirrorBoxes.size(); i++)
	{
		mirrorBoxes[i]->Set_ON_OFF(trigger);
	}
}

int Stage_CollsionWithMirror(CollisionLine cl)
{
	return 0;
}


//type2:M_collisionBOX2を取得などなど
//type3:などなど、




bool loadMapXML(int mapNumber) {

	char loadpath[64] = "MapConfig/";
	strcat_s(loadpath, stageName[mapNumber]);
	strcat_s(loadpath, ".xml");

	tinyxml2::XMLDocument mydocument;
	mydocument.LoadFile(loadpath);
	tinyxml2::XMLElement* rootElement = mydocument.RootElement();

	int boxCount = rootElement->IntAttribute("boxCount");
	tinyxml2::XMLElement* firstNode = rootElement->FirstChildElement();
	StageSizeWidth = rootElement->IntAttribute("mapSizeX");
	StageSizeHeight = rootElement->IntAttribute("mapSizeY");
	GM_mainCamera()->SetBoundary(0, 0, StageSizeWidth, StageSizeHeight);
	for (int i = 0; i < boxCount; i++)
	{
		const char* boxKind = firstNode->Attribute("kind");
		if (strcmp(boxKind, "textureBox") == 0) {
			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");

			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");
			M_textureBOX* tex = new M_textureBOX(filename, x, y, w, h, layer);
			textureBoxes.push_back(tex);
			
		}

		if (strcmp(boxKind, "collisionBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			M_collsionBOX* col = new M_collsionBOX(x, y, w, h);
			collisionBoxes.push_back(col);
			
		}

		if (strcmp(boxKind, "trans_areaBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");
			M_heartBox* htb = new M_heartBox("Asset/key_heart_box.png", x, y, w, h, layer);
			heartBoxes.push_back(htb);
		}

		if (strcmp(boxKind, "stageTransBox") == 0) {
			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");

			const char* nextStage = firstNode->Attribute("nextStage");
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");

			int nextStNumber = -1;
			for (int i = 0; i < STAGEMAX; i++)
			{
				if (strcmp(nextStage, stageName[i]) == 0) {
					nextStNumber = i;
				}
			}

			M_stageTransBox* tex = new M_stageTransBox(filename, x, y, w, h, layer, nextStNumber);
			stageTransBoxes.push_back(tex);
		}

		if (strcmp(boxKind, "goalBox") == 0) {
			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");

			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");
			M_goalBox* tex = new M_goalBox(filename, x, y, w, h, layer);
			tex->LoadState(true);
			goalBoxes.push_back(tex);
		}
		if (strcmp(boxKind, "damegeBox") == 0) {
			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");

			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");

			if (strcmp(tName, "null") == 0) {
				M_damegeBox* tex = new M_damegeBox(NULL, x, y, w, h, layer);
				damegeBoxes.push_back(tex);
			}
			else {
				M_damegeBox* tex = new M_damegeBox(filename, x, y, w, h, layer);
				damegeBoxes.push_back(tex);
			}		
		}

		if (strcmp(boxKind, "enemyBox") == 0) {

			const char* enemyName = firstNode->Attribute("enemyName");
			const char* dirTypeName = firstNode->Attribute("dirTypeName");
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			//float w = (float)firstNode->IntAttribute("width");
			//float h = (float)firstNode->IntAttribute("height");

			M_enemyBox* enx = new M_enemyBox(enemyName, x, y, dirTypeName);
			enemyBoxes.push_back(enx);
		}

		if (strcmp(boxKind, "lineCreateBox") == 0) {
			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");

			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");
			float dirX = (float)firstNode->IntAttribute("lenX");
			float dirY = -(float)firstNode->IntAttribute("lenY");
			//float len = (float)firstNode->IntAttribute("length");

			M_lineCreateBox* lcb = new M_lineCreateBox(filename, x, y, w, h, layer);
			lcb->LoadParameta(dirX,dirY);
			lineBoxes.push_back(lcb);
		}

		if (strcmp(boxKind, "diagonalBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			const char* dirTypeName = firstNode->Attribute("diaDir");
			int dirT = 0;
			if (strcmp(dirTypeName, "left")==0) {
				dirT = 1;
			}
			else if (strcmp(dirTypeName, "right") == 0) {
				dirT = 0;
			}
			M_diagonalCollisionBox* dib = new M_diagonalCollisionBox(x, y, w, h, dirT);
			diagonalBoxes.push_back(dib);
		}

		if (strcmp(boxKind, "enemy2Box") == 0) {
			const char* enemyName = firstNode->Attribute("enemyName");
			const char* dirTypeName = firstNode->Attribute("dirTypeName");
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");

			
			float hx = (float)firstNode->IntAttribute("heartX");
			float hy = -(float)firstNode->IntAttribute("heartY");
			float hw = (float)firstNode->IntAttribute("heartW");
			float hh = (float)firstNode->IntAttribute("heartH");
			const char* chirlName = firstNode->Attribute("loadName");

			int hiddenCount = -1;
			if (strcmp(chirlName, "key_heart_box")==0) {
				M_heartBox* htb = new M_heartBox("Asset/Stage/key_heart_box.png", hx, hy, hw, hh, 7);
				htb->LoadState(false);
				heartBoxes.push_back(htb);
				hiddenCount = (int)heartBoxes.size() - 1;
			}else if (strcmp(chirlName, "area_heart_box")==0) {
				const char* nextName = firstNode->Attribute("childName");
				int nextStNumber = -1;
				for (int i = 0; i < STAGEMAX; i++)
				{
					if (nextName == NULL)continue;
					if (strcmp(nextName, stageName[i]) == 0) {
						nextStNumber = i;
					}
				}
				M_stageTransBox* mstb = new M_stageTransBox("Asset/Stage/area_heart_box.png", hx, hy, hw, hh, 7, nextStNumber);
				mstb->LoadState(false);
				stageTransBoxes.push_back(mstb);
				hiddenCount = (int)stageTransBoxes.size() - 1 + 500;
			}
			//int layer = firstNode->IntAttribute("layer");
			
			
			M_enemy2Box* en2b = new M_enemy2Box(enemyName, x, y, hiddenCount, dirTypeName);
			enemy2Boxes.push_back(en2b);
		}

		if (strcmp(boxKind, "playerBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			M_startBox* mst = new M_startBox(x, y, w, h);
			startBoxes.push_back(mst);
		}

		if (strcmp(boxKind, "eventBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			const char* evName = firstNode->Attribute("eventName");
			//int eNuber = eventNumberGet(evName);
			M_eventBox* ebox = new M_eventBox(evName, x, y, w, h);
			eventBoxes.push_back(ebox);
		}

		if (strcmp(boxKind, "mirrorBox") == 0) {
			float x = (float)firstNode->IntAttribute("posX");
			float y = -(float)firstNode->IntAttribute("posY");
			float w = (float)firstNode->IntAttribute("width");
			float h = (float)firstNode->IntAttribute("height");
			int layer = firstNode->IntAttribute("layer");

			char filename[64] = "Asset/";
			strcat_s(filename, "Stage");
			strcat_s(filename, "/");
			const char* tName = firstNode->Attribute("loadName");
			strcat_s(filename, tName);
			strcat_s(filename, ".png");
			const char* text = firstNode->Attribute("Rot");
			int rot = 0;
			if (strcmp(text, "OFF") == 0) {
				rot = 1;
			}
			M_mirorrBox* mir = new M_mirorrBox(filename, x, y, w, h, rot);
			mirrorBoxes.push_back(mir);
		}

		if (i < boxCount - 1)firstNode = firstNode->NextSiblingElement();
	}



	return true;
}

void StageTransCheck() {
	if (Now_StageNumber == Next_StageNumber)return;
	GetGameScene()->UnloadEnemy();
	Stage_Final();

	Now_StageNumber = Next_StageNumber;
	LoadingTexture_SetZeroCount();
	loadMapXML(Now_StageNumber);

	StartPosX = 300;
	StartPosY = 500;

	GetGameScene()->LoadEnemy();
	Texture_Load();
	GetGameScene()->InitEnemy();
	Stage_Init();
	//Player_Setp
}


void BGMInit() {
	//PlaySound(bgmList[Now_StageNumber]);
}

void BGMFinal() {
	//StopSound(bgmList[Now_StageNumber]);
}


int eventNumberGet(const char* name) {
	for (int i = 0; i < EVENTTYPE_MAX; i++)
	{
		if (strcmp(name, eventName[i]) == 0) {
			return i;
		}
	}
	return -1;
}


float2D Stage_mapCheck(float2D stPos, float2D dir)
{
	CollisionLine cL = { stPos.x,stPos.y,stPos.x + 750 * dir.x,stPos.y + 750 * dir.y };
	for (size_t i = 0; i < collisionBoxes.size(); i++)
	{
		CollisionRectangle cb = collisionBoxes[i]->GetColl();

		if (dir.x == 1.0f && dir.y == -1.0f) {
			CollisionLine bl_left = { cb.x,cb.y,cb.x,cb.y + cb.h };
			CollisionLine bl_down = { cb.x,cb.y + cb.h,cb.x + cb.w,cb.y + cb.h };
			Cross_imf csleft = Collision_LineAndLineHit(cL, bl_left);
			if (csleft.flag) {
				if (cL.ex > csleft.interX)cL.ex = csleft.interX;
				if (cL.ey < csleft.interY)cL.ey = csleft.interY;
			}
			Cross_imf csdown = Collision_LineAndLineHit(cL, bl_down);
			if (csdown.flag) {
				if (cL.ex > csdown.interX)cL.ex = csdown.interX;
				if (cL.ey < csdown.interY)cL.ey = csdown.interY;
			}
		}
		if (dir.x == 1.0f && dir.y == 0.0f) {
			CollisionLine bl_left = { cb.x,cb.y,cb.x,cb.y + cb.h };
			Cross_imf csleft = Collision_LineAndLineHit(cL, bl_left);
			if (csleft.flag) {
				if (cL.ex > csleft.interX)cL.ex = csleft.interX;
				//if (cL.ey < csleft.interY)cL.ey = csleft.interY;
			}
		}
		if (dir.x == 1.0f && dir.y == 1.0f) {
			CollisionLine bl_left = { cb.x,cb.y,cb.x,cb.y + cb.h };
			CollisionLine bl_up = { cb.x,cb.y,cb.x + cb.w,cb.y };
			Cross_imf csleft = Collision_LineAndLineHit(cL, bl_left);
			if (csleft.flag) {
				if (cL.ex > csleft.interX)cL.ex = csleft.interX;
				if (cL.ey < csleft.interY)cL.ey = csleft.interY;
			}
			Cross_imf csup = Collision_LineAndLineHit(cL, bl_up);
			if (csup.flag) {
				if (cL.ex > csup.interX)cL.ex = csup.interX;
				if (cL.ey > csup.interY)cL.ey = csup.interY;
			}
		}
		if (dir.x == 0.0f && dir.y == 1.0f) {
			CollisionLine bl_up = { cb.x,cb.y,cb.x + cb.w,cb.y };
			Cross_imf csup = Collision_LineAndLineHit(cL, bl_up);
			if (csup.flag) {
				//if (cL.ex > csup.interX)cL.ex = csup.interX;
				if (cL.ey > csup.interY)cL.ey = csup.interY;
			}
		}
		if (dir.x == -1.0f && dir.y == 1.0f) {
			CollisionLine bl_right = { cb.x + cb.w, cb.y,cb.x + cb.w,cb.y + cb.h };
			CollisionLine bl_up = { cb.x,cb.y,cb.x + cb.w,cb.y };
			Cross_imf csright = Collision_LineAndLineHit(cL, bl_right);
			if (csright.flag) {
				if (cL.ex < csright.interX)cL.ex = csright.interX;
				if (cL.ey < csright.interY)cL.ey = csright.interY;
			}
			Cross_imf csup = Collision_LineAndLineHit(cL, bl_up);
			if (csup.flag) {
				if (cL.ex < csup.interX)cL.ex = csup.interX;
				if (cL.ey > csup.interY)cL.ey = csup.interY;
			}
		}
		if (dir.x == -1.0f && dir.y == 0.0f) {
			CollisionLine bl_right = { cb.x + cb.w, cb.y,cb.x + cb.w,cb.y + cb.h };
			Cross_imf csright = Collision_LineAndLineHit(cL, bl_right);
			if (csright.flag) {
				if (cL.ex < csright.interX)cL.ex = csright.interX;
				//if (cL.ey < csright.interY)cL.ey = csright.interY;
			}
		}
		if (dir.x == -1.0f && dir.y == -1.0f) {
			CollisionLine bl_right = { cb.x + cb.w, cb.y,cb.x + cb.w,cb.y + cb.h };
			CollisionLine bl_down = { cb.x,cb.y + cb.h,cb.x + cb.w,cb.y + cb.h };
			Cross_imf csright = Collision_LineAndLineHit(cL, bl_right);
			if (csright.flag) {
				if (cL.ex < csright.interX)cL.ex = csright.interX;
				if (cL.ey < csright.interY)cL.ey = csright.interY;
			}
			Cross_imf csdown = Collision_LineAndLineHit(cL, bl_down);
			if (csdown.flag) {
				if (cL.ex < csdown.interX)cL.ex = csdown.interX;
				if (cL.ey < csdown.interY)cL.ey = csdown.interY;
			}
		}
		if (dir.x == 0.0f && dir.y == -1.0f) {
			CollisionLine bl_down = { cb.x,cb.y + cb.h,cb.x + cb.w,cb.y + cb.h };
			Cross_imf csdown = Collision_LineAndLineHit(cL, bl_down);
			if (csdown.flag) {
				//if (cL.ex > csdown.interX)cL.ex = csdown.interX;
				if (cL.ey < csdown.interY)cL.ey = csdown.interY;
			}
		}
	}
	float2D ep = { cL.ex,cL.ey };
	return ep;
}

