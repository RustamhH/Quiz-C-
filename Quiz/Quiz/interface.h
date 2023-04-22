#pragma once


void color(int color) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);}
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int Interface(vector<string>*options,bool forQuiz=false) {
    if (options->size() == 0) throw exception("No Quiz");
    if (forQuiz) {
        options->push_back("Next");
        options->push_back("Previous");
    }
    char key;
    int color1 = 112, color2 = 7,center=52;
    vector<int> Set {color1};
    for (size_t i = 1; i < options->size(); i++){Set.push_back(color2);}
    int counter = 1;
    while (true) {
        int count = 10,j=0;
        for (auto& i : *options)
        {
            color(Set[j++]);
            gotoxy(center - ((i.size() / 2) - 1), count++);
            cout << i;
            
        }
        key = _getch();
        if (key == 72 && (counter > 1 && counter < (options->size() + 1))) counter--;
        if (key == 80 && (counter > 0 && counter < options->size())) counter++;
        if (key == '\r') break;
        for (size_t i = 0; i < options->size(); i++) { Set[i] = color2; }
        for (size_t i = 1; i <= options->size(); i++) { if (counter == i) Set[i-1] = color1; }
    }
    color(7);
    system("cls");
    return counter;
}