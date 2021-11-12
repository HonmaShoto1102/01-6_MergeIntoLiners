#ifndef BASE_MAPBLOCK_H
#define BASE_MAPBLOCK_H
#include"collision.h"
#include"base_Sprite.h"
#include"base_Animation.h"
#include"typeLine.h"
#include"Line.h"

class M_collsionBOX {
public:
	M_collsionBOX();
	M_collsionBOX(float x,float y,float w,float h);
	~M_collsionBOX() {};

	void LoadData(float x, float y, float w, float h);
	void Init() {};
	virtual CollisionRectangle GetColl();

protected:
	float posX;
	float posY;
	float width;
	float height;
};

class M_textureBOX {
public:
	M_textureBOX();
	M_textureBOX(const char* filename, float x, float y, int layer);
	M_textureBOX(const char* filename, float x, float y,float w,float h, int layer);
	virtual ~M_textureBOX();

	void LoadData(const char* filename, float x, float y,float w, float h, int layer);
	virtual void Init();
	//void Play();
	//void Update();
	virtual CollisionRectangle GetColl();
protected:
	bool Onwh;
	bool isSp;

	SpriteC* sp;
	float posX;
	float posY;
	float width;
	float height;
	int spriteLayer;
	//bool pl;
};
//*******************カメラbox************************************
class M_cameraBox:public M_collsionBOX {
public:
	M_cameraBox(float x, float y, float w, float h) :M_collsionBOX(x, y, w, h) {};
};

//瞬間移動box************************************************************************
class M_heartBox  {
public:
	M_heartBox(const char* filename, float x, float y, float w, float h, int layer);
	~M_heartBox();
	virtual void LoadState(bool b);
	virtual void Init();
	virtual void Update();
	float2D GetPosCn();
	virtual CollisionRectangle GetColl();
	void SetActive(bool b);
	bool GetActive() { return active; }
	void SetHeartActive(bool b);
	void SetAreahActive(bool b);
protected:
	AnimationC* ani;
	SpriteC* sp;
	SpriteC* hsp;
	SpriteC* tsp;
	float posX;
	float posY;
	float width;
	float height;
	bool active;
	
};
//***********************************************************************************
//*******************************仮想box*********************************************
//***********************************************************************************
class M_invisibleBox:public M_collsionBOX {
public:
	M_invisibleBox(float x, float y, float w, float h): M_collsionBOX(x, y, w, h) {};
	~M_invisibleBox();

	float2D GetPrantformPos(float x, float y);
private:
};
//***********************************************************************************
//***************************水晶、ラインが生成できるbox*****************************
//***********************************************************************************
class M_lineCreateBox:public M_textureBOX {
public:
	//M_lineCreateBox();
	M_lineCreateBox(const char* filename, float x, float y, float w, float h, int layer) :M_textureBOX(filename, x, y, w, h, layer) { isTrigger = false; };
	~M_lineCreateBox() {};

	void LoadParameta(float lenX, float lenY);

	void OnTrigger();
	void Update();
	void OffTrigger();
	void SetTimeMax(int time) { timeMax = time; }
	bool GetTrigger() { return isTrigger; }
private:
	//spriteC* sp;
	int timeCount;
	int timeMax;
	bool isTrigger;
	//float posX;
	//float posY;
	//float width;
	//float height;

	float lengthX;
	float lengthY;
};

//***********************************************************************************
//***************************刺、罠、穴box*******************************************
//***********************************************************************************

class M_damegeBox:public M_textureBOX {
public:
	M_damegeBox(const char* filename, float x, float y, float w, float h, int layer, int tp = M_damegeBox::Dabox_Cliff) :M_textureBOX(filename, x, y, w, h, layer) { DaboxType = tp; }
	~M_damegeBox() {};
	enum 
	{
		Dabox_Spines,
		Dabox_Trap,
		Dabox_Cliff,
	};
	int GetType() { return DaboxType; }

private:
	int DaboxType;
};

//***********************************************************************************
//***************************ゴールボックス******************************************
//***********************************************************************************

class M_goalBox : public M_heartBox {
public:
	M_goalBox(const char* filename, float x, float y, float w, float h, int layer) :M_heartBox(filename, x, y, w, h, layer) {};
	~M_goalBox() {};
	virtual void Init();
};

//***********************************************************************************
//***************************移動踏み場ボックス**************************************
//***********************************************************************************

class M_moveBox : public M_textureBOX {

};

class M_stageTransBox : public M_heartBox {
public:
	M_stageTransBox(const char* filename, float x, float y, float w, float h, int layer, int nextStage) :M_heartBox(filename, x, y, w, h, layer) { nextStageName = nextStage; };
	~M_stageTransBox() {};

	int GetNextName() { return nextStageName; }
private:
	int nextStageName;
};

//*************************************************************************
//***************************イベントボックス******************************
//*************************************************************************

class M_eventBox :public M_collsionBOX {
public:
	M_eventBox(const char* eventNumber, float x, float y, float w, float h) :M_collsionBOX(x, y, w, h) { 
		strcpy_s(eventKey, eventNumber);
		trigger = false;
	};
	bool GetTrigger() { return trigger; }
	void OnTrigger() { trigger = true; }
	const char* GetEventKey() { return eventKey; }
private:
	char eventKey[64];
	bool trigger;
};


//*********************************************************************************
//*******************************エネミーボックス**********************************
class M_enemyBox {
public:
	M_enemyBox(const char* eName, float x, float y,const char* dtname = "null");
	virtual void SetEnemyEnable();
	const char* GetName() {
		return name;
	}
	const char* GetDirTypeName() {
		return dirTypename;
	}
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
private:
	bool eEnable;
	char name[32];
	char dirTypename[32];
	float posX;
	float posY;

};

class M_diagonalCollisionBox {
public:
	M_diagonalCollisionBox(float x, float y, float w, float h,int Dir);
	~M_diagonalCollisionBox();
	void Init() {};
	enum 
	{
		ld_ru,
		lu_rd,
	};

	LineStraightC* GetDiaLine() {
		return diaLine;
	}
	//CollisionLine GetDiaLine
private:
	LineStraightC* diaLine;
	int m_dir;
};

class M_enemy2Box:public M_enemyBox {
public:
	M_enemy2Box(const char* eName, float x, float y,int id, const char* dtname = "null") :M_enemyBox(eName, x, y, dtname) {
		hidden_heartBoxID = id;
	};
	~M_enemy2Box() {};
	//void LoadParameta(const char* loadName, float x, float y, float w, float h, int layer);

	int GetHeartBoxID() { return hidden_heartBoxID; }
private:
	int hidden_heartBoxID;
};


class M_startBox :public M_collsionBOX {
public:
	M_startBox(float x, float y, float w, float h) :M_collsionBOX(x, y, w, h) {}

};


class M_mirorrBox {
public:
	M_mirorrBox(const char* filename, float x, float y, float w, float h, int mir);
	~M_mirorrBox();
	enum 
	{
		mirorr_ON,
		mirorr_OFF,
	};

	void Init();
	void Update();
	void Final();
	void Set_ON_OFF(int onAoff);
	void SetMirorrRotate();
	CollisionRectangle GetColl();
	int LineReflex(LINE* line);
	int GetMirType() { return mirType; }
private:
	float2D pos;
	float2D lspos;
	float2D size;
	int mirType;
	SpriteC* msp[2];
	int Current;
	int Dir;
	int LineNumber;
	int rLineNumber;
	CollisionLine mirorrLine[2];
	SpriteC* aniSp;
	AnimationC* ani;
	int AtimeCount;
	int timeCount;
	D3DXCOLOR mColor[9];
	D3DXCOLOR mirColor;
	D3DXCOLOR oldColor;
	int currentColor;
private:
	void changeColor(D3DXCOLOR color);
};


#endif // !BASE_MAPBLOCK_H

