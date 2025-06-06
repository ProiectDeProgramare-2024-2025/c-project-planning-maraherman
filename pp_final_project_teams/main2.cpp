#include "include/QuizGame.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Use --leaderboard, --history, or add." << endl;
        return 1;
    }

    string mode = argv[1];
    QuizGame game;

    if (mode == "--leaderboard") {
        if (argc > 2) {
            cerr << "Too many arguments for --leaderboard." << endl;
            return 1;
        }
        game.viewLeaderboard();
        return 0;
    }

    if (mode == "--history") {
        string name;
        for (int i = 2; i < argc; ++i) {
            if (strncmp(argv[i], "--name=", 7) == 0)
                name = argv[i] + 7;
            else {
                cerr << "Unknown argument: " << argv[i] << endl;
                return 1;
            }
        }
        if (name.empty()) {
            cerr << "--name required." << endl;
            return 1;
        }
        game.viewGameHistory(name);
        return 0;
    }

    if (mode == "add") {
        if (argc != 8) {
            cerr << "Usage: add <question> <opt1> <opt2> <opt3> <opt4> <correctIndex>" << endl;
            return 1;
        }

        string question = argv[2];
        vector<string> options = {argv[3], argv[4], argv[5], argv[6]};
        int correctIndex;

        try {
            correctIndex = stoi(argv[7]);
        } catch (...) {
            cerr << "Invalid correct option index." << endl;
            return 1;
        }

        if (correctIndex < 0 || correctIndex > 3) {
            cerr << "Correct index must be between 0 and 3." << endl;
            return 1;
        }

        game.addQuestion(question, options, correctIndex);
        return 0;
    }

    cerr << "Unknown command." << endl;
    return 1;
}
