cmake_minimum_required(VERSION 3.10)

project(TAF_WHTR CXX)
set(CURL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/curl-7.80.0-win64-mingw)

find_library(
        LIB_CURL
        NAMES
            curl
        PATHS 
            ${CURL_PATH}/lib)


add_executable(taf
main_taf.cpp

source/colored_cout.cpp
source/ForecastNode.cpp
source/Function.cpp
source/Icing.cpp
source/Main_Inform_METAR.cpp
source/Main_Inform_TAF.cpp
source/Sky_Cover.cpp
source/Station_Sensors.cpp
source/Surface_Temperature.cpp
source/Turbulence.cpp
source/Wind_Shear.cpp
source/Wind.cpp
include/download_weather_curl.h
)

target_link_libraries(
    taf
     ${LIB_CURL}
)
        
target_include_directories(
    taf
    PRIVATE include 
    PRIVATE "${CURL_PATH}/include"
)    

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(taf PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(taf PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

set(MY_PROG_PATCH  ${PROJECT_SOURCE_DIR}/!MyProgram)
install (TARGETS taf DESTINATION ${MY_PROG_PATCH})
install (DIRECTORY dictionary DESTINATION ${MY_PROG_PATCH})

target_compile_features(taf PUBLIC cxx_std_17)


