# Install script for directory: /mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Animation/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Audio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Camera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ConvertScene/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportDocument/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportScene01/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportScene02/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportScene03/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportScene04/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportScene05/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExportShader/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ExternalDocsRefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/FileStream/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ImportScene/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Instances/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Layers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Normals/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Pivot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ProceduralTexture/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ShapeAttributes/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/StereoCamera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/SwitchBinding/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/Transformations/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/UserProperties/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/UVSample/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/ViewScene/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/mnt/hgfs/software/後期/SoftwareTeamDevelopment/fbx202037_fbxsdk_gcc_linux/samples/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
