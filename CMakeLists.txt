cmake_minimum_required (VERSION 3.3)
# 设置C/C++标准
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# 声明一个项目
project(DirectXLittleMaster)
# 我们使用Unicode字符编码
add_definitions(-D "UNICODE")
add_definitions(-D "_UNICODE")
# 获取程序的源文件和头文件
file(GLOB_RECURSE src source/*.cxx source/*.c source/*.cc source/*.cpp)
file(GLOB_RECURSE headers source/*.hpp source/*.h source/*.hh)
# 添加程序目标
add_executable(DirectXLittleMaster ${src} ${headers})
# 定义目标的包含路径
target_include_directories(DirectXLittleMaster PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 将目标链接到windows的一些API上
set(PLATFORM_FRAMEWORKS psapi user32 advapi32 iphlpapi userenv ws2_32)
target_link_libraries(DirectXLittleMaster PRIVATE ${PLATFORM_FRAMEWORKS})
# 添加目录结构
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${headers})
