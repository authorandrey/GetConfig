#pragma once
#include "core/types.h"
#include "core/string_extension.h"
#include "lexer/lexer.h"

namespace get_config::parser {
class Parser {
public:
	Parser(std::istream& _is)
		: m_lexer(_is) { }

	ConfigType parse() {
		ConfigType config;
		config.reserve(8);

		std::string block_name = "";
		lexer::Token token = m_lexer.next();
		while (token.type != lexer::Token::END_OF_FILE) {
			switch (token.type) {
			case lexer::Token::BLOCK:
				block_name = token.content;
				break;
			case lexer::Token::IDENTIFIER:
				parse_parameter(config, block_name, token.content);
				break;
			case lexer::Token::ERROR:
				throw std::runtime_error(token.content);
			default:
				throw std::runtime_error("Unexpected token");
			}
			token = m_lexer.next();
		}

		return config;
	}

private:
	void parse_parameter(
		ConfigType& config,
		const std::string& block,
		const std::string& parameter) {
		lexer::Token token = m_lexer.next();
		if (token.type != lexer::Token::PUNCTUATION) {
			throw std::runtime_error("Not found \'=\' symbol at the parameter definition");
		}

		std::string value = strings::trim_copy(m_lexer.get_line());

		config[block][parameter] = value;
	}

private:
	lexer::Lexer m_lexer;
};
}  // namespace get_config::parser