#source files
set(SOURCE_FILES
        main.cpp
        Game.cpp
        Item.cpp
        Worm.cpp
)

#find SFML library
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

#build and link
add_executable(BattleWorms ${SOURCE_FILES})
target_link_libraries(BattleWorms ${SFML_LIBRARIES})
