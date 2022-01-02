# learn opengl 子目录
 
set(TARGET_NAME  Demo ) 

 
# inlude 头文件目录 
include_directories( 
 ${Demo} 
 ${Demo}//glad 
 ) 
 
include_directories(
${THIRD_PARTY_GLFW_INCLUDE}
${THIRD_PARTY_GLM_INCLUDE}
${THIRD_PARTY_ASSIMP_INCLUDE}
)
 
 
link_directories(
${THIRD_PARTY_GLFW_LIB}
${THIRD_PARTY_ASSIMP_LIB}
)
 
link_libraries(
opengl32.lib
glfw3.lib
assimp.lib
)


# cpp 文件夹
file(GLOB RootFiles *.cpp *.h *.rc *.ico *.json *.bat) 
source_group("" FILES ${RootFiles}) 

# 生成 glad 文件夹
file(GLOB gladFiles ${CMAKE_CURRENT_SOURCE_DIR}/glad/*.*) 
source_group("glad" FILES ${gladFiles}) 
 
set(ALL_DEMO_SRC ${RootFiles} ${gladFiles})
 
file(GLOB_RECURSE CppFiles *.cpp) 
IF(NOT CppFiles) 
    set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX   LINK_FLAGS  /NOENTRY) 
ENDIF(NOT CppFiles) 
 
add_executable(${TARGET_NAME} ${ALL_DEMO_SRC})
# 添加依赖模块
#dd_dependencies
