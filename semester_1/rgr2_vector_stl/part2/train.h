#pragma once

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train(TrainId id, TrainType type, const std::string& dest,
    std::time_t dispatch, std::time_t travel)
    : id_(id), type_(type), destination_(dest),
    dispatch_time_(dispatch), travelling_time_(travel) {}
    
    Train() : id_(0), type_(TrainType::PASSENGER), 
    dispatch_time_(0), travelling_time_(0) {}

    TrainId getId() const {
    return id_; 
    }
    TrainType getType() const {
    return type_; 
    }
    std::string getDestination() const {
    return destination_; 
    }
    std::time_t getDispatchTime() const { 
    return dispatch_time_; 
    }
    std::time_t getTravellingTime() const { 
    return travelling_time_; 
    }
    
    bool operator<(const Train& other) const {
    return dispatch_time_ < other.dispatch_time_;
    }
    
    static TrainType RewriteStringAsAType(const std::string& str) {
        if (str == "PASSENGER")
        return TrainType::PASSENGER;
        if (str == "FREIGHT")
        return TrainType::FREIGHT;
        if (str == "HIGH_SPEED")
        return TrainType::HIGH_SPEED;
        if (str == "SUBWAY")
        return TrainType::SUBWAY;
        if (str == "SPECIALIZED")
        return TrainType::SPECIALIZED;
        else
        return TrainType::PASSENGER;
    }
    
    static std::string RewriteTypeAsAString(TrainType t) {
        switch(t) {
            case TrainType::PASSENGER : return "Passenger";
            case TrainType::FREIGHT : return "Freight";
            case TrainType::HIGH_SPEED : return "High-speed";
            case TrainType::SUBWAY : return "Subway";
            case TrainType::SPECIALIZED : return "Specialized";
            default: return "Unknown";
        }
    }
    
    friend std::istream& operator>>(std::istream& instr, Train& train);
    friend std::ostream& operator<<(std::ostream& outstr, const Train& train);
};

inline std::istream& operator>>(std::istream& instr, Train& train) {
    std::string type_str;
    
    if (instr >> train.id_ >> type_str) {
        train.type_ = Train::RewriteStringAsAType(type_str);
        
        instr >> train.destination_;
        
        int hours, minutes;
        char colon1, colon2;
        
        if (!(instr >> hours >> colon1 >> minutes)) {
            instr.setstate(std::ios::failbit);
            return instr;
        }
        if (colon1 != ':') {
            instr.setstate(std::ios::failbit);
            return instr;
        }
        
        try {
            train.dispatch_time_ = SetTime(hours, minutes);
        } catch (const std::out_of_range& e) {
            std::cerr << "Error reading departure time: " << e.what() << std::endl;
            instr.setstate(std::ios::failbit);
            return instr;
        }
        
        if (!(instr >> hours >> colon2 >> minutes)) {
            instr.setstate(std::ios::failbit);
            return instr;
        }
        if (colon2 != ':') {
            instr.setstate(std::ios::failbit);
            return instr;
        }
        
        try {
            train.travelling_time_ = SetTime(hours, minutes);
        } catch (const std::out_of_range& e) {
            std::cerr << "Error reading travel time: " << e.what() << std::endl;
            instr.setstate(std::ios::failbit);
            return instr;
        }
    }
    
    return instr;
}

inline std::ostream& operator<<(std::ostream& outstr, const Train& train) {
    std::tm dep_tm = *std::localtime(&train.dispatch_time_);  // Копия
    std::tm trav_tm = *std::localtime(&train.travelling_time_);
    
    outstr << "Train №" << train.id_ 
           << " [" << Train::RewriteTypeAsAString(train.type_) << "]"
           << " to " << train.destination_
           << "\n  Departure: " 
           << std::setfill('0') << std::setw(2) << dep_tm.tm_hour << ":"
           << std::setfill('0') << std::setw(2) << dep_tm.tm_min
           << "\n  Travel time: "
           << std::setfill('0') << std::setw(2) << trav_tm.tm_hour << ":"
           << std::setfill('0') << std::setw(2) << trav_tm.tm_min;
    
    return outstr;
}
