#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <direct.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <list>
using namespace std;

class Question
{
    pair<string, string>Question_Answer;
    vector<string>wrongAnswers;
    bool isSubmitted=false;
public:
    Question(string question, string correctanswer, vector<string>wrongAnswers) :wrongAnswers(wrongAnswers) { Question_Answer.first = question; Question_Answer.second = correctanswer; }
    pair<string, string>getQuestion_Answer() const { return Question_Answer; }
    vector<string>getwrongAnswers()const { return wrongAnswers; }
    void setisSubmitted(bool s) { isSubmitted = s; }
    bool getisSubmitted() { return isSubmitted; }
    
};

#include "interface.h"
#include "quiz.h"
#include "person.h"



// Quiz Names

vector<string> QuizNamesFile() {
    vector<string>QuizNames;
    ifstream file("Quiz Names.txt", ios::in);
    if (!file) throw exception("File not created");
    if (!file.is_open()) throw exception("File not opened");
    while (!file.eof()) {
        string data;
        getline(file, data);
        if(data!="") QuizNames.push_back(data);
    }
    file.close();
    return QuizNames;
}



int main()
{

    // Main Flow

    while (true) {
    start:
        vector<string> au{ "Admin", "User" };
        int choice = Interface(&au);
        if (choice == 1) {
            // Admin Page
            vector<string> lr {"Login", "Register"} ;
            int choice1 = Interface(&lr);
            Admin a;
            if (choice1 == 1) {
                a.login(true);
                system("cls");
                vector<string>q{ "Create Quiz", "Show Leader Board" };
                int choice2 = Interface(&q);
                if (choice2 == 1) a.createQuiz();
                else a.showLeaderBoard();
            }
            else {
                a.register_(true);
                system("pause");
            }
        }
        else {
            // Player Page
            vector<string> lrp{ "Login", "Register" };
            int choice1 = Interface(&lrp);
            Player p;
            if (choice1 == 1) {
                if (!p.login(false)) {
                    system("pause");
                    goto start;
                }
                system("cls");
                vector<string> pql{ "Play Quiz", "Show Leader Board" };
                int choice2 = Interface(&pql);
                if (choice2 == 1) {
                    try {
                        vector<string>qnf = QuizNamesFile();
                        int choice3 = Interface(&qnf);
                        p.playQuiz(QuizNamesFile()[choice3 - 1]);
                    }catch (const exception& ex) { 
                        cout << ex.what() << endl;
                        system("pause");
                        system("cls");
                    }
                }
                else {
                    p.showLeaderBoard();
                    system("pause");
                }
            }
            else {
                p.register_(false);
                system("pause");
            }
        }
    }
}

