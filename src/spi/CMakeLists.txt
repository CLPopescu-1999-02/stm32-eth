
add_cpp_library(stm32-spiwriter OBJECT SpiWriter.cpp)
target_link_libraries(stm32-spiwriter PRIVATE SYSTEM stm32hal-api)

