#ifndef CRODNUN_PROFILER_H
#define CRODNUN_PROFILER_H

#include <iostream>
#include <string>
#include <chrono>

namespace crodnun {

// C++ object that we can use to profile a given C++ function just creating an object at a given scope
// Example:
//  void myFunction () {  Profiler p("name"); }
// This simple code will give you the time in us consumed by the function (object is destroyed when scope is done)        
class Profiler {
        std::string _name;
        std::chrono::time_point<std::chrono::high_resolution_clock> _startPoint;

public:
        Profiler(const std::string &name) : _name(name) {
                _startPoint = std::chrono::high_resolution_clock::now();
        }

        void Stop() {
                auto stopPoint = std::chrono::high_resolution_clock::now();
                auto startMs = std::chrono::time_point_cast<std::chrono::microseconds>(_startPoint).time_since_epoch().count();
                auto stopMs = std::chrono::time_point_cast<std::chrono::microseconds>(stopPoint).time_since_epoch().count();
                auto duration = stopMs - startMs;
                std::cout << "PROFILING: " << _name << " : " << duration << " us" << std::endl;
        }

        // at destructor stop timer and show microseconds elapsed
        ~Profiler() {
                Stop();
        }
};

}  // namespace crodnun

#endif  // CRODNUN_PROFILER_H