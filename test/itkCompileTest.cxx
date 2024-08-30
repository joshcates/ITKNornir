#include <itkImageMaskSpatialObject.h>
#include <list>

template <typename T>
inline std::list<T>
operator+(const T & a, const T & b)
{
  std::list<T> ab;
  ab.push_back(a);
  ab.push_back(b);
  return ab;
}

typedef itk::ImageMaskSpatialObject<2> mask_so_t;

int
itkCompileTest(int argc, char * argv[])
{
  mask_so_t::Pointer testVar = mask_so_t::New();
  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
