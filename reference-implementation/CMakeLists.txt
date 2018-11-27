cmake_minimum_required(VERSION 3.5)
project(libsmalltime VERSION 1.0.0 LANGUAGES C CXX)

#Make sure that custom modules are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)


##############################################
# Create target and set properties

add_library(smalltime
    src/library.c
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(SMALLTIME::smalltime ALIAS smalltime)

#Set target properties
target_include_directories(smalltime
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(smalltime PRIVATE cxx_auto_type)
target_compile_options(smalltime PRIVATE $<$<CXX_COMPILER_ID:GNU>:
    -Wall
    -Wextra
#    -Wduplicated-cond
#    -Wduplicated-branches
    -Wlogical-op
#    -Wrestrict
#    -Wnull-dereference
    -Wjump-misses-init
    -Wdouble-promotion
    -Wshadow
    -fstrict-aliasing
    -Wformat=2
>)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/smalltime)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS smalltime
    EXPORT smalltime-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name smalltime and not smalltime
set_target_properties(smalltime PROPERTIES EXPORT_NAME smalltime)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT smalltime-targets
  FILE
    smalltimeTargets.cmake
  NAMESPACE
    SMALLTIME::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SmalltimeConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/SmalltimeConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SmalltimeConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SmalltimeConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SmalltimeConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT smalltime-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/SmalltimeTargets.cmake NAMESPACE SMALLTIME::)

#Register package in user's package registry
export(PACKAGE smalltime)

add_subdirectory(test)
