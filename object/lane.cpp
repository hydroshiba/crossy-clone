#include "lane.hpp"

void Lane::render() {
    std::cout << sprite << std::endl;
}

void Lane::process(int time) {
    std::cout << "Lane processed" << std::endl;
}