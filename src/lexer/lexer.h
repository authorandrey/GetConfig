#pragma once
#include <istream>
#include <string>

namespace get_config::lexer {
constexpr char COMMENT = '#';
constexpr char BLOCK_OPEN = '[';
constexpr char BLOCK_CLOSE = ']';

inline constexpr bool is_identifier_start_symbol(char symbol) {
	return symbol >= 'a' && symbol <= 'z'
		|| symbol >= 'A' && symbol <= 'Z'
		|| symbol == '_';
}

inline constexpr bool is_identifier_symbol(char symbol) {
	return is_identifier_start_symbol(symbol)
		|| symbol >= '0' && symbol <= '9';
}

struct Token {
	enum TokenType {
		IDENTIFIER,
		BLOCK,
		PUNCTUATION,
		IGNORED,
		END_OF_FILE,
		ERROR
	};

	TokenType type;
	std::string content;
};

class Lexer {
public:
	Lexer(std::istream& _is) : m_is(_is) { }

	Token next() {
		char symbol;
		while (m_is.get(symbol)) {
			Token token = process_next_symbol(symbol);
			if (token.type != Token::IGNORED) {
				return token;
			}
		}

		return { Token::END_OF_FILE, "" };
	}

	std::string get_line() {
		std::string value;
		value.reserve(8);
		std::getline(m_is, value);
		return value;
	}

private:
	Token process_next_symbol(char symbol) {
		if (symbol == COMMENT) {
			m_is.ignore(
				std::numeric_limits<std::streamsize>::max(),
				'\n'
			);
			return { Token::IGNORED, "" };
		}

		if (symbol == BLOCK_OPEN) {
			m_is.get(symbol);
			if (is_identifier_start_symbol(symbol) == false) {
				m_is.putback(symbol);
				return { Token::ERROR, "Invalid identifier start symbol" };
			}
			std::string identifier = process_identifier(symbol);
			skip_until(BLOCK_CLOSE);
			return { Token::BLOCK, std::move(identifier) };
		}

		if (symbol == '=') {
			return { Token::PUNCTUATION,"=" };
		}

		if (std::isspace(symbol)) {
			return { Token::IGNORED, "" };
		}

		if (is_identifier_start_symbol(symbol)) {
			std::string identifier = process_identifier(symbol);
			return { Token::IDENTIFIER, std::move(identifier) };
		}

		return { Token::ERROR, "Unexpected symbol" };
	}

	void skip_until(char _symbol) {
		char symbol;
		while (m_is.get(symbol)) {
			if (std::isspace(symbol)) {
				continue;
			}
			if (symbol == _symbol) {
				break;
			}
			m_is.putback(symbol);
			throw std::runtime_error("Not found expected " + std::to_string(_symbol) + " symbol");
		}
	}

	std::string process_identifier(char symbol) {
		std::string value;
		value.reserve(8);
		value += symbol;
		while (m_is.get(symbol)) {
			if (is_identifier_symbol(symbol) == false) {
				m_is.putback(symbol);
				break;
			}
			value += symbol;
		}
		return value;
	}

private:
	std::istream& m_is;
};
}  // namespace get_config::lexer