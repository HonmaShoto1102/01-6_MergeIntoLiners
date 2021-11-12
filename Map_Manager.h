#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

void MapManager_Load();
void MapManager_Init();
void MapManager_Update();
void MapManager_Final();
void MapManager_StageTrans(int num);
void MapManager_StageClear();
int MapManager_GetTransHeart();
int MapManager_GetStangeNumber();

#endif // !MAP_MANAGER_H

