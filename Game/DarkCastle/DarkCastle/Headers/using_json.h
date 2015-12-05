#pragma once
#include "../Libs/json_spirit/json_spirit.h"
#include <fstream>
#include "consts_and_enums.h"
#include "SFML/Graphics.hpp"

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

inline std::vector<json_spirit::Pair>* GetEntitiesVector(std::string file_name) {
	std::ifstream is(file_name);
	json_spirit::Value value;
	read(is, value);
	const json_spirit::Object& object = value.get_obj();
	std::vector<json_spirit::Pair>* entities = new std::vector<json_spirit::Pair>;
	for (size_t i = 0; i < object.size(); i++) {
		entities->push_back(object[i]);
	}
	is.close();
	return entities;
}

inline sf::IntRect GetIntRect(std::vector<json_spirit::Pair>& vector, std::string entity, std::string action) {
	sf::IntRect anim_rect;
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i].name_ == entity) {
			auto action_types = vector[i].value_.get_obj();
			for (size_t j = 0; j < action_types.size(); j++) {
				if (action_types[j].name_ == action) {
					const json_spirit::Pair& x = action_types[j].value_.get_obj()[0];
					const json_spirit::Pair& y = action_types[j].value_.get_obj()[1];
					const json_spirit::Pair& width = action_types[j].value_.get_obj()[2];
					const json_spirit::Pair& height = action_types[j].value_.get_obj()[3];
					anim_rect = sf::IntRect(x.value_.get_int(), y.value_.get_int(), width.value_.get_int(), height.value_.get_int());
					break;
				}
			}
			break;
		}
	}
	return anim_rect;
}

inline int GetConfig(std::vector<json_spirit::Pair>& vector, std:: string entity, BonusType type) {
	std::string bonus_type = TypeToString(type);
	json_spirit::Value value;
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i].name_ == entity) {
			auto action_types = vector[i].value_.get_obj();
			for (size_t j = 0; j < action_types.size(); j++) {
				if (action_types[j].name_ == bonus_type) {
					value = action_types[j].value_;
					break;
				}
			}
			break;
		}
	}
	return value.get_int();
}
