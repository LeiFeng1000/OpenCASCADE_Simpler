add_executable(Make main.cpp)

target_include_directories(Make PRIVATE ${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(Make PRIVATE 
    ${OpenCASCADE_LIBRARIES}
)
target_include_directories(Make PRIVATE ${CMAKE_SOURCE_DIR}/Common)