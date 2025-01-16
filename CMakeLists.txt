cmake_minimum_required(VERSION 3.10)

project(mysh)

include_directories(${PROJECT_SOURCE_DIR}/includes)

# 添加可执行文件
add_executable(shared_main src/main.c)
add_executable(static_main src/main.c)

# 添加共享库
add_library(shared_builtin SHARED src/utils/builtin.c)
add_library(shared_exec SHARED src/utils/exec.c)
add_library(shared_user SHARED src/utils/user.c)

# 添加静态库
add_library(static_builtin STATIC src/utils/builtin.c)
add_library(static_exec STATIC src/utils/exec.c)
add_library(static_user STATIC src/utils/user.c)

# 链接静态库
target_link_libraries(static_exec static_builtin)
target_link_libraries(static_user static_exec)

# 链接共享库
target_link_libraries(shared_main shared_builtin shared_exec shared_user)

# 链接静态库到静态可执行文件
target_link_libraries(static_main static_user)

# 设置静态链接标志
set_target_properties(static_main static_user static_exec static_builtin PROPERTIES LINK_FLAGS "-static")
