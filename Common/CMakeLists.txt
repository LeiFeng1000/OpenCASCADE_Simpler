file(GLOB hed_files "*.h")
file(GLOB src_files "*.cpp")

add_library(Common ${hed_files} ${src_files}) 

find_package(OpenCASCADE REQUIRED)
find_package(Freetype REQUIRED)

target_include_directories(Common PRIVATE ${OpenCASCADE_INCLUDE_DIR})
message(${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(Common PRIVATE Freetype::Freetype
    
)