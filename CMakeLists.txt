project(babel_client)
project(babel_server)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags")

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.13.1\\msvc2017")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

INCLUDE_DIRECTORIES(
   ${PROJECT_SOURCE_DIR}/include
)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
FILE(GLOB SRCS_C client/*.cpp)
FILE(GLOB SRCS_S server/*.cpp)
FILE(GLOB HDRS include/*.hpp)
FILE(GLOB UIS *.ui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDAR_REQUIRED ON)
set(CMAKE CXX_EXTENSIONS OFF)

QT5_WRAP_CPP(QT_SRC ${HDRS})

QT5_WRAP_UI( UI_HEADERS ${UIS} )

ADD_EXECUTABLE(babel_client
   ${SRCS_C}
   ${HDRS}
   ${UIS}
   ${QT_SRC}
   ${UI_HEADERS}
)

ADD_EXECUTABLE(babel_server
   ${SRCS_S}
   ${HDRS}
   ${UIS}
)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Network Qt5::Widgets Qt5::Multimedia)
target_link_libraries(babel_server ${CONAN_LIBS} Qt5::Network Qt5::Widgets)
