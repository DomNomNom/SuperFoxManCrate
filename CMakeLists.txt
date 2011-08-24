CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(VERSION 2.6)
PROJECT(sfmc)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

SET(FLAGS "${FLAGS} -g")

#FIND_PACKAGE(SFML REQUIRED)

SET(SRCS
  ./main.cpp 
  ./player.cpp 
  ./physics.cpp 
  ./platform.cpp 
  ./collisionObject.cpp 
  ./level.cpp 
  ./box.cpp
  ./enemy.cpp
  ./spawner.cpp
  ./spawnPoint.cpp
  ./bullets/bullet.cpp
  ./bullets/explosion.cpp
  ./guns/gun.cpp
  )

SET(PROGRAMS sfmc)

#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

ADD_EXECUTABLE(sfmc ${SRCS})

TARGET_LINK_LIBRARIES(sfmc
  #${SFML_LIBRARY}
  -lsfml-graphics
  -lsfml-audio
  -lsfml-window
  -lsfml-network
  -lsfml-system
  )

INSTALL(TARGETS sfmc RUNTIME DESTINATION .)

SET_TARGET_PROPERTIES(sfmc PROPERTIES COMPILE_FLAGS "${FLAGS}")
