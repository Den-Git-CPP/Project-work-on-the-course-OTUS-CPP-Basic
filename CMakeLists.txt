cmake_minimum_required(VERSION 3.10)

project(REQUEST_TAF_METAR)
set(CMAKE_CXX_STANDARD 20)

find_package(CURL) 
if(CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
  else()
    #set(CURL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/curl-7.80.0-win64-mingw)
    #
    #find_library(
    #        LIB_CURL
    #        NAMES
    #            curl
    #        PATHS 
    #            ${CURL_PATH}/lib)
    #
    #OR
    #
    #message(STATUS "Fetching CURL")
    #include(FetchContent)
    #FetchContent_Declare(      
    #CURL
    #URL https://curl.se/download/curl-8.6.0.zip 
    #DOWNLOAD_EXTRACT_TIMESTAMP true
    #OVERRIDE_FIND_PACKAGE
    #)
    #
    #FetchContent_MakeAvailable(CURL)
  endif()

set(PROJECT_HEADERS
include/colored_cout.h 
include/download_weather_curl.h 
include/ForecastNode.h 
include/Function.h 
include/Icing.h 
include/Main_Inform_METAR.h 
include/Main_Inform_TAF.h 
include/Sky_Cover.h 
include/Station_Sensors.h 
include/Surface_Temperature.h 
include/Turbulence.h 
include/Wind.h 
include/Wind_Shear.h
)

set(PROJECT_SOURCES
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
)

add_executable(${CMAKE_PROJECT_NAME}
  ${PROJECT_HEADERS}
  ${PROJECT_SOURCES}
main_taf.cpp
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE include 
    PRIVATE "${CURL_INCLUDE_DIRS}/include"    # PRIVATE "${CURL_PATH}/include"
)  
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE 
    CURL::libcurl #  ${LIB_CURL}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()
#"Dictionary copy in: ${CMAKE_SOURCE_DIR}/dictionary"
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dictionary
        ${CMAKE_BINARY_DIR}/dictionary
)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/!MyProgram)
#set(MY_PROG_PATCH  ${PROJECT_SOURCE_DIR}/!MyProgram)
#install (TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${MY_PROG_PATCH})
#install (DIRECTORY dictionary DESTINATION ${MY_PROG_PATCH})


