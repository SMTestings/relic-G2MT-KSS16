# Install script for directory: /home/zyh/Documents/relic-main-subgroupmenber_kss16330

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE FILE FILES
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_alloc.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_arch.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_bc.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_bench.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_bn.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_core.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_cp.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_dv.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_eb.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_ec.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_ed.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_ep.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_epx.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_err.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_fb.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_fbx.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_fp.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_fpx.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_label.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_md.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_mpc.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_multi.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_pc.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_pp.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_rand.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_test.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_types.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/relic_util.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic/low" TYPE FILE FILES
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/low/relic_bn_low.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/low/relic_dv_low.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/low/relic_fb_low.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/low/relic_fp_low.h"
    "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/include/low/relic_fpx_low.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE DIRECTORY FILES "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/build/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/cmake/relic-config.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/zyh/Documents/relic-main-subgroupmenber_kss16330/build/src/cmake_install.cmake")
  include("/home/zyh/Documents/relic-main-subgroupmenber_kss16330/build/test/cmake_install.cmake")
  include("/home/zyh/Documents/relic-main-subgroupmenber_kss16330/build/bench/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/zyh/Documents/relic-main-subgroupmenber_kss16330/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
