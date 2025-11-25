#include "../include/Format.hpp"
#include <string>
#include <sstream>


std::string Format::str()
{
    return result_stream.str();
}

void Format::parse() {
        size_t len = format_str.size();
        for (size_t i = 0; i < len; ++i) {
            if (format_str[i] == '{') {
                ++i;
                if (i >= len)
                    throw Format("Accolade ouvrante sans fermeture");
                if (!std::isdigit(format_str[i]))
                    throw Format("Indice non numérique dans les accolades");

                int index = 0;
                while (i < len && std::isdigit(format_str[i])) {
                    index = index * 10 + (format_str[i] - '0');
                    ++i;
                }

                if (i >= len || format_str[i] != '}')
                    throw Format("Accolade non fermée ou syntaxe incorrecte");

                // Ici, on pourrait ajouter la récupération de l’argument indexé
                // et son insertion dans result_stream.

                // Pour l’instant, pour test, on écrit l’index dans le flux :
                result_stream << "[" << index << "]";

            } else if (format_str[i] == '}') {
                throw Format("Accolade fermante sans ouvrante correspondante");
            } else {
                // Texte normal, on le copie dans le flux résultat
                result_stream << format_str[i];
            }
        }
}

