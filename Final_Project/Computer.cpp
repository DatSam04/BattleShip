#include <iomanip>
#include <ctime>
#include "Computer.h"

using namespace std;

//default constructor
Computer::Computer(){
}

/**
 * @brief //Constructor to generate the position for different ships for computer
 * @param //Also checked if the start position and end position are valid
 */
void Computer::InputShip(){
    srand(time(NULL));
    vector<string> currShip;
    vector<string> checkedPosition;
    string shipType, startPos, endPos;
    string testPosition;
    int random, number;
    char letter;
    bool result = false;
    shipSize.clear();
    shipHitted.clear();
    ship.clear();
    shipPos.clear();

    shipSize.push_back(5);
    shipSize.push_back(4);
    shipSize.push_back(3);
    shipSize.push_back(3);
    shipSize.push_back(2);
    for(int h = 0; h < 5; h++){
        shipHitted.push_back(false);
    }
    
    for(int i = 0; i < 5; i++){
        if(i == 0){
            shipType = "Carrier";
        }else if (i == 1){
            shipType = "Battleship";
        }else if (i == 2){
            shipType = "Cruiser";
        }else if (i == 3){
            shipType = "Submarine";
        }else if (i == 4){
            shipType = "Destroyer";
        }
        do{//Generate startPos and endPos for each ship
            here:currShip.clear();
            currShip.push_back(shipType);
            letter = 'A';
            number = 1;

            random = rand() % 100;
            letter += random / 10;
            number += random % 10;
            startPos = letter + to_string(number);
            currShip.push_back(startPos);
            if(random > rand() % 100){
                endPos = 'V';
                if(random > rand() % 100){
                    endPos += 'U';
                }else{
                    endPos += 'D';
                }
            }else{
                endPos = 'H';
                if(random > rand() % 100){
                    endPos += 'L';
                }else{
                    endPos += 'R';
                }
            }
            currShip.push_back(endPos);
            if(!(ShipChecked(currShip))){
                goto here;
            }
            checkedPosition = shipPos;
            testPosition = SetPosition(currShip, shipSize.at(i));
            checkedPosition.push_back(testPosition);
            if(!(PositionChecked(checkedPosition))){
                goto here;
            }
            result = true;
        }while(!result);
        shipPos.push_back(testPosition);
        ship.push_back(currShip);
    }
}

// checked the validity of startPos and endPos
bool Computer::ShipChecked(vector<string> currShip){
    int num;
    char first = 'A';
    char last = 'J';
    if(currShip.at(1).size() > 2){
        if(currShip.at(1).at(2) == '0'){
            num = currShip.at(1).at(1)-39;
        }else{
            num = currShip.at(1).at(1);
        }
    }else{
        num = currShip.at(1).at(1) - 48;
    }
    if(currShip.at(1).at(0) < first || currShip.at(1).at(0) > last){
        return false;
    }else if(num < 1 || num > 10){
        return false;
    }
    if(currShip.at(2).at(0) != 'V' && currShip.at(2).at(0) != 'H'){               
        return false;
    }else if(currShip.at(2).at(0) == 'V'){
        if(currShip.at(2).at(1) != 'U' && currShip.at(2).at(1) != 'D'){
            return false;
        }
    }else if (currShip.at(2).at(0) == 'H'){
        if(currShip.at(2).at(1) != 'L' && currShip.at(2).at(1) != 'R'){
            return false;
        }
    }
    return true;
}

//Set the position of each type of ship
string Computer::SetPosition(vector<string> currShip, int shipSize){
    string next;
    string position;
    int num;
    position = "";
    switch (currShip.at(2).at(0)){ //endPos at index 2 for each ship type
        case 'V':
            if(currShip.at(2).at(1) == 'U'){
                for(int i = 0; i < shipSize; i++){
                    next += currShip.at(1).at(0);
                    if(currShip.at(1).size() > 2 && currShip.at(1).at(2) == '0' && i == 0){
                        num = currShip.at(1).at(1)-39;
                    }else if (currShip.at(1).size() == 2){
                        num = currShip.at(1).at(1)-48-i;
                    }else{
                        num = currShip.at(1).at(1)-39;
                        num += currShip.at(1).at(1)-49-i;
                    }
                    next += to_string(num);
                    position += next;
                    if(i < shipSize-1){
                        position += " ";
                    }
                    next = "";
                }
            }else if (currShip.at(2).at(1) == 'D'){
                for(int i = 0; i < shipSize; i++){
                    next += currShip.at(1).at(0);
                    if(currShip.at(1).size() > 2 && currShip.at(1).at(2) == '0' && i == 0){
                        num = currShip.at(1).at(1)-39;
                    }else if (currShip.at(1).size() == 2){
                        num = currShip.at(1).at(1)-48+i;
                    }else{
                        num = currShip.at(1).at(1)-39;
                        num += currShip.at(1).at(1)-49+i;
                    }
                    next += to_string(num);
                    position += next;
                    if(i < shipSize-1){
                        position += " ";
                    }
                    next = "";
                }
            }
            break;
        case 'H':
            if(currShip.at(2).at(1) == 'L'){
                for(int i = 0; i < shipSize; i++){
                    next += (currShip.at(1).at(0)-i);
                    if(currShip.at(1).size() > 2 && currShip.at(1).at(2) == '0' && i == 0){
                        num = currShip.at(1).at(1)-39;
                    }else if (currShip.at(1).size() == 2){
                        num = currShip.at(1).at(1)-48;
                    }
                    next += to_string(num);
                    position += next;
                    if(i < shipSize-1){
                        position += " ";
                    }
                    next = "";
                }
            }else if(currShip.at(2).at(1) == 'R'){
                for(int i = 0; i < shipSize; i++){
                    next += (currShip.at(1).at(0)+i);
                    if(currShip.at(1).size() > 2 && currShip.at(1).at(2) == '0' && i == 0){
                        num = currShip.at(1).at(1)-39;
                    }else if (currShip.at(1).size() == 2){
                        num = currShip.at(1).at(1)-48;
                    }
                    next += to_string(num);
                    position += next;
                    if(i < shipSize-1){
                        position += " ";
                    }
                    next = "";
                }
            }
            break;
        default:
            break;
    }
    return position;
}

//Checked if the position of ships are overlapped
//Return true if no error
bool Computer::PositionChecked(vector<string> shipPos){
    vector<string> allPosition;
    string currPos;
    string position;
    int number;
    for(int i = 0; i < shipPos.size(); i++){
        position = shipPos.at(i);
        position += ' ';
        for(int o = 0; o < position.size(); o++){
            if(position.at(o) != ' '){
                currPos += position.at(o);
            }else{
                if(currPos.size() > 2 && currPos.at(2) == '0'){
                    number = currPos.at(1)-39;
                }else if (currPos.size() == 2){
                    number = currPos.at(1)-48;
                }else{
                    number = currPos.at(1)-39;
                    number += currPos.at(2)-48;
                }
                for(int c = 0; c < allPosition.size(); c++){
                    if(currPos == allPosition.at(c)){
                        return false;
                    }
                    if(currPos.at(0) < 'A' || currPos.at(0) > 'J'){
                        return false;
                    }else if(number < 1 || number > 10){
                        return false;
                    }
                }
                allPosition.push_back(currPos);
                currPos = "";
            }
        }
    }
    return true;
}

//Create a vector for the battle grid
void GenerateLine(vector<string> &line){
    string addLine = "";
    char letter = 'A';
    for(int i = 0; i < 10; i++){
        for(int o = 0; o < 10; o++){
            addLine += letter;
            letter++;
        }
        line.push_back(addLine);
        addLine = "";
        letter = 'A';
    }
}

void Computer::PrintBattleGrid(){
    vector<string> line;
    GenerateLine(line);
    string position, currShip, currPosition;
    int i, o, n, a;
    char letter = 'A';

    for(i = 0; i < line.size(); i++){
        for(o = 0; o < line.at(i).size(); o++){
            position = line.at(i).at(o);
            position += to_string(i+1);
            for(int p = 0; p < HumanMovement.size(); p++){//set the missed positions into table
                if(position == HumanMovement.at(p)){
                    line.at(i).at(o) = 'X';
                }
            }
            currShip = "";
            for(a = 0; a < shipHitted.size(); a++){//set the hitted positions into table
                if(shipHitted.at(a) == true){
                    currShip = shipPos.at(a);
                    currShip += ' ';
                    for(n = 0; n < currShip.size(); n++){
                        if(currShip.at(n) != ' '){
                            currPosition += currShip.at(n);
                        }else{
                            if(currPosition == position){
                                line.at(i).at(o) = 'O';
                            }
                            currPosition = "";
                        }
                    }
                }
            }
        }
    }
    cout << "   ";
    for(i = 0; i < 10; i++){
        cout << letter;
        if(i < 10-1){
            cout << "   ";
        }
        letter++;
    }
    cout << endl;
    for(o = 0; o < 10; o++){
        cout << left << setw(3) << o+1;
        for(n = 0; n < 10; n++){
            if (line.at(o).at(n) == 'O'){
                cout << 'O';
            }else if (line.at(o).at(n) == 'X'){
                cout << 'X';
            }else{
                cout << '-';
            }
            if(n < 9){
                cout << "   ";
            }
        }
        cout << endl;
    }
}

//Checked whether Human hit any ships of Computer
void Computer::IsHitted(string position){
    string line;
    string currPos;
    bool miss = true;
    for(int i = 0; i < ship.size(); i++){
        line = shipPos.at(i);
        line += " ";
        for(int o = 0; o < line.size(); o++){
            if(line.at(o) != ' '){
                currPos += line.at(o);
            }else{
                if(currPos == position){
                    shipHitted.at(i) = true;
                    miss = false;
                    cout << "You hitted " << ship.at(i).at(0) << endl;
                    goto here;
                }
                currPos = "";
            }
        }
    }
    here: if(miss == true){
        HumanMovement.push_back(position);
    }
    if(miss == true){
        cout << "You missed\n";
    }
}

void Computer::HitShip(string shipPosition){
    string currPos = "";
    string line = shipPosition;
    line += ' ';
    for(int i = 0; i < line.size(); i++){
        if(line.at(i) != ' '){
            currPos += shipPosition.at(i);
        }else{
            ComputerMovement.push_back(currPos);
            currPos = "";
        }
    }
}

//Generate Computer movement
string Computer::Fire(){
    srand(time(NULL));
    int random, number;
    char letter;
    string target;

    here:random = rand() % 100;
    letter = 'A';
    number = 1;
    letter += random / 10;
    number += random % 10;
    target = letter + to_string(number);
    for(int i = 0; i < ComputerMovement.size(); i++){
        if(target == ComputerMovement.at(i)){
            goto here;
        }
    }
    ComputerMovement.push_back(target);
    return target;
}

bool Computer::IsLost(){
    int sunk = 0;
    for(int i = 0; i < shipHitted.size(); i++){
        if(shipHitted.at(i) == true){
            sunk++;
        }
    }
    if(sunk == 5){
        return true;
    }
    return false;
}

void Computer::RemainingShip(){
    cout << "Computer remaining ships\n";
    for(int i = 0; i < shipHitted.size(); i++){
        if(shipHitted.at(i) == false){
            cout << ship.at(i).at(0) << endl;
        }
    }
}
//Get ship's type and size
string Computer::GetShipType(){
    string shipType;
    for(int i = 0; i < this->ship.size(); i++){
      shipType += this->ship.at(i).at(0);
      shipType += " size = ";
      shipType += to_string(this->shipSize.at(i));
      shipType += '\n';
    }
    return shipType;
}

//Get position in the grid of all ships
string Computer::GetPos(){
    string position;
    for(int i = 0; i < shipPos.size(); i++){
        position += shipPos.at(i);
        position += "\n";
    }
    return position;
}