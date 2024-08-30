itk_module_test()

set(NornirTests
  itkCompileTest.cxx
  )

CreateTestDriver(Nornir "${Nornir-Test_LIBRARIES}" "${NornirTests}")
