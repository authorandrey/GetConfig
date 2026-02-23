#pragma once
#include <string>
#include <stdexcept>

namespace get_config {
template<class T>
inline T config_cast(const std::string& str) {
	return static_cast<T>(str);
}

template<>
inline char config_cast<char>(const std::string& str) {
	return str.at(0);
}

template<>
inline bool config_cast<bool>(const std::string& str) {
	if (str == "true") {
		return true;
	}
	if (str == "false") {
		return false;
	}
	throw std::runtime_error("Failed to convert string to bool");
}

template<>
inline int config_cast<int>(const std::string& str) {
	return std::stoi(str);
}

template<>
inline long config_cast<long>(const std::string& str) {
	return  std::stol(str);
}

template<>
inline long long config_cast<long long>(const std::string& str) {
	return  std::stoll(str);
}

template<>
inline unsigned long config_cast<unsigned long>(const std::string& str) {
	return std::stoul(str);
}

template<>
inline unsigned long long config_cast<unsigned long long>(const std::string& str) {
	return std::stoull(str);
}

template<>
inline float config_cast<float>(const std::string& str) {
	return std::stof(str);
}

template<>
inline double config_cast<double>(const std::string& str) {
	return std::stod(str);
}

template<>
inline long double config_cast<long double>(const std::string& str) {
	return std::stold(str);
}
}  // namespace get_config