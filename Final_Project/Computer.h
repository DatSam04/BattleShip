#ifndef Computer_H
#define Computer_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Computer{
    private:
        vector<int> shipSize;
        vector<vector<string> > ship;
        vector<string> shipPos;
        vector<bool> shipHitted;
        vector<string> ComputerMovement;
        vector<string> HumanMovement;
    
    public:
        Computer();
        
        void InputShip();
        string SetPosition(vector<string> currShip, int shipSize);
        bool ShipChecked(vector<string> currShip);
        bool PositionChecked(vector<string> shipPos);

        bool IsLost();
        void IsHitted(string position);
        void HitShip(string shipPosition);
        void RemainingShip();
        string Fire();
        string GetShipType();
        string GetPos();
        void PrintBattleGrid();
};

#endif