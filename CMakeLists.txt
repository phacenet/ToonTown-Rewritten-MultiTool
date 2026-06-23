cmake_minimum_required(VERSION 3.28)
project(proj)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# stop namespace collision for Qt's emit and libsodium's internal emit
add_compile_definitions(QT_NO_EMIT)

#libcurl
find_package(CURL REQUIRED)

#QT
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
qt_standard_project_setup()

#libsodium
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

#openssl
find_package(OpenSSL REQUIRED)

#socket.io-client-cpp
include(FetchContent)
FetchContent_Declare(
	socketio
	GIT_REPOSITORY https://github.com/socketio/socket.io-client-cpp.git
	GIT_TAG 3b7be7e4173b5bdeed393966e3274f65d513a280
	GIT_SHALLOW ON
	PATCH_COMMAND git apply -p0 ${CMAKE_SOURCE_DIR}/patches/sio_client_impl_alpn.patch
)
FetchContent_MakeAvailable(socketio)

# Force C++17 for both the non-TLS and TLS sioclient targets (websocketpp incompatible with C++20)
foreach(sio_target sioclient sioclient_tls)
    if(TARGET ${sio_target})
        set_target_properties(${sio_target} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
        )
        target_compile_options(${sio_target} PRIVATE -Wno-deprecated-declarations)
    endif()
endforeach()

#cpp files
qt_add_executable(${PROJECT_NAME}
	src/usr/mainwindow.ui
	src/usr/mainwindow.hpp
	src/usr/mainwindow.cpp
	src/main.cpp
	src/usr/ttr_api_reqs.cpp
	src/usr/encryption.cpp
	src/usr/file_detect.cpp
	src/usr/adblocker.cpp
)

#libcurl
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
#QT
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)
#QT webengine
find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)
target_link_libraries(proj PRIVATE Qt6::WebEngineWidgets)
#libsodium
target_link_libraries(${PROJECT_NAME} PRIVATE ${SODIUM_LIBRARIES})
#openssl + socket.io-client-cpp (TLS variant + SIO_TLS define required for ALPN fix to compile in)
target_link_libraries(${PROJECT_NAME} PRIVATE sioclient_tls OpenSSL::SSL OpenSSL::Crypto)
target_compile_definitions(${PROJECT_NAME} PRIVATE SIO_TLS)

#X11 for UNIX vs WIN32 libs
if(UNIX)
    target_sources(proj PRIVATE src/usr/direct_inputs_x11.cpp)
    find_package(X11 REQUIRED)
    target_link_libraries(proj PRIVATE X11::X11)
elseif(WIN32)
    target_sources(proj PRIVATE src/usr/direct_inputs_win32.cpp)
    target_link_libraries(proj PRIVATE user32)
endif()


target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/src/usr
	${SODIUM_INCLUDE_DIRS}
)
