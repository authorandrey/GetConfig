#pragma once
#include <string>

namespace get_config::strings {
static inline std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](int c) {
            return !std::isspace(c);
        }
    ));
    return s;
}

static inline std::string ltrim_copy(const std::string& s) {
    auto it = std::find_if(s.begin(), s.end(),
        [](int c) {
            return !std::isspace(c);
        }
    );
    return std::string(it, s.end());
}

static inline std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](int c) {
            return !std::isspace(c);
        }
    ).base(), s.end());
    return s;
}

static inline std::string rtrim_copy(const std::string& s) {
    auto it = std::find_if(s.rbegin(), s.rend(),
        [](int c) {
            return !std::isspace(c);
        }
    );
    return std::string(s.begin(), it.base());
}

static inline std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}

static inline std::string trim_copy(const std::string& s) {
    return ltrim_copy(rtrim_copy(s));
}
}  // namespace get_config::strings