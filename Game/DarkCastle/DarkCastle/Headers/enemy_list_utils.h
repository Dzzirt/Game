#include <list>
#include "enemy.h"

std::list<Enemy*>* CreateEnemyList(Resourses & res);
void EnemyListInit(std::list<Enemy*> & en_list, Resourses & res, Type type);
void ProcessEnemyListEvents(std::list<Enemy*> & enemy_list, sf::FloatRect & player_rect);
void EnemyListUpdate(std::list<Enemy*> & enemy_list, Level & level, const sf::Time& deltaTime);
void DrawEnemies(std::list<Enemy*> & enemies, sf::RenderWindow &window);
void DestroyEnemyList(std::list<Enemy*> *& enemy_list);