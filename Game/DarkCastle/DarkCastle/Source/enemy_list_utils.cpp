#include "../Headers/enemy_list_utils.h"
#include "../Headers/safe_delete.h"

using namespace std;
using namespace sf;

void EnemyListInit(list<Enemy*>& enemy_list, Resourses& res, Type type)
{
	int enemies_count = GetEnemiesCount(*res.lvl, type);
	for (int i = 0; i < enemies_count; i++)
	{
		Enemy* enemy = CreateEnemy(res, i, type);
		enemy_list.push_back(enemy);
	}
}

std::list<Enemy*>* CreateEnemyList(Resourses & res)
{
	std::list<Enemy*>* list = new std::list<Enemy*>();
	EnemyListInit(*list, res, SPEARMAN);
	EnemyListInit(*list, res, JELLY);
	EnemyListInit(*list, res, JELLY_BOSS);
	return list;
}



void ProcessEnemyListEvents(std::list<Enemy*> & enemy_list, sf::FloatRect & player_rect)
{
	for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end(); ++iter)
	{
		Enemy* enemy = *iter;
		ProcessEnemyEvents(*enemy, player_rect);
	}
}

void EnemyListUpdate(std::list<Enemy*> & enemy_list, Level & level, const sf::Time& deltaTime, sf::View & view)
{
	for (Enemy * enemy : enemy_list)
	{
		EnemyUpdate(*enemy, deltaTime, level, view);
	}
}

void DrawEnemies(std::list<Enemy*> & enemies, RenderWindow &window)
{
	for (list<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		Enemy* enemy = *iter;
		VisualHpBar& enemy_hp = *enemy->hp_bar->visual_hp;
		Sprite& enemy_sprite = enemy->visual->animation->frame->sprite;
		window.draw(enemy_sprite);
		window.draw(enemy_hp.strip_sprite);
		window.draw(enemy_hp.bar_sprite);
	}
}

void DestroyEnemyList(std::list<Enemy*> *& enemy_list)
{
	for_each(enemy_list->begin(), enemy_list->end(), DestroyEnemy);
	SafeDelete(enemy_list);
}