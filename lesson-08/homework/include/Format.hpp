#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <cctype>
#include <utility>

struct FormatError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

template<typename... Args>
class Format {
public:
    explicit Format(const std::string& fmt, Args&&... args)
        : fmt_(fmt), args_(std::forward<Args>(args)...) {}

    void parse() {
        // Convert arguments to strings
        arg_strings_ = std::apply([](auto&&... xs) {
            return std::vector<std::string>{ toString(xs)... };
        }, args_);

        result_.str("");
        result_.clear();

        const size_t n = fmt_.size();
        for (size_t i = 0; i < n; ++i) {
            char c = fmt_[i];
            if (c == '{') {
                ++i;
                if (i >= n) throw FormatError("Accolade ouvrante sans fermeture");
                if (!std::isdigit(static_cast<unsigned char>(fmt_[i])))
                    throw FormatError("Indice non numérique dans les accolades");

                int idx = 0;
                while (i < n && std::isdigit(static_cast<unsigned char>(fmt_[i]))) {
                    idx = idx * 10 + (fmt_[i] - '0');
                    ++i;
                }

                if (i >= n || fmt_[i] != '}')
                    throw FormatError("Accolade non fermée ou syntaxe incorrecte");

                if (idx < 0 || static_cast<size_t>(idx) >= arg_strings_.size())
                    throw std::out_of_range("Argument index hors limites");

                result_ << arg_strings_[idx];

            } else if (c == '}') {
                throw FormatError("Accolade fermante sans ouvrante correspondante");
            } else {
                result_ << c;
            }
        }
    }

    std::string str() const { return result_.str(); }

private:
    template<typename T>
    static std::string toString(const T& v) {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    }

    std::string fmt_;
    std::tuple<Args...> args_{};
    std::vector<std::string> arg_strings_;
    std::ostringstream result_;
};

#endif