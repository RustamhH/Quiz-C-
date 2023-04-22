#pragma once


class Quiz
{
    string quizName;
    vector<Question*>questions;
    int trueCount;
    int falseCount;
    int passCount;
    int questionCount;
public:
    Quiz() = default;
    Quiz(string name, vector<Question*>questions, int questionCount) :quizName(name), questions(questions), questionCount(questionCount) { writeFile(); }
    void setQuizName(string name) { quizName = name; }
    void setQuestions(vector<Question*>questions) { this->questions = questions; }
    void setTrueCount(int count) { trueCount = count; }
    void setFalseCount(int count) { falseCount = count; }
    void setPassCount(int count) { passCount = count; }
    void setQuestionCount(int count) { questionCount = count; }

    string getQuizName()const { return quizName; }
    vector<Question*> getQuestions()const { return questions; }
    int getTrueCount()const { return trueCount; }
    int getFalseCount()const { return falseCount; }
    int getPassCount()const { return passCount; }
    int getQuestionCount()const { return questionCount; }


    void writeFile() {
        ofstream file(quizName.c_str(), ios::app);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        file << questionCount << endl;
        for (auto& i : questions)
        {
            file << i->getQuestion_Answer().first << endl << i->getQuestion_Answer().second << endl;
            for (auto& j : i->getwrongAnswers())
            {
                file << j << "-";
            }
            if(i!=questions.back()) file << endl<<endl;
        }
        file.close();
        // Quiz Name to the quizname.txt file
        ofstream file2("Quiz Names.txt", ios::app);
        if (!file2) throw exception("File not created");
        if (!file2.is_open()) throw exception("File not opened");
        file2 << quizName<<endl;
        file2.close();
    }
    void setFromFile(string chosenQuiz) {
        ifstream file(chosenQuiz.c_str(), ios::in);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        string questionCount;
        getline(file, questionCount);
        while (!file.eof()) {
            string question, correctAnswer, wrongAnswer, empty;
            vector<string>wrongAnswers;
            getline(file, question);
            getline(file, correctAnswer);
            for (size_t i = 0; i < 3; i++)
            {
                getline(file, wrongAnswer, '-');
                wrongAnswers.push_back(wrongAnswer);
            }
            questions.push_back(new Question(question, correctAnswer, wrongAnswers));
            getline(file, empty);
            getline(file, empty);
        }
        setQuestionCount(stoi(questionCount));
        file.close();
    }
};