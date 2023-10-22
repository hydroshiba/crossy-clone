#include "lane.hpp"
using namespace std;

void Lane::render() {
    cout << sprite << endl;
}

void Lane::process(int time) {
    cout << "Lane processed" << endl;
}