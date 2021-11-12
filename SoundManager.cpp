#include "SoundManager.h"

static SOUND_LABEL nowBgm = SL_BGM_Title;
static bool BgmPlayFlag = false;

void SoundManager_PlayBGM(SOUND_LABEL sl)
{
	if (BgmPlayFlag)StopSound(nowBgm);
	nowBgm = sl;
	PlaySound(nowBgm);
	BgmPlayFlag = true;
}

void SoundManager_StopBGM()
{
	if (BgmPlayFlag)StopSound(nowBgm);
	BgmPlayFlag = false;
}

void SoundManager_PlaySE(SOUND_LABEL sl)
{
	PlaySound(sl);
}
