#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Human.h"
const int size = 10;
using namespace std;

//default constructor
Human::Human(){
    shipSize.at(0) = 0;
    ship.at(0).at(0) = "none";
    shipPos.at(0) = "none";
    
}

/**
 * @brief Constructor to set the position for different type ship
 * 
 * @param ShipType (Carrier, Battleship, Cruiser, Submarine, Destroyer)
 * @param startPosition[A-J][1-10]
 * @param endPosition[V][U or D](vertial with up or down) or [H][L or R](horizontal with left or right)
 */
Human::Human(string file){
    ifstream inFS;
    string line;
    string input;
    inFS.open(file);
    vector<string> shipType;
    if(!inFS.is_open()){
        cout << "Couldn't open file " << file << "\n";
    }
    while(inFS >> line){
        line += ',';
        for(int i = 0; i < line.size(); i++){
            if(line.at(i) != ','){
                input += line.at(i);
            }else{
                shipType.push_back(input);
                input = "";
            }
        }
        this->ship.push_back(shipType);
        shipType.clear();
    }
    inFS.close();
    //Set default size for each type of Ships
    for(int i = 0; i < this->ship.size(); i++){
        shipHitted.push_back(false);
        if(this->ship.at(i).at(0) == "Carrier"){
            shipSize.push_back(5);
        }else if(this->ship.at(i).at(0) == "Battleship"){
            shipSize.push_back(4);
        }else if(this->ship.at(i).at(0) == "Cruiser"){
            shipSize.push_back(3);
        }else if(this->ship.at(i).at(0) == "Submarine"){
            shipSize.push_back(3);
        }else if(this->ship.at(i).at(0) == "Destroyer"){
            shipSize.push_back(2);
        }
    }

}

//Checked whether the input for ship type, start position, and end position are valid
bool Human::ShipChecked(){
    int index = 0;
    char first = 'A';
    char last = 'J';
    int number;
    bool result = true;
    while(index < ship.size()){
        if(ship.at(index).at(1).size() > 2){
            if(ship.at(index).at(1).at(2) == '0'){
                number = ship.at(index).at(1).at(1)-39;
            }else{
                number = ship.at(index).at(1).at(1);
            }
        }else{
            number = ship.at(index).at(1).at(1) - 48;
        }
        try{
            if(ship.at(index).at(1).at(0) < first || ship.at(index).at(1).at(0) > last){
                throw runtime_error("is invalid");
            }else if(number < 1 || number > 10){
                throw runtime_error("is invalid");
            }
            if(ship.at(index).at(2).at(0) != 'V' && ship.at(index).at(2).at(0) != 'H'){               
                goto here;
            }else if(ship.at(index).at(2).at(0) == 'V'){
                if(ship.at(index).at(2).at(1) != 'U' && ship.at(index).at(2).at(1) != 'D'){
                    goto here;
                }
            }else if (ship.at(index).at(2).at(0) == 'H'){
                if(ship.at(index).at(2).at(1) != 'L' && ship.at(index).at(2).at(1) != 'R'){
                    here:throw "is invalid";
                }
            }
        }
        catch(runtime_error& excpt){
            result = false;
            cout << ship.at(index).at(0) << ": " << excpt.what() << endl;
            cout << "Changed the start position" << endl;
        }
        catch(const char* str){
            result = false;
            cout << ship.at(index).at(0) << ": " << str << endl;
            cout << "Changed the end position" << endl;
        }
        index++;
    }
    return result;
}

//Set the position for each ships
void Human::SetPosition(){
    string next;
    string position;
    int num;
    for(int o = 0; o < ship.size(); o++){
        position = "";
        switch (ship.at(o).at(2).at(0)){ //endPos at index 2 for each ship type
            case 'V'://Set position for ship with vertical direction
                if(ship.at(o).at(2).at(1) == 'U'){
                    for(int i = 0; i < shipSize.at(o); i++){
                        next += ship.at(o).at(1).at(0);
                        if(ship.at(o).at(1).size() > 2 && ship.at(o).at(1).at(2) == '0' && i == 0){
                            num = ship.at(o).at(1).at(1)-39;
                        }else if (ship.at(o).at(1).size() == 2){
                            num = ship.at(o).at(1).at(1)-48-i;
                        }else{
                            num = ship.at(o).at(1).at(1)-39;
                            num += ship.at(o).at(1).at(1)-49-i;
                        }
                        next += to_string(num);
                        position += next;
                        if(i < shipSize.at(o)-1){
                            position += " ";
                        }
                        next = "";
                    }
                    shipPos.push_back(position);
                }else if (ship.at(o).at(2).at(1) == 'D'){
                    for(int i = 0; i < shipSize.at(o); i++){
                        next += ship.at(o).at(1).at(0);
                        if(ship.at(o).at(1).size() > 2 && ship.at(o).at(1).at(2) == '0' && i == 0){
                            num = ship.at(o).at(1).at(1)-39;
                        }else if (ship.at(o).at(1).size() == 2){
                            num = ship.at(o).at(1).at(1)-48+i;
                        }else{
                            num = ship.at(o).at(1).at(1)-39;
                            num += ship.at(o).at(1).at(1)-49+i;
                        }
                        next += to_string(num);
                        position += next;
                        if(i < shipSize.at(o)-1){
                            position += " ";
                        }
                        next = "";
                    }
                    shipPos.push_back(position);
                }
                break;
            case 'H'://Set position for ship with horizontal direction
                if(ship.at(o).at(2).at(1) == 'L'){
                    for(int i = 0; i < shipSize.at(o); i++){
                        next += (ship.at(o).at(1).at(0)-i);
                        if(ship.at(o).at(1).size() > 2 && ship.at(o).at(1).at(2) == '0' && i == 0){
                            num = ship.at(o).at(1).at(1)-39;
                        }else if (ship.at(o).at(1).size() == 2){
                            num = ship.at(o).at(1).at(1)-48;
                        }
                        next += to_string(num);
                        position += next;
                        if(i < shipSize.at(o)-1){
                            position += " ";
                        }
                        next = "";
                    }
                    shipPos.push_back(position);
                }else if(ship.at(o).at(2).at(1) == 'R'){
                    for(int i = 0; i < shipSize.at(o); i++){
                        next += (ship.at(o).at(1).at(0)+i);
                        if(ship.at(o).at(1).size() > 2 && ship.at(o).at(1).at(2) == '0' && i == 0){
                            num = ship.at(o).at(1).at(1)-39;
                        }else if (ship.at(o).at(1).size() == 2){
                            num = ship.at(o).at(1).at(1)-48;
                        }
                        next += to_string(num);
                        position += next;
                        if(i < shipSize.at(o)-1){
                            position += " ";
                        }
                        next = "";
                    }
                    shipPos.push_back(position);
                }
                break;
            default:
                break;
        }
    }
}

//Return false if there is error in the position.
bool Human::PositionChecked(){
    vector<string> allPosition;
    string currPos;
    string line;
    int number;
    for(int i = 0; i < shipPos.size(); i++){
        line = shipPos.at(i);
        line += ' ';
        for(int o = 0; o < line.size(); o++){
            if(line.at(o) != ' '){
                currPos += shipPos.at(i).at(o);
            }else{
                if(currPos.size() > 2 && currPos.at(2) == '0'){
                    number = currPos.at(1)-39;
                }else if (currPos.size() == 2){
                    number = currPos.at(1)-48;
                }else{
                    number = currPos.at(1)-39;
                    number += currPos.at(2)-48;
                }
                try{
                    for(int c = 0; c < allPosition.size(); c++){
                        if(currPos == allPosition.at(c)){//catch the ship that overlaps other ships
                            throw runtime_error("Overlapped");
                        }
                        //detect position exceed the battle grid table
                        if(currPos.at(0) < 'A' || currPos.at(0) > 'J'){
                            here:throw " contained invalid position";
                        }else if(number < 1 || number > 10){
                            goto here;
                        }
                    }
                    allPosition.push_back(currPos);
                    currPos = "";
                }
                catch(runtime_error& excpt){
                    cout << ship.at(i).at(0) << " are " << excpt.what() << endl;
                    return false;
                }
                catch(const char* result){
                    cout << ship.at(i).at(0) << result << endl;
                    return false;
                }
            }
        }
        allPosition.push_back(currPos);
        currPos = "";
    }
    return true;
}

//Create a vector for the battle grid
void SetLine(vector<string> &line){
    string addLine = "";
    char letter = 'A';
    for(int i = 0; i < size; i++){
        for(int o = 0; o < size; o++){
            addLine += letter;
            letter++;
        }
        line.push_back(addLine);
        addLine = "";
        letter = 'A';
    }
}

/**
 * @brief This function used to print the table of human
 */
// void Human::PrintBattleGrid(){
//     vector<string> line;
//     SetLine(line);
//     vector<string> position;
//     string addPos;
//     string move;
//     char letter = 'A';
//     string num;
//     int index = 0;
//     int next = 0;
//     vector<string> reverse;

//     while(index < shipPos.size()){
//         position.clear();
//         reverse.clear();
//         for(int p = 0; p < shipPos.at(index).size(); p++){
//             if(shipPos.at(index).at(p) != ' '){
//                 addPos += shipPos.at(index).at(p);
//             }else{
//                 reverse.push_back(addPos);
//                 addPos = "";
//             }
//         }
//         reverse.push_back(addPos);
//         addPos = "";
//         //Rearrange the position in the increment order
//         if(reverse.at(0).at(0) > reverse.at(1).at(0) || reverse.at(0).at(1) > reverse.at(1).at(1)){
//             for(int r = reverse.size()-1; r >= 0; r--){
//                 position.push_back(reverse.at(r));
//             }
//         }else{
//             for(int r = 0; r < reverse.size(); r++){
//                 position.push_back(reverse.at(r));
//             }
//         }
//         //Input ship location into table
//         for(int i = 0; i < size; i++){
//             for(int o = 0; o < size; o++){
//                 move = line.at(i).at(o);
//                 move += to_string(i+1);
//                 if(position.at(next) == move){
//                     num = to_string(shipSize.at(index));
//                     line.at(i).at(o) = num.at(0);
//                     if(next == position.size()-1){
//                         goto here;
//                     }
//                     next++;
//                 }
//             }
//         }
//         here:next = 0;
//         index++;
//     }
//     //Print Table
//     cout << "   ";
//     for(int i = 0; i < size; i++){
//         cout << letter;
//         if(i < 10-1){
//             cout << "   ";
//         }
//         letter++;
//     }
//     cout << endl;
//     for(int o = 0; o < size; o++){
//         cout << left << setw(3) << o+1;
//         for(int n = 0; n < size; n++){
//             if(isdigit(line.at(o).at(n))){
//                 cout << line.at(o).at(n);
//             }else{
//                 cout << '-';
//             }
//             if(n < size-1){
//                 cout << "   ";
//             }
//         }
//         cout << endl;
//     }
// }

void Human::RemainingShip(){
    cout << "Your remaining ships\n";
    for(int i = 0; i < shipHitted.size(); i++){
        if(shipHitted.at(i) == false){
            cout << ship.at(i).at(0) << endl;
        }
    }
}

//Checked if ship is hitted and store the result to vector
void Human::IsHitted(string& move){
    string currPosition, currShip;
    currPosition = "";
    for(int i = 0; i < shipPos.size(); i++){
        currShip = shipPos.at(i);
        currShip += ' ';
        for(int o = 0; o < currShip.size(); o++){
            if(currShip.at(o) != ' '){
                currPosition += currShip.at(o);
            }else{
                if(move == currPosition){
                    shipHitted.at(i) = true;
                    cout << "Computer hits your " << ship.at(i).at(0) << endl;
                    move = shipPos.at(i);
                    return;
                }
                currPosition = "";
            }
        }
    }
    cout << "Computer missed" << endl << endl;
}

bool Human::IsLost(){
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

//Get ship's type and size
string Human::GetShipType(){
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
string Human::GetPos(){
    string ShipPosition = "";
    for(int i = 0; i < shipPos.size(); i++){
        cout << shipPos.at(i) << endl;
    }
    return ShipPosition;
}