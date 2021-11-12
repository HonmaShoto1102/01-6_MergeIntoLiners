#include "MapCollision.h"
#include "Stage.h"

int CollsiionWithMap(float* boxLUPosX, float* boxLUposY, float oldBoxPosX, float oldBoxPosY, CollisionRectangle crt)
{
	int RetureType = 0;
	int RetureType2 = 0;

	CollisionRectangle coll = crt;
	CollisionRectangle oldC = { oldBoxPosX,oldBoxPosY,crt.w,crt.h};


	//マップとの当たり判定
	int boxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < boxCount; i++)
	{
		M_collsionBOX* cbox = Stage_collisionBOX_hit(&coll, i);
		if (cbox == NULL) continue;
		if (oldC.y + oldC.h <= cbox->GetColl().y) {
			crt.y = cbox->GetColl().y - crt.h - 1;
			//LastMapBox = cbox->GetColl();
			RetureType = 1;
			continue;
		}

		if (oldC.y >= cbox->GetColl().y + cbox->GetColl().h) {
			crt.y = cbox->GetColl().y + cbox->GetColl().h + crt.h;
			//speed_H = 0;
			RetureType = 1;
			continue;
		}

		if (oldC.x + oldC.w <= cbox->GetColl().x) {
			crt.x = cbox->GetColl().x - crt.w - 1;
			RetureType2 = 1;
			continue;
		}

		if (oldC.x >= cbox->GetColl().x + cbox->GetColl().w) {
			crt.x = cbox->GetColl().x + cbox->GetColl().w + crt.w + 1;
			RetureType2 = 1;
			continue;
		}
	}


	/*int StCount = Stage_GetNumberOfBlock(bl_stageTransBox);
	for (int i = 0; i < StCount; i++)
	{
		M_stageTransBox* stb = Stage_transBox_hit(&oldC, i);
		if (stb != NULL) {
			MapManager_StageTrans(stb->GetNextName());
		}
	}*/

	coll = crt;
	//斜めの地面との当たり判定*******************************************
	int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
	for (int i = 0; i < DiCount; i++)
	{
		M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
		if (dib != NULL) {
			LineStraightC* hill = dib->GetDiaLine();

			CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w + 2,coll.y + coll.h };
			CollisionLine hillline = hill->GetLine();
			Cross_imf cr = Collision_LineAndLineHit(botl, hillline);
			if (cr.flag) {
				float Y1, Y2;
				hill->GetY_formX(&Y1, botl.sx);
				hill->GetY_formX(&Y2, botl.ex);
				float minSEy = min(hillline.sy, hillline.ey);
				float maxSEy = max(hillline.sy, hillline.ey);
				if (Y1 > maxSEy) {
					Y1 = maxSEy;
				}
				if (Y2 < minSEy) {
					Y2 = minSEy;
				}

				float offY1 = botl.sy - Y1;
				float offY2 = botl.ey - Y2;
				float MaxY = max(offY1, offY2);
				crt.y -= MaxY;
				//speed_H = 0;
				//if (movingF == false && collisionSt == ps_default) {                  //移動ボタン押さないと待機状態
				//	PlayerAction_SetAction(ani_standby);
				//}
				RetureType = 1;
			}
		}
	}

	
	*boxLUPosX = crt.x;
	*boxLUposY = crt.y;


	if (RetureType == 0 && RetureType2 == 0)return 0;
	if (RetureType == 1 && RetureType2 == 0)return 1;
	if (RetureType == 0 && RetureType2 == 1)return 2;
	if (RetureType == 1 && RetureType2 == 1)return 3;
	return 0;
}
