#include <iostream>
#include <string>

using namespace std;

unsigned char original_text[] = "Team Swift";
unsigned char original_pattern[] = "if";

unsigned char *simple_search(unsigned char* text, unsigned char* pattern) {
    int i;
    while ((*text) != '\0') {
        cout << endl;
        cout << original_text << endl;
        for (i = 0; i < text - original_text; i++) {
            cout << " ";
        }
        cout << pattern;
        for (i = 0; pattern[i] != '\0'; i++) {
            if (pattern[i] != text[i])
                break;
        }
        if (pattern[i] == '\0')
            return text;
        text++;
    }
    return NULL;
}


int main() {
    unsigned char *result;
    result = simple_search(original_text, original_pattern);
    if (result == NULL) {
        cout << endl << "NOT Found" << endl;
    } else {
        cout << " -> Found" << endl;
    }
    return 0;
}
