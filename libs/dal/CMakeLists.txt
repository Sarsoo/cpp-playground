set(LIB_NAME "dal")

add_library(${LIB_NAME} src/lib.cpp src/secret.cpp)

FetchContent_Declare(
    libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG        7.7.5
)

FetchContent_MakeAvailable(libpqxx)

# We need this directory, and users of our library will need it too
target_include_directories(${LIB_NAME} PUBLIC ../../include PRIVATE ./include)
target_link_libraries(${LIB_NAME} PUBLIC pqxx)

# All users of this library will need at least C++11
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})