#include <iostream>

#define CLR_RESET "\033[0m"
#define CLR_RED "\033[1;31m"
#define CLR_GREEN "\033[1;32m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_BLUE "\033[1;34m"
#define CLR_CYAN "\033[1;36m"
#define CLR_WHITE "\033[1;37m"

/**
 * @param color ASCII Color code, can selecting with above
 * @param x Text input source
 */
#define LOG(color, x) std::cout << color << x << CLR_RESET << std::endl;
