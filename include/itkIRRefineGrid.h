/*=========================================================================
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkIRRefineGrid_h
#define itkIRRefineGrid_h

// Local ir-specific includes
#include "itkIRCommon.h"
#include "IRMosaicRefinementCommon.h"
#include "itkImageMosaicVarianceMetric.h"
#include "itkRadialDistortionTransform.h"
#include "itkLegendrePolynomialTransform.h"
#include "itkRegularStepGradientDescentOptimizer2.h"
#include "itkMeshTransform.h"
#include "itkIRDynamicArray.h"
#include "IRPath.h"
#include "itkGridTransform.h"

//#include "utils/the_dynamic_array.hxx"
//#include "thread/the_boost_mutex.hxx" -> IRStdMutex.h?
//#include "thread/the_boost_thread.hxx" -> IRStdThread.h?

// system includes:
#include <math.h>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>

// ITK includes:
#include <itkDiscreteGaussianImageFilter.h>
#include <itkShrinkImageFilter.h>


//#include "UsageReader.h"

//----------------------------------------------------------------
// SAVE_INTERMEDIATE_MOSAIC
// 
#define SAVE_INTERMEDIATE_MOSAIC


//----------------------------------------------------------------
// optimizer_t
//
typedef itk::RegularStepGradientDescentOptimizer2 optimizer_t;

namespace itk
{

class IRRefineGrid {
public:

  IRRefineGrid() = default; // default constructor

  static void LoadMosaic(std::istream &input_stream,
                         double &pixel_spacing,
                         bool &use_std_mask,
                         std::vector<std::string> &images,
                         std::vector<itk::TransformBase::Pointer> &transforms);

};


//----------------------------------------------------------------
// optimization_observer_t
// 
template<class mosaic_metric_t>
class optimization_observer_t : public itk::Command
{
public:
  typedef optimization_observer_t Self;
  typedef itk::Command Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  
  itkNewMacro(Self);
  
  void Execute(itk::Object *caller, const itk::EventObject & event)
  { Execute((const itk::Object *)(caller), event); }
  
  void Execute(const itk::Object * object, const itk::EventObject & event)
  {
    if (typeid(event) != typeid(itk::IterationEvent)) return;
    
    const optimizer_t * optimizer = dynamic_cast<const optimizer_t *>(object);
    cout << (unsigned int)(optimizer->GetCurrentIteration()) << '\t'
         << optimizer->GetValue() << '\t'
         << metric_->GetNumberOfPixelsCounted() << '\t'
         << optimizer->GetCurrentPosition() << endl;
    
    // FIXME: 2005/11/09
#ifdef SAVE_INTERMEDIATE_MOSAIC
    {
      static unsigned int counter = 0;
      
      the_text_t fn =
        prefix_ + the_text_t::number(counter, 3, '0') + the_text_t(".mosaic");
      std::fstream fout;
      fout.open(fn, ios::out);
      save_mosaic<base_transform_t>(fout,
                                    pixel_spacing_,
                                    use_std_mask_,
                                    in_,
                                    transform_);
      fout.close();
      counter++;
    }
#endif
  }
  
  // FIXME: 2005/11/09
  typename mosaic_metric_t::Pointer metric_;
  std::list<the_text_t> in_;
  double pixel_spacing_;
  bool use_std_mask_;
  std::vector<base_transform_t::Pointer> transform_;
  the_text_t prefix_;
  
protected:
  optimization_observer_t() {}
};


//----------------------------------------------------------------
// radial_distortion_t
//
typedef itk::RadialDistortionTransform<double, 2>
radial_distortion_t;

//----------------------------------------------------------------
// affine_transform_t
// 
typedef itk::LegendrePolynomialTransform<double, 1>
affine_transform_t;

//----------------------------------------------------------------
// cubic_transform_t
// 
typedef itk::LegendrePolynomialTransform<double, 3>
cubic_transform_t;

//----------------------------------------------------------------
// image_interpolator_t
// 
typedef itk::LinearInterpolateImageFunction<image_t, double>
image_interpolator_t;



} // namespace itk

#endif // itkIRRefineGrid
