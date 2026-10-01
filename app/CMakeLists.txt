cmake_minimum_required(VERSION 3.20.0)
set(BOARD nrf54l15dk/nrf54l05/cpuapp)
find_package(Zephyr REQUIRED)
project(my_zephyr_app)



target_sources(app PRIVATE src/main.cpp)
