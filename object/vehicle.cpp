#include "vehicle.hpp"

void Vehicle::move(const bool& direction){
    if(direction){
        cout << "Move left";
    }
    else cout << "Move right";
}
void Vehicle::render(){
    cout << sprite;
}
void Vehicle::playSound(){
    cout << "Play sound...";
}