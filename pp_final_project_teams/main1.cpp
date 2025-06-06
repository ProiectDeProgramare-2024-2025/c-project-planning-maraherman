#include "include/QuizGame.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "✅ Hello from main!" << std::endl;

    if (argc < 2) {
        cerr << "Use --menu, --play, --leaderboard, --history, or add." << endl;
        return 1;
    }

    string mode = argv[1];
    QuizGame game;

    if (mode == "--menu") {
        cout << "--play --q=1 --name=Giulia --use5050=0 --answer=0" << endl;
        cout << "--leaderboard\n--history --name=Giulia\nadd <q> <o1> <o2> <o3> <o4> <correct>" << endl;
        return 0;
    }

    if (mode == "--leaderboard") {
        game.viewLeaderboard();
        return 0;
    }

    if (mode == "--history") {
        string name;
        for (int i = 2; i < argc; ++i) {
            if (strncmp(argv[i], "--name=", 7) == 0)
                name = argv[i] + 7;
        }
        if (name.empty()) {
            cerr << "--name required." << endl;
            return 1;
        }
        game.viewGameHistory(name);
        return 0;
    }

    if (mode == "add" && argc == 8) {
        string question = argv[2];
        vector<string> options = {argv[3], argv[4], argv[5], argv[6]};
        int correctIndex;
        try {
            correctIndex = stoi(argv[7]);
        } catch (...) {
            cerr << "Invalid correct option index." << endl;
            return 1;
        }
        game.addQuestion(question, options, correctIndex);
        return 0;
    }

    if (mode == "--play") {
        string name;
        int qNum = -1, answer = -1;
        bool use5050 = false;

        for (int i = 2; i < argc; ++i) {
            if (strncmp(argv[i], "--name=", 7) == 0) name = argv[i] + 7;
            else if (strncmp(argv[i], "--q=", 4) == 0) qNum = stoi(argv[i] + 4);
            else if (strncmp(argv[i], "--answer=", 9) == 0) answer = stoi(argv[i] + 9);
            else if (strncmp(argv[i], "--use5050=", 10) == 0) use5050 = stoi(argv[i] + 10) == 1;
        }

        if (name.empty() || qNum < 1 || answer < 0 || answer > 4) {
            cerr << "Missing or invalid arguments." << endl;
            return 1;
        }

        float score = game.loadCurrentScore(name);
        if (!game.askQuestionFromArgs(qNum, name, answer, use5050, score)) {
            if (answer != 0) game.saveScore(name, score);
        } else if (answer != 0) {
            game.saveProgress(name, score);
            cout << "Continue with: ./main1 --play --q=" << (qNum + 1)
                 << " --name=" << name << " --use5050=0 --answer=0" << endl;
        }
        return 0;
    }

    cerr << "Unknown command." << endl;
    return 1;
}
