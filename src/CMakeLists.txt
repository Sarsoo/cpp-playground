add_executable(cppScratch main.cpp)

FetchContent_Declare(
    json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2
)

FetchContent_MakeAvailable(json)

target_link_libraries(cppScratch PRIVATE nlohmann_json::nlohmann_json dal library)