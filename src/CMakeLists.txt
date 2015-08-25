
cmake_minimum_required(VERSION 2.8)

project(JLApplication)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_module/")
find_package(Boost COMPONENTS system filesystem thread REQUIRED)
find_package(Readline MODULE REQUIRED)

set(CGDG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/libCGDG)
set(CGDG_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

link_directories(${CGDG_LIB_DIR})
include_directories(${Boost_INCLUDE_DIR} ${CGDG_INCLUDE_DIR} 
${READLINE_INCLUDE_DIR})

set(SRCS Application.cpp BfsData.cpp Invoker.cpp SearchTree.cpp
Arguments.cpp BrokerAgent.cpp JobLevelCommands.cpp SearchTreeCommands.cpp
AsyncSocket.cpp CommandsEngine.cpp JobLevelConfigure.cpp UctData.cpp
CommonBfJlModules.cpp ConfigureLoader.cpp JobLevelMiddleware.cpp UctHandler.cpp
BfsHandler.cpp Connect6Move.cpp Node.cpp main.cpp BaseData.cpp 
CgiHandler.cpp Point.cpp strops.cpp GameHandler.cpp GoMove.cpp ProgramOption.cpp
SgfSerializer.cpp GameParser.cpp CgiParser.cpp JobLevelManager.cpp
SearchTreeBrowser.cpp Nctu6Handler.cpp Nctu6Parser.cpp
MiniMaxHandler.cpp CgiUctRetriever.cpp Nctu6UctRetriever.cpp)

add_executable(JLApplication ${SRCS})

set(LIBS ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} 
${Boost_THREAD_LIBRARY} ${Readline_LIBRARY})
target_link_libraries(JLApplication ${LIBS} debug -lCGDG-d optimized -lCGDG)

