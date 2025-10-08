project(main)
set(CMAKE_CXX_STANDARD 17)

FILE(GLOB CPP_FILES "*.cpp")

foreach(CPP_FILE ${CPP_FILES})
  get_filename_component(F_NAME ${CPP_FILE}  NAME_WE)
  add_executable(${F_NAME} ${CPP_FILE})
endforeach()
