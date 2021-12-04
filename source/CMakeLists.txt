# learn OpenGL

cmake_minimum_required(VERSION 3.8) 

project(OpenGL)

# 设置一些编译时变量
set(CMAKE_CONFIGURATION_TYPES "Debug;Release") 
set(CMAKE_CXX_FLAGS "/DWIN64 /D_WINDOWS /D_USRDLL /Zi /nologo /W3 /WX /MP  /EHsc -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS /wd4250 /wd4251 /wd4996 /wd4267") 
set(CMAKE_CXX_FLAGS_RELEASE "/Od /MD /DNDEBUG") 
set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd /D_DEBUG") 

set(Platform "$(Platform)")
set(Configuration "$(Configuration)")
set(ProjectName "$(ProjectName)")

set(Demo ${CMAKE_CURRENT_SOURCE_DIR}/Demo) 

set(THIRD_PARTY_GLFW_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/include/GLFW)
set(THIRD_PARTY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/lib/$(Configuration))

# 链接库目录
link_directories(${PROJECT_BINARY_DIR}/../$(Platform)$(Configuration)) 


# 添加子目录
add_subdirectory(Demo)


# 设置输出目录
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} ) 
string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG ) 
set_target_properties(Demo PROPERTIES   RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG}  ${PROJECT_BINARY_DIR}/../$(Platform)$(Configuration) ) 
set_target_properties(Demo PROPERTIES   LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG}  ${PROJECT_BINARY_DIR}/../$(Platform)$(Configuration) ) 
set_target_properties(Demo PROPERTIES   ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG}  ${PROJECT_BINARY_DIR}/../$(Platform)$(Configuration) ) 
endforeach( OUTPUTCONFIG ) 


# 设置文件夹层级关系
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 
set_property(TARGET Demo PROPERTY FOLDER "OpenGL") 
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Demo")   # 设置启动项

