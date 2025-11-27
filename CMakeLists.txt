cmake_minimum_required(VERSION 3.6.0)
project(cfm)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
	"${PROJECT_SOURCE_DIR}/src/cfm/*"
	
)
add_library(cfm SHARED ${SRCS})
add_library(cfm STATIC ${SRCS})

