#include "QuizGame.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

const string COLOR_RESET = "\x1b[0m";
const string COLOR_GREEN = "\x1b[32m";
const string COLOR_YELLOW = "\x1b[33m";
const string COLOR_RED = "\x1b[31m";

QuizGame::QuizGame() {
    loadQuestions();
}

void QuizGame::loadQuestions() {
    questions.clear();
    ifstream file("questions.txt");
    string line;
    while (getline(file, line)) {
        string q = line;
        vector<string> opts;
        for (int i = 0; i < 4 && getline(file, line); ++i)
            opts.push_back(line);
        if (!getline(file, line)) break;
        try {
            int correct = stoi(line);
            questions.emplace_back(q, opts, correct);
        } catch (...) {
            cerr << "Invalid correct answer format. Skipping question.\n";
        }
    }
}

float QuizGame::loadCurrentScore(const string& name) {
    ifstream inFile(name + "_session.txt");
    float score = 0;
    if (inFile) inFile >> score;
    return score;
}

void QuizGame::saveProgress(const string& name, float score) {
    ofstream outFile(name + "_session.txt");
    if (outFile) outFile << score;
}

void QuizGame::saveScore(const string& name, float score) {
    ofstream leaderboardFile("leaderboard.txt", ios::app);
    leaderboardFile << name << " " << score << "\n";

    ofstream outputFile("output.txt");
    time_t now = time(nullptr);
    outputFile << "Player: " << name << "\nScore: " << score << "\nDate: " << ctime(&now);

    remove((name + "_session.txt").c_str());
}

bool QuizGame::askQuestionFromArgs(int index, const string& name, int answer, bool use5050, float& score) {
    if (index < 1 || index > questions.size()) {
        cout << COLOR_RED << "No more questions." << COLOR_RESET << endl;
        return false;
    }
    const Question& q = questions[index - 1];

    vector<bool> remainingOptions(4, true);
    if (use5050) {
        int removed = 0;
        for (int i = 0; i < 4; ++i) {
            if (i != q.correctOption && removed < 2) {
                remainingOptions[i] = false;
                removed++;
            }
        }
    }

    cout << COLOR_YELLOW << "Question " << index << ": " << q.question << COLOR_RESET << endl;
    for (int i = 0; i < 4; ++i) {
        if (remainingOptions[i])
            cout << (i + 1) << ". " << q.options[i] << endl;
    }

    if (answer == 0) {
        cout << "To answer, use: ./quiz --play --q=" << index
             << " --name=" << name << " --use5050=" << (use5050 ? 1 : 0)
             << " --answer=<1-4>" << endl;
        return true;
    }

    if (answer < 1 || answer > 4 || !remainingOptions[answer - 1]) {
        cout << COLOR_RED << "Invalid answer." << COLOR_RESET << endl;
        return false;
    }

    if (answer - 1 == q.correctOption) {
        cout << COLOR_GREEN << "Correct!" << COLOR_RESET << endl;
        score += use5050 ? 0.5f : 1.0f;
        return true;
    } else {
        cout << COLOR_RED << "Wrong! Correct was: " << q.options[q.correctOption] << COLOR_RESET << endl;
        return false;
    }
}

void QuizGame::viewLeaderboard() {
    leaderboard.clear();
    ifstream file("leaderboard.txt");
    string name;
    float score;
    while (file >> name >> score)
        leaderboard.emplace_back(name, score);

    sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
        return a.score > b.score;
    });

    for (const auto& entry : leaderboard)
        cout << COLOR_YELLOW << entry.name << COLOR_RESET << " - " << entry.score << " pts\n";
}

void QuizGame::viewGameHistory(const string& name) {
    ifstream file("leaderboard.txt");
    string entryName;
    float score;
    bool found = false;
    while (file >> entryName >> score) {
        if (entryName == name) {
            found = true;
            cout << COLOR_YELLOW << entryName << COLOR_RESET << " - " << score << " pts\n";
        }
    }
    if (!found) {
        cout << COLOR_RED << "No records for " << name << "." << COLOR_RESET << endl;
    }
}

void QuizGame::addQuestion(const string& question, const vector<string>& options, int correctIndex) {
    ofstream outFile("questions.txt", ios::app);
    outFile << question << "\n";
    for (auto& o : options) outFile << o << "\n";
    outFile << correctIndex << "\n";
    cout << "Question added." << endl;
}
