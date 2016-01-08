#include "../Headers/collision_utils.h"

using namespace std;
using namespace sf;

void CheckPlayerAndEnemiesCollisions(std::list<Enemy*> & enemy_list, Player& player)
{
	list<Enemy*>::iterator enemy_list_begin = enemy_list.begin();
	list<Enemy*>::iterator enemy_list_end = enemy_list.end();
	for (list<Enemy*>::iterator iter = enemy_list_begin; iter != enemy_list_end; ++iter)
	{
		Enemy* enemy = *iter;
		PlayerEnemyCollision(player, *enemy);
		EnemyPlayerCollision(*enemy, player);
		if (enemy->fight->is_dead)
		{
			DestroyEnemy(enemy);
			enemy_list.remove(*iter);
			break;
		}
	}
}

void PlayerEnemyCollision(const Player& player, Enemy& enemy)
{
	Animation& player_anim = *player.visual->animation;
	FightLogic& enemy_fight = *enemy.fight;
	float& enemy_hp = enemy.fight->health_points;
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& enemy_rect = *enemy.visual->rect;
	float& player_damage = player.fight->damage;
	float& player_stored_damage = player.fight->stored_damage;
	bool is_hit = int(player_anim.current_attack_frame) == PlayerAttackFrame;
	if (player_sprite.intersects(enemy_rect) && is_hit)
	{
		enemy.is_attacked = true;
		if (enemy_hp <= 0)
		{
			enemy_fight.is_dead = true;
			player_damage = player_stored_damage;
		}
		else
		{
			enemy_hp -= player_damage;
			player_damage = 0;
			enemy.is_injured = true;
		}
	}
	else
	{
		if (enemy.is_attacked)
		{
			enemy.is_attacked = false;
			player_damage = player_stored_damage;
		}
	}
}

void PlayerMaceTrapCollision(Player& player, MaceTrap & trap)
{
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect mace_sprite = trap.sprite.getGlobalBounds();
	mace_sprite.left += DisplaceMace;
	mace_sprite.width -= DecreaseMaceSize;
	mace_sprite.height -= DecreaseMaceSize;
	float& player_hp = player.fight->health_points;
	FightLogic& player_fight = *player.fight;
	if (player_sprite.intersects(mace_sprite))
	{
		if (player_hp <= 0)
		{
			player_fight.is_dead = true;
		}
		else
		{
			player_hp -= trap.damage;
			player.visual->animation->frame->sprite.setColor(Color::Red);
			trap.damage = 0;
		}
	}
	else
	{
		trap.damage = MaceTrapDamage;
	}
}

void CheckPlayerBonusCollision(const Player& player, Bonus& bonus)
{
	FloatRect player_sprite = player.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect bonus_sprite = bonus.bonus_visual->sprite.getGlobalBounds();
	if (player_sprite.intersects(bonus_sprite))
	{
		bonus.bonus_logic->picked_up = true;
	}
}

void EnemyPlayerCollision(const Enemy& enemy, Player& player)
{
	Animation& enemy_anim = *enemy.visual->animation;
	FightLogic& player_fight = *player.fight;
	float& player_hp = player.fight->health_points;
	FloatRect enemy_sprite = enemy.visual->animation->frame->sprite.getGlobalBounds();
	FloatRect& player_rect = *player.visual->rect;
	float& enemy_damage = enemy.fight->damage;
	bool is_hit = int(enemy_anim.current_attack_frame) == SpearmanAttackFrame;
	if (enemy_sprite.intersects(player_rect) && is_hit)
	{
		if (player_hp <= 0)
		{
			player_fight.is_dead = true;
		}
		else
		{
			player_hp -= enemy_damage;
			player.is_injured = true;
			enemy_damage = 0;
		}
	}
	else
	{
		enemy_damage = CEnemyDamage;
	}
}