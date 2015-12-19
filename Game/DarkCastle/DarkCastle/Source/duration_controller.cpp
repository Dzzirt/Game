#include "../Headers/duration_controller.h"
#include "../Headers/safe_delete.h"


DurationController* CreateDurationController(CellLogic & cell_logic) {
	DurationController* ctrl = new DurationController();
	DurationControllerInit(*ctrl, cell_logic);
	return ctrl;
}

void DurationControllerInit(DurationController& ctrl, CellLogic & cell_logic) {
	ctrl.curr_elapsed_time = 0.f;
	ctrl.max_elapsed_time = float(cell_logic.duration);
	ctrl.type = cell_logic.type;
}

void DuratonControllerUpdate(DurationController& ctrl, const sf::Time& deltaTime) {
	ctrl.curr_elapsed_time += deltaTime.asSeconds();
}

void DestroyDurationController(DurationController *& ctrl) {
	SafeDelete(ctrl);
}