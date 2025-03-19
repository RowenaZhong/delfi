#!/bin/bash
cd build
cmake .. -DENABLE_COVERAGE=ON
make
ctest
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report
cd ..