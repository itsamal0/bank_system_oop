#include <iostream>
#include "ClsLoginScreen.h"

int main() {
    
    while (true) {

        if (!ClsLoginScreen::showLoginScreen()) 
            break;
    }
    
    system("pause>0");
    return 0;
}