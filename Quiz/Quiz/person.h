#pragma once

class Person
{
    string _name;
    string _surname;
    string _username;
    string _password;
public:

    void setName(string name) { _name = name; }
    void setSurname(string surname) { _surname = surname; }
    void setUsername(string username) {
        if (username.size() > 3)_username = username;
        else throw exception("Username invalid");
    }
    void setPassword(string password) {
        if (password.size() > 8)_password = password;
        else throw exception("Password invalid");
    }
    string getName()const { return _name; }
    string getUsername()const { return _username; }
    string getPassword()const { return _password; }
    string getSurname()const { return _surname; }
    void writeFile(string fileName) {
        ofstream file(fileName.c_str(), ios::app);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        file << _username << "-" << _password << "-" << _name << "-" << _surname << "-" << endl;
        file.close();
    }
    bool fileCheck(string username, string password, string fileName, bool forLogin) {
        ifstream file(fileName.c_str(), ios::in|ios::app);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        while (!file.eof()) {
            string data;
            getline(file, data, '-');
            if (data == username) {
                getline(file, data, '-');
                if (data == password && forLogin) {
                    getline(file, data, '-');
                    this->setName(data);
                    getline(file, data, '-');
                    this->setSurname(data);
                    return true;
                }
                else if (data == password && !forLogin) return false;
                else if (data != password && !forLogin) return true;
            }
            else getline(file, data);
        }
        file.close();
        if (!forLogin) return true;
        return false;

    }
    void register_(bool isAdmin) {
        system("cls");
        string name, surname, username, password;
        try {
            cout << "Enter Name: ";
            getline(cin, name);
            this->setName(name);
            cout << "Enter Surname: ";
            getline(cin, surname);
            this->setSurname(surname);
            cout << "Enter Username: ";
            getline(cin, username);
            this->setUsername(username);
            cout << "Enter Password: ";
            getline(cin, password);
            this->setPassword(password);

            if (isAdmin) {
                if (fileCheck(username, password, "admins.txt", false)) {
                    writeFile("admins.txt");
                }
                else throw exception("This user already exists");
            }
            else { 
                if (fileCheck(username, password, "players.txt", false)) writeFile("players.txt"); 
                else throw exception("This user already exists");
            }
        }
        catch (const exception& ex) {
            cout << ex.what() << endl;
            return;
        }
    }
    bool login(bool isAdmin) {
        string username, password;
        try {
            cout << "Enter Username: ";
            getline(cin, username);
            this->setUsername(username);
            cout << "Enter Password: ";
            getline(cin, password);
            this->setPassword(password);
            if (isAdmin) {
                return fileCheck(username, password, "admins.txt", true);
            }
            else return fileCheck(username, password, "players.txt", true);
            system("cls");
        }
        catch (const exception& ex) {
            cout << ex.what() << endl;
            return false;
        }
        
    }
    friend ostream& operator<<(ostream& print, const Person& p) {
        print << "Name: " << p._name << endl;
        print << "Surname: " << p._surname << endl;
        print << "Username: " << p._username << endl;
        print << "Password: " << p._password << endl;
        return print;
    }
    void showLeaderBoard() {
        ifstream file("Statistics.txt", ios::in | ios::app);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        map<string, list<double>>playerStats; // password and its scores' sum
        while (!file.eof()) {
            string password,empty,score,username;
            getline(file, username, ':'); // username oxuma
            getline(file, empty, ';'); // score -a kimi pass
            getline(file, score); // score oxuma
            if(username!="")playerStats[username].push_back(stoi(score)); // score-u elave etdi
        }
        map<double, string>totalScores;
        for (auto& i : playerStats)
        {
            int total = 0;
            for (auto& j :i.second) {total += j;}
            totalScores[total] = i.first;
        }
        int counter = 1;
        cout << "\n\n\n";
        for (auto i = totalScores.rbegin(); i != totalScores.rend(); i++) {cout << "\t\t\t\t\t" << counter++ << ")\t" << (* i).first << " " << (*i).second << endl;}
    };
};



class Admin :public Person {
public:

    void createQuiz() {
        try {
            system("cls");
            string quizName;
            vector<Question*>allquestions;
            int questioncount;
            cout << "Enter quiz name:";
            getline(cin, quizName);
            cout << "Enter question count:";
            cin >> questioncount;
            cin.ignore();
            for (size_t i = 0; i < questioncount; i++)
            {
                string question, correctAnswer;
                vector<string>wrongAnswers;
                cout << "Enter question: ";
                getline(cin, question);
                cout << "Enter correct answer: ";
                getline(cin, correctAnswer);
                for (size_t j = 0; j < 3; j++)
                {
                    string data;
                    cout << "Enter wrong answer: ";
                    getline(cin, data);
                    if (data == correctAnswer || count(begin(wrongAnswers),end(wrongAnswers),data)!=0) throw exception("Answers can't be repeated");
                    wrongAnswers.push_back(data);
                }
                Question* newQuestion = new Question(question, correctAnswer, wrongAnswers);
                allquestions.push_back(newQuestion);
            }
            Quiz newQuiz(quizName, allquestions, questioncount);
        }
        catch (const exception& ex) {
            cout << ex.what() << endl;
            return;
        }
        
    }
};






class Player:public Person
{
    double _score;
public:
    Player() = default;
    void setScore(int score) { _score = score; }
    int getScore() const { return _score; }

    bool readPlayedQuizs(string __quizName) {
        ifstream file("PlayedQuizs.txt", ios::in|ios::app);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        while(!file.eof()) {
            string quizName,password;
            getline(file, quizName, ':');
            getline(file, password, ':');
            if (quizName == __quizName && password == getPassword()) return true;
        }
        return false;
        file.close();
    }
    void writePlayedQuizs(string quizName) {
        ofstream file("PlayedQuizs.txt", ios::app|ios::out);
        if (!file) throw exception("File not created");
        if (!file.is_open()) throw exception("File not opened");
        file << quizName << ":" << getPassword()<<":" << endl;
        file.close();
    }


    void playQuiz(string quizName) {
        if (readPlayedQuizs(quizName)) throw exception("You already played this quiz");
        
        Quiz* newQuiz = new Quiz();
        try {
            newQuiz->setFromFile(quizName);
        }catch (const exception& ex) { 
            cout << ex.what() << endl;
            system("cls");
            return; 
        }
        
        newQuiz->setQuizName(quizName);
        int questionCount = 1;
        vector <string>allAnswers;
        
        auto questions = newQuiz->getQuestions();
        auto iterator = begin(questions);

        while (true) {


            allAnswers = (*iterator)->getwrongAnswers();
            allAnswers.push_back(((*iterator)->getQuestion_Answer().second));
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(begin(allAnswers), end(allAnswers), default_random_engine(seed));

            // Showing the questions


            gotoxy(50, 8);
            cout << questionCount << ")" << (*iterator)->getQuestion_Answer().first << endl;
            int PlayerChoice = Interface(&allAnswers, true);
            if (PlayerChoice <= 4) { // One of the answers
                if ((*iterator)->getisSubmitted()) { // Question is Already Answered
                    continue;
                }
                (*iterator)->setisSubmitted(true);
                if (allAnswers[PlayerChoice - 1] == (*iterator)->getQuestion_Answer().second) { // True Answer
                    newQuiz->setTrueCount(newQuiz->getTrueCount() + 1);
                }
                else
                {
                    newQuiz->setFalseCount(newQuiz->getFalseCount() + 1); // False Answer
                }
                if ((*iterator) == newQuiz->getQuestions().back()) break;
                iterator++;
                questionCount++;
            }
            else {
                if (allAnswers[PlayerChoice - 1] == "Previous") {
                    if ((*iterator) != newQuiz->getQuestions().front()) {
                        iterator--;
                        questionCount--;
                    }
                }
                else { // Next
                    if ((*iterator) != newQuiz->getQuestions().back()) {
                        iterator++;
                        questionCount++;
                    }
                    else break;
                }
                

                
            }
        }
        if (newQuiz->getTrueCount() + newQuiz->getFalseCount() != newQuiz->getQuestionCount()) newQuiz->setPassCount(newQuiz->getQuestionCount()-(newQuiz->getTrueCount() + newQuiz->getFalseCount()));
        setScore(100 / newQuiz->getQuestionCount() * newQuiz->getTrueCount());
        cout << "Quiz Result" << endl;
        cout << "True: " << newQuiz->getTrueCount() << endl;
        cout << "False: " << newQuiz->getFalseCount() << endl;
        cout << "Pass: " << newQuiz->getPassCount() << endl;
        cout << "Total Score: 100/" << _score << endl;
        writePlayedQuizs(quizName);
        
        [=]()->void {
            ofstream file("Statistics.txt", ios::app);
            if (!file) throw exception("File not created");
            if (!file.is_open()) throw exception("File not opened");
            file << getUsername() << ":" << getPassword() << ":" << newQuiz->getQuizName() << ":" << newQuiz->getFalseCount() <<":" << newQuiz->getTrueCount()<<":" << newQuiz->getPassCount() << ";" << getScore() << "-\n";
        }();
        system("pause");
        system("cls");
    }
};
