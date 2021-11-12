#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>

class Game
{
public:
	void Load();
	void Init();
	void Update();
	void Final();
	void Draw();

	void LoadEnemy();
	void InitEnemy();
	void UpdateEnemy();
	void UnloadEnemy();

	void AddEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);

	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
private:
	std::vector<class Enemy*> mEnemies;
};
#endif
