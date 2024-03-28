cmake_minimum_required(VERSION 3.28)

project(REQUEST_TAF_METAR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#===============================CURL_LIBRARY===================================
#set( CURL_LIBRARY      ${CMAKE_SOURCE_DIR}/curl-8.6.0_7-win64-mingw/lib )
#set( CURL_INCLUDE_DIR  ${CMAKE_SOURCE_DIR}/curl-8.6.0_7-win64-mingw/include )
#add_definitions("-DCURL_STATICLIB")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(CURL)
  if(CURL_FOUND)
    message(STATUS "CURL found" )  
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
    include_directories( ${CURL_INCLUDE_DIRS} )
    link_directories( ${CURL_LIBRARIES} )
    add_library(CURL STATIC IMPORTED)
  else()   
    message(STATUS "DOWNLOAD CURL https://curl.se/windows" )
    #https://www.foonathan.net/2022/06/cmake-fetchcontent/
    #Bring in the CURL library
    include(FetchContent)
    FetchContent_Declare(
    curl
    URL https://curl.se/windows/dl-8.6.0_7/curl-8.6.0_7-win64-mingw.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
     )
    FetchContent_MakeAvailable(CURL)
    #https://stackoverflow.com/questions/63311116/how-to-find-the-source-directory-of-package-downloaded-via-fetchcontent
    set(CURL_LIBRARY ${curl_SOURCE_DIR}/lib )           
    set(CURL_INCLUDE_DIR  ${curl_SOURCE_DIR}/include )
    find_package(CURL)
     if(CURL_FOUND)
        message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
        message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
        message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
        include_directories( ${CURL_INCLUDE_DIRS} )
        link_directories( ${CURL_LIBRARIES} )
        add_library(CURL STATIC IMPORTED)
      endif()
 endif()
#==============================================================================

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
main.cpp
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE include 
) 

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE libcurl #wldap32 winmm ws2_32 advapi32 crypt32 
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
#
set(MY_PROG_PATCH  ${PROJECT_SOURCE_DIR}/!MyProgram)
install (TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${MY_PROG_PATCH})
install (DIRECTORY dictionary DESTINATION ${MY_PROG_PATCH})




