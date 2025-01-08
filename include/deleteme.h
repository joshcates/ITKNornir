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
// Josh Cates moved from itkIRCommon to facilitate wrapping in ITK 12-18-24

#ifndef itkIRIO_h
#define itkIRIO_h

#include "itkGridTransform.h"
#include <vector>
#include <string>
#include <istream>

namespace itk
{

class IRIO
{
public:

  IRIO() = default; // default constructor

  // Load mosaic metadata
  static void LoadMosaic(std::istream &input_stream,
                         double &pixel_spacing,
                         bool &use_std_mask,
                         std::vector<std::string> &images,
                         std::vector<itk::TransformBase::Pointer> &transforms);

  // Save mosaic metadata
  static void SaveMosaic(const itk::GridTransform::Pointer &transform,
                         const std::string &filename);
};

} // namespace itk


#endif //itkIRIO_h
