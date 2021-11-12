#ifndef MAPCOLLISION_H
#define MAPCOLLISION_H
#include "collision.h"
//BoxLUPosX,BoxLUPosX,目標物今の当たり判定ボックスの左上座標。
//oldBoxPosX,oldBoxPosY,目標物１フレーム前当たり判定ボックス左上の座標。
//cr        目標物の当たり判定ボックス。
//戻り値　0 (空中)　１（地面のみと当たり）　２（壁のみと当たり）　３（地面と壁を同時に当たり）
int CollsiionWithMap(float* boxLUPosX, float* boxLUposY, float oldBoxPosX, float oldBoxPosY, CollisionRectangle crt);

#endif // !MAPCOLLISION_H

