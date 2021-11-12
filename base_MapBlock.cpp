#include "base_MapBlock.h"
#include "Line.h"
#include "config.h"
#include "Stage.h"
#include "SoundManager.h"

static float layerP[16] = {
	1,
	0,
	0.125f,
	0.25f,
	0.5f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f
};


M_collsionBOX::M_collsionBOX()
{
}

M_collsionBOX::M_collsionBOX(float x, float y, float w, float h)
{
	posX = x;
	posY = y;
	width = w;
	height = h;
}

void M_collsionBOX::LoadData(float x, float y, float w, float h)
{
	posX = x;
	posY = y;
	width = w;
	height = h;
}

CollisionRectangle M_collsionBOX::GetColl()
{
	CollisionRectangle co;
	co.x = posX;
	co.y = posY;
	co.w = width;
	co.h = height;
	return co;
}

M_textureBOX::M_textureBOX()
{
	//pl = false;
}

M_textureBOX::M_textureBOX(const char * filename, float x, float y, int layer)
{
	if (filename != NULL) {
		sp = new SpriteC(filename, layer);
		isSp = true;
	}
	else {
		isSp = false;
	}
	posX = x;
	posY = y;
	Onwh = false;
}

M_textureBOX::M_textureBOX(const char * filename, float x, float y, float w, float h, int layer)
{
	if (filename != NULL) {
		sp = new SpriteC(filename, layer);
		isSp = true;
	}
	else {
		isSp = false;
	}
	posX = x;
	posY = y;
	width = w;
	height = h;
	spriteLayer = layer;
	Onwh = true;
}

M_textureBOX::~M_textureBOX()
{
	if (isSp) {
		delete sp;
		sp = NULL;
	}
	
}

void M_textureBOX::LoadData(const char * filename, float x, float y, float w, float h, int layer)
{

	if (filename != NULL) {
		sp = new SpriteC(filename, layer);
		isSp = true;
	}
	else {
		isSp = false;
	}
	posX = x;
	posY = y;
	width = w;
	height = h;
	Onwh = true;
}

void M_textureBOX::Init()
{
	if (isSp) {
		sp->Init();
		sp->SetPosition(posX, posY);
		sp->SetMultiple(layerP[spriteLayer], layerP[spriteLayer]);
		if (spriteLayer < 5) {
			sp->SetAnchorPoint(ANCHOR_CENTER);
			sp->SetScale(1.5f, 1.5f);
		}
		if (Onwh) {
			sp->SetHeight(height);
			sp->SetWidth(width);
		}
		else
		{
			width = sp->GetWidth();
			height = sp->GetHeight();
		}
	}	
	//pl = false;
}


CollisionRectangle M_textureBOX::GetColl()
{
	CollisionRectangle co;
	co.x = posX;
	co.y = posY;
	co.w = width;
	co.h = height;
	return co;
}



M_heartBox::M_heartBox(const char * filename, float x, float y, float w, float h, int layer)
{
	sp = new SpriteC(filename, layer);
	hsp = new SpriteC("Asset/key_heart.png",12);
	tsp = new SpriteC("Asset/area_heart.png", 12);
	posX = x;
	posY = y;
	width = w;
	height = h;
	active = true;
}

M_heartBox::~M_heartBox()
{
	ani->End();
	delete ani;
	ani = NULL;

	delete hsp;
	hsp = NULL;
	delete tsp;
	tsp = NULL;

	delete sp;
	sp = NULL;
}

void M_heartBox::LoadState(bool b)
{
	active = b;
}

void M_heartBox::Init()
{
	sp->Init();
	float w = sp->GetWidth();
	float h = sp->GetHeight();
	sp->SetCutSize(w/4, h/4);
	sp->SetSpriteSize(width, height);
	sp->SetPosition(posX, posY);
	sp->SetActive(active);
	ani = new AnimationC(sp, 16, { 0,0 }, 10,"hearAni");
	ani->Init();
	if(active)ani->Play(true);

	hsp->Init();
	hsp->SetActive(false);
	hsp->SetAnchorPoint(ANCHOR_CENTER);
	hsp->SetPosition(posX + width / 2, posY + (height / 2) + 64);

	tsp->Init();
	tsp->SetActive(false);
	tsp->SetAnchorPoint(ANCHOR_CENTER);
	tsp->SetPosition(posX + width / 2, posY + (height / 2) + 64);
}



void M_heartBox::Update()
{
	
}

float2D M_heartBox::GetPosCn()
{
	float2D f2d = {
		posX + width / 2,posY + height / 2
	};
	return f2d;
}

CollisionRectangle M_heartBox::GetColl()
{
	CollisionRectangle co;
	co.x = posX;
	co.y = posY;
	co.w = width;
	co.h = height;
	return co;
}

void M_heartBox::SetActive(bool b)
{
	if (active == b)return;
	active = b;
	sp->SetActive(active);
	if (active) {
		ani->Init();
		ani->Play(true);
	}
	else {
		ani->End();
	}
}

void M_heartBox::SetHeartActive(bool b)
{
	hsp->SetActive(b);
}

void M_heartBox::SetAreahActive(bool b)
{
	tsp->SetActive(b);
}

M_invisibleBox::~M_invisibleBox()
{
}

float2D M_invisibleBox::GetPrantformPos(float x, float y)
{
	float2D f2d;
	if (x < posX + width / 2) {
		f2d.x = posX + width;
		f2d.y = posY + height;
	}
	else {
		f2d.x = posX;
		f2d.y = posY + height;
	}
	return f2d;
}

void M_lineCreateBox::LoadParameta(float lenX, float lenY)
{
	lengthX = lenX;
	lengthY = lenY;
	timeCount = 0;
	timeMax = 400;
}

void M_lineCreateBox::OnTrigger()
{
	if (isTrigger)return;
	isTrigger = true;
	
	float sx = posX + (width / 2);
	float sy = posY + (height / 2);
	float ex = posX + lengthX + width / 2;
	float ey = posY + lengthY + height / 2;

	Line_CreateLineMap(sx, sy, ex, ey);
}

void M_lineCreateBox::Update()
{
	if (isTrigger) {
		if (timeCount >= timeMax) {
			OffTrigger();
		}

		timeCount++;
	}
}

void M_lineCreateBox::OffTrigger()
{
	if (isTrigger == false)return;
	isTrigger = false;
	timeCount = 0;
}

M_enemyBox::M_enemyBox(const char * eName, float x, float y, const char* dtname)
{
	strcpy_s(name,eName);
	strcpy_s(dirTypename, dtname);
	posX = x;
	posY = y;
}

void M_enemyBox::SetEnemyEnable()
{
	if (eEnable)return;
	eEnable = true;



}

M_diagonalCollisionBox::M_diagonalCollisionBox(float x, float y, float w, float h, int Dir)
{
	if (Dir == ld_ru) {
		diaLine = new LineStraightC(x, y + h, x + w, y);
	}
	else {
		diaLine = new LineStraightC(x, y, x + w, y + h);
	}
	m_dir = Dir;
}

M_diagonalCollisionBox::~M_diagonalCollisionBox()
{
	delete diaLine;
}

void M_goalBox::Init()
{
	sp->Init();
	int w = sp->GetWidth();
	int h = sp->GetHeight();

	sp->SetCutSize(w/4, h/4);
	sp->SetSpriteSize(width, height);
	sp->SetPosition(posX, posY);
	sp->SetActive(active);
	ani = new AnimationC(sp, 16, { 0,0 }, 10, "hearAni");
	ani->Init();
	if (active)ani->Play(true);
}

M_mirorrBox::M_mirorrBox(const char * filename, float x, float y, float w, float h, int mir)
{
	if (strcmp(filename, "Asset/Stage/mirror_slant_left.png")==0) {
		msp[0] = new SpriteC("Asset/Stage/mirror_vertical_left.png");
		msp[1] = new SpriteC("Asset/Stage/mirror_slant_left.png");
		aniSp = new SpriteC("Asset/Stage/mirror_rotation_LB.png");
		Current = 1;
		Dir = -1;
		mirorrLine[0] = { x + w * 0.45f,y,x + w * 0.45f,y + 0.9f*h };
		mirorrLine[1] = { x + w * 0.75f,y,x + w * 0.15f,y + 0.9f*h };
	}
	if (strcmp(filename, "Asset/Stage/mirror_vertical_left.png") == 0) {
		msp[0] = new SpriteC("Asset/Stage/mirror_vertical_left.png");
		msp[1] = new SpriteC("Asset/Stage/mirror_slant_left.png");
		aniSp = new SpriteC("Asset/Stage/mirror_rotation_LB.png");
		Current = 0;
		Dir = -1;
		mirorrLine[0] = { x + w * 0.45f,y,x + w * 0.45f,y + 0.9f*h };
		mirorrLine[1] = { x + w * 0.75f,y,x + w * 0.15f,y + 0.9f*h };
	}
	if (strcmp(filename, "Asset/Stage/mirror_slant_right.png") == 0) {
		msp[0] = new SpriteC("Asset/Stage/mirror_vertical_right.png");
		msp[1] = new SpriteC("Asset/Stage/mirror_slant_right.png");
		aniSp = new SpriteC("Asset/Stage/mirror_rotation_RB.png");
		Current = 1;
		Dir = 1;
		mirorrLine[0] = { x + w * 0.55f,y,x + w * 0.55f,y + 0.9f*h };
		mirorrLine[1] = { x + w * 0.25f,y,x + w * 0.85f,y + 0.9f*h };
	}
	if (strcmp(filename, "Asset/Stage/mirror_vertical_right.png") == 0) {
		msp[0] = new SpriteC("Asset/Stage/mirror_vertical_right.png");
		msp[1] = new SpriteC("Asset/Stage/mirror_slant_right.png");
		aniSp = new SpriteC("Asset/Stage/mirror_rotation_RB.png");
		Current = 0;
		Dir = 1;
		mirorrLine[0] = { x + w * 0.55f,y,x + w * 0.55f,y + 0.9f*h };
		mirorrLine[1] = { x + w * 0.25f,y,x + w * 0.85f,y + 0.9f*h };
	}
	mirType = mir;
	pos.x = x;
	pos.y = y;
	size.x = w;
	size.y = h;
	lspos.x = x + w * 0.5f;
	lspos.y = y + h * 0.3f;

	mColor[0] = D3DCOLOR_RGBA(255, 0, 0, 255);
	mColor[1] = D3DCOLOR_RGBA(255, 165, 0, 255);
	mColor[2] = D3DCOLOR_RGBA(255, 255, 0, 255);
	mColor[3] = D3DCOLOR_RGBA(0, 128, 0, 255);
	mColor[4] = D3DCOLOR_RGBA(0, 255, 255, 255);
	mColor[5] = D3DCOLOR_RGBA(0, 0, 255, 255);
	mColor[6] = D3DCOLOR_RGBA(128, 0, 128, 255);
	mColor[7] = D3DCOLOR_RGBA(255, 255, 255, 255);
	mColor[8] = D3DCOLOR_RGBA(155, 155, 155, 255);
	mirColor = mColor[6];
	oldColor = D3DCOLOR_RGBA(255, 255, 255, 255);
}

M_mirorrBox::~M_mirorrBox()
{

	delete ani;
	delete aniSp;
	delete msp[0];
	delete msp[1];
	
}

void M_mirorrBox::Init()
{
	msp[0]->Init();
	msp[0]->SetPosition(pos.x, pos.y);
	msp[0]->SetSpriteSize(size.x, size.y);
	msp[0]->SetActive(false);

	msp[1]->Init();
	msp[1]->SetPosition(pos.x, pos.y);
	msp[1]->SetSpriteSize(size.x, size.y);
	msp[1]->SetActive(false);
	msp[Current]->SetActive(true);
	LineNumber = -1;
	rLineNumber = -1;

	aniSp->Init();
	aniSp->SetCutSize(512, 512);
	aniSp->SetPosition(pos.x, pos.y);
	aniSp->SetSpriteSize(size.x, size.y);
	aniSp->SetActive(false);

	ani = new AnimationC(aniSp, 20, { 0,0 }, 2);
	ani->Init();
	AtimeCount = 0;
	currentColor = 0;
}

void M_mirorrBox::Update()
{
	if (ani->GetPlayF()) {
		if (Current == 0) {
			if (AtimeCount > 20 && ani->GetFrameCount()%20 == 0) {
				ani->Pause();
				aniSp->SetActive(false);
				msp[0]->SetActive(true);
			}
		}
		if (Current == 1) {
			if (AtimeCount > 20 && ani->GetFrameCount() % 20 == 17) {
				ani->Pause();
				aniSp->SetActive(false);
				msp[1]->SetActive(true);
			}
		}
		AtimeCount++;
	}
	if (mirType == mirorr_ON) {
		currentColor = (timeCount / 30) % 7;
		changeColor(mColor[currentColor]);
		msp[0]->SetColor(mirColor);
		msp[1]->SetColor(mirColor);
	}
	if (mirType == mirorr_OFF) {
		msp[0]->SetColor(mColor[8]);
		msp[1]->SetColor(mColor[8]);
	}

	timeCount++;
	if (timeCount >= 6000) {
		timeCount = 0;
	}

	if (LineNumber == -1)return;
	if (Line_GetLineForNumberAllMAP(LineNumber) == NULL) {
		LineNumber = -1;
	}
}

void M_mirorrBox::Final()
{
}

void M_mirorrBox::Set_ON_OFF(int onAoff)
{
	mirType = onAoff;
	if (mirType == mirorr_ON) {
		SoundManager_PlaySE(SL_mirror_unlocked);
	}
	else if (mirType == mirorr_OFF) {
		SoundManager_PlaySE(SL_mirror_locked);
	}
}

void M_mirorrBox::SetMirorrRotate()
{
	if (mirType == mirorr_OFF)return;
	msp[Current]->SetActive(false);
	Current++;
	if (Current >= 2)Current = 0;
	aniSp->SetActive(true);
	ani->RePlay(true);
	AtimeCount = 0;
	//msp[Current]->SetActive(true);
}

CollisionRectangle M_mirorrBox::GetColl()
{
	CollisionRectangle coll;
	coll.x = pos.x + size.x * 0.2f;
	coll.y = pos.y;
	coll.w = size.x * 0.6f;
	coll.h = size.y * 0.8f;
	return coll;
}

int M_mirorrBox::LineReflex(LINE* line)
{
	if (line->Num == LineNumber)return 0;
	if (line->Num == rLineNumber)return 0;
	switch (line->lintType)
	{
	case l_lhory:
		if (line->startPos.y >= pos.y)return 1;
		if (Current == 0)return 1;
		if (Dir == -1) {
			Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
			if (cs.flag == false)return 0;
			lspos.x = cs.interX;
			lspos.y = cs.interY;
			float2D ep = Stage_mapCheck(lspos, { -1.0f,0.0f });
			rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
			LineNumber = line->Num;
			return 2;
		}
		if (Dir == 1) {
			Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
			if (cs.flag == false)return 0;
			lspos.x = cs.interX;
			lspos.y = cs.interY;
			float2D ep = Stage_mapCheck(lspos, { 1.0f,0.0f });
			rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
			LineNumber = line->Num;
			return 2;
		}
		break;
	case l_lvert:
		if (line->startPos.x < pos.x&&Dir == -1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { -1.0f,0.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
			if (Current == 1) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 0.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
		}
		if (line->startPos.x > pos.x&&Dir == 1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 1.0f,0.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
			if (Current == 1) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 0.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
		}
		break;
	case l_oleft:
		if (line->startPos.x < pos.x && Dir == -1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { -1.0f,1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
			if (Current == 1) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { -1.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
		}
		if (line->startPos.x > pos.x && Dir == 1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 1.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y, line->Num);
				LineNumber = line->Num;
				return 2;
			}
		}
		break;
	case l_oright:
		if (line->startPos.x > pos.x && Dir == 1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 1.0f,1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}
			if (Current == 1) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { 1.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y,line->Num);
				LineNumber = line->Num;
				return 2;
			}		
		}
		if (line->startPos.x < pos.x && Dir == -1) {
			if (Current == 0) {
				Cross_imf cs = Collision_LineAndLineHit(line->GetColl(), mirorrLine[Current]);
				if (cs.flag == false)return 0;
				lspos.x = cs.interX;
				lspos.y = cs.interY;
				float2D ep = Stage_mapCheck(lspos, { -1.0f,-1.0f });
				rLineNumber = Line_CreateLineMap(lspos.x, lspos.y, ep.x, ep.y, line->Num);
				LineNumber = line->Num;
				return 2;
			}
		}
		break;
	default:
		break;
	}

	return 1;
}

void M_mirorrBox::changeColor(D3DXCOLOR color)
{
	int oldColor = currentColor - 1;
	if (oldColor < 0)oldColor = 6;

	D3DXCOLOR offc = mColor[currentColor] - mColor[oldColor];
	mirColor += offc/30.0f;

}


