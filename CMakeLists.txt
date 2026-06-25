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
qt_add_executable(${PROJECT_NAME} WIN32
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
	target_sources(${PROJECT_NAME} PRIVATE app.rc) #exe icon
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

	# --------------------------------------------------------------------------
	# Third-party DLL deployment (libcurl, OpenSSL, libsodium, zlib)
	#
	# TARGET_RUNTIME_DLLS silently skips targets that vcpkg declares as
	# UNKNOWN IMPORTED rather than SHARED IMPORTED — OpenSSL does this.
	# Instead, derive the vcpkg bin directory from CURL::libcurl (which vcpkg
	# does declare correctly) and glob the specific DLLs we need.
	# --------------------------------------------------------------------------
	get_target_property(_curl_dll CURL::libcurl IMPORTED_LOCATION_RELEASE)
	if(NOT _curl_dll OR _curl_dll MATCHES "NOTFOUND")
		get_target_property(_curl_dll CURL::libcurl IMPORTED_LOCATION)
	endif()

	# IMPORTED_LOCATION is the DLL itself for SHARED targets; for targets where
	# it points to the .lib, look in the sibling bin/ directory instead.
	if(_curl_dll MATCHES "\\.dll$")
		get_filename_component(_vcpkg_bin "${_curl_dll}" DIRECTORY)
	else()
		get_filename_component(_vcpkg_lib_dir "${_curl_dll}" DIRECTORY)
		set(_vcpkg_bin "${_vcpkg_lib_dir}/../bin")
		cmake_path(NORMAL_PATH _vcpkg_bin)
	endif()

	file(GLOB _third_party_dlls
		"${_vcpkg_bin}/libcurl*.dll"
		"${_vcpkg_bin}/libssl*.dll"
		"${_vcpkg_bin}/libcrypto*.dll"
		"${_vcpkg_bin}/libsodium*.dll"
		"${_vcpkg_bin}/zlib1.dll"    # vcpkg names it zlib1, not z
		"${_vcpkg_bin}/z.dll"        # keep as fallback
	)

	if(NOT _third_party_dlls)
		message(WARNING
			"No third-party DLLs found in ${_vcpkg_bin}. "
			"The packaged app will be missing libcurl/OpenSSL/libsodium.")
	else()
		message(STATUS "Third-party DLLs to deploy: ${_third_party_dlls}")
	endif()

	# Copy third-party DLLs next to the exe on every build (Debug and Release)
	# so the build directory is always runnable.
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${_third_party_dlls}
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND_EXPAND_LISTS
		COMMENT "Copying third-party DLLs (curl, OpenSSL, sodium, zlib)..."
	)

	# Run windeployqt only on Release builds — Qt DLL deployment is slow and
	# not needed during debug iteration.
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "$<$<CONFIG:Release>:${WINDEPLOYQT}>"
			--release
			--no-translations        # saves ~20 MB
			--no-system-d3d-compiler # saves ~5 MB
			--no-opengl-sw           # saves ~15 MB; TTR users have a GPU
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

if(WIN32)
	# Third-party DLLs
	install(FILES ${_third_party_dlls} DESTINATION .)

	# Qt DLLs — run windeployqt against the staging directory
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
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "TTR-MultiTool")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "hunter")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Toontown Rewritten MultiTool")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")

include(CPack)   # must be the last line
