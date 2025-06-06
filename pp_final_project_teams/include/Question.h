#pragma once

#include <string>
#include <vector>

struct Question {
    std::string question;
    std::vector<std::string> options;
    int correctOption;

    Question(const std::string& q, const std::vector<std::string>& opts, int correct)
        : question(q), options(opts), correctOption(correct) {}
};

struct LeaderboardEntry {
    std::string name;
    float score;

    LeaderboardEntry(const std::string& n, float s) : name(n), score(s) {}
};
