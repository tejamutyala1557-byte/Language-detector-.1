# 🌍 Language Detector (C++)

A simple yet efficient **Language Detection System** built in **C++** that identifies the language of an input sentence using word-frequency dictionaries and approximate string matching (Levenshtein Distance).

## 📌 Features

- Detects the language of user input.
- Supports multiple languages through dictionary files.
- Uses **word frequency analysis** for accurate detection.
- Implements **Levenshtein Edit Distance** to handle spelling mistakes.
- Easily extensible by adding new dictionary files.
- Built using modern **C++17** features.

---

## 🛠 Technologies Used

- C++17
- STL (Standard Template Library)
- File Handling
- Hash Maps (`unordered_map`)
- Dynamic Programming
- Filesystem Library

---

## 📂 Project Structure

```
LanguageDetector/
│
├── language_detector.cpp
├── dictionaries/
│   ├── english.txt
│   ├── hindi.txt
│   └── (more languages can be added)
│
└── README.md
```

---

## ⚙️ How It Works

1. Loads all dictionary files from the `dictionaries` folder.
2. Each dictionary contains words with their frequency.
3. User enters a sentence.
4. The sentence is tokenized and converted to lowercase.
5. Each word is compared with dictionary words.
6. If an exact match is found:
   - High score is awarded.
7. Otherwise:
   - Levenshtein Distance is calculated.
   - Similar words receive a small score.
8. The language with the highest total score is displayed.

---

## 🚀 Compilation

Compile using **g++** with C++17 support.

```bash
g++ language_detector.cpp -std=c++17 -o detector
```

Run the program:

```bash
./detector
```

On Windows (MinGW):

```bash
g++ language_detector.cpp -std=c++17 -o detector.exe
detector.exe
```

---

## 📥 Sample Input

```
Enter a sentence:
How are you today?
```

### Output

```
Detected Language: english
```

---

### Sample Input

```
आप कैसे हैं
```

### Output

```
Detected Language: hindi
```

---

## 📖 Algorithm

### Exact Match

- Searches each word directly in the language dictionary.
- Matching words receive a large score based on frequency.

### Approximate Match

If an exact match isn't found, the program computes the **Levenshtein Edit Distance**.

- Distance = 0 → Exact match
- Distance = 1 → Very similar
- Distance = 2 → Slight spelling error

This helps detect languages even when the user makes minor typing mistakes.

---

## ➕ Adding a New Language

1. Create a new text file inside the `dictionaries` folder.

Example:

```
spanish.txt
```

2. Store words in the format:

```
hola 5000
gracias 3000
como 2500
```

3. Run the program again.

The new language will automatically be loaded.

---

## 📊 Time Complexity

Let:

- **N** = Number of input words
- **L** = Number of languages
- **W** = Number of words in each dictionary

| Operation | Complexity |
|----------|------------|
| Tokenization | O(N) |
| Exact Matching | O(N × L) |
| Approximate Matching | O(N × L × W) |

---

## 🎯 Future Improvements

- Add more language dictionaries.
- Improve detection using n-grams.
- Support mixed-language sentences.
- Add GUI using Qt.
- Train using larger language corpora.
- Export detection confidence scores.

---

## 👨‍💻 Author

**Teja Mutyala**

Engineering Physics Student

---

## ⭐ If you found this project useful, don't forget to star the repository!
