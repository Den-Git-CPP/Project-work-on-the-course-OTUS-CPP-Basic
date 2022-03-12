cmake_minimum_required(VERSION 3.10)

project(request_ CXX)
set(CURL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/curl-7.80.0-win64-mingw)

find_library(
        LIB_CURL
        NAMES
            curl
        PATHS 
            ${CURL_PATH}/lib)


add_executable(${CMAKE_PROJECT_NAME}
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
    ${CMAKE_PROJECT_NAME}
     ${LIB_CURL}
)
        
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE include 
    PRIVATE "${CURL_PATH}/include"
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
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/!MyProgram)
#"Dictionary copy in: ${CMAKE_SOURCE_DIR}/dictionary"
add_custom_target(copy_target ALL
 ${CMAKE_COMMAND} -E copy_directory     ${CMAKE_SOURCE_DIR}/dictionary 
                                        ${CMAKE_BINARY_DIR}/dictionary 
                                        DEPENDS ${CMAKE_PROJECT_NAME}
 )

set(MY_PROG_PATCH  ${PROJECT_SOURCE_DIR}/!MyProgram)
install (TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${MY_PROG_PATCH})
install (DIRECTORY dictionary DESTINATION ${MY_PROG_PATCH})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)


