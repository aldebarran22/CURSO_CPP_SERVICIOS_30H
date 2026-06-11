#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include <optional>

template<typename T>
class MemCache {
private:
	std::unordered_map<std::string, T> datos;
	std::mutex mtx;

public:
	std::optional<T> get(const std::string& key) {
		std::lock_guard<std::mutex> lock(mtx);
		auto it = datos.find(key);
		return (it != it.end()) ? std::optional<T>(it->second) : std::nullopt;
	}

	void set(const std::string& key, const T& value) {
		std::lock_guard<std::mutex> lock(mtx);
		datos[key] = value;
	}

	void remove(const std::string& key) {
		std::lock_guard<std::mutex> lock(mtx);
		datos.erase(key);
	}

	void clear() {
		std::lock_guard<std::mutex> lock(mtx);
		datos.clear();
	}
};


