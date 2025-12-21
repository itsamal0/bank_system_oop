#include <iostream>
#include "Screens\Login\ClsLoginScreen.h"

int main() {
    
    while (true) {

        if (!ClsLoginScreen::showLoginScreen()) 
            break;
    }
    
    system("pause>0");
    return 0;
}