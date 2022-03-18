#ifndef Ship_H
#define Ship_H

#include <iostream>
#include <vector>

using namespace std;

class Human{
    private:
        vector<int> shipSize;
        vector<vector<string> > ship;
        vector<string> shipPos;
        vector<bool> shipHitted;

    public:
        Human();
        Human(string file);

        void SetPosition();
        void SetShip();
        bool ShipChecked();
        bool PositionChecked();

        void IsHitted(string& move);
        void RemainingShip();
        bool IsLost();

        string GetShipType();
        string GetPos();
        void PrintBattleGrid();

};

#endif