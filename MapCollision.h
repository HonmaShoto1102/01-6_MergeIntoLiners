#ifndef MAPCOLLISION_H
#define MAPCOLLISION_H
#include "collision.h"
//BoxLUPosX,BoxLUPosX,�ڕW�����̓����蔻��{�b�N�X�̍�����W�B
//oldBoxPosX,oldBoxPosY,�ڕW���P�t���[���O�����蔻��{�b�N�X����̍��W�B
//cr        �ڕW���̓����蔻��{�b�N�X�B
//�߂�l�@0 (��)�@�P�i�n�ʂ݂̂Ɠ�����j�@�Q�i�ǂ݂̂Ɠ�����j�@�R�i�n�ʂƕǂ𓯎��ɓ�����j
int CollsiionWithMap(float* boxLUPosX, float* boxLUposY, float oldBoxPosX, float oldBoxPosY, CollisionRectangle crt);

#endif // !MAPCOLLISION_H

