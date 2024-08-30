set(Nornir_SRCS
  placeholder.cxx  # At least one file is required by CMake to create a library
)

itk_module_add_library(Nornir ${Nornir_SRCS})
