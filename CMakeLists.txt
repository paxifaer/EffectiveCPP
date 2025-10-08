project(main)
set(CMAKE_CXX_STANDARD 17)
# add_executable(main main.cpp)
# add_executable(item8 item8.cpp)
# add_executable(item9 item9.cpp)
# add_executable(item10 item10.cpp)

# add_executable(function function.cpp)

FILE(GLOB CPPFILES "*.cpp")

foreach(CPPFILE ${CPPFILES})
    get_filename_component(FILE_NAME ${CPPFILE} NAME_WE)
    add_executable(${FILE_NAME} ${CPPFILE})
    target_link_libraries(${FILE_NAME} pthread)
endforeach()
