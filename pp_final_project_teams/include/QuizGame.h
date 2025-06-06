#pragma once
#include <string>
#include <vector>
#include "Question.h"

class QuizGame {
private:
    std::vector<Question> questions;
    std::vector<LeaderboardEntry> leaderboard;

public:
    QuizGame();

    void loadQuestions();
    float loadCurrentScore(const std::string& name);
    void saveProgress(const std::string& name, float score);
    void saveScore(const std::string& name, float score);
    bool askQuestionFromArgs(int index, const std::string& name, int answer, bool use5050, float& score);
    void viewLeaderboard();
    void viewGameHistory(const std::string& name);
    void addQuestion(const std::string& question, const std::vector<std::string>& options, int correctIndex);
};
