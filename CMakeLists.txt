cmake_minimum_required(VERSION 3.10)

set(PROJECT_N BankConsole)
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${mongocxx_INCLUDE_DIRS};${bsoncxx_INCLUDE_DIRS}")


file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(/usr/local/include/mongocxx/v_noabi /usr/local/include/libmongoc-1.0 /usr/local/include/bsoncxx/v_noabi /usr/local/include/libbson-1.0)
link_directories(/usr/local/lib)

# a macro that gets all of the header containing directories. 
MACRO(header_directories return_list includes_base_folder extention )
    FILE(GLOB_RECURSE new_list ${includes_base_folder}/*.${extention})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# using said macro.
header_directories(INCLUDES ${PROJECT_SOURCE_DIR}/include/ hpp)

message("src files:")
foreach(file ${SRCS})
        message(STATUS ${file})
endforeach()

message("include directories:")
foreach(dir ${INCLUDES})
        message(STATUS ${dir})
endforeach()

add_executable(${PROJECT_N} ${SRCS})

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

target_include_directories(${PROJECT_N} PUBLIC include ${mongocxx_INCLUDE_DIRS} ${bsoncxx_INCLUDE_DIRS})

target_link_libraries(${PROJECT_N} mongocxx bsoncxx)