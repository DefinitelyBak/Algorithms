# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(benchmark_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(benchmark_FRAMEWORKS_FOUND_RELEASE "${benchmark_FRAMEWORKS_RELEASE}" "${benchmark_FRAMEWORK_DIRS_RELEASE}")

set(benchmark_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET benchmark_DEPS_TARGET)
    add_library(benchmark_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET benchmark_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${benchmark_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${benchmark_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:benchmark::benchmark>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### benchmark_DEPS_TARGET to all of them
conan_package_library_targets("${benchmark_LIBS_RELEASE}"    # libraries
                              "${benchmark_LIB_DIRS_RELEASE}" # package_libdir
                              "${benchmark_BIN_DIRS_RELEASE}" # package_bindir
                              "${benchmark_LIBRARY_TYPE_RELEASE}"
                              "${benchmark_IS_HOST_WINDOWS_RELEASE}"
                              benchmark_DEPS_TARGET
                              benchmark_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "benchmark"    # package_name
                              "${benchmark_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${benchmark_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT benchmark::benchmark_main #############

        set(benchmark_benchmark_benchmark_main_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(benchmark_benchmark_benchmark_main_FRAMEWORKS_FOUND_RELEASE "${benchmark_benchmark_benchmark_main_FRAMEWORKS_RELEASE}" "${benchmark_benchmark_benchmark_main_FRAMEWORK_DIRS_RELEASE}")

        set(benchmark_benchmark_benchmark_main_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET benchmark_benchmark_benchmark_main_DEPS_TARGET)
            add_library(benchmark_benchmark_benchmark_main_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET benchmark_benchmark_benchmark_main_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'benchmark_benchmark_benchmark_main_DEPS_TARGET' to all of them
        conan_package_library_targets("${benchmark_benchmark_benchmark_main_LIBS_RELEASE}"
                              "${benchmark_benchmark_benchmark_main_LIB_DIRS_RELEASE}"
                              "${benchmark_benchmark_benchmark_main_BIN_DIRS_RELEASE}" # package_bindir
                              "${benchmark_benchmark_benchmark_main_LIBRARY_TYPE_RELEASE}"
                              "${benchmark_benchmark_benchmark_main_IS_HOST_WINDOWS_RELEASE}"
                              benchmark_benchmark_benchmark_main_DEPS_TARGET
                              benchmark_benchmark_benchmark_main_LIBRARIES_TARGETS
                              "_RELEASE"
                              "benchmark_benchmark_benchmark_main"
                              "${benchmark_benchmark_benchmark_main_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET benchmark::benchmark_main
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_LIBRARIES_TARGETS}>
                     )

        if("${benchmark_benchmark_benchmark_main_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET benchmark::benchmark_main
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         benchmark_benchmark_benchmark_main_DEPS_TARGET)
        endif()

        set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_LIB_DIRS_RELEASE}>)
        set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_main_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT benchmark::benchmark #############

        set(benchmark_benchmark_benchmark_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(benchmark_benchmark_benchmark_FRAMEWORKS_FOUND_RELEASE "${benchmark_benchmark_benchmark_FRAMEWORKS_RELEASE}" "${benchmark_benchmark_benchmark_FRAMEWORK_DIRS_RELEASE}")

        set(benchmark_benchmark_benchmark_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET benchmark_benchmark_benchmark_DEPS_TARGET)
            add_library(benchmark_benchmark_benchmark_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET benchmark_benchmark_benchmark_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'benchmark_benchmark_benchmark_DEPS_TARGET' to all of them
        conan_package_library_targets("${benchmark_benchmark_benchmark_LIBS_RELEASE}"
                              "${benchmark_benchmark_benchmark_LIB_DIRS_RELEASE}"
                              "${benchmark_benchmark_benchmark_BIN_DIRS_RELEASE}" # package_bindir
                              "${benchmark_benchmark_benchmark_LIBRARY_TYPE_RELEASE}"
                              "${benchmark_benchmark_benchmark_IS_HOST_WINDOWS_RELEASE}"
                              benchmark_benchmark_benchmark_DEPS_TARGET
                              benchmark_benchmark_benchmark_LIBRARIES_TARGETS
                              "_RELEASE"
                              "benchmark_benchmark_benchmark"
                              "${benchmark_benchmark_benchmark_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET benchmark::benchmark
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_LIBRARIES_TARGETS}>
                     )

        if("${benchmark_benchmark_benchmark_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET benchmark::benchmark
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         benchmark_benchmark_benchmark_DEPS_TARGET)
        endif()

        set_property(TARGET benchmark::benchmark APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET benchmark::benchmark APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET benchmark::benchmark APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_LIB_DIRS_RELEASE}>)
        set_property(TARGET benchmark::benchmark APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET benchmark::benchmark APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${benchmark_benchmark_benchmark_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_LINK_LIBRARIES benchmark::benchmark_main)
    set_property(TARGET benchmark::benchmark_main APPEND PROPERTY INTERFACE_LINK_LIBRARIES benchmark::benchmark)

########## For the modules (FindXXX)
set(benchmark_LIBRARIES_RELEASE benchmark::benchmark_main)
