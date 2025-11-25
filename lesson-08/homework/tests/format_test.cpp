#include <gtest/gtest.h>
#include "../include/Format.hpp" 
TEST(FormatTest, Basic) {
    Format<int> f("Bonjour {0}!", 42);
    f.parse();
    EXPECT_EQ(f.str(), "Bonjour 42!");
}

// Répétition d’indices
TEST(FormatTest, RepeatIndices) {
    Format<int, std::string> f("{1}+{1}={0}", 2, "one");
    f.parse();
    EXPECT_EQ(f.str(), "one+one=2");
}

// Erreur : accolades vides
TEST(FormatTest, EmptyBraces) {
    EXPECT_THROW({
        Format<> f("{}");
        f.parse();
    }, FormatError);
}

// Erreur : caractère non numérique dans accolades
TEST(FormatTest, InvalidIndex) {
    EXPECT_THROW({
        Format<> f("{a}");
        f.parse();
    }, FormatError);
}

// Erreur : accolade ouvrante non fermée
TEST(FormatTest, UnclosedBrace) {
    EXPECT_THROW({
        Format<> f("{0");
        f.parse();
    }, FormatError);
}

// Erreur : accolade fermante sans ouvrante
TEST(FormatTest, ClosingWithoutOpening) {
    EXPECT_THROW({
        Format<> f("text }");
        f.parse();
    }, FormatError);


// Erreur : indice hors borne
TEST(FormatTest, IndexOutOfRange) {
    EXPECT_THROW({
        Format<int> f("{1}", 42);  // Seulement un argument (indice 0), demande 1
        f.parse();
    }, std::out_of_range);
}
