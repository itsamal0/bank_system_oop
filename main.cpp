#include <iostream>
#include "ClsBankClient.h"

int main() {

    ClsBankClient Client1 = ClsBankClient::find("A101");

    if (!Client1.isEmpty())
        cout << "\nClient 1 Found :-)\n";
    
    else
        cout << "\nClient 1 Was not Found :-(\n";

    Client1.print();     
    
    ClsBankClient Client2 = ClsBankClient::find("A102", "1234");

    if (!Client2.isEmpty())
        cout << "\nClient 2 Found :-)\n";

    else
        cout << "\nClient 2 Was not Found :-(\n";

    Client2.print(); 
    
    cout << "\nIs Client A102 Exist? "<< ClsBankClient::isClientExist("A102");

    system("pause>0");
    return 0;
}