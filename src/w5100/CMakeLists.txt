
add_cpp_library(stm32-w5100device OBJECT Device.cpp)
target_link_libraries(stm32-w5100device PRIVATE GSL::GSL SYSTEM stm32hal-api)
