#pragma once
#include <nlohmann/json.hpp>
#include <string>

inline std::string build_auth_request(const std::string& user, const std::string& pass) {
	nlohmann::json j = { {"username", user}, {"password", pass } };
	return j.dump();
}


inline std::string build_auth_request(const std::string& user) {
	nlohmann::json j = { {"username", user} };
	return j.dump();
}
