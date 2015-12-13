#include "../Headers/cell_visual.h"
#include "../Headers/bonuses_panel_const.h"

CellVisual* CreateCellVisual(BonusVisual & b_visual) {
	CellVisual * cell_visual = new CellVisual();
	CellVisualInit(*cell_visual, b_visual);
	return cell_visual;
}

void CellVisualInit(CellVisual& cell_visual, BonusVisual & b_visual) {
	cell_visual.sprite = b_visual.sprite;
	cell_visual.texture = b_visual.texture;
	cell_visual.sprite_rect = b_visual.sprite_rect;
	cell_visual.sprite.setTexture(cell_visual.texture);
	cell_visual.sprite.setTextureRect(cell_visual.sprite_rect);
	sf::IntRect cell_size = cell_visual.sprite_rect;
	cell_visual.sprite.setScale(CellWidth / cell_size.width, CellHeight / cell_size.height);
}

void DestroyCellVisual(CellVisual& cell_visual) {
	delete &cell_visual;
}