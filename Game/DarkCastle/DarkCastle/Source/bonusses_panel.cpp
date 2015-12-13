#include "../Headers/bonuses_panel.h"

using namespace sf;

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

std::vector<Cell*>* CreateItemsVec() {
	std::vector<Cell*>* items = new std::vector<Cell*>();
	items->reserve(3);
	return items;
}

bool AddToItemsVec(std::vector<Cell*> & items, Bonus & bonus) {
	Cell * items_cell = CreateCell(bonus);
	if (items.size() < PanelCapacity) {
		items.push_back(items_cell);
		return true;
	}
	return false;
}

void DrawBonusesPanel(BonusesPanel& panel, sf::RenderWindow & window) {
	window.draw(panel.sprite);
	for (Cell * cell : *panel.items) {
		window.draw(cell->visual->sprite);
	}
}

void BonusesPanelUpdate(BonusesPanel& panel, sf::View view) {
	float view_top = view.getCenter().y - view.getSize().y / 2.f;
	float view_left = view.getCenter().x - view.getSize().x / 2.f;
	panel.sprite.setPosition(view_left + PanelXPos, view_top + PanelYPos);
	sf::FloatRect panel_box = panel.sprite.getGlobalBounds();
	float cell_x = panel_box.left + PanelLeftBorderWidth;
	float cell_y = panel_box.top + PanelTopBorderHeight;
	float delimeter = 0;
	for (size_t i = 0; i < panel.items->size(); i++) {
		if (i != 0) {
			delimeter = CellDelimeterHeight;
		}
		panel.items[0][i]->visual->sprite.setPosition(cell_x, cell_y + (CellHeight * i) + delimeter);
	}
}

void ProcessPanelEvents(BonusesPanel& panel) {
	if (Keyboard::isKeyPressed(Keyboard::Z) && panel.items->size() >= 1) {
		panel.items[0][0]->logic->is_activated = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::X) && panel.items->size() >= 2) {
		panel.items[0][1]->logic->is_activated = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::C) && panel.items->size() == 3) {
		panel.items[0][2]->logic->is_activated = true;
	}
}

void DestroyBonusesPanel(BonusesPanel& panel) {
	delete &panel;
}

void DestroyPanelCells(std::vector<Bonus*>& items) {
	
}