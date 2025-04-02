#pragma once
#ifndef DELFI_REPORTER_H
#define DELFI_REPORTER_H
#include <string>
#include <stdexcept>
namespace delfi
{
    class InvalidArgumentReporter : public std::runtime_error
    {
    public:
        /*content : Invalid argument reported : expected for ? variables, but ? variables*/
        InvalidArgumentReporter() : std::runtime_error("Invalid argument reported") {}
        InvalidArgumentReporter(std::string msg) : std::runtime_error("Invalid argument reported :" + msg) {}
        InvalidArgumentReporter(const size_t expected, const size_t actual) : std::runtime_error("Invalid argument reported : expected for " + std::to_string(expected) + " variables, but " + std::to_string(actual) + " variables") {}
    };
    class FunctionUndefinedReporter : public std::runtime_error
    {
    public:
        /*content : Function ? is not defined*/
        FunctionUndefinedReporter() : std::runtime_error("Undefined function reported") {}

        FunctionUndefinedReporter(const std::string name) : std::runtime_error("Undefined function reported in function " + name) {}
    };
} // namespace delfi

#endif // DELFI_REPORTER_H