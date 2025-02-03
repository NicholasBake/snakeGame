# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-src"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-build"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/nicholas/E/ThermusGameEngine/Engine/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
