#include "../Headers/bonuses_panel.h"

BonusesPanel* CreateBonusesPanel() {
	BonusesPanel* panel = new BonusesPanel();
	BonusesPanelInit(*panel);
	return panel;
}

void BonusesPanelInit(BonusesPanel& panel) {
	panel.img.loadFromFile("Resourses/BonusPanel/bonuses_panel.png");
	panel.texture.loadFromImage(panel.img);
	panel.sprite.setTexture(panel.texture);
	panel.items = CreateItemsVec();
	
}

std::vector<Bonus*>* CreateItemsVec() {
	std::vector<Bonus*>* cells = new std::vector<Bonus*>();
	cells->reserve(3);
	return cells;
}

void AddToItemsVec(std::vector<Bonus*> & items, Bonus & bonus) {
	BonusVisual & visual = *bonus.bonus_visual;
	visual.image.loadFromFile("Resourses/BonusPanel/bonuses.png");
	visual.texture.loadFromImage(visual.image);
	visual.sprite.setTexture(visual.texture);
	visual.sprite.setTextureRect(bonus.bonus_visual->sprite_rect);
}

void DrawBonusesPanel(BonusesPanel& panel, sf::RenderWindow & window) {
	window.draw(panel.sprite);
}

void BonusesPanelUpdate(BonusesPanel& panel, sf::View view) {
	float view_top = view.getCenter().y - view.getSize().y / 2.f;
	float view_left = view.getCenter().x - view.getSize().x / 2.f;
	panel.sprite.setPosition(view_left + PanelXPos, view_top + PanelYPos);
}


void DestroyBonusesPanel(BonusesPanel& panel) {
	delete &panel;
}

void DestroyPanelCells(std::vector<Bonus*>& items) {
	
}