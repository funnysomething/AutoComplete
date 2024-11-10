#include "autocomplete.cpp"
#include <iostream>
using namespace std;


int main()
{   
    AutoComplete test;
    string text;
    while (true){
        cout << ">> ";
        cin >> text;
        auto suggestions = test.get_suggestions(text);
        for (int i = 0; i < 5 && i < suggestions.size(); i++){
            cout << suggestions[i] << '\n';
        }
    }
}
