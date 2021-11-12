/*---------------------------------------------------------------------------*/
//  FILE : HUD_LineTime.h
//
//         　　　　　　horizyとverticaのLineTimeのUIの演出
//
/*===========================================================================*/
//
//                                                          Author : Honma Shoto
/*---------------------------------------------------------------------------*/

#ifndef HUD_LINETIME
#define HUD_LINETIME

#include "FairyVH.h"

void HUD_LineTime_Load(void);
void HUD_LineTime_Init(bool enable);
void HUD_LineTime_Update(bool enable);
void HUD_LineTime_SpriteDraw(bool enable);
void HUD_LineTime_Unload(void);


#endif // HUD_LINETIME
