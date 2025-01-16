cmake_minimum_required(VERSION 3.10)

project(mysh)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(shared_main src/main.c)
add_executable(static_main src/main.c)

add_library(shared_builtin SHARED src/utils/builtin.c)
add_library(static_builtin STATIC src/utils/builtin.c)

add_library(shared_exec SHARED src/utils/exec.c)
add_library(static_exec STATIC src/utils/exec.c)

add_library(shared_user SHARED src/utils/user.c)
add_library(static_user STATIC src/utils/user.c)

target_link_libraries(static_exec static_builtin)
target_link_libraries(static_user static_exec)

target_link_libraries(shared_main shared_builtin shared_exec shared_user)
target_link_libraries(static_main static_user)

set_target_properties(static_main static_user static_exec static_builtin PROPERTIES LINK_FLAGS "-static")
