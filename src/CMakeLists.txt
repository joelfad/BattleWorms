#source files
set(SOURCE_FILES main.cpp game.cpp)

#build and link
add_executable(BattleWorms ${SOURCE_FILES})
target_link_libraries(BattleWorms ${SFML_LIBRARIES})
