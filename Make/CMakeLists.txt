add_executable(Make main.cpp)

find_package(OpenCASCADE REQUIRED)
find_package(Freetype REQUIRED)

target_include_directories(Make PRIVATE ${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(Make PRIVATE 
    ${OpenCASCADE_LIBRARIES} Freetype::Freetype Common
)
target_include_directories(Make PRIVATE ${CMAKE_SOURCE_DIR}/Common)