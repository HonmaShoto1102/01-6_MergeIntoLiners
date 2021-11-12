#include "FairyStates.h"
#include "keyloger.h"
#include "playerCollision.h"
#include "collision.h"
#include "Stage.h"
#include "GM.h"
//#include "Liners.h"
#include "Effect.h"
#include "Heart.h"
#include "InputManager.h"
#include "playerEffect.h"
#include "playerAction.h"

Fs_Stand::Fs_Stand(FAIRYSTATEe fs,FAIRY* fa)
{
	stateName = fs;
	fairy = fa;
	AddNextState(fs_appear);
	AddNextState(fs_oblmoving);
	CoolTimeMax = 10;
	CoolTime = 0;
}

Fs_Stand::~Fs_Stand()
{
}

void Fs_Stand::Init()
{

	fairy->sprite->SetActive(false);
	fairy->sprite->SetPosition(0.0f, 0.0f);
	CoolTime = CoolTimeMax;
	if (FairyVH_GetboolByFocus() == false) {
		SetCamera_Foucs(cf_player);
		GM_mainCamera()->SetFocusLens(1.0f);
	}
}

void Fs_Stand::Update()
{
	CoolTime--;
	if (CoolTime <= 0) {
		CoolTime = 0;
	}
	if (CoolTime > 0)return;

	if (fairy->name == VERTICA) {
		if (keylogger_Trigger(KL_ENTER)&&GetKey_CallFairyV()) {
			if (Player_GetState() == ps_default||Player_GetState()==ps_teleport) {
				stateMachine->StateTrans(fs_appear);
			}
			if (Player_GetState() == ps_heartRotate&& FairyVH_GetStateForAllH(fs_oblmoving)==false) {
				stateMachine->StateTrans(fs_oblmoving);
			}
		}
	}
	if (fairy->name == HORIZY) {
		if (keylogger_Trigger(KL_SPACE)&&GetKey_CallFairyH()) {
			if (Player_GetState() == ps_default || Player_GetState() == ps_teleport) {
				stateMachine->StateTrans(fs_appear);
			}
			if (Player_GetState() == ps_heartRotate && FairyVH_GetStateForAllV(fs_oblmoving) == false) {
				stateMachine->StateTrans(fs_oblmoving);
			}
		}
	}
}

void Fs_Stand::Final()
{
}
void Fs_Stand::SetCoolTimeMax(int tim)
{
	CoolTimeMax = tim;
}
//*************************************************
Fs_Appear::Fs_Appear(FAIRYSTATEe fs, FAIRY * fa)
{
	stateName = fs_appear;
	fairy = fa;
	AddNextState(fs_stand);
	AddNextState(fs_lineBecome);
	startPosX = startPosY = endPosX = endPosY = 0;
	timeCount = 0;
	epX = epY = 0;
	fairyCountDownTime = 0;
	fairyDruationTime = FAIRYAS_TIME;
	targetCusour = new SpriteC("Asset/target_cursor.png", 10);
	zf = 0.01f;
	wtha = 0.0f;
	Hz = 3.0f;
}

Fs_Appear::~Fs_Appear()
{
	delete targetCusour;
}

void Fs_Appear::Init()
{
	targetCusour->Init();
	targetCusour->SetAnchorPoint(ANCHOR_CENTER);
	targetCusour->SetActive(false);
	FL = fl_defalt;
	timeCount = 0;
	fairyCountDownTime = 0;
	PL_DIR dir = Player_GetDirection();
	fdir = (int)dir;
	fairy->endPoint->SetActive(true);
	fairy->sprite->SetActive(true);

	if (fairy->name == VERTICA) {
		
		//epY = GM_mainCamera()->GetPosY() + GM_mainCamera()->GetScreenCameraHeight() / 2;
		PlayerEffect_SetEffect(pe_callFairy, Player_GetPosX(), Player_GetPosY());

		startPosX = Player_GetPosX() + dir * PlayerCollision_GetCollision().w;
		startPosY = Player_GetPosY() - PlayerCollision_GetCollision().h;
		epY = startPosY + VERTICA_LINELENGTH_MAX;
		if (epY > GM_mainCamera()->GetBoundrayBottem() - EN_PSIZE)epY = GM_mainCamera()->GetBoundrayBottem() - EN_PSIZE;

		SetCamera_Foucs(cf_fariy);
		GM_mainCamera()->SetFocusLens(1.3f);
		GM_mainCamera()->SetFocusPosX(startPosX + HORIZY_LINELENGTH_MAX / 2 * fdir);

		float y = GM_mainCamera()->GetOffsetPosY();
		CollisionRectangle coll{
			startPosX, y,
			FAIRY_SIZE,startPosY - y
		};
		startPosY = y;
		int index = Stage_GetNumberOfBlock(bl_collisionBox);
		for (int i = 0; i < index; i++)
		{
			M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll, i);
			if (mbox != NULL) {
				if (startPosY < mbox->GetColl().y + mbox->GetColl().h) {
					startPosY = mbox->GetColl().y + mbox->GetColl().h;
				}
			}
		}
		startPosY += LIMIT_FAIRY;
		//float x = GM_mainCamera()->GetPosX() + (GM_mainCamera()->GetScreenCameraWidth() / 2)*dir;
		float x = startPosX + HORIZY_LINELENGTH_MAX * fdir;
		//float x = GM_mainCamera()->GetPosX() + VERTICA_LINELENGTH_MAX * dir;
		CollisionRectangle coll2;
		if (x >= startPosX) {
			coll2.x = startPosX;
			coll2.y = startPosY;
			coll2.w = x - startPosX;
			coll2.h = FAIRY_SIZE;
			for (int i = 0; i < index; i++)
			{
				M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll2, i);
				if (mbox != NULL) {
					if (coll2.x + coll2.w > mbox->GetColl().x) {
						float tempX = coll2.x + coll2.w - mbox->GetColl().x;
						coll2.w -= tempX;
						
					}
				}
			}
			endPosX = coll2.x + coll2.w - LIMIT_FAIRY;
		}
		else
		{
			coll2.x = x;
			coll2.y = startPosY;
			coll2.w = startPosX - x;
			coll2.h = FAIRY_SIZE;
			for (int i = 0; i < index; i++)
			{
				M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll2, i);
				if (mbox != NULL) {
					if (coll2.x < mbox->GetColl().x) {
						float tempX = mbox->GetColl().x - coll2.x + mbox->GetColl().w;
						coll2.x += tempX;
						coll2.w -= tempX;
					}
				}
			}
			endPosX = coll2.x + LIMIT_FAIRY;
			
		}
		endPosY = startPosY;
		posX = startPosX;
		posY = startPosY;
		zf = fabsf((endPosX - startPosX) / 2);
		Hz = (700 / (zf+100)) * 3;
		fairy->sprite->SetPosition(posX, posY);
		fairy->endPoint->SetPosition(posX, posY);
		ActivateEffect("effect_call_vertica", { posX ,posY }, { 1,1 });
	}
	if (fairy->name == HORIZY) {
		//epX = GM_mainCamera()->GetPosX() + (GM_mainCamera()->GetScreenCameraWidth() / 2)*fdir;
		PlayerEffect_SetEffect(pe_callFairy, Player_GetPosX(), Player_GetPosY());
		startPosX = Player_GetPosX() + dir * PlayerCollision_GetCollision().w;
		startPosY = Player_GetPosY() + PlayerCollision_GetCollision().h/3;
		float tempPosY = Player_GetPosY() - PlayerCollision_GetCollision().h / 3;
		epX = startPosX + HORIZY_LINELENGTH_MAX * fdir;

		SetCamera_Foucs(cf_fariy);
		GM_mainCamera()->SetFocusLens(1.3f);
		GM_mainCamera()->SetFocusPosX(startPosX + HORIZY_LINELENGTH_MAX/2 * fdir);

		float top = GM_mainCamera()->GetOffsetPosY();
		CollisionRectangle coll{
			startPosX, top,
			FAIRY_SIZE,startPosY - top
		};
		//startPosY = y;
		int index = Stage_GetNumberOfBlock(bl_collisionBox);
		for (int i = 0; i < index; i++)
		{
			M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll, i);
			if (mbox != NULL) {
				if (coll.y < mbox->GetColl().y + mbox->GetColl().h) {
					float tempY = mbox->GetColl().y + mbox->GetColl().h - coll.y;
					coll.y = mbox->GetColl().y + mbox->GetColl().h;
					coll.h -= tempY;
				}
			}
		}
		endPosY = coll.y + LIMIT_FAIRY;
		//startPosY += LIMIT_LENGTH;
		
		endPosX = startPosX;
		posX = startPosX;
		posY = tempPosY;
		zf = (endPosY - startPosY) / 2;
		Hz = (500 / (100 - zf))* 3;
		float value =1.0f - (endPosY - tempPosY) / zf;
		wtha = asinf(value);
		fairy->sprite->SetPosition(posX, posY);
		fairy->endPoint->SetPosition(posX, posY);
		ActivateEffect("effect_call_horizy", { posX,posY }, { 1,1 });
	}
}

void Fs_Appear::Update()
{
	if (fairy->name == VERTICA) {
		posX = startPosX + fdir * fabsf(sinf(timeCount*0.01f * Hz/2)*(endPosX - startPosX));
		//posX = startPosX + sinf(timeCount*0.01f * Hz / 2)*(endPosX - startPosX);
		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);
		//float enpY = epY;
		float enpY = epY;
		CollisionRectangle coll{
			posX,posY,FAIRY_SIZE,enpY - posY
		};
		int index = Stage_GetNumberOfBlock(bl_collisionBox);
		for (int i = 0; i < index; i++)
		{
			M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll, i);
			if (mbox != NULL) {
				if (enpY > mbox->GetColl().y) {
					enpY = mbox->GetColl().y;
				}
			}
		}

		CollisionLine cLine = { posX + FAIRY_SIZE / 2,posY,posX + FAIRY_SIZE / 2,enpY };
		int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
		for (int i = 0; i < DiCount; i++)
		{
			M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
			if (dib != NULL) {
				LineStraightC* hill = dib->GetDiaLine();

				//CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w + 2,coll.y + coll.h };
				CollisionLine hillline = hill->GetLine();
				Cross_imf cr = Collision_LineAndLineHit(cLine, hillline);
				if (cr.flag) {
					enpY = cr.interY;
				}
			}
		}

		enpY -= LIMIT_LENGTH;
		fairy->endPoint->SetPosition(posX, enpY);
		fairy->endX = posX;
		fairy->endY = enpY;

//***********************************強化ライン************************************************
		htPosx = fairy->posX;
		CollisionLine line1 = { fairy->posX,fairy->posY,fairy->endX,fairy->endY };
		int hCount = Heart_GetHeartCount();
		for (int i = 0; i < hCount; i++)
		{
			Heart* ht = Heart_GetHeart(i);
			if (ht != NULL) {
				CollisionCircle cc;
				cc.center = { ht->sp->GetPosX(),ht->sp->GetPosY() };
				cc.radius = LIMIT_FAIRY * 0.5f;
				if (Collision_LineAndCircleHit(line1, cc)) {
					FL = fl_strong;
					htPosx = cc.center.x;
					htPosy = cc.center.y;
				}
			}
		}

		for (int i = 0; i < LINEMAX + 2*FMAX; i++)
		{
			LINE* li = Line_GetLineForNumberAllMAP(i);
			if (li != NULL && li->Num != fairy->fairyID) {
				if (li->lintType == l_lhory) {
					CollisionLine cl = { li->startPos.x,li->startPos.y,li->endPos.x,li->endPos.y };
					if (Collision_LineAndLineDistance(line1, cl, LIMIT_FAIRY*0.5f)) {
						ClearLineNum = i;
						htPosx = li->startPos.x;
						FL = fl_strong;
					}
				}
			}
		}


		if (keylogger_Trigger(KL_ENTER)&&GetKey_LineCreatV()) {
			//Liners_SetVEnable(true);
			if (FL == fl_defalt) {
				Line_CreateLineV(fairy->fairyID, fairy->posX, fairy->posY, fairy->endX, fairy->endY);
			}
			if (FL == fl_strong) {
				if (ClearLineNum != LINENULL) {
					Line_BecomeStrongLineMap(ClearLineNum);
					Line_CreateLineStrongV(fairy->fairyID, htPosx, fairy->posY, htPosx, fairy->endY, ClearLineNum);
				}
				else {
					Line_CreateLineV(fairy->fairyID, htPosx, fairy->posY, htPosx, fairy->endY, fl_strong);
				}
				
			}
			//Liners_CleateLineVertica(PLAYER_GROUND);
			stateMachine->StateTrans(fs_lineBecome);
		}

		if (FL == fl_defalt) {
			fairy->sprite->SetColor(255, 255, 255);
			fairy->endPoint->SetColor(255, 255, 255);
		}
		else
		{
			fairy->sprite->SetColor(255, 0, 0);
			fairy->endPoint->SetColor(255, 0, 0);
		}
		FL = fl_defalt;
	}

	if (fairy->name == HORIZY) {
		posY = (startPosY + endPosY)/2 - sinf(timeCount*0.01f* Hz - wtha)* zf;
		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);
		epX = startPosX + HORIZY_LINELENGTH_MAX * fdir;
		float enPX = epX;
		//epX = GM_mainCamera()->GetPosX() + (SCREEN_WIDTH / 2)*fdir;
		CollisionRectangle coll;
		int index = Stage_GetNumberOfBlock(bl_collisionBox);
		if (fdir == 1) {
			coll.x = posX;
			coll.y = posY;
			coll.w = enPX - posX;
			coll.h = FAIRY_SIZE;
			for (int i = 0; i < index; i++)
			{
				M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll, i);
				if (mbox != NULL) {
					if (enPX > mbox->GetColl().x) {
						enPX = mbox->GetColl().x;
					}
				}
			}
			CollisionLine cLine = { posX, posY + FAIRY_SIZE / 2,enPX, posY + FAIRY_SIZE / 2 };
			int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
			for (int i = 0; i < DiCount; i++)
			{
				M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
				if (dib != NULL) {
					LineStraightC* hill = dib->GetDiaLine();

					//CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w + 2,coll.y + coll.h };
					CollisionLine hillline = hill->GetLine();
					Cross_imf cr = Collision_LineAndLineHit(cLine, hillline);
					if (cr.flag) {
						enPX = cr.interX;
					}
				}
			}

			enPX -= LIMIT_LENGTH;
			epY = posY;
		}
		if (fdir == -1) {
			coll.x = GM_mainCamera()->GetOffsetPosX();
			coll.y = posY;
			coll.w = posX - coll.x;
			coll.h = FAIRY_SIZE;
			for (int i = 0; i < index; i++)
			{
				M_collsionBOX* mbox = Stage_collisionBOX_hit(&coll, i);
				if (mbox != NULL) {
					if (enPX < mbox->GetColl().x + mbox->GetColl().w) {
						enPX = mbox->GetColl().x + mbox->GetColl().w;
					}
				}
			}

			CollisionLine cLine = { posX, posY + FAIRY_SIZE / 2,enPX, posY + FAIRY_SIZE / 2 };
			int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
			for (int i = 0; i < DiCount; i++)
			{
				M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
				if (dib != NULL) {
					LineStraightC* hill = dib->GetDiaLine();

					//CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w + 2,coll.y + coll.h };
					CollisionLine hillline = hill->GetLine();
					Cross_imf cr = Collision_LineAndLineHit(cLine, hillline);
					if (cr.flag) {
						enPX = cr.interX;
					}
				}
			}

			enPX += LIMIT_LENGTH;
			epY = posY;
		}
		fairy->endPoint->SetPosition(enPX, epY);
		fairy->endX = enPX;
		fairy->endY = epY;


		htPosy = fairy->posY;
		CollisionLine line2 = { fairy->posX,fairy->posY,fairy->endX,fairy->endY };
		int hCount = Heart_GetHeartCount();
		for (int i = 0; i < hCount; i++)
		{
			Heart* ht = Heart_GetHeart(i);
			if (ht != NULL) {
				CollisionCircle cc;
				cc.center = { ht->sp->GetPosX(),ht->sp->GetPosY() };
				cc.radius = LIMIT_FAIRY * 0.5f;
				if (Collision_LineAndCircleHit(line2, cc)) {
					FL = fl_strong;
					htPosx = cc.center.x;
					htPosy = cc.center.y;
				}
			}
		}

		for (int i = 0; i < LINEMAX + FMAX*2; i++)
		{

			LINE* li = Line_GetLineForNumberAllMAP(i);
			if (li != NULL&&li->Num!=fairy->fairyID) {
				if (li->lintType == l_lvert) {
					CollisionLine cl = { li->startPos.x,li->startPos.y,li->endPos.x,li->endPos.y };
					if (Collision_LineAndLineDistance(line2, cl, LIMIT_FAIRY*0.5f)) {
						ClearLineNum = i;
						htPosy = li->startPos.y;
						FL = fl_strong;
					}
				}
			}
		}


		if (keylogger_Trigger(KL_SPACE)&&GetKey_LineCreatH()) {
			//Liners_SetVEnable(true);
			if (FL == fl_defalt) {
				Line_CreateLineH(fairy->fairyID, fairy->posX, fairy->posY, fairy->endX, fairy->endY);
			}
			if (FL == fl_strong) {
				if (ClearLineNum != LINENULL) {
					Line_BecomeStrongLineMap(ClearLineNum);
					Line_CreateLineStrongH(fairy->fairyID, fairy->posX, htPosy, fairy->endX, htPosy, ClearLineNum);
				}
				else {
					Line_CreateLineH(fairy->fairyID, fairy->posX, htPosy, fairy->endX, htPosy, fl_strong);
				}				
			}
			
			stateMachine->StateTrans(fs_lineBecome);
		}

		if (FL == fl_defalt) {
			fairy->sprite->SetColor(255, 255, 255);
			fairy->endPoint->SetColor(255, 255, 255);
		}
		else
		{
			fairy->sprite->SetColor(255, 0, 0);
			fairy->endPoint->SetColor(255, 0, 0);
		}

		FL = fl_defalt;
	}
	
	ClearLineNum = LINENULL;
	fairy->endPoint->SetAngle(timeCount*0.05f);
	timeCount++;
	fairyCountDownTime++;
	if (fairyCountDownTime >= fairyDruationTime) {
		fairyCountDownTime = fairyDruationTime;
		stateMachine->StateTrans(fs_stand);
	}
}

void Fs_Appear::Final()
{
	
	fairy->endPoint->SetActive(false);
	fairyCountDownTime = 0;
	targetCusour->SetActive(false);
	
}

//*****************************************************************************
Fs_LineBecame::Fs_LineBecame(FAIRYSTATEe fs, FAIRY * fa)
{
	stateName = fs;
	fairy = fa;
	AddNextState(fs_stand);

	lineCountDownTime = 0;
	lineDruationTime = LINEAS_TIME;
}

Fs_LineBecame::~Fs_LineBecame()
{
}

void Fs_LineBecame::Init()
{
	fairy->sprite->SetActive(false);
	fairy->endPoint->SetActive(false);
	lineCountDownTime = 0;
	if (fairy->name == VERTICA) {
		FairyVH_SetLockV(false, fairy->fairyID);
	}
	if (fairy->name == HORIZY) {
		FairyVH_SetLockH(false, fairy->fairyID);
	}
}

void Fs_LineBecame::Update()
{
	if (Player_GetState() == ps_leaveHeart) {
		stateMachine->StateTrans(fs_stand);
	}
	if (keylogger_Trigger(KL_END)&&GetKey_DestroyAll()) {
		stateMachine->StateTrans(fs_stand);	
	}

	if (fairy->name == VERTICA) {
		LINE* lv = Line_GetLineMessageV(fairy->fairyID);
		if (lv->st == ls_off) {
			stateMachine->StateTrans(fs_stand);
		}
	}
	if (fairy->name == HORIZY) {
		LINE* lh = Line_GetLineMessageH(fairy->fairyID);
		if (lh->st == ls_off) {
			stateMachine->StateTrans(fs_stand);
		}
	}

	lineCountDownTime++;
	if (lineCountDownTime >= lineDruationTime) {
		lineCountDownTime = lineDruationTime;
	}

}

void Fs_LineBecame::Final()
{
	//Liners_SetVEnable(false);
	if (fairy->name == VERTICA) {
		if (Line_GetActiveLineV() == false&&FairyVH_GetStateForAllV(fs_appear) == false) {
			//FairyVH_SetLockV(true, fairy->fairyID);
			FairyVH_SetLockAllV(true);
		}
		//Line_DeleteLineV(fairy->fairyID);
	}
	if (fairy->name == HORIZY) {
		if (Line_GetActiveLineH() == false&&FairyVH_GetStateForAllH(fs_appear) == false) {
			//FairyVH_SetLockH(true, fairy->fairyID);
			FairyVH_SetLockAllH(true);
		}
		//Line_DeleteLineH(fairy->fairyID);
	}
	
	if (FairyVH_GetboolByFocus() == false) {
		SetCamera_Foucs(cf_player);
		GM_mainCamera()->SetFocusLens(1.0f);
	}
	//if (Line_GetActiveLineV() == false && Line_GetActiveLineH() == false&&
	//	FairyVH_GetStateV(fairy->fairyID)!=fs_appear&&FairyVH_GetStateH(fairy->fairyID)!=fs_appear&&
	//	Player_GetState()!= ps_heartRotate) {
	//	SetCamera_Foucs(cf_player);
	//	GM_mainCamera()->SetFocusLens(1.0f);
	//	//FairyVH_SetLockAll(true);
	//}
	//Liners_SetHEnable(false);
	lineCountDownTime = 0;
}
//********************************************************************************
Fs_OblMoving::Fs_OblMoving(FAIRYSTATEe fs, FAIRY * fa)
{
	stateName = fs;
	fairy = fa;
	AddNextState(fs_lineBecome);
	AddNextState(fs_stand);
	startPoint = new SpriteC("Asset/arrow.png",13);
	endPoint = new SpriteC("Asset/cursor_horizy.png",13);
	targetCusour = new SpriteC("Asset/target_cursor.png", 13);
	startPoint->SetActive(false);
	endPoint->SetActive(false);
	for (int i = 0; i < 4; i++)
	{
		angle[i] = -PI / 4 + (PI / 2)*i;
	}

	fairyCountDownTime = 0;
	fairyDruationTime = FAIRYAS_TIME;

}

Fs_OblMoving::~Fs_OblMoving()
{
	delete startPoint;
	delete endPoint;
	delete targetCusour;
}

void Fs_OblMoving::Init()
{
	PlayerAction_SetOneStickModel(false);
	targetCusour->Init();
	targetCusour->SetAnchorPoint(ANCHOR_CENTER);
	targetCusour->SetActive(false);

	PlayerEffect_SetEffect(pe_callFairy, Player_GetPosX(), Player_GetPosY());


	SetCamera_Foucs(cf_movingfairy);

	FL = fl_defalt;
	fairyCountDownTime = 0;
	startPoint->Init();
	startPoint->SetAnchorPoint(ANCHOR_CENTER);
	endPoint->Init();
	endPoint->SetAnchorPoint(ANCHOR_CENTER);
	timeCount = 0;
	fairy->sprite->SetActive(true);
	//fairy->endPoint->SetActive(true);
	startPoint->SetActive(true);
	startPoint->SetScale(0.6f, 0.6f);
	endPoint->SetActive(true);
	endPoint->SetScale(0.6f, 0.6f);
	//CameraScreenW = GM_mainCamera()->GetScreenCameraWidth();
	//CameraScreenH = GM_mainCamera()->GetScreenCameraHeight();
	CameraScreenW = GM_mainCamera()->GetBoundrayW() - EN_PSIZE * 2;
	CameraScreenH = GM_mainCamera()->GetBoundrayH() - EN_PSIZE * 2;
	//screenLeft = GM_mainCamera()->GetPosX() - CameraScreenW * 0.5f;
	//screenTop = GM_mainCamera()->GetPosY() - CameraScreenH * 0.5f;
	screenLeft = GM_mainCamera()->GetBoundrayX() + EN_PSIZE;
	screenTop = GM_mainCamera()->GetBoundrayY() + EN_PSIZE;
	
	if (fairy->name == VERTICA) {
		fdir = (int)Player_GetDirection();
		if (fdir == 1)angNum = 0;
		if (fdir == -1)angNum = 3;

		if (angNum % 2 == 0) {
			currentltp = l_oright;
		}
		if (angNum % 2 == 1) {
			currentltp = l_oleft;
		}
		
		posX = Player_GetHeartPos().x;
		posY = Player_GetHeartPos().y;

		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);

	}

	if (fairy->name == HORIZY) {
		fdir = (int)Player_GetDirection();
		if (fdir == 1)angNum = 1;
		if (fdir == -1)angNum = 2;

		if (angNum % 2 == 0) {
			currentltp = l_oright;
		}
		if (angNum % 2 == 1) {
			currentltp = l_oleft;
		}
		//***ハートの座標を取得
		posX = Player_GetHeartPos().x;
		posY = Player_GetHeartPos().y;

		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);
	}
}

void Fs_OblMoving::Update()
{
	if (fairy->name == VERTICA||fairy->name == HORIZY) {
		/*float length = (endPosX - startPosX)*0.5f;
		posX = startPosX + length + length * sinf(timeCount*0.01f)*fdir;
		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);*/
		if (GetCamera_Foucs() == cf_movingfairy) {
			GM_mainCamera()->SetFocusPos(fairy->posX, fairy->posY);
		}

		CollisionLine stl = { posX,posY,posX + OBLMOVING_LINELENGTH_HALF * cosf(angle[angNum]),posY + OBLMOVING_LINELENGTH_HALF *sinf(angle[angNum]) };
		CollisionLine enl = { posX,posY,posX - OBLMOVING_LINELENGTH_HALF * cosf(angle[angNum]),posY - OBLMOVING_LINELENGTH_HALF * sinf(angle[angNum]) };
		CollisionLine scl[4];
		scl[0] = { screenLeft,screenTop,screenLeft + CameraScreenW,screenTop };
		scl[1] = { screenLeft + CameraScreenW,screenTop,screenLeft + CameraScreenW,screenTop + CameraScreenH };
		scl[2] = { screenLeft,screenTop + CameraScreenH,screenLeft + CameraScreenW,screenTop + CameraScreenH };
		scl[3] = { screenLeft,screenTop,screenLeft,screenTop + CameraScreenH };


		Cross_imf sc0 = Collision_LineAndLineHit(stl, scl[angNum%4]);
		Cross_imf sc1 = Collision_LineAndLineHit(stl, scl[(angNum+1)%4]);
		Cross_imf sc2 = Collision_LineAndLineHit(enl, scl[(angNum+2)%4]);
		Cross_imf sc3 = Collision_LineAndLineHit(enl, scl[(angNum+3)%4]);

		if (sc0.flag) {
			float old_length = (stl.ex - stl.sx)*(stl.ex - stl.sx) + (stl.ey - stl.sy)*(stl.ey - stl.sy);
			float new_length = (sc0.interX - stl.sx)*(sc0.interX - stl.sx) + (sc0.interY - stl.sy)*(sc0.interY - stl.sy);
			if (new_length < old_length) {
				stl.ex = sc0.interX;
				stl.ey = sc0.interY;
			}
		}
		if (sc1.flag) {
			float old_length = (stl.ex - stl.sx)*(stl.ex - stl.sx) + (stl.ey - stl.sy)*(stl.ey - stl.sy);
			float new_length = (sc1.interX - stl.sx)*(sc1.interX - stl.sx) + (sc1.interY - stl.sy)*(sc1.interY - stl.sy);
			if (new_length < old_length) {
				stl.ex = sc1.interX;
				stl.ey = sc1.interY;
			}
		}
		if (sc2.flag) {
			float old_length = (enl.ex - enl.sx)*(stl.ex - enl.sx) + (enl.ey - enl.sy)*(enl.ey - enl.sy);
			float new_length = (sc2.interX - enl.sx)*(sc2.interX - enl.sx) + (sc2.interY - enl.sy)*(sc2.interY - enl.sy);
			if (new_length < old_length) {
				enl.ex = sc2.interX;
				enl.ey = sc2.interY;
			}
		}
		if (sc3.flag) {
			float old_length = (enl.ex - stl.sx)*(enl.ex - enl.sx) + (enl.ey - enl.sy)*(enl.ey - enl.sy);
			float new_length = (sc3.interX - enl.sx)*(sc3.interX - enl.sx) + (sc3.interY - enl.sy)*(sc3.interY - enl.sy);
			if (new_length < old_length) {
				enl.ex = sc3.interX;
				enl.ey = sc3.interY;
			}
		}

		int index = Stage_GetNumberOfBlock(bl_collisionBox);
		for (int i = 0; i < index; i++)
		{
			M_collsionBOX* mbox = Stage_collisionBOX_Get(i);
			float bx = mbox->GetColl().x;
			float by = mbox->GetColl().y;
			float bw = mbox->GetColl().w;
			float bh = mbox->GetColl().h;
			CollisionLine boxline[4];

			boxline[0] = { bx,by + bh,bx + bw,by + bh };
		    boxline[1] = { bx,by,bx,by + bh };
			boxline[2] = { bx,by,bx + bw,by };
			boxline[3] = { bx + bw,by,bx + bw,by + bh };
			
			Cross_imf cs0 = Collision_LineAndLineHit(stl, boxline[(0 + angNum)%4]);
			Cross_imf cs1 = Collision_LineAndLineHit(stl, boxline[(1 + angNum) % 4]);
			Cross_imf cs2 = Collision_LineAndLineHit(enl, boxline[(2 + angNum) % 4]);
			Cross_imf cs3 = Collision_LineAndLineHit(enl, boxline[(3 + angNum) % 4]);
			if (cs0.flag) {
				float old_length = (stl.ex - stl.sx)*(stl.ex - stl.sx) + (stl.ey - stl.sy)*(stl.ey - stl.sy);
				float new_length = (cs0.interX - stl.sx)*(cs0.interX - stl.sx) + (cs0.interY - stl.sy)*(cs0.interY - stl.sy);
				if (new_length < old_length) {
					stl.ex = cs0.interX;
					stl.ey = cs0.interY;
				}
			}
			if (cs1.flag) {
				float old_length = (stl.ex - stl.sx)*(stl.ex - stl.sx) + (stl.ey - stl.sy)*(stl.ey - stl.sy);
				float new_length = (cs1.interX - stl.sx)*(cs1.interX - stl.sx) + (cs1.interY - stl.sy)*(cs1.interY - stl.sy);
				if (new_length < old_length) {
					stl.ex = cs1.interX;
					stl.ey = cs1.interY;
				}
			}

			if (cs2.flag) {
				float old_length = (enl.ex - enl.sx)*(enl.ex - enl.sx) + (enl.ey - enl.sy)*(enl.ey - enl.sy);
				float new_length = (cs2.interX - enl.sx)*(cs2.interX - enl.sx) + (cs2.interY - enl.sy)*(cs2.interY - enl.sy);
				if (new_length < old_length) {
					enl.ex = cs2.interX;
					enl.ey = cs2.interY;
				}
			}
			if (cs3.flag) {
				float old_length = (enl.ex - enl.sx)*(enl.ex - enl.sx) + (enl.ey - enl.sy)*(enl.ey - enl.sy);
				float new_length = (cs3.interX - enl.sx)*(cs3.interX - enl.sx) + (cs3.interY - enl.sy)*(cs3.interY - enl.sy);
				if (new_length < old_length) {
					enl.ex = cs3.interX;
					enl.ey = cs3.interY;
				}
			}
		}

		CollisionLine cLine1 = { posX, posY ,stl.ex, stl.ey };
		CollisionLine cLine2 = { posX, posY ,enl.ex, enl.ey };
		int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
		for (int i = 0; i < DiCount; i++)
		{
			M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
			if (dib != NULL) {
				LineStraightC* hill = dib->GetDiaLine();

				//CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w + 2,coll.y + coll.h };
				CollisionLine hillline = hill->GetLine();
				Cross_imf cr = Collision_LineAndLineHit(cLine1, hillline);
				if (cr.flag) {
					stl.ex = cr.interX;
					stl.ey = cr.interY;
				}
				Cross_imf cr1 = Collision_LineAndLineHit(cLine2, hillline);
				if (cr1.flag) {
					enl.ex = cr1.interX;
					enl.ey = cr1.interY;
				}
			}
		}


		startPosX = stl.ex - LIMIT_LENGTH * cosf(angle[angNum]) * 1.5f;
		startPosY = stl.ey - LIMIT_LENGTH * sinf(angle[angNum]) * 1.5f;
		endPosX = enl.ex + LIMIT_LENGTH * cosf(angle[angNum]) * 1.5f;
		endPosY = enl.ey + LIMIT_LENGTH * sinf(angle[angNum]) * 1.5f;

		startPoint->SetPosition(startPosX, startPosY);
		startPoint->SetAngle(angle[(angNum + 2) % 4] + PI/4);
		endPoint->SetPosition(endPosX, endPosY);
//*********************************************************************

//**************************************************************************************
	
		AllInput();
		StrongLineCheck();


		if (keylogger_Trigger(KL_U)&&GetKey_LineDir()) {
			angNum++;
			if (angNum >= 4) angNum = 0;
			if (angNum % 2 == 0) {
				currentltp = l_oright;
			}
			if(angNum%2==1) {
				currentltp = l_oleft;
			}
			//if(angle)
		}

		if (keylogger_Trigger(KL_ENTER)&&fairy->name == VERTICA&&GetKey_LineCreatV()) {
			if (FL == fl_defalt) {
				Line_CreateLineV(fairy->fairyID, startPoint->GetPosX(), startPoint->GetPosY(), endPoint->GetPosX(), endPoint->GetPosY());
			}
			if (FL == fl_strong) {
				if (ClearLineNum != LINENULL) {
					Line_BecomeStrongLineMap(ClearLineNum);
					Line_CreateLineStrongV(fairy->fairyID, startPosXtemp, startPosYtemp, endPosXtemp, endPosYtemp, ClearLineNum);
				}
				else {
					Line_CreateLineV(fairy->fairyID, startPosXtemp, startPosYtemp, endPosXtemp, endPosYtemp, fl_strong);
				}			
			}
			stateMachine->StateTrans(fs_lineBecome);
		}
		if (keylogger_Trigger(KL_SPACE) && fairy->name == HORIZY&&GetKey_LineCreatH()) {
			if (FL == fl_defalt) {
				Line_CreateLineH(fairy->fairyID, startPoint->GetPosX(), startPoint->GetPosY(), endPoint->GetPosX(), endPoint->GetPosY());
			}
			if (FL == fl_strong) {
				if (ClearLineNum != LINENULL) {
					Line_BecomeStrongLineMap(ClearLineNum);
					Line_CreateLineStrongH(fairy->fairyID, startPosXtemp, startPosYtemp, endPosXtemp, endPosYtemp, ClearLineNum);
				}
				else {
					Line_CreateLineH(fairy->fairyID, startPosXtemp, startPosYtemp, endPosXtemp, endPosYtemp, fl_strong);
				}
				
			}
			stateMachine->StateTrans(fs_lineBecome);
		}

		fairy->posX = posX;
		fairy->posY = posY;
		fairy->sprite->SetPosition(posX, posY);
	}

	
	timeCount++;
	endPoint->SetAngle(timeCount*0.05f);
	fairyCountDownTime++;
	if (fairyCountDownTime >= fairyDruationTime) {
		fairyCountDownTime = fairyDruationTime;
	}

	if (FL == fl_defalt) {
		fairy->sprite->SetColor(255, 255, 255);
		endPoint->SetColor(255, 255, 255);
		startPoint->SetColor(255, 255, 255);
	}
	else
	{		
		fairy->sprite->SetColor(255, 0, 0);
		endPoint->SetColor(255, 0, 0);
		startPoint->SetColor(255, 0, 0);
	}

	if (Player_GetState() == ps_default) {
		stateMachine->StateTrans(fs_stand);
	}

	FL = fl_defalt;
	ClearLineNum = LINENULL;
}

void Fs_OblMoving::Final()
{
	startPoint->SetActive(false);
	endPoint->SetActive(false);
	fairyCountDownTime = 0;
	targetCusour->SetActive(false);
}

void Fs_OblMoving::AllInput()
{
	float tpx = posX;
	float tpy = posY;
	if (keylogger_Press(KL_A)) {
		float tx = tpx;
		float ty = tpy;
		tx -= 15.0f;
		MoveInFairyLine(l_lvert, tx, ty);
	}
	if (keylogger_Press(KL_D)) {
		float tx = tpx;
		float ty = tpy;
		tx += 15.0f;
		MoveInFairyLine(l_lvert,tx,ty);
	}
	if (keylogger_Press(KL_W)) {
		float tx = tpx;
		float ty = tpy;
		ty -= 15.0f;
		MoveInFairyLine(l_lhory, tx, ty);
	}
	if (keylogger_Press(KL_S)) {
		float tx = tpx;
		float ty = tpy;
		ty += 15.0f;
		MoveInFairyLine(l_lhory, tx, ty);
	}
	//左上
	if (keylogger_Press(KL_A) && keylogger_Press(KL_W)) {
		float tx = tpx;
		float ty = tpy;
		ty -= 10.0f;
		tx -= 10.0f;
		MoveInFairyLine(l_oleft, tx, ty);
	}
	//右上
	if (keylogger_Press(KL_W) && keylogger_Press(KL_D)) {
		float tx = tpx;
		float ty = tpy;
		ty -= 10.0f;
		tx += 10.0f;
		MoveInFairyLine(l_oright, tx, ty);
	}
	//右下
	if (keylogger_Press(KL_D) && keylogger_Press(KL_S)) {
		float tx = tpx;
		float ty = tpy;
		ty += 10.0f;
		tx += 10.0f;
		MoveInFairyLine(l_oleft, tx, ty);
	}
	//左下
	if (keylogger_Press(KL_S) && keylogger_Press(KL_A)) {
		float tx = tpx;
		float ty = tpy;
		ty += 10.0f;
		tx -= 10.0f;
		MoveInFairyLine(l_oright, tx, ty);
	}
}

void Fs_OblMoving::MoveInFairyLine(ltp tp,float tx,float ty)
{
	CollisionLine hl;	
	
	switch (tp)
	{
	case l_lhory:
		hl = { tx - 30,ty,tx + 30,ty };
		break;
	case l_lvert:
		hl = { tx,ty - 30,tx,ty + 30 };
		break;
	case l_oleft:
		hl = { tx + 20,ty - 20,tx - 20,ty + 20 };
		break;
	case l_oright:
		hl = { tx - 20,ty - 20,tx + 20,ty + 20 };
		break;
	default:
		break;
	}

	//CollisionLine hvL;
	for (int j = 0; j < FMAX; j++)
	{
		if (FairyVH_GetStateV(j) == fs_lineBecome) {

			
				CollisionLine hvL = Line_GetLineV(j);
				ltp vtp = l_lhory;
				if (fabsf(hvL.ex - hvL.sx) <= 0.1f) {
					vtp = l_lhory;
				}
				else if (fabsf(hvL.ey - hvL.ex) <= 0.1f) {
					vtp = l_lvert;
				}
				else if ((hvL.ey - hvL.sy) / (hvL.ex - hvL.sx) > 0) {
					vtp = l_oleft;
				}
				else {
					vtp = l_oright;
				}

				if (tp == vtp) {
					Cross_imf cH2 = Collision_LineAndLineHit(hvL, hl);
					if (cH2.flag) {
						posY = cH2.interY;
						posX = cH2.interX;
					}
				}
			


		}
		if (FairyVH_GetStateH(j) == fs_lineBecome) {


			CollisionLine hvL = Line_GetLineH(j);
			ltp vtp = l_lhory;
			if (fabsf(hvL.ex - hvL.sx) <= 0.1f) {
				vtp = l_lhory;
			}
			else if (fabsf(hvL.ey - hvL.sy) <= 0.1f) {
				vtp = l_lvert;
			}
			else if ((hvL.ey - hvL.sy) / (hvL.ex - hvL.sx) > 0) {
				vtp = l_oleft;
			}
			else {
				vtp = l_oright;
			}

			if (tp == vtp) {
				Cross_imf cH2 = Collision_LineAndLineHit(hvL, hl);
				if (cH2.flag) {
					posY = cH2.interY;
					posX = cH2.interX;
				}
			}
			
		}
	}
	

	for (int i = 0; i < LINEMAX; i++)
	{
		CollisionLine cl = Line_GetLine(i);
		ltp vtp = l_lhory;
		if (fabsf(cl.ex - cl.sx) <= 0.1f) {
			vtp = l_lhory;
		}
		else if (fabsf(cl.ey - cl.sy) <= 0.1f) {
			vtp = l_lvert;
		}
		else if ((cl.ey - cl.sy) / (cl.ex - cl.sx) > 0) {
			vtp = l_oleft;
		}
		else {
			vtp = l_oright;
		}
		if (tp == vtp) {
			Cross_imf cH = Collision_LineAndLineHit(cl, hl);
			if (cH.flag) {

				posY = cH.interY;
				posX = cH.interX;
			}
		}
		//Cross_imf cV = Collision_LineAndLineHit(cl, vl);
		
	}
}

void Fs_OblMoving::StrongLineCheck()
{
	startPosXtemp = startPosX;
	startPosYtemp = startPosY;
	endPosXtemp = endPosX;
	endPosYtemp = endPosY;
	
	CollisionLine cline = { startPoint->GetPosX(),startPoint->GetPosY(),endPoint->GetPosX(),endPoint->GetPosY() };

	int hCount = Heart_GetHeartCount();
	for (int i = 0; i <= hCount; i++)
	{
		Heart* ht = Heart_GetHeart(i);
		if (ht != NULL) {
			CollisionCircle cc;
			cc.center = { ht->sp->GetPosX(),ht->sp->GetPosY() };
			cc.radius = LIMIT_FAIRY * 0.5f;
			if (Collision_LineAndCircleHit(cline, cc)) {
				FL = fl_strong;
				CollisionLine cn = { cc.center.x - LIMIT_FAIRY,cc.center.y,cc.center.x + LIMIT_FAIRY,cc.center.y };
				Cross_imf cif = Collision_LineAndLineHit(cn, cline);
				if (cif.flag) {
					float offx = cc.center.x - cif.interX;
					//float offy = cc.center.y - cif.interY;
					startPosXtemp = startPosX + offx;
					//startPosYtemp = startPosY - offy;
					endPosXtemp = endPosX + offx;
					//endPosYtemp = endPosY - offy;
				}
			}
		}
	}

	for (int i = 0; i < LINEMAX + FMAX * 2; i++)
	{
		LINE* li = Line_GetLineForNumberAllMAP(i);
		if (li != NULL&&li->Num!= fairy->fairyID) {
			if (li->lintType == currentltp) {
				CollisionLine cl = { li->startPos.x,li->startPos.y,li->endPos.x,li->endPos.y };
				//bool b = Collision_LineAndLineDistance(cline, cl, LIMIT_LENGTH * 0.5f);
				if (Collision_LineAndLineDistance(cline, cl, LIMIT_FAIRY*0.5f)) {
					ClearLineNum = i;
					FL = fl_strong;
				}
			}
		}
	}
}
