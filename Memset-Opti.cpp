#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>
using namespace std;
using namespace chrono;

string alphabet = "abc";
int k = alphabet.size();

vector<vector<char>> multiplicationTable = {{'c', 'c', 'b'},
                                             {'a', 'c', 'b'}, 
                                             {'b', 'a', 'a'}};

// Memoization table to store already computed results
unordered_map<string, unordered_map<char, int>> memo;

/* Recursive function that returns 1 if it is 
 * possible to get symbol from 
 * string s of length n. 
 */
int isSymbolPossible(const string& s, char symbol, int n) {
    if (n == 1) {
        return s[0] == symbol;
    }

    // Check if the result is already computed
    if (memo[s].count(symbol)) {
        return memo[s][symbol];
    }

    /* Loop over all possible ways to split the string in two. */
    for (int i = 0; i < n - 1; i++) {
        /* For each such subdivision, find all the multiplications that yield the desired symbol */
        for (int j1 = 0; j1 < k; j1++) {
            for (int j2 = 0; j2 < k; j2++) {
                if (multiplicationTable[j1][j2] == symbol) {
                    /* Check if it is possible to get the required left and right symbols for this multiplication */
                    if (isSymbolPossible(s.substr(0, i + 1), alphabet[j1], i + 1) &&
                        isSymbolPossible(s.substr(i + 1), alphabet[j2], n - i - 1)) {
                        // Memoize the result
                        memo[s][symbol] = 1;
                        return 1;
                    }
                }
            }
        }
    }

    // Memoize the result
    memo[s][symbol] = 0;
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

    cout << "Runtime: " << duration.count() << " microseconds" << endl;
    return 0;
}

