#include "base_Sprite.h"
#include <iostream>
//#include "sprite.h"
#include "texture.h"
#include "GM.h"
#include "myDirect3D.h"


SpriteC::SpriteC(const char * pFilename, const char * Name, int Layer, SPRITETYPE sptype)
{
	textureID = Texture_SetTextureLoadFile(pFilename);
	strcpy_s(name, Name);
	layer = Layer;
	multiple.x = 1.0f;
	multiple.y = 1.0f;
	active = true;
	spriteType = sptype;
	arrayID = GM_AddSprite(this);
}

SpriteC::SpriteC(const char * pFilename, int Layer, SPRITETYPE sptype)
{
	const char* Name = "defname";
	textureID = Texture_SetTextureLoadFile(pFilename);
	strcpy_s(name, Name);
	layer = Layer;
	multiple.x = 1.0f;
	multiple.y = 1.0f;
	active = true;
	spriteType = sptype;
	arrayID = GM_AddSprite(this);
}

SpriteC::~SpriteC()
{
	//if (deleteFlag)return;
	int b = GM_UnAddSprite(arrayID);
	if(b==0)Texture_Release(&textureID, 1);
	//deleteFlag = true;
}

void SpriteC::SpriteCparameteSet(const char * pFilename, const char * Name, int Layer, SPRITETYPE sptype)
{
	textureID = Texture_SetTextureLoadFile(pFilename);
	strcpy_s(name, Name);
	layer = Layer;
	multiple.x = 1.0f;
	multiple.y = 1.0f;
	active = true;
	spriteType = sptype;
	arrayID = GM_AddSprite(this);
}

void SpriteC::Init()
{
	texture_width = (float)Texture_GetTextureWidth(textureID);
	texture_height =(float)Texture_GetTextureHeight(textureID);
	width = texture_cutW = texture_width;
	height = texture_cutH = texture_height;
}

void SpriteC::Draw(CameraC* ca)
{
	float lens = ca->GetLensDistance();   

	float C_posX = ca->GetOffsetPosX();
	float C_posY = ca->GetOffsetPosY();

	cameraOffsetX = (1 - multiple.x) * (ca->GetPosX()-posX);
	cameraOffsetY = (1 - multiple.y) * (ca->GetPosY()-posY);
	
	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);

	float pX = (posX - anchorX * scale.x - C_posX + cameraOffsetX)/lens;
	float pY = (posY - anchorY * scale.y - C_posY + cameraOffsetY)/lens;

	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;

	SpriteDrawBuffer(textureID, pX, pY, width * scale.x /lens, height*scale.y /lens, Tc_posX, Tc_posY, tcW, tcH, texture_width, texture_height, angle, { 1,1 }, color,anchorPoint);
}



void SpriteC::SetMultiple(float x, float y)
{
	multiple.x = x;
	multiple.y = y;
}

void SpriteC::SetCutSize(int size_w, int size_h)
{
	width = (float)size_w * HVratio.x;
	height = (float)size_h * HVratio.y;
	texture_cutW =(float) size_w;
	texture_cutH = (float)size_h;
	textureRegionTotal.x = (int)(texture_width / texture_cutW);
	textureRegionTotal.y = (int)(texture_height / texture_cutH);
	SetAnchorPoint(anchorPoint);
}


void SpriteC::SetRegion(int x, int y)
{
	if (textureRegionTotal.x <= 1)textureRegionTotal.x = 1;
	if (textureRegionTotal.y <= 1)textureRegionTotal.y = 1;
	x = x % textureRegionTotal.x;
	y = y % textureRegionTotal.y;
	texture_cutX = x * texture_cutW;
	texture_cutY = y * texture_cutH;
}


void SpriteC::SetLayerChange(int laye)
{
	if (layer == laye)return;
	GM_UnAddSprite(arrayID);

	layer = laye;
	arrayID = GM_AddSprite(this);
}

void SpriteC::SetPosition(float x, float y)
{
	posX = x;
	posY = y;
}


SpriteUI::~SpriteUI()
{
}

void SpriteUI::Draw(CameraC * ca)
{
	lens = ca->GetLensDistance();

	float C_posX = ca->GetOffsetPosX();
	float C_posY = ca->GetOffsetPosY();

	cameraOffsetX = ca->GetPosX() - C_posX;
	cameraOffsetY = ca->GetPosY() - C_posY;

	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);

	float pX = (posX - anchorX * scale.x);
	float pY = (posY - anchorY * scale.y);

	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;

	SpriteDrawBuffer(textureID, pX, pY, width * scale.x, height*scale.y, Tc_posX, Tc_posY, tcW, tcH, texture_width, texture_height, angle, { 1,1 }, color,anchorPoint);
}

SpritePL::~SpritePL()
{
	delete[] v2dList;

	delete[] pvl;
}

void SpritePL::InitPL()
{
	Init();
	float ul = texture_cutX / texture_width;
	float ur = (texture_cutX + texture_cutW) / texture_width;
	float vt = texture_cutY / texture_height;
	float vb = (texture_cutY + texture_cutH) / texture_height;

	verCount = 4;
	v2dList = new Vertex2D[verCount];
	v2dList[0].Position = D3DXVECTOR4(posX, posY, 1.0f, 1.0f);
	v2dList[1].Position = D3DXVECTOR4(posX + width, posY, 1.0f, 1.0f);
	v2dList[2].Position = D3DXVECTOR4(posX + width, posY + height, 1.0f, 1.0f);	
	v2dList[3].Position = D3DXVECTOR4(posX, posY + height, 1.0f, 1.0f);
	
	//v2dList[4].Position = D3DXVECTOR4(posX, posY + height, 1.0f, 1.0f);
	//v2dList[5].Position = D3DXVECTOR4(posX + width, posY, 1.0f, 1.0f);

	v2dList[0].Color = color;
	v2dList[1].Color = color;
	v2dList[2].Color = color;
	v2dList[3].Color = color;
	//v2dList[4].Color = color;
	//v2dList[5].Color = color;

	v2dList[0].TexCoord = D3DXVECTOR2(ul, vt);
	v2dList[1].TexCoord = D3DXVECTOR2(ur, vt);
	v2dList[2].TexCoord = D3DXVECTOR2(ur, vb);
	v2dList[3].TexCoord = D3DXVECTOR2(ul, vb);
	//v2dList[4].TexCoord = D3DXVECTOR2(ul, vb);
	//v2dList[5].TexCoord = D3DXVECTOR2(ur, vt);
	//012,213,
	pvl = new float2D[verCount];
	pvl[0] = { 0,0 };
	pvl[1] = { 1,0 };
	pvl[2] = { 1,1 };
	pvl[3] = { 0,1 };
	//pvl[4] = { width,0 };
	//pvl[5] = { width,height };
}

void SpritePL::Draw(CameraC * ca)
{
	float lens = ca->GetLensDistance();

	float C_posX = ca->GetOffsetPosX();
	float C_posY = ca->GetOffsetPosY();

	cameraOffsetX = (1 - multiple.x) * (ca->GetPosX() - posX);
	cameraOffsetY = (1 - multiple.y) * (ca->GetPosY() - posY);

	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);

	float poX = (posX - anchorX * scale.x - C_posX + cameraOffsetX) / lens;
	float poY = (posY - anchorY * scale.y - C_posY + cameraOffsetY) / lens;

	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;

	float la_width = width * scale.x / lens;
	float la_height = height * scale.y / lens;

	//SpritePolygonDraw(textureID, v2dList);
	DrawPolygon(poX, poY, width * scale.x / lens, height*scale.y / lens, Tc_posX, Tc_posY, tcW, tcH);
}

void SpritePL::SetPolygonPoint(float2D * vList,int Count)
{
	delete[] pvl;
	pvl = NULL;
	verCount = Count;
	pvl = new float2D[Count];

	//float2D st = vList[0];
	for (int i = 0; i < verCount; i++)
	{
		if (vList[0].x > vList[i].x) {
			float2D t = vList[i];
			vList[i] = vList[0];
			vList[0] = t;
		}
		if(vList[0].x == vList[i].x && vList[0].y>vList[i].y){
			float2D t = vList[i];
			vList[i] = vList[0];
			vList[0] = t;
		}
	}

	for (int k = 0; k < verCount - 2; k++)
	{
		for (int i = 1; i < verCount - 1 - k; i++)
		{
			float xl1 = vList[i].x - vList[0].x;
			float yl1 = vList[i].y - vList[0].y;
			float xl2 = vList[i + 1].x - vList[0].x;
			float yl2 = vList[i + 1].y - vList[0].y;
			if (xl1 == 0) {
				if (xl1 == 0) {
					float2D t2 = vList[i];
					vList[i] = vList[i + 1];
					vList[i + 1] = t2;
				}
			}
			else
			{
				float slope1 = yl1 / xl1;
				float slope2 = yl2 / xl2;
				if (slope1 > slope2) {
					float2D t2 = vList[i];
					vList[i] = vList[i + 1];
					vList[i + 1] = t2;
				}
			}			
		}
	}
	
	for (int i = 0; i < verCount; i++)
	{
		pvl[i].x = (vList[i].x - (posX - anchorX))/ (width * scale.x);
		pvl[i].y = (vList[i].y - (posY - anchorY)) / (height*scale.x);
	}
	delete[] v2dList;
	v2dList = new Vertex2D[verCount];
}


void SpritePL::DrawPolygon(float pX, float pY, float w, float h, float tc_posX, float tc_posY, float tcW, float tcH)
{
	//pvl = new float2D[verCount];
	
	float ul = tc_posX / texture_width;
	float ur = (tc_posX + tcW) / texture_width;
	float vt = tc_posY / texture_height;
	float vb = (tc_posY + tcH) / texture_height;
	for (int i = 0; i < verCount; i++)
	{
		v2dList[i].Position = D3DXVECTOR4(pX + w * pvl[i].x,pY + h * pvl[i].y, 1.0f, 1.0f);
		v2dList[i].Color = color;
		
		float offx = pvl[i].x;
		float offy = pvl[i].y;
		float ux = offx * (ur - ul) + ul;
		float vy = offy * (vb - vt) + vt;

		v2dList[i].TexCoord = D3DXVECTOR2(ux, vy);
	}

	SpritePolygonDraw(textureID, v2dList,verCount);
}

SpritePA::~SpritePA()
{
}

void SpritePA::SetPartialWidth(float w)
{
	partialW = w;
	SetPartialAnchorPoint(pAnchorPoint);
}

void SpritePA::SetPartialHeight(float h)
{
	partialH = h;
	SetPartialAnchorPoint(pAnchorPoint);
}

void SpritePA::SetPartialAnchorPoint(ANCHORPOINT ap)
{
	pAnchorPoint = ap;
	switch (pAnchorPoint)
	{
	case ANCHOR_LU:
		partialX = 0.0f;
		partialY = 0.0f;
		break;
	case ANCHOR_LD:
		partialX = 0.0f;
		partialY = 1.0f - partialH;
		break;
	case ANCHOR_RU:
		partialX = 1.0f - partialW;
		partialY = 0.0f;
		break;
	case ANCHOR_RD:
		partialX = 1.0f - partialW;
		partialY = 1.0f - partialH;
		break;
	case ANCHOR_CENTER:
		partialX = (1.0f - partialW) * 0.5f;
		partialY = (1.0f - partialH) * 0.5f;
		break;
	case ANCHOR_LC:
		partialX = 0.0f;
		partialY = (1.0f - partialH) * 0.5f;
		break;
	case ANCHOR_RC:
		partialX = 1.0f - partialW;
		partialY = (1.0f - partialH) * 0.5f;
		break;
	case ANCHOR_TC:
		partialX = (1.0f - partialW) * 0.5f;
		partialY = 0.0f;
		break;
	case ANCHOR_BC:
		partialX = (1.0f - partialW) * 0.5f;
		partialY = 1.0f - partialH;
		break;
	default:
		break;
	}
}

void SpritePA::Draw(CameraC * ca)
{
	float lens = ca->GetLensDistance();

	float C_posX = ca->GetOffsetPosX();
	float C_posY = ca->GetOffsetPosY();

	cameraOffsetX = (1 - multiple.x) * (ca->GetPosX() - posX);
	cameraOffsetY = (1 - multiple.y) * (ca->GetPosY() - posY);

	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);

	float pX = (posX - anchorX * scale.x - C_posX + cameraOffsetX) / lens;
	float pY = (posY - anchorY * scale.y - C_posY + cameraOffsetY) / lens;

	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;

	SpriteDrawParatial(textureID, pX, pY, width * scale.x / lens, height*scale.y / lens, Tc_posX, Tc_posY, tcW, tcH, texture_width, texture_height, angle, { 1,1 }, color, anchorPoint,partialX,partialY,partialW,partialH);
}

SpriteAB::~SpriteAB()
{
}

void SpriteAB::SetAlphaBlendDest(int blendType)
{
}

void SpriteAB::SetAlphaBlendSrc(int blendType)
{
}

void SpriteAB::Draw(CameraC * ca)
{
	float lens = ca->GetLensDistance();

	float C_posX = ca->GetOffsetPosX();
	float C_posY = ca->GetOffsetPosY();

	cameraOffsetX = (1 - multiple.x) * (ca->GetPosX() - posX);
	cameraOffsetY = (1 - multiple.y) * (ca->GetPosY() - posY);

	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);

	float pX = (posX - anchorX * scale.x - C_posX + cameraOffsetX) / lens;
	float pY = (posY - anchorY * scale.y - C_posY + cameraOffsetY) / lens;

	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;

	LPDIRECT3DDEVICE9 mDevice = MyDirect3D_GetDevice();

	//mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//mDevice->SetRenderState(D3DRS_SRCBLEND)
	SpriteDrawBuffer(textureID, pX, pY, width * scale.x / lens, height*scale.y / lens, Tc_posX, Tc_posY, tcW, tcH, texture_width, texture_height, angle, { 1,1 }, color, anchorPoint);
	//mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}



SpData::SpData()
{
	scale.x = 1.0f;
	scale.y = 1.0f;
	textureDirection.x = 1;
	textureDirection.y = 1;
	textureRegionNumber.x = 0;
	textureRegionNumber.y = 0;
	textureRegionTotal.x = 1;
	textureRegionTotal.y = 1;
	anchorPoint = ANCHOR_LU;
	angle = 0.0f;
	posX = posY = anchorX = anchorY = texture_cutX = texture_cutY = 0;
	cameraOffsetX = cameraOffsetY = 0;
	active = true;
	texture_width = 1;
	texture_height = 1;
	texture_cutW = texture_cutH = 1;
	colorData = { 255,255,255,255 };
	HVratio = { 1.0f,1.0f };
	color = D3DCOLOR_RGBA(colorData.x, colorData.y, colorData.z, colorData.a);
	texture_width = 100;
	texture_height = 100;
	width = texture_cutW = texture_width;
	height = texture_cutH = texture_height;
}

SpData::~SpData()
{
}


void SpData::SetAlpha(float al)
{
	colorData.a = (int)(al * 255);
	color = D3DCOLOR_RGBA(colorData.x, colorData.y, colorData.z, colorData.a);
}

void SpData::SetScale(float scaleX, float scaleY)
{
	scale.x = scaleX;
	scale.y = scaleY;
}

void SpData::SetAnchorPoint(ANCHORPOINT aPoint)
{
	anchorPoint = aPoint;

	switch (anchorPoint)
	{
	case ANCHOR_LU:
		anchorX = 0;
		anchorY = 0;
		break;
	case ANCHOR_LD:
		anchorX = 0;
		anchorY = height;
		break;
	case ANCHOR_RU:
		anchorX = width;
		anchorY = 0;
		break;
	case ANCHOR_RD:
		anchorX = width;
		anchorY = height;
		break;
	case ANCHOR_CENTER:
		anchorX = width / 2;
		anchorY = height / 2;
		break;
	case ANCHOR_LC:
		anchorX = 0;
		anchorY = height / 2;
		break;
	case ANCHOR_RC:
		anchorX = width;
		anchorY = height / 2;
		break;
	case ANCHOR_TC:
		anchorX = width / 2;
		anchorY = 0;
		break;
	case ANCHOR_BC:
		anchorX = width / 2;
		anchorY = height;
		break;
	default:
		break;
	}
}

void SpData::SetColor(int cR, int cG, int cB)
{
	colorData.x = cR;
	colorData.y = cG;
	colorData.z = cB;
	color = D3DCOLOR_RGBA(colorData.x, colorData.y, colorData.z, colorData.a);
}

void SpData::SetColor(D3DCOLOR d3dcolor)
{
	color = d3dcolor;
	D3DXCOLOR cx = d3dcolor;
	colorData.x = (int)cx.r;
	colorData.y = (int)cx.g;
	colorData.z = (int)cx.b;
	colorData.a = (int)cx.a;
}

void SpData::SetWidth(float x)
{
	width = x;
	HVratio.x = x / texture_cutW;
	SetAnchorPoint(anchorPoint);
}

void SpData::SetHeight(float y)
{
	height = y;
	HVratio.y = y / texture_cutH;
	SetAnchorPoint(anchorPoint);
}

void SpData::SetSpriteSize(float x, float y)
{
	width = x;
	height = y;
	HVratio.x = x / texture_cutW;
	HVratio.y = y / texture_cutH;
	SetAnchorPoint(anchorPoint);
}

void SpData::SetTextureSize(float x, float y)
{
	texture_width = x;
	texture_height = y;
	width = texture_cutW = texture_width;
	height = texture_cutH = texture_height;
}



float2D SpData::GetLUUV()
{
	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);
	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;
	return { Tc_posX / texture_width,Tc_posY / texture_height };
}

float2D SpData::GetLDUV()
{
	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);
	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;
	return { Tc_posX / texture_width,(Tc_posY + tcH) / texture_height };
}

float2D SpData::GetRUUV()
{
	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);
	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;
	return { (Tc_posX + tcW) / texture_width,Tc_posY / texture_height };
}

float2D SpData::GetRDUV()
{
	float Tc_posX = texture_cutX - texture_cutW * (textureDirection.x*0.5f - 0.5f);
	float Tc_posY = texture_cutY - texture_cutH * (textureDirection.y*0.5f - 0.5f);
	float tcW = texture_cutW * textureDirection.x;
	float tcH = texture_cutH * textureDirection.y;
	return { (Tc_posX + tcW) / texture_width,(Tc_posY + tcH) / texture_height };
}


ParticleC::ParticleC(const char * pFilename, int Count, int Layer)
{
	textureID = Texture_SetTextureLoadFile(pFilename);
	posX = posY = 0.0f;
	pCount = Count;
	layer = Layer;
	active = true;
	partID = SpriteParticle_CreatBuffer(pCount);
	arrayID = GM_AddParticle(this);
	pSpData = new SpData[pCount];
	pVertex2D = new Vertex2D[pCount*4];	
}

ParticleC::~ParticleC()
{
	
	int b = GM_UnAddParticle(arrayID,layer);
	if (b == 0)Texture_Release(&textureID, 1);
	SpriteParticle_Release(partID);
	
	delete[] pVertex2D;
	delete[] pSpData;
	
}

void ParticleC::Init()
{
	float cellw = (float)Texture_GetTextureWidth(textureID);
	float cellh = (float)Texture_GetTextureHeight(textureID);
	for (int i = 0; i < pCount; i++)
	{
		pSpData[i].SetTextureSize(cellw, cellh);
		pSpData[i].SetAnchorPoint(ANCHOR_CENTER);
	}
}

void ParticleC::SetSpDataAngleAll(float ang)
{
	for (int i = 0; i < pCount; i++)
	{
		pSpData[i].SetAngle(ang);
	}
}

void ParticleC::Set_SpData_ScaleAll(float x, float y)
{
	for (int i = 0; i < pCount; i++)
	{
		pSpData[i].SetScale(x,y);
	}
}

void ParticleC::Draw(CameraC * ca)
{
	for (int i = 0; i < pCount; i++)
	{
		//pSpData[i].SetPosition(posX, posY);

		float x = pSpData[i].GetPosX();
		float y = pSpData[i].GetPosY();
		float w = pSpData[i].GetWidth();
		float h = pSpData[i].GetHeight();

		float lens = ca->GetLensDistance();

		float C_posX = ca->GetOffsetPosX();
		float C_posY = ca->GetOffsetPosY();

		float2D lu = pSpData[i].GetLUpos();
		float2D ld = pSpData[i].GetLDpos();
		float2D ru = pSpData[i].GetRUpos();
		float2D rd = pSpData[i].GetRDpos();
		float2D uvlu = pSpData[i].GetLUUV();
		float2D uvld = pSpData[i].GetLDUV();
		float2D uvru = pSpData[i].GetRUUV();
		float2D uvrd = pSpData[i].GetRDUV();
		float2D scl = pSpData[i].GetScale();

		float ang = pSpData[i].GetAngle();
		D3DCOLOR co = pSpData[i].GetD3DColor();

		pVertex2D[i * 4 + 0].Position = { lu.x,lu.y,1.0f,1.0f };
		pVertex2D[i * 4 + 1].Position = { ru.x,ru.y,1.0f,1.0f };
		pVertex2D[i * 4 + 2].Position = { ld.x,ld.y,1.0f,1.0f };
		pVertex2D[i * 4 + 3].Position = { rd.x,rd.y,1.0f,1.0f };

		pVertex2D[i * 4 + 0].Color = co;
		pVertex2D[i * 4 + 1].Color = co;
		pVertex2D[i * 4 + 2].Color = co;
		pVertex2D[i * 4 + 3].Color = co;

		pVertex2D[i * 4 + 0].TexCoord = { uvlu.x,uvlu.y };
		pVertex2D[i * 4 + 1].TexCoord = { uvru.x,uvru.y };
		pVertex2D[i * 4 + 2].TexCoord = { uvld.x,uvld.y };
		pVertex2D[i * 4 + 3].TexCoord = { uvrd.x,uvrd.y };

				
		D3DXMATRIX mtxWorld,mtxT,mtxR,mtxT2,mtxS;
		D3DXMatrixScaling(&mtxS, scl.x / lens, scl.y / lens,1.0f);
		D3DXMatrixTranslation(&mtxT, -x, -y, 0.0f);
		D3DXMatrixRotationZ(&mtxR, ang);
		D3DXMatrixTranslation(&mtxT2, (x + posX - C_posX)/lens, (y + posY - C_posY)/lens, 0.0f);
		mtxWorld = mtxT * mtxS * mtxR * mtxT2;

		D3DXVec4Transform(&pVertex2D[i * 4 + 0].Position, &pVertex2D[i * 4 + 0].Position, &mtxWorld);
		D3DXVec4Transform(&pVertex2D[i * 4 + 1].Position, &pVertex2D[i * 4 + 1].Position, &mtxWorld);
		D3DXVec4Transform(&pVertex2D[i * 4 + 2].Position, &pVertex2D[i * 4 + 2].Position, &mtxWorld);
		D3DXVec4Transform(&pVertex2D[i * 4 + 3].Position, &pVertex2D[i * 4 + 3].Position, &mtxWorld);
	}

	SpriteParticle_Draw(textureID, pVertex2D,partID);
}
