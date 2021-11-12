#ifndef BASE_SPRITE_H
#define BASE_SPRITE_H
#include <d3dx9.h>
#include"base_Camera.h"
#include"texture.h"
#include "sprite.h"
#include "Math.h"



enum SPRITETYPE {
	SPRITE_OBJ,
	SPRITE_UI,
	SPRITE_POLYGON,
	SPRITE_PARTIAL,
	SPRITE_ALPHABLEND,
	SPRITE_PARTICLE,
};

class SpData {
public:
	SpData();
	virtual ~SpData();
public:
	float posX;                        //�|���S�����WX
	float posY;                        //�|���S�����WY

//���̕�����
protected:
	float width;                         //�|���S������
	float height;					       //�|���S���c��
	float2D HVratio;

	float texture_width;                 //�e�N�X�`������
	float texture_height;				 //�e�N�X�`���c��
	float texture_cutX;                  //�e�N�X�`���؂�����WX
	float texture_cutY;                  //�e�N�X�`���؂�����WY
	float texture_cutW;                  //�e�N�X�`���؂��艡��
	float texture_cutH;                  //�e�N�X�`���؂���c��

	float angle;                       //��]�p�x
	D3DCOLOR color;                     //r,g,b,a;
	int4D colorData;

	float2D scale;			           //�|���S���̃T�C�Y�ϊ�
	float2D multiple;                  //���W�ϊ����A�̕ϊ��{���B
	float cameraOffsetX;               //multiple.x��1�ł͂Ȃ��ꍇ�A���W�v�Z�p�B
	float cameraOffsetY;               //multiple.y��1�ł͂Ȃ��ꍇ�A���W�v�Z�p�B


	int2D textureDirection;            //�e�N�X�`���v�����g����
	int2D textureRegionNumber;         //�e�N�X�`�����ԍ�
	int2D textureRegionTotal;		   //�e�N�X�`����搔

	ANCHORPOINT anchorPoint;           //�A���J�[�|�C���g
	float anchorX;                     //�X�v���C�g�̃A���J�[�|�C���g�ƍ���̋���x
	float anchorY;                     //�X�v���C�g�̃A���J�[�|�C���g�ƍ���̋���y

	bool active;                       //�A�N�e�B�u��ԃt���O

public:
	//�|�W�V������ݒ�
 	virtual void SetPosition(float x, float y) { posX = x; posY = y; }
	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }

	//�A�N�e�B�u��Ԑݒ�
	void SetActive(bool actf) { active = actf; }
	//�A�N�e�B�u��Ԃ��擾�B
	bool GetActive() { return active; }

	//��]�p�x��ݒ�
	void SetAngle(float ang) { angle = ang; }

	//�����x��ݒ�
	void SetAlpha(float al);

	//�X�v���C�g�̊g��A�k���{�����w��
	void SetScale(float scaleX, float scaleY);
	float2D GetScale() { return { scale.x,scale.y }; }

	void SetAnchorPoint(ANCHORPOINT aPoint);

	//�e�N�X�`���̓\������A-1 or 1 ���w�肵�Ă��������B�ix,������.���A�c�����j
	void SetSprteDirection(int x, int y) { textureDirection.x = x; textureDirection.y = y; }

	//�F�ς�
	void SetColor(int cR, int cG, int cB);
	void SetColor(D3DCOLOR d3dcolor);

	//�X�v���C�g�̒����ƍ������w��,setCutSize()�ƈႤ�A
	void SetWidth(float x);
	void SetHeight(float y);
	void SetSpriteSize(float x, float y);

	//�X�v���C�g�̒����ƍ������l��
	float GetWidth() { return width * scale.x; }
	float GetHeight() { return height * scale.y; }

	//�e�N�X�`���\��������擾�B
	int GetDirX() { return textureDirection.x; }
	int GetDirY() { return textureDirection.y; }

	//�����x���擾�B
	float GetAlpha() { return ((float)colorData.a) / 255.0f; }

	float GetAngle() const { return angle; }

	//���W���擾�B
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }

	void SetTextureSize(float x, float y);

	ANCHORPOINT GetAnchorPoint() { return anchorPoint; }

	D3DCOLOR GetD3DColor() { return color; }

	float2D GetLUpos() { return { posX - anchorX * scale.x,posY - anchorY * scale.y }; }
	float2D GetLDpos() { return { posX - anchorX * scale.x,posY - anchorY * scale.y + GetHeight() }; }
	float2D GetRUpos() { return { posX - anchorX * scale.x + GetWidth(),posY - anchorY * scale.y }; }
	float2D GetRDpos() { return { posX - anchorX * scale.x + GetWidth(), posY - anchorY * scale.y + GetHeight() }; }
	float2D GetLUUV();
	float2D GetLDUV();
	float2D GetRUUV();
	float2D GetRDUV();
};

class SpriteC :public SpData{
public:
	SpriteC() {};
	SpriteC(const char* pFilename, const char* Name,int Layer = 9,SPRITETYPE sptype = SPRITE_OBJ);
	SpriteC(const char* pFilename, int Layer = 9, SPRITETYPE sptype = SPRITE_OBJ);
	virtual ~SpriteC();
	void SpriteCparameteSet(const char* pFilename, const char* Name, int Layer = 9, SPRITETYPE sptype = SPRITE_OBJ);
public:
	//float posX;                        //�|���S�����WX
	//float posY;                        //�|���S�����WY

//���̕�����
protected:
	//float width;                         //�|���S������
	//float height;					       //�|���S���c��
	//float2D HVratio;
	//
	//float texture_width;                 //�e�N�X�`������
	//float texture_height;				 //�e�N�X�`���c��
	//float texture_cutX;                  //�e�N�X�`���؂�����WX
	//float texture_cutY;                  //�e�N�X�`���؂�����WY
	//float texture_cutW;                  //�e�N�X�`���؂��艡��
	//float texture_cutH;                  //�e�N�X�`���؂���c��

	//float angle;                       //��]�p�x
	//D3DCOLOR color;                     //r,g,b,a;
	//int4D colorData;
	//
	//float2D scale;			           //�|���S���̃T�C�Y�ϊ�
	//float2D multiple;                  //���W�ϊ����A�̕ϊ��{���B
	//float cameraOffsetX;               //multiple.x��1�ł͂Ȃ��ꍇ�A���W�v�Z�p�B
	//float cameraOffsetY;               //multiple.y��1�ł͂Ȃ��ꍇ�A���W�v�Z�p�B


	//int2D textureDirection;            //�e�N�X�`���v�����g����
	//int2D textureRegionNumber;         //�e�N�X�`�����ԍ�
	//int2D textureRegionTotal;		   //�e�N�X�`����搔

	//ANCHORPOINT anchorPoint;           //�A���J�[�|�C���g
	//float anchorX;                     //�X�v���C�g�̃A���J�[�|�C���g�ƍ���̋���x
	//float anchorY;                     //�X�v���C�g�̃A���J�[�|�C���g�ƍ���̋���y

	char name[64];
	
	int textureID;                     //texture�Ǘ�ID
	int layer;					       //���C���[
	int arrayID;                       //sprite�Ǘ�ID

	SPRITETYPE spriteType;             //�X�v���C�g�̃^�C�v
	//bool deleteFlag;

public:
	void Init();
	//void Update();
	virtual void Draw(CameraC* ca);
	//void Final();

	//�X�v���C�g�̃^�C�v�w��
	void SetSpriteType(SPRITETYPE sptype) { spriteType = sptype; }
	//�J�����ɑ��ΓI���W�ϊ��{���ݒ�
	void SetMultiple(float x, float y);
	//�X�v���C�g�̃J�[�g�T�C�Y�w��A�i�X�v���C�g�T�C�Y�ƃe�N�X�`���̕`��͈͂𓯎��ɐݒ�j�e�N�X�`����UV���W�ƍ��킹�Ă��������B
	void SetCutSize(int size_w, int size_h);
	
	//�e�N�X�`���̕`��͈͂��w��i�J�[�g�T�C�Y��P�ʂƂ��āA�P���Ŏw��j
	void SetRegion(int x, int y);
	
	//���C���[�ύX
	void SetLayerChange(int laye);
	
	//�e�N�X�`���Ǘ��ԍ����擾�B
	int GetID() { return textureID; }
	//�X�v���C�g�Ǘ��ԍ����擾�B
	int GetArrayID() { return arrayID; }
	//���C���[���l��
	int GetLayer() { return layer; }
	//�e�N�X�`����搔���擾�B
	int GetRegionTotalX() { return textureRegionTotal.x; }
	int GetRegionTotalY() { return textureRegionTotal.y; }
	
	
	//multiple(���W���Z�䗦�j���P�ł͂Ȃ��ꍇ�A���Z��̍��W���擾�B
	float GetCameraOffsetPosX() { return posX + cameraOffsetX; }
	float GetCameraOffsetPosY() { return posY + cameraOffsetY; }
	
	const char* GetName() { return name; }
	
	Vector2 GetPosition() const { return Vector2(posX, posY); }
	void SetPosition(float x, float y)override;
	void SetPosition(const Vector2& position) { posX = position.x, posY = position.y; }
};

//UI�X�v���C�g�A�J�����ɑ��ΓI�Î~�Ȃ̂ŁA�J�����̍���͍��W�i0,0�j
class SpriteUI :public SpriteC {
public:
	SpriteUI(const char* pFilename, const char* Name, int Layer = 15, SPRITETYPE sptype = SPRITE_UI) : SpriteC(pFilename, Name, Layer, sptype) { lens = 1; }
	SpriteUI(const char* pFilename, int Layer = 15, SPRITETYPE sptype = SPRITE_UI) :SpriteC(pFilename, Layer, sptype) { lens = 1; };
	~SpriteUI();

public:
	void Draw(CameraC* ca) override;
	//UI���X�e�[�W��̍��W���擾�iGetPosX()��GetPosY���J�����̍���ɑ��ΓI���W���擾�Ȃ̂ŁAUI�ƃX�e�[�W���̕��Ɠ����蔻��ɂ������Ȃ�A���̊֐����g���āj
	float GetCameraOffsetWidth() { return width * scale.x * lens; }    //�J�������Q�Ƃ��āA���΍��W���擾�B
	float GetCameraOffsetHeight() { return height * scale.y * lens; }
private:
	//�J�����Ɖ�ʂ̋���
	float lens;    
};

//���p�`�X�v���C�g�A�f�t�H���g�͋�`, 
class SpritePL :public SpriteC {
public:
	SpritePL(const char* pFilename,const char* Name,int Layer = 9,SPRITETYPE sp = SPRITE_POLYGON):SpriteC(pFilename,Name,Layer,sp){	}
	SpritePL(const char* pFilename,int Layer = 9,SPRITETYPE sp = SPRITE_POLYGON):SpriteC(pFilename,Layer,sp){}
	~SpritePL();

public:
	void InitPL();
	void Draw(CameraC* ca)override;

	//���p�`�̒��_���w��B
	void SetPolygonPoint(float2D* vList,int Count);
private:
	//���_
	Vertex2D* v2dList;
	//���_�ƃe�N�X�`���ʒu�֌W
	float2D* pvl;
	//���_��
	int verCount;

	//���p�`�̒��_�`�撲��
	void DrawPolygon(float pX, float pY, float w, float h, float tc_posX, float tc_posY, float tcW, float tcH);
};


//�����`��X�v���C�g
class SpritePA :public SpriteC {
public:
	SpritePA(const char* pFilename, const char* Name, int Layer = 9, SPRITETYPE sp = SPRITE_PARTIAL) :SpriteC(pFilename, Name, Layer, sp) {
		partialX = partialY = 0.0f;
		partialW = partialH = 1.0f;
		pAnchorPoint = ANCHOR_LU;
	}
	SpritePA(const char* pFilename, int Layer = 9, SPRITETYPE sp = SPRITE_PARTIAL) :SpriteC(pFilename, Layer, sp) {
		partialX = partialY = 0.0f;
		partialW = partialH = 1.0f;
		pAnchorPoint = ANCHOR_LU;
	}
	~SpritePA();

public:
	//�`�敔���̔䗦�����w��
	void SetPartialWidth(float w);
	//�`�敔���̔䗦�̏c�����w��
	void SetPartialHeight(float h);
	//�`��䗦�ݒ�Q�l�|�C���g
	void SetPartialAnchorPoint(ANCHORPOINT ap);

	void Draw(CameraC* ca)override;
private:
	float partialX;
	float partialY;
	float partialW;
	float partialH;
	ANCHORPOINT pAnchorPoint;
	//�`�敔���Čv�Z�B
	//void ParitalPosReSet(float x, float y);
};

//�A���t�@�u�����h�����ł���X�v���C�g
class SpriteAB :public SpriteC {
public:
	SpriteAB(const char* pFilename, const char* Name, int Layer = 14, SPRITETYPE sp = SPRITE_ALPHABLEND) :SpriteC(pFilename,Name, Layer, sp) {

	}
	SpriteAB(const char* pFilename, int Layer = 14, SPRITETYPE sp = SPRITE_ALPHABLEND) :SpriteC(pFilename, Layer, sp) {

	}
	~SpriteAB();

	enum 
	{
		dest_one,
	};

	void SetAlphaBlendDest(int blendType);
	void SetAlphaBlendSrc(int blendType);
public:
	void Draw(CameraC* ca)override;
	int destType;
	int srcType;
	
};


class ParticleC {
public:
	ParticleC(const char* pFilename, int Count, int Layer = 14);
	~ParticleC();
public:
	float posX;
	float posY;
public:
	void Init();

	SpData* GetPdata(int number) { return &pSpData[number]; }
	int GetPcount() { return pCount; }
	int GetLayer() { return layer; }
	void SetActive(bool act) { active = act; }
	bool GetActive() { return active; }
	int GetArrayID() { return arrayID; }
	int GetTextureID() { return textureID; }
	float2D GetPostion() { return { posX, posY }; }

	void SetSpDataAngleAll(float ang);
	void Set_SpData_ScaleAll(float x, float y);
	void SetPostion(float x, float y) { posX = x; posY = y; }
private:
	int pCount;
	SpData* pSpData;
	Vertex2D* pVertex2D;
	int textureID;
	int layer;
	bool active;
	int partID;
	int arrayID;

public:
	void Draw(CameraC * ca);
};

#endif // !BASE_SPRITE_H

