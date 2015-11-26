#pragma once
#include "../Libs/json_spirit/json_spirit.h"
#include <fstream>
#include "consts_and_enums.h"

inline std::string TypeToString(Type type) {
	switch (type) {
		case PLAYER:
			return "PLAYER";
		case SPEARMAN:
			return "SPEARMAN";
		case SWORDSMAN:
			return "SWORDSMAN";
		default:
			return "INVALID ENUM";
	}
}

inline std::string TypeToString(BonusType type) {
	switch (type) {
		case HP_REGEN:
			return "HP_REGEN";
		case SPEED_UP:
			return "SPEED_UP";
		case ATK_UP:
			return "ATK_UP";
		default:
			return "INVALID_VALUE";
	}
}

inline sf::IntRect GetIntRect(std::string entity, std::string action, std::string file_name) {
	sf::IntRect anim_rect;
	std::ifstream is("Resourses/" + file_name);
	json_spirit::Value value;
	read(is, value);
	const json_spirit::Object& object = value.get_obj();
	for (size_t i = 0; i < object.size(); i++) {
		const json_spirit::Pair& pair = object[i];
		const std::string& entity_name = pair.name_;
		const json_spirit::Value& entity_val = pair.value_;
		if (entity_name == entity) {
			const json_spirit::Object& entity_obj = entity_val.get_obj();
			for (size_t j = 0; j < entity_obj.size(); j++) {
				if (entity_obj[j].name_ == action) {
					const json_spirit::Pair& x = entity_obj[j].value_.get_obj()[0];
					const json_spirit::Pair& y = entity_obj[j].value_.get_obj()[1];
					const json_spirit::Pair& width = entity_obj[j].value_.get_obj()[2];
					const json_spirit::Pair& height = entity_obj[j].value_.get_obj()[3];
					anim_rect = sf::IntRect(x.value_.get_int(), y.value_.get_int(), width.value_.get_int(), height.value_.get_int());
					break;
				}
			}
			break;

		}
	}
	is.close();
	return anim_rect;

}

inline int GetBonusValue(BonusType type, std::string file_name) {
	std::string bonus_type = TypeToString(type);
	std::ifstream is("Resourses/" + file_name);
	json_spirit::Value value;
	read(is, value);
	const json_spirit::Object& object = value.get_obj();
	for (size_t i = 0; i < object.size(); i++) {
		const json_spirit::Pair& pair = object[i];
		const std::string& name = pair.name_;
		const json_spirit::Value& val = pair.value_;
		if (name == "BONUS") {
			const json_spirit::Object& entity_obj = val.get_obj();
			for (size_t j = 0; j < entity_obj.size(); j++) {
				if (entity_obj[j].name_ == bonus_type) {
					return entity_obj[j].value_.get_int();

				}
			}
			break;
		}
	}
	return -1;
}
