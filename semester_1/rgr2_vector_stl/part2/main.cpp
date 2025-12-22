#include "time_utility.h"
#include "train.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>

int main() {
    
    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);
    
    std::cout << "t2: ";
    PrintTime(t2);
    
    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
    
    std::vector<Train> trains;
    std::ifstream file("file.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file" << std::endl;
        std::cerr << "Please create a file with train data." << std::endl;
        return EXIT_FAILURE;
    }
    
    Train train;
    while (file >> train) {
        trains.push_back(train);
    }
    file.close();
    
    if (trains.empty()) {
        std::cout << "No data on trains found in this file." << std::endl;
        return EXIT_SUCCESS;
    }
    
    std::sort(trains.begin(), trains.end());
    std::cout << "Trains in order of departure time:" << std::endl;
    for (const auto& train : trains) {
        std::cout << train << std::endl;
    }
    
    std::cout << "Trains departing between 08:00 and 09:00" << std::endl;
    std::time_t start_time = SetTime(8, 0);
    std::time_t end_time = SetTime(9, 0);
    
    bool found_train = false;
    for (const auto& train : trains) {
        if (train.getDispatchTime() >= start_time && 
            train.getDispatchTime() <= end_time) {
            std::cout << train << std::endl;
            found_train = true;
        }
    }
    if (!found_train) {
        std::cout << "No trains found in this time range." << std::endl;
    }
    
    std::string destination = "Minsk";
    std::cout << "All trains to " << destination << " " << std::endl;
    
    found_train = false;
    for (const auto& train : trains) {
        if (train.getDestination() == destination) {
            std::cout << train << std::endl;
            found_train = true;
        }
    }
    if (!found_train) {
        std::cout << "No trains found to " << destination << std::endl;
    }

    TrainType needed_type = TrainType::SPECIALIZED;
    std::cout << "\n" << Train::RewriteTypeAsAString(needed_type) 
    << " trains to " << destination << std::endl;
    
    found_train = false;
    for (const auto& train : trains) {
        if (train.getDestination() == destination && 
            train.getType() == needed_type) {
            std::cout << train << std::endl;
            found_train = true;
        }
    }
    if (!found_train) {
        std::cout << "No " << Train::RewriteTypeAsAString(needed_type)
        << " trains found to " << destination << std::endl;
    }
    
    std::cout << "Fastest train to " << destination << "" << std::endl;
    
    const Train* fastest_train = nullptr;
    std::time_t min_travel_time = std::numeric_limits<std::time_t>::max();
    
    for (const auto& train : trains) {
        if (train.getDestination() == destination) {
            if (train.getTravellingTime() < min_travel_time) {
                min_travel_time = train.getTravellingTime();
                fastest_train = &train;
            }
        }
    }
    
    if (fastest_train != nullptr) {
        std::cout << *fastest_train << std::endl;
        
        std::tm* travel_tm = std::localtime(&min_travel_time);
        std::cout << "Travel time: " 
        << std::setfill('0') << std::setw(2) << travel_tm->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << travel_tm->tm_min 
        << std::endl;
    } 
    else {
        std::cout << "No trains found to " << destination << std::endl;
    }
    
    return EXIT_SUCCESS;
}
