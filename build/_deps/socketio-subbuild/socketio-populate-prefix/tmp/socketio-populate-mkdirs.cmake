# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/hunter/proj/ta/build/_deps/socketio-src"
  "/home/hunter/proj/ta/build/_deps/socketio-build"
  "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix"
  "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/tmp"
  "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/src/socketio-populate-stamp"
  "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/src"
  "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/src/socketio-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/src/socketio-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/hunter/proj/ta/build/_deps/socketio-subbuild/socketio-populate-prefix/src/socketio-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
