#include "enemy.h"
#include "player.h"
#include "bonus.h"
#include "mace_trap.h"
#include "list"

void CheckPlayerAndEnemiesCollisions(std::list<Enemy*> & enemy_list, Player& player);
void CheckPlayerBonusCollision(const Player& player, Bonus& bonus);
void PlayerEnemyCollision(const Player & player, Enemy & enemy);
void PlayerMaceTrapCollision(Player& player, MaceTrap & trap);
void EnemyPlayerCollision(const Enemy& enemy, Player& player);