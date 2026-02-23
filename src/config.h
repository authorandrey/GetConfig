#pragma once
#include <variant>
#include <stdexcept>
#include <fstream>
#include "core/config_cast.h"
#include "parser/parser.h"

namespace get_config {
class Config {
public:
	const Config& load_config(std::istream& _is) {
		parser::Parser parser(_is);
		m_config = parser.parse();
		return *this;
	}

	const Config& load_config(const std::string& _filepath) {
		std::ifstream file(_filepath);
		parser::Parser parser(file);
		m_config = parser.parse();
		return *this;
	}

	const std::string& get(const std::string& _space, const std::string& _parameter) const {
		return m_config.at(_space).at(_parameter);
	}

	const std::string& get(const std::string& _parameter) const {
		return get(m_default_block, _parameter);
	}

	template<class T>
	T get(const std::string& _space, const std::string& _parameter) const {
		const std::string& value = m_config.at(_space).at(_parameter);
		return config_cast<T>(value);
	}

	template<class T>
	T get(const std::string& _parameter) const {
		return get<T>(m_default_block, _parameter);
	}

	const std::string& operator[](const std::string& _parameter) const {
		return get(_parameter);
	}

#if __cplusplus > 202002L
	const std::string& operator[](const std::string& _space, const std::string& _parameter) const {
		return get(_space, _parameter);
	}
#endif

	const std::string& operator()(const std::string& _parameter) const {
		return get(_parameter);
	}

	const std::string& operator()(const std::string& _space, const std::string& _parameter) const {
		return get(_space, _parameter);
	}

private:
	std::string m_default_block = "";
	ConfigType m_config;
};
}  // namespace get_config