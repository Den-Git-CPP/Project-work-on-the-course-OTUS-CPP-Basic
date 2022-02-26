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
download_weather_curl.h
source/Main_Inform_TAF.cpp
)

target_link_libraries(
    taf
                ${LIB_CURL})
        
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

target_compile_features(taf PUBLIC cxx_std_17)
