#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

string alphabet = "abc";
int k = alphabet.size();

vector<vector<char>> multiplicationTable = {{'c', 'c', 'b'},
                                             {'a', 'c', 'b'}, 
                                             {'b', 'a', 'a'}};

/* Recursive function that returns 1 if it is 
 * possible to get symbol from 
 * string s of length n. 
 */
int isSymbolPossible(const string& s, char symbol, int n, int level = 0) {
    int i, j1, j2;
    if (n == 1) {
        //cout << string(level, ' ') << "Reached base case: s = " << s << ", symbol = " << symbol << ", n = " << n << endl;
        //bool res = (s[0] == symbol);
        //cout<<"Result in base case is:"<<res<<endl;
        return s[0] == symbol;  // Use s[0] instead of *s
    }

    //cout << string(level, ' ') << "Entering recursion: s = " << s << ", symbol = " << symbol << ", n = " << n << endl;

    /* Loop over all possible ways to split the string in two. */
    for (i = 0; i < n - 1; i++) {
        /* For each such subdivision, find all the multiplications that yield the desired symbol */
        for (j1 = 0; j1 < k; j1++) {
            for (j2 = 0; j2 < k; j2++) {
                if (multiplicationTable[j1][j2] == symbol) {
                    /* Check if it is possible to get the required left and right symbols for this multiplication */
                    //cout << string(level, ' ') << "Trying multiplication: " << alphabet[j1] << " * " << alphabet[j2] << " = " << symbol << endl;
                    if (isSymbolPossible(s.substr(0, i + 1), alphabet[j1], i + 1, level + 1) &&
                        isSymbolPossible(s.substr(i + 1), alphabet[j2], n - i - 1, level + 1)) {
                        cout << string(level*4, ' ') << "Trying multiplication: " << alphabet[j1] << " * " << alphabet[j2] << " = " << symbol << endl;
                        cout << string(level*4, ' ') << "Found a valid split!" << endl;
                        return 1;
                    }
                }
            }
        }
    }

    cout << string(level*4, ' ') << "No valid split found for s = " << s << ", symbol = " << symbol << ", n = " << n << endl;
    return 0;
}

int main() {
    string s;
    cout << "Enter the String" << endl;
    cin >> s;
    int N = s.size();

    auto start_time = high_resolution_clock::now(); // Start the timer

    if (isSymbolPossible(s, 'a', N,0)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    auto end_time = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<microseconds>(end_time - start_time); // Calculate the runtime in microseconds

    // cout << "Runtime: " << duration.count() << " microseconds" << endl;
    return 0;
}

