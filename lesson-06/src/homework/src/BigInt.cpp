#include "../include/BigInt.hpp"
#include <string.h>

BigInt::BigInt(const char* numberchar)  {
    
    number_length = strlen(numberchar) ;

    number = new char[number_length] ;

    size_t i = 0 ;

    while (i < number_length && numberchar[i] > 0 )
         {
            number[i] = numberchar[i];
            i++;
            pos = false ;
        }

    if (i < number_length ) throw std::invalid_argument("bad and signed content") ;

    number_length = i ;

    bigNumber = std::stoi(numberchar) ;

}