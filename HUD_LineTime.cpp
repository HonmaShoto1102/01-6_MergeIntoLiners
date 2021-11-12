/*---------------------------------------------------------------------------*/
//  FILE : HUD_LineTime.cpp
//
//         @@@@@@horizy‚Ævertica‚ÌLineTime‚ÌUI‚Ì‰‰o
//
/*===========================================================================*/
//
//                                                          Author : Honma Shoto
/*---------------------------------------------------------------------------*/

#include "HUD_LineTime.h"
#include "sprite.h"
#include "texture.h"
#include "PlayerData.h"
#include "base_Sprite.h"
#include "config.h"


#define scale_size_line (512.0f)
#define scale_size_line_shade (302.0f)
#define line_cut_size (96.0f)
#define line_cut_size_V (96.0f)
#define Refresh_W (1280)
#define Refresh_H (720)
#define ANIMATION_MAX (5)//3`5‚Ü‚Å‚Å’²®‰Â
#define ANIMATION_FPS (3)//”‚ð‘‚â‚·‚ÆƒAƒjƒ[ƒVƒ‡ƒ“‚ª’x‚­‚È‚é

namespace line {
	//Vertica
	SpriteUI* LineVertica;
	SpriteUI* LineVerticaShade;
	
	bool LVenable;
	bool LVenable_enable;
	int linetime_V;

	// Horizy
	SpriteUI* LineHorizy;
	SpriteUI* LineHorizyShade;

	bool LHenable;
	bool LHenable_enable;
	int linetime_H;

	
	// Horizy2
	SpriteUI* LineHorizy2;
	SpriteUI* LineHorizy2Shade;

	bool LH2enable;
	bool LH2enable_enable;
	int linetime_H2;
	
	
}

static int Line_Animaion_H_Id = INVALID_TEXTURE_ID;
static int Line_Animaion_V_Id = INVALID_TEXTURE_ID;

static int anime_H;
static int anime_H2;
static int anime_V;

static int g_FrameCount_H;
static int g_FrameCount_H2;
static int g_FrameCount_V;

void HUD_LineTime_Load(void)
{
	line::LineVertica = new SpriteUI("Asset/HUD/hud_vertica_line.png", 14, SPRITE_UI);
	line::LineVerticaShade = new SpriteUI("Asset/HUD/hud_line_black.png", 15, SPRITE_UI);//Žg—pÏ‚Ý‚Ì•
	

	line::LineHorizy = new SpriteUI("Asset/HUD/hud_horizy_line.png", 14, SPRITE_UI);
	line::LineHorizyShade = new SpriteUI("Asset/HUD/hud_line_black.png", 15, SPRITE_UI);//Žg—pÏ‚Ý‚Ì•

	
	line::LineHorizy2 = new SpriteUI("Asset/HUD/hud_horizy_line.png", 14, SPRITE_UI);
	line::LineHorizy2Shade = new SpriteUI("Asset/HUD/hud_line_black.png", 15, SPRITE_UI);//Žg—pÏ‚Ý‚Ì•
	

	Line_Animaion_H_Id = Texture_SetTextureLoadFile("Asset/HUD/refresh_line_horizy.png");
	Line_Animaion_V_Id = Texture_SetTextureLoadFile("Asset/HUD/refresh_line_vertica.png");

	Texture_Load();
}

void HUD_LineTime_Init(bool enable)
{
	line::LineVertica->Init();
	line::LineHorizy->Init();
	line::LineHorizy2->Init();
	line::LineVerticaShade->Init();
	line::LineHorizyShade->Init();
	line::LineHorizy2Shade->Init();
	
	if (enable == true)
	{

		//----------------------------------------------------Vertica(Ž‡F)-----------------------------------------------------------------

		//line::LineVertica->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2);//	1”{
		//line::LineVertica->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2 - 150.0f);//	1.25”{
		line::LineVertica->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2 - 150.0f);//	1.5”{
		line::LineVertica->SetPosY(55.0f);
		line::LineVertica->SetAnchorPoint(ANCHOR_LC);
		//line::LineVertica->SetScale(1.0f, 0.5f);//	‚P”{
		//line::LineVertica->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineVertica->SetScale(1.5f, 0.5f);//	1.5”{


		//line::LineVerticaShade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2 - 13.0f);//	1”{
		//line::LineVerticaShade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2-61.0f);//	1.25”{
		line::LineVerticaShade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2 + 34.0f);//	1.5”{
		line::LineVerticaShade->SetPosY(55.0f);
		line::LineVerticaShade->SetAnchorPoint(ANCHOR_RC);
		//line::LineVerticaShade->SetScale(1.0f, 0.5f);//	‚P”{
		//line::LineVerticaShade->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineVerticaShade->SetScale(1.5f, 0.5f);//	1.5”{



		line::LVenable = false;
		line::LVenable_enable = false;
		//----------------------------------------------------Vertica(Ž‡F)-----------------------------------------------------------------




		//======================================================Horizy(ÂF)===============================================================

		//line::LineHorizy->SetPosX(SCREEN_WIDTH / 2 - scale_size_line / 2);//	1”{
		//line::LineHorizy->SetPosX(SCREEN_WIDTH / 2 - scale_size_line / 2 - 350.0f);//	1.25”{
		line::LineHorizy->SetPosX(SCREEN_WIDTH / 2 - scale_size_line / 2 - 350.0f);//	1.5”{
		line::LineHorizy->SetPosY(55.0f);
		line::LineHorizy->SetAnchorPoint(ANCHOR_LC);
		//line::LineHorizy->SetScale(1.0f, 0.5f);//	1”{
		//line::LineHorizy->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineHorizy->SetScale(1.5f, 0.5f);//	1.5”{


		//line::LineHorizyShade->SetPosX(SCREEN_WIDTH / 2 + scale_size_line_shade / 2 - 10.0f);//	1”{
		//line::LineHorizyShade->SetPosX(SCREEN_WIDTH / 2 + scale_size_line_shade / 2 - 10.0f - 250.0f);//	1.25”{
		line::LineHorizyShade->SetPosX(SCREEN_WIDTH / 2 + scale_size_line_shade / 2 - 10.0f - 150.0f);//	1.5”{
		line::LineHorizyShade->SetPosY(55.0f);
		line::LineHorizyShade->SetAnchorPoint(ANCHOR_RC);
		//line::LineHorizyShade->SetScale(1.0f, 0.5f);//	1”{
		//line::LineHorizyShade->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineHorizyShade->SetScale(1.5f, 0.5f);//	1.5”{



		line::LHenable = false;
		line::LHenable_enable = false;
		//======================================================Horizy(ÂF)===============================================================


	//======================================================Horizy2(ÂF)===============================================================

		//line::LineHorizy2->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2);//	1”{
		//line::LineHorizy2->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2 - 150.0f);//	1.25”{
		line::LineHorizy2->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 - scale_size_line / 2 - 150.0f);//	1.5”{
		line::LineHorizy2->SetPosY(55.0f);
		line::LineHorizy2->SetAnchorPoint(ANCHOR_LC);
		//line::LineHorizy2->SetScale(1.0f, 0.5f);//	‚P”{
		//line::LineHorizy2->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineHorizy2->SetScale(1.5f, 0.5f);//	1.5”{


		//line::LineHorizy2Shade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2 - 13.0f);//	1”{
		//line::LineHorizy2Shade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2-61.0f);//	1.25”{
		line::LineHorizy2Shade->SetPosX(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 + scale_size_line_shade / 2 + 34.0f);//	1.5”{
		line::LineHorizy2Shade->SetPosY(55.0f);
		line::LineHorizy2Shade->SetAnchorPoint(ANCHOR_RC);
		//line::LineHorizy2Shade->SetScale(1.0f, 0.5f);//	‚P”{
		//line::LineHorizy2Shade->SetScale(1.25f, 0.5f);//	1.25”{
		line::LineHorizy2Shade->SetScale(1.5f, 0.5f);//	1.5”{



		line::LH2enable = false;
		line::LH2enable_enable = false;
		//======================================================Horizy2(ÂF)===============================================================


		anime_H = 0;
		anime_H2 = 0;
		anime_V = 0;
		g_FrameCount_H = 0;
		g_FrameCount_H2 = 0;
		g_FrameCount_V = 0;

	}
}

void HUD_LineTime_Update(bool enable)
{
	if (enable == true)
	{

		if (FairyVH_GetHorizy(1)->sprite->GetActive() == false)
		{
		line::linetime_V = FairyVH_GetTimeOfLine_CountDownV();
		line::LineVerticaShade->SetCutSize(line_cut_size + line::linetime_V, (int)scale_size_line);
		}

		line::linetime_H = FairyVH_GetTimeOfLine_CountDownH();
		line::LineHorizyShade->SetCutSize(line_cut_size + line::linetime_H, (int)scale_size_line);


		if (FairyVH_GetHorizy(1)->sprite->GetActive() == true)
		{
		line::linetime_H2 = FairyVH_GetTimeOfLine_CountDownH();//	<--------------------------------------ƒzƒ‰ƒCƒW[‚Q‚É•ÏX‚·‚é
		line::LineHorizy2Shade->SetCutSize(line_cut_size + line::linetime_H2, (int)scale_size_line);
		}

		//++++++++++++++++++++++++++++++++++++++++++++ANIMATION++++++++++++++++++++++++++++++++++++++++++++++++++++++++


		if (line::LHenable_enable == true)
		{
			g_FrameCount_H += 1;
			g_FrameCount_H = g_FrameCount_H % 6;
			anime_H = (g_FrameCount_H / ANIMATION_FPS) % ANIMATION_MAX;
		}
		if (g_FrameCount_H >= 5)
		{
			line::LHenable = false;
			line::LHenable_enable = false;
			g_FrameCount_H = 0;
		}

		if (line::LH2enable_enable == true)
		{
			g_FrameCount_H2 += 1;
			g_FrameCount_H2 = g_FrameCount_H2 % 6;
			anime_H2 = (g_FrameCount_H2 / ANIMATION_FPS) % ANIMATION_MAX;
		}
		if (g_FrameCount_H2 >= 5) {
			line::LH2enable = false;
			line::LH2enable_enable = false;
			g_FrameCount_H2 = 0;
		}

		if (line::LVenable_enable == true) {
			g_FrameCount_V += 1;
			g_FrameCount_V = g_FrameCount_V % 6;
			anime_V = (g_FrameCount_V / ANIMATION_FPS) % ANIMATION_MAX;


		}
		if (g_FrameCount_V >= 5) {
			line::LVenable = false;
			line::LVenable_enable = false;
			g_FrameCount_V = 0;
		}


		if (line::linetime_H >= 2 && line::linetime_H <= 298) {
			line::LHenable = true;
			line::LHenable_enable = false;
		}
		if (line::LHenable == true) {
			line::LHenable_enable = false;
		}


		if (line::linetime_H2 >= 2 && line::linetime_H2 <= 298) {
			line::LH2enable = true;
			line::LH2enable_enable = false;
		}
		if (line::LH2enable == true) {
			line::LH2enable_enable = false;
		}


		if (line::linetime_V >= 2 && line::linetime_V <= 298) {
			line::LVenable = true;
			line::LVenable_enable = false;
		}
		if (line::LVenable == true) {
			line::LVenable_enable = false;
		}

		if (FairyVH_GetTimeOfLine_CountDownH() <= 1 && line::LHenable == true)line::LHenable_enable = true;//true‚Ì‚Æ‚«‚É•`‰æ
		if (FairyVH_GetTimeOfLine_CountDownH() <= 1 && line::LH2enable == true)line::LH2enable_enable = true;//	<--------------------------------------ƒzƒ‰ƒCƒW[‚Q‚É•ÏX‚·‚é
		if (FairyVH_GetTimeOfLine_CountDownV() <= 1 && line::LVenable == true)line::LVenable_enable = true;

		//FairyVH_GetTimeOfLine_CountDownH() <= 0		<-ƒQ[ƒW‚ª‚l‚`‚w‚Ì‚Æ‚«
		//FairyVH_GetTimeOfLine_CountDownH() <= 1		<-‚½‚Ü‚É‚P‚É‚È‚é‚Æ‚«‚ª‚ ‚éiŠm”FÏ‚Ýby–{ŠÔj


		//++++++++++++++++++++++++++++++++++++++++++++ANIMATION++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	}
}

void HUD_LineTime_SpriteDraw(bool enable)
{
	if (enable == true)
	{
		if (line::LHenable_enable == true) {
		SpriteDraw(Line_Animaion_H_Id, -128.0f - 100.0f, -128.0f + 4.0f, Refresh_W*1.5f, Refresh_H*0.5f, Refresh_W*anime_H, Refresh_H*anime_H, Refresh_W, Refresh_H, Refresh_W * 5, Refresh_H * 5, 0.0f);//1.5”{
	}

	if (FairyVH_GetHorizy(1)->sprite->GetActive() == true)
	{
		if (line::LH2enable_enable == true) {
		SpriteDraw(Line_Animaion_H_Id, scale_size_line - 60.0f, -128.0f + 4.0f, Refresh_W*1.5f, Refresh_H*0.5f, Refresh_W*anime_H2, Refresh_H*anime_H2, Refresh_W, Refresh_H, Refresh_W * 5, Refresh_H * 5, 0.0f);//1.5”{
	}
	}

	if (FairyVH_GetHorizy(1)->sprite->GetActive() == false)
	{
		if (line::LVenable_enable == true) {
		SpriteDraw(Line_Animaion_V_Id, scale_size_line - 60.0f, -128.0f + 4.0f, Refresh_W*1.5f, Refresh_H*0.5f, Refresh_W*anime_V, Refresh_H*anime_V, Refresh_W, Refresh_H, Refresh_W * 5, Refresh_H * 5, 0.0f);//1.5”{
	}
}
	}
}

void HUD_LineTime_Unload(void)
{
	Texture_Release(&Line_Animaion_H_Id, 1);
	Texture_Release(&Line_Animaion_V_Id, 1);

	
	delete line::LineHorizyShade;
	line::LineHorizyShade = NULL;
	delete line::LineHorizy;
	line::LineHorizy = NULL;

	
	delete line::LineHorizy2Shade;
	line::LineHorizy2Shade = NULL;
	delete line::LineHorizy2;
	line::LineHorizy2 = NULL;
	
	
	delete line::LineVerticaShade;
	line::LineVerticaShade = NULL;
	delete line::LineVertica;
	line::LineVertica = NULL;

}