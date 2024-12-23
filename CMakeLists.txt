project(fr)
set(CMAKE_CXX_COMPILER gcc)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)                   

file(GLOB sources *.cpp)
				   
set(THREADS_PREFER_PTHREAD_FLAG ON)                 
find_package(Threads REQUIRED)                    

add_executable(${PROJECT_NAME}   STATIC ${sources} )


set_target_properties(${PROJECT_NAME} PROPERTIES
 COMPILE_FLAGS " -pthread "
 LINKER_FLAGS ""
)


target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})
          
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
target_link_options(${PROJECT_NAME} PRIVATE -pthread)

# Add any additional linker flags
target_link_options(${PROJECT_NAME} PRIVATE $(LINKER_FLAGS))

# Link against required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs stdc++)



