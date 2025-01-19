cmake_minimum_required(VERSION 3.10)


project(mysh)

include_directories(${PROJECT_SOURCE_DIR}/includes)

# 添加可执行文件
add_executable(main src/main.c)

# 添加共享库
add_library(builtin SHARED src/utils/builtin.c)
add_library(exec SHARED src/utils/exec.c)
add_library(user SHARED src/utils/user.c)

# 链接共享库
target_link_libraries(main builtin exec user)
target_link_libraries(main readline)
