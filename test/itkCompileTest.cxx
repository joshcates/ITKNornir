#include <list>
#include <itkImageMaskSpatialObject.h>

template <typename T>
inline std::list<T>
operator+(const T & a, const T & b)
{
  std::list<T> ab;
  ab.push_back(a);
  ab.push_back(b);
  return ab;
}

int
itkCompileTest(int argc, char * argv[])
{
  auto testVar = itk::ImageMaskSpatialObject<2>::New();
  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
