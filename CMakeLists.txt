cmake_minimum_required(VERSION 3.15)

set(__the_PROJECT_NAME pipeline)
project(${__the_PROJECT_NAME}
  DESCRIPTION "流水线"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src/inc)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

function(add_source_group_executable)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_executable(${ARGV})
endfunction(add_source_group_executable)

aux_source_directory(src SRC_LIST)
file(GLOB_RECURSE INC_LIST src/inc/*.h src/inc/*.hxx)

add_source_group_executable(${__the_PROJECT_NAME} ${SRC_LIST} ${INC_LIST})
# add_executable(${__the_PROJECT_NAME} ${SRC_LIST} ${INC_LIST})
