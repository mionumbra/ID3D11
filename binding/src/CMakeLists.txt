set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

# =============================================================================
# GameMaker iOS integration (optional)
# =============================================================================
# Keep these as optional cache entries. A real user value must survive
# regeneration and must not be replaced by the template placeholder.
set(EXT_GM_XCODEPROJ_OVERRIDE "" CACHE STRING "Override GM .xcodeproj (optional)")
set(EXT_GM_APP_TARGET_OVERRIDE "" CACHE STRING "Override GM app target (optional)")

# extgen's root template defaults to the repository parent. Redirect only that
# untouched default while preserving an explicit caller-provided output path.
if(EXT_OUTPUT_DIR STREQUAL "../")
  set(EXT_OUTPUT_DIR "../extensions/ID3D11" CACHE STRING
      "Where to copy the final built binary" FORCE)
endif()

# =============================================================================
# Public headers for Apple XCFramework packaging
# Users should edit these to match their project structure.
# The packager will copy these into a headers folder passed to xcodebuild.
# =============================================================================
set(EXT_PUBLIC_HEADERS_IOS
    "${CMAKE_SOURCE_DIR}/src/ios/${PROJECT_NAME}_ios.h;${CMAKE_SOURCE_DIR}/code_gen/ios/${PROJECT_NAME}Internal_ios.h"
    CACHE STRING "Semicolon-separated list of public headers to embed in the iOS xcframework")

set(EXT_PUBLIC_HEADERS_TVOS
    "${CMAKE_SOURCE_DIR}/src/tvos/${PROJECT_NAME}_tvos.h;${CMAKE_SOURCE_DIR}/code_gen/tvos/${PROJECT_NAME}Internal_tvos.h"
    CACHE STRING "Semicolon-separated list of public headers to embed in the tvOS xcframework")

# =============================================================================
# User implementation sources per platform (editable template)
# =============================================================================
if(WIN32)
  file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/native/*.cpp")

elseif(APPLE)
  if(CMAKE_OSX_SYSROOT MATCHES "iphone")
    file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/ios/*.mm" "${SRC_DIR}/ios/*.cpp" "${SRC_DIR}/ios/*.swift")
  elseif(CMAKE_OSX_SYSROOT MATCHES "appletv")
    file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/tvos/*.mm" "${SRC_DIR}/tvos/*.cpp" "${SRC_DIR}/tvos/*.swift")
  else()
    file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/native/*.mm" "${SRC_DIR}/native/*.cpp" "${SRC_DIR}/native/*.swift")
  endif()

elseif(ANDROID)
  file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/android/*.cpp")

elseif(UNIX)
  file(GLOB TARGET_SRCS CONFIGURE_DEPENDS "${SRC_DIR}/native/*.cpp")
endif()

target_sources(${PROJECT_NAME} PRIVATE ${TARGET_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

if(WIN32)
  target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
  target_link_libraries(${PROJECT_NAME} PRIVATE d3d11 dxgi d3dcompiler)
endif()
