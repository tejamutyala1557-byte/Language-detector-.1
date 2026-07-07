#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <limits>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Type aliases
using WordFreqMap = unordered_map<string, int>;
using LanguageDict = unordered_map<string, WordFreqMap>;

// Lowercase conversion
string toLower(const string& s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

// Tokenize input string
vector<string> tokenize(const string& line) {
    istringstream iss(line);
    string word;
    vector<string> words;
    while (iss >> word) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        if (word.length() > 1)
            words.push_back(toLower(word));
    }
    return words;
}

// Levenshtein Distance (DP)
int editDistance(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
        }
    }
    return dp[m][n];
}

// Load all dictionaries from directory
LanguageDict loadDictionaries(const string& dir) {
    LanguageDict langDict;
    for (const auto& entry : fs::directory_iterator(dir)) {
        string filename = entry.path().filename().string();
        string langName = filename.substr(0, filename.find(".txt"));
        ifstream file(entry.path());
        string word;
        int freq;
        WordFreqMap wordFreq;
        while (file >> word >> freq) {
            wordFreq[toLower(word)] = freq;
        }
        langDict[langName] = wordFreq;
    }
    return langDict;
}

// Detect language of input string
string detectLanguage(const string& input, const LanguageDict& langDict) {
    vector<string> inputWords = tokenize(input);
    unordered_map<string, int> scores;

    for (const auto& word : inputWords) {
        for (const auto& [lang, dict] : langDict) {
            if (dict.find(word) != dict.end()) {
                scores[lang] += 10 + dict.at(word); // exact match boost
            } else {
                // Try edit distance up to 2
                int bestDist = 3;
                for (const auto& [dictWord, freq] : dict) {
                    int dist = editDistance(word, dictWord);
                    if (dist <= 2 && dist < bestDist) {
                        scores[lang] += 3 - dist; // small boost for close match
                        bestDist = dist;
                    }
                }
            }
        }
    }

    string bestLang;
    int maxScore = -1;
    for (const auto& [lang, score] : scores) {
        if (score > maxScore) {
            maxScore = score;
            bestLang = lang;
        }
    }
    return bestLang;
}

int main() {
    cout << "Loading language dictionaries...\n";
    LanguageDict langDict = loadDictionaries("dictionaries");
    cout << "Loaded " << langDict.size() << " languages.\n";

    string input;
    cout << "Enter a sentence: ";
    getline(cin, input);

    string detected = detectLanguage(input, langDict);
    cout << "\nDetected Language: " << detected << endl;
    return 0;
}
