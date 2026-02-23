#pragma once
#include <string>
#include <unordered_map>

namespace get_config {
using ConfigInnerType = std::unordered_map<std::string, std::string>;

using ConfigType = std::unordered_map<
	std::string,
	ConfigInnerType
>;
} // namespace get_config