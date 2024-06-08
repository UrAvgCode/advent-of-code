# 2023/CMakeLists.txt

add_executable(hot_springs day_12/hot_springs.cpp day_12/hot_springs.h)
add_executable(clumsy_crucible day_17/clumsy_crucible.cpp day_17/clumsy_crucible.h)

if (TBB_FOUND)
    target_compile_definitions(hot_springs PRIVATE PARALLEL)
    target_link_libraries(hot_springs PRIVATE TBB::tbb)
endif ()
