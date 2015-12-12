#include "../Headers/duration_controller.h"

DurationController* CreateDurationController(BonusLogic & b_logic) {
	DurationController* ctrl = new DurationController();
	DurationControllerInit(*ctrl, b_logic);
	return ctrl;
}

void DurationControllerInit(DurationController& ctrl, BonusLogic & b_logic) {
	ctrl.curr_elapsed_time = 0.f;
	ctrl.max_elapsed_time = float(b_logic.duration);
	ctrl.type = b_logic.bonus_type;
}

void DuratonControllerUpdate(DurationController& ctrl, const sf::Time& deltaTime) {
	ctrl.curr_elapsed_time += deltaTime.asSeconds();
}

void DestroyDurationController(DurationController& ctrl) {
	delete &ctrl;
}