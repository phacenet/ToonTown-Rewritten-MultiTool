cmake_minimum_required(VERSION 3.28)
project(proj)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# stop namespace collision for Qt's emit and libsodium's internal emit
add_compile_definitions(QT_NO_EMIT)

# Output exe name — separate from the CMake target name so hyphens are safe
set(EXE_NAME "TTR-MultiTool")

#QT
if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/msvc2022_64" ${CMAKE_PREFIX_PATH})
endif()
find_package(Qt6 REQUIRED COMPONENTS
	Widgets
	Network
	WebEngineWidgets
)
qt_standard_project_setup()

#libcurl
find_package(CURL REQUIRED)

#libsodium
if(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(SODIUM REQUIRED libsodium)
elseif(WIN32)
	find_package(unofficial-sodium CONFIG REQUIRED)
endif()

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

# Force C++17 for both the non-TLS and TLS sioclient targets
# (websocketpp is incompatible with C++20)
foreach(sio_target sioclient sioclient_tls)
	if(TARGET ${sio_target})
		set_target_properties(${sio_target} PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
		)
		target_link_libraries(${sio_target} PRIVATE
			OpenSSL::SSL
			OpenSSL::Crypto
		)
		if(WIN32)
			target_link_libraries(${sio_target} PRIVATE unofficial-sodium::sodium)
		else()
			target_link_libraries(${sio_target} PRIVATE ${SODIUM_LIBRARIES})
		endif()
		if(MSVC)
			target_compile_options(${sio_target} PRIVATE /wd4996)
		else()
			target_compile_options(${sio_target} PRIVATE -Wno-deprecated-declarations)
		endif()
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

# Rename the output binary from "proj" to EXE_NAME
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${EXE_NAME}")

# Copy config/ next to the exe after every build (fonts, icons, etc.)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/config
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/config
	COMMENT "Copying config/ to output directory..."
)

# link libs
target_link_libraries(${PROJECT_NAME} PRIVATE
	CURL::libcurl
	Qt6::Widgets
	Qt6::Network
	Qt6::WebEngineWidgets
	sioclient_tls
	OpenSSL::SSL
	OpenSSL::Crypto
)

# libsodium for main app
if(UNIX)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${SODIUM_LIBRARIES})
	target_include_directories(${PROJECT_NAME} PRIVATE ${SODIUM_INCLUDE_DIRS})
elseif(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE unofficial-sodium::sodium)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE SIO_TLS)

# Platform-specific input handling
if(UNIX)
	target_sources(${PROJECT_NAME} PRIVATE src/usr/direct_inputs_x11.cpp)
	find_package(X11 REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE X11::X11)
elseif(WIN32)
	target_sources(${PROJECT_NAME} PRIVATE src/usr/direct_inputs_win32.cpp)
	target_link_libraries(${PROJECT_NAME} PRIVATE user32)
endif()

# include paths
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/src/usr
)

# -------------------------------------------------------------------------
# Windows deployment
# -------------------------------------------------------------------------
if(WIN32)
	# Locate windeployqt from the Qt prefix rather than hardcoding the path.
	find_program(WINDEPLOYQT
		NAMES windeployqt windeployqt6
		HINTS "C:/Qt/6.11.1/msvc2022_64/bin"
		      "${Qt6_DIR}/../../../bin"
		REQUIRED
	)

	# Copy non-Qt runtime DLLs (libcurl, OpenSSL, libsodium, etc.) next to
	# the exe for every build type so the build directory is always runnable.
	# TARGET_RUNTIME_DLLS walks all linked imported targets automatically.
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND_EXPAND_LISTS
		COMMENT "Copying runtime DLLs (curl, OpenSSL, sodium)..."
	)

	# Only run windeployqt on Release builds — no point deploying Qt DLLs
	# during debug iteration, and it adds noticeable build time.
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "$<$<CONFIG:Release>:${WINDEPLOYQT}>"
			--release
			--no-translations        # saves ~20 MB
			--no-system-d3d-compiler # saves ~5 MB, not needed at runtime
			--no-opengl-sw           # saves ~15 MB; skip Mesa fallback
			                         # (users running TTR already have a GPU)
			"$<TARGET_FILE:${PROJECT_NAME}>"
		COMMENT "Running windeployqt..."
		VERBATIM
	)
endif()

# -------------------------------------------------------------------------
# Install rules  (used by CPack below and by cmake --install)
# -------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/config" DESTINATION .)

# Install non-Qt runtime DLLs (libcurl, OpenSSL, libsodium).
# windeployqt handles Qt's own DLLs in the install(CODE) block below.
if(WIN32)
	install(FILES $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> DESTINATION .)
endif()

# Run windeployqt against the install prefix so CPack gets the Qt DLLs too.
# The post-build step above only covers the build tree.
if(WIN32)
	install(CODE "
		execute_process(
			COMMAND \"${WINDEPLOYQT}\"
				--release
				--no-translations
				--no-system-d3d-compiler
				--no-opengl-sw
				\"\${CMAKE_INSTALL_PREFIX}/${EXE_NAME}.exe\"
		)
	")
endif()

# -------------------------------------------------------------------------
# CPack  (run: cpack -C Release  after a Release build)
# -------------------------------------------------------------------------
set(CPACK_GENERATOR "ZIP")           # produces TTR-MultiTool-x.y.z-win64.zip
                                     # switch to "NSIS" for a click-through installer
set(CPACK_PACKAGE_NAME "TTR-MultiTool")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "hunter")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Toontown Rewritten MultiTool")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")

include(CPack)   # must be the last line
