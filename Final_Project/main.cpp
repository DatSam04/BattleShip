#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include "Human.cpp"
#include "Computer.cpp"
using namespace std;

void PrintMenu(){
    cout << "Option MENU:\n";
    cout << "f - to fire to the enemy battle grid\n";
    cout << "p - to print the enemy table\n";
    cout << "r - to print remaining ships of both sides\n";
    cout << "c - to get the computer ship's position(cheated mode)\n";
    cout << "q - to quit\n\n";
}

bool FiringGrid(string move){
    int size = move.size();
    char firstLetter = move.at(0);
    int number;
    if (firstLetter - 'A' < 0 || firstLetter - 'A' > 9) {
        return false;
    }
    if (size == 2) {
        char secondLetter = move.at(1);
        if (secondLetter - '1' < 0 || secondLetter - '1' > 8) {
            return false;
        }
    } else if (size == 3) {
        string s = move.substr(1,2);
        if (s != "10") {
            return false;
        }
    }
    return true;
}

int main(){
    Computer Bot;
    char choice;
    string move, file;

    cout << right << setw(15) << "----";
    cout << "BATTLESHIP----" << endl;
    cout << "Welcome to battlship, you will play with a computer.\n";
    again:cout << "Enter your input file:\n";
    getline(cin, file);
    cout << endl;

    //"ship_placement.csv"
    Human player = Human(file);
    if(!player.ShipChecked()){
        goto again;
    }else{
        cout << "SetPosition\n";
        player.SetPosition();
    }
    if(!player.PositionChecked()){
        goto again;
    }
    Bot.InputShip();
    PrintMenu();
    do{
        cout <<"Enter your option:";
        cin >> choice;
        cout << endl;
        if(choice == 'q'){
            break;
        }else if(choice == 'p'){
            Bot.PrintBattleGrid();
        }else if(choice == 'f'){
            start:cout << "Enter your move:";
            cin >> move;
            if(FiringGrid(move) == false){
                cout << "Invalid input.\n";
                goto start;
            }
            Bot.IsHitted(move);
            cout << endl;
            if(Bot.IsLost()){
                cout << "Computer lost\n";
                goto here;
            }

            cout << "Computer Turn!" << endl;
            move = Bot.Fire();
            cout << "It fires at " << move << endl;
            player.IsHitted(move);
            if(move.size() > 3){
                Bot.HitShip(move);
            }
            if(player.IsLost()){
                cout << "You lost\n";
                goto here;
            }
        }else if (choice == 'r'){
            player.RemainingShip();
            cout << endl;
            Bot.RemainingShip();
        }else if(choice == 'c'){
            cout << Bot.GetPos() << endl;
        }
    }while(choice != 'q');
    here:cout << "Do you want to play again?(Y or N)\n";
    cout << "Enter your choice:";
    cin >> choice;
    if(choice == 'Y'){
        goto again;
    }
    cout << endl;
    cout << "End game\n";
    
    return 0;
}