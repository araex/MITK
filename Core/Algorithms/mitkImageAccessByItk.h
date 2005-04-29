/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef MITKIMAGEACCESSBYITK_H_HEADER_INCLUDED
#define MITKIMAGEACCESSBYITK_H_HEADER_INCLUDED
 
#include <itkCastImageFilter.h>
#include <mitkImageToItk.h>

//##Documentation
//## @brief Instantiate access function without additional parammeters
//## for all datatypes and dimensions
//## @ingroup Process
//##
//## Use this macro once after the definition of your access function.
//## Some compilers have memory problems without the explicit instantiation.
//## You may need to move the access function to a separate file.
//## \sa InstantiateAccessFunction_1
//## \sa InstantiateAccessFunction_2
#define InstantiateAccessFunction(itkImgFunc)                       \
  InstantiateAccessFunctionForFixedDimension(itkImgFunc, 2)         \
  InstantiateAccessFunctionForFixedDimension(itkImgFunc, 3)         

//##Documentation
//## @brief Instantiate access function with one additional parammeter
//## for all datatypes and dimensions
//## @ingroup Process
//##
//## Use this macro once after the definition of your access function.
//## Some compilers have memory problems without the explicit instantiation.
//## You may need to move the access function to a separate file.
//## \sa InstantiateAccessFunction
//## \sa InstantiateAccessFunction_2
#define InstantiateAccessFunction_1(itkImgFunc, param1Type)                       \
  InstantiateAccessFunctionForFixedDimension_1(itkImgFunc, 2, param1Type)         \
  InstantiateAccessFunctionForFixedDimension_1(itkImgFunc, 3, param1Type)         

//##Documentation
//## @brief Instantiate access function with two additional parammeters
//## for all datatypes and dimensions
//## @ingroup Process
//##
//## Use this macro once after the definition of your access function.
//## Some compilers have memory problems without the explicit instantiation.
//## You may need to move the access function to a separate file.
//## \sa InstantiateAccessFunction
//## \sa InstantiateAccessFunction_1
#define InstantiateAccessFunction_2(itkImgFunc, param1Type, param2Type)                \
  InstantiateAccessFunctionForFixedDimension_2(itkImgFunc, 2, param1Type, param2Type)  \
  InstantiateAccessFunctionForFixedDimension_2(itkImgFunc, 3, param1Type, param2Type)         

#define InstantiateAccessFunctionForFixedDimension(itkImgFunc, dimension)  \
template void itkImgFunc(itk::Image<double, dimension>*);                  \
template void itkImgFunc(itk::Image<float, dimension>*);                   \
template void itkImgFunc(itk::Image<int, dimension>*);                     \
template void itkImgFunc(itk::Image<unsigned int, dimension>*);            \
template void itkImgFunc(itk::Image<short, dimension>*);                   \
template void itkImgFunc(itk::Image<unsigned short, dimension>*);          \
template void itkImgFunc(itk::Image<char, dimension>*);                    \
template void itkImgFunc(itk::Image<unsigned char, dimension>*);           

#define InstantiateAccessFunctionForFixedDimension_1(itkImgFunc, dimension, param1Type)\
template void itkImgFunc(itk::Image<double, dimension>*, param1Type);                  \
template void itkImgFunc(itk::Image<float, dimension>*, param1Type);                   \
template void itkImgFunc(itk::Image<int, dimension>*, param1Type);                     \
template void itkImgFunc(itk::Image<unsigned int, dimension>*, param1Type);            \
template void itkImgFunc(itk::Image<short, dimension>*, param1Type);                   \
template void itkImgFunc(itk::Image<unsigned short, dimension>*, param1Type);          \
template void itkImgFunc(itk::Image<char, dimension>*, param1Type);                    \
template void itkImgFunc(itk::Image<unsigned char, dimension>*, param1Type);           

#define InstantiateAccessFunctionForFixedDimension_2(itkImgFunc, dimension, param1Type, param2Type)\
template void itkImgFunc(itk::Image<double, dimension>*, param1Type, param2Type);                  \
template void itkImgFunc(itk::Image<float, dimension>*, param1Type, param2Type);                   \
template void itkImgFunc(itk::Image<int, dimension>*, param1Type, param2Type);                     \
template void itkImgFunc(itk::Image<unsigned int, dimension>*, param1Type, param2Type);            \
template void itkImgFunc(itk::Image<short, dimension>*, param1Type, param2Type);                   \
template void itkImgFunc(itk::Image<unsigned short, dimension>*, param1Type, param2Type);          \
template void itkImgFunc(itk::Image<char, dimension>*, param1Type, param2Type);                    \
template void itkImgFunc(itk::Image<unsigned char, dimension>*, param1Type, param2Type);           

#define _accessByItk(mitkImage, itkImageTypeFunction, pixeltype, dimension)            \
  if ( typeId == typeid(pixeltype) )                                                   \
{                                                                                      \
    typedef itk::Image<pixeltype, dimension> ImageType;                                \
    typedef mitk::ImageToItk<ImageType> ImageToItkType;                                \
    ImageToItkType::Pointer imagetoitk = ImageToItkType::New();                        \
    imagetoitk->SetInput(mitkImage);                                                   \
    imagetoitk->Update();                                                              \
    itkImageTypeFunction<pixeltype, dimension>(imagetoitk->GetOutput());               \
}                                                              

#define _accessAllTypesByItk(mitkImage, itkImageTypeFunction, dimension)               \
      _accessByItk(mitkImage, itkImageTypeFunction, double, dimension) else            \
      _accessByItk(mitkImage, itkImageTypeFunction, float, dimension) else             \
      _accessByItk(mitkImage, itkImageTypeFunction, int, dimension) else               \
      _accessByItk(mitkImage, itkImageTypeFunction, unsigned int, dimension) else      \
      _accessByItk(mitkImage, itkImageTypeFunction, short, dimension) else             \
      _accessByItk(mitkImage, itkImageTypeFunction, unsigned short, dimension) else    \
      _accessByItk(mitkImage, itkImageTypeFunction, char, dimension) else              \
      _accessByItk(mitkImage, itkImageTypeFunction, unsigned char,  dimension)         \

//##Documentation
//## @brief Access an mitk-image by an itk-image
//## @ingroup Process
//## 
//## Define a templated function or method (@a itkImageTypeFunction) 
//## within which the mitk-image (@a mitkImage) is accessed:
//## \code
//##   template < typename TPixel, unsigned int VImageDimension > 
//##     void ExampleFunction( itk::Image<typename TPixel, VImageDimension>* itkImage, TPixel* dummy = NULL );
//## \endcode
//## Instantiate the function using
//## \code
//##   InstantiateAccessFunction(ExampleFunction);
//## \endcode
//## Within the itk::Image passed to the function/method has the same
//## data-pointer as the mitk-image. So you have full read- and write-
//## access to the data vector of the mitk-image using the itk-image.
//## Call by:
//## \code
//##  // inputMitkImage being of type mitk::Image*
//##  AccessByItk(inputMitkImage, ExampleFunction);
//## \endcode
//## @note If your inputMitkImage is an mitk::Image::Pointer, use 
//## inputMitkImage.GetPointer()
//## @note If you need to pass an additional parameter to your 
//## access-function (@a itkImageTypeFunction), use AccessByItk_1.
//## @note If you know the dimension of your input mitk-image,
//## it is better to use AccessFixedDimensionByItk (less code
//## is generated).
//## \sa AccessFixedDimensionByItk
//## \sa AccessByItk_1
#define AccessByItk(mitkImage, itkImageTypeFunction)                                   \
{                                                                                      \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                 \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()>=2 && mitkImage->GetDimension()<=3);                \
  if(mitkImage->GetDimension()==2)                                                     \
  {                                                                                    \
    _accessAllTypesByItk(mitkImage, itkImageTypeFunction, 2);                          \
    return;                                                                            \
  }                                                                                    \
  else                                                                                 \
  {                                                                                    \
    _accessAllTypesByItk(mitkImage, itkImageTypeFunction, 3)                           \
  }                                                                                    \
}

//##Documentation
//## @brief Access an mitk-image with known dimension by an itk-image
//## @ingroup Process
//## 
//## For usage, see AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk.
//## \sa AccessByItk
#define AccessFixedDimensionByItk(mitkImage, itkImageTypeFunction, dimension)          \
{                                                                                      \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                 \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                        \
  _accessAllTypesByItk(mitkImage, itkImageTypeFunction, dimension)                     \
}

//##Documentation
//## @brief Access an mitk-image with known type (pixel type and dimension) 
//## by an itk-image
//## @ingroup Process
//## 
//## For usage, see AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk.
//## \sa AccessByItk_2
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk
#define AccessFixedTypeByItk(mitkImage, itkImageTypeFunction, pixeltype, dimension)              \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
   const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                                  \
  _accessByItk(mitkImage, itkImageTypeFunction, pixeltype, dimension)                            \
}

//----------------------- version with 1 additional paramater ------------------
#define _accessByItk_1(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1)            \
  if ( typeId == typeid(pixeltype) )                                                             \
  {                                                                                              \
    typedef itk::Image<pixeltype, dimension> ImageType;                                          \
    typedef mitk::ImageToItk<ImageType> ImageToItkType;                                          \
    ImageToItkType::Pointer imagetoitk = ImageToItkType::New();                                  \
    imagetoitk->SetInput(mitkImage);                                                             \
    imagetoitk->Update();                                                                        \
    itkImageTypeFunction<pixeltype, dimension>(imagetoitk->GetOutput(), param1);                 \
  }

#define _accessAllTypesByItk_1(mitkImage, itkImageTypeFunction, dimension, param1)               \
      _accessByItk_1(mitkImage, itkImageTypeFunction, double, dimension, param1) else            \
      _accessByItk_1(mitkImage, itkImageTypeFunction, float, dimension, param1) else             \
      _accessByItk_1(mitkImage, itkImageTypeFunction, int, dimension, param1) else               \
      _accessByItk_1(mitkImage, itkImageTypeFunction, unsigned int, dimension, param1) else      \
      _accessByItk_1(mitkImage, itkImageTypeFunction, short, dimension, param1) else             \
      _accessByItk_1(mitkImage, itkImageTypeFunction, unsigned short, dimension, param1) else    \
      _accessByItk_1(mitkImage, itkImageTypeFunction, char, dimension, param1) else              \
      _accessByItk_1(mitkImage, itkImageTypeFunction, unsigned char,  dimension, param1)         \

//##Documentation
//## @brief Access an mitk-image by an itk-image and pass one 
//## additional parameter to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk. The only difference to AccessByItk
//## is that an additional parameter (@param1) is passed.
//## @note If you know the dimension of your input mitk-image,
//## it is better to use AccessFixedDimensionByItk_1 (less code
//## is generated).
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk_1
#define AccessByItk_1(mitkImage, itkImageTypeFunction, param1)                                   \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()>=2 && mitkImage->GetDimension()<=3);                          \
  if(mitkImage->GetDimension()==2)                                                               \
  {                                                                                              \
    _accessAllTypesByItk_1(mitkImage, itkImageTypeFunction, 2, param1);                         \
  }                                                                                              \
  else                                                                                           \
  {                                                                                              \
    _accessAllTypesByItk_1(mitkImage, itkImageTypeFunction, 3, param1)                          \
  }                                                                                              \
}

//##Documentation
//## @brief Access an mitk-image with known dimension by an itk-image 
//## and pass one additional parameter to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk_1 and AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk_1.
//## \sa AccessByItk_1
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk
#define AccessFixedDimensionByItk_1(mitkImage, itkImageTypeFunction, dimension, param1)          \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                                  \
  _accessAllTypesByItk_1(mitkImage, itkImageTypeFunction, dimension, param1)                     \
}

//##Documentation
//## @brief Access an mitk-image with known type (pixel type and dimension) 
//## by an itk-image and pass one additional parameters to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk_1 and AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk_1.
//## \sa AccessByItk_2
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk
#define AccessFixedTypeByItk_1(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1)    \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                                  \
  _accessByItk_1(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1)                  \
}

//----------------------- version with 2 additional paramaters -----------------
#define _accessByItk_2(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1, param2)    \
  if ( typeId == typeid(pixeltype) )                                                             \
{                                                                                                \
    typedef itk::Image<pixeltype, dimension> ImageType;                                          \
    typedef mitk::ImageToItk<ImageType> ImageToItkType;                                          \
    ImageToItkType::Pointer imagetoitk = ImageToItkType::New();                                  \
    imagetoitk->SetInput(mitkImage);                                                             \
    imagetoitk->Update();                                                                        \
    itkImageTypeFunction<pixeltype, dimension>(imagetoitk->GetOutput(), param1, param2);         \
}

#define _accessAllTypesByItk_2(mitkImage, itkImageTypeFunction, dimension, param1, param2)               \
      _accessByItk_2(mitkImage, itkImageTypeFunction, double, dimension, param1, param2) else            \
      _accessByItk_2(mitkImage, itkImageTypeFunction, float, dimension, param1, param2) else             \
      _accessByItk_2(mitkImage, itkImageTypeFunction, int, dimension, param1, param2) else               \
      _accessByItk_2(mitkImage, itkImageTypeFunction, unsigned int, dimension, param1, param2) else      \
      _accessByItk_2(mitkImage, itkImageTypeFunction, short, dimension, param1, param2) else             \
      _accessByItk_2(mitkImage, itkImageTypeFunction, unsigned short, dimension, param1, param2) else    \
      _accessByItk_2(mitkImage, itkImageTypeFunction, char, dimension, param1, param2) else              \
      _accessByItk_2(mitkImage, itkImageTypeFunction, unsigned char,  dimension, param1, param2)         \

//##Documentation
//## @brief Access an mitk-image by an itk-image and pass two 
//## additional parameters to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk. The only difference to AccessByItk
//## is thattwo additional parametera (@param1, @param2) is passed.
//## @note If you know the dimension of your input mitk-image,
//## it is better to use AccessFixedDimensionByItk_2 (less code
//## is generated).
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk_2
#define AccessByItk_2(mitkImage, itkImageTypeFunction, param1, param2)                           \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()>=2 && mitkImage->GetDimension()<=3);                          \
  if(mitkImage->GetDimension()==2)                                                               \
  {                                                                                              \
    _accessAllTypesByItk_2(mitkImage, itkImageTypeFunction, 2, param1, param2);                 \
  }                                                                                              \
  else                                                                                           \
  {                                                                                              \
    _accessAllTypesByItk_2(mitkImage, itkImageTypeFunction, 3, param1, param2)                  \
  }                                                                                              \
}

//##Documentation
//## @brief Access an mitk-image with known dimension by an itk-image 
//## and pass two additional parameters to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk_2 and AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk_2.
//## \sa AccessByItk_2
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk
#define AccessFixedDimensionByItk_2(mitkImage, itkImageTypeFunction, dimension, param1, param2)  \
{                                                                                                \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                           \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                                  \
  _accessAllTypesByItk_2(mitkImage, itkImageTypeFunction, dimension, param1, param2)             \
}

//##Documentation
//## @brief Access an mitk-image with known type (pixel type and dimension) 
//## by an itk-image and pass two additional parameters to the access-function
//## @ingroup Process
//## 
//## For usage, see AccessByItk_2 and AccessByItk.
//## @param dimension dimension of the mitk-image. If the image 
//## has a different dimension, an exception is thrown (by assert).
//## If you do not know the dimension for sure, use AccessByItk_2.
//## \sa AccessByItk_2
//## \sa AccessByItk
//## \sa AccessFixedDimensionByItk
#define AccessFixedTypeByItk_2(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1, param2)  \
{                                                                                                      \
  const std::type_info& typeId=*mitkImage->GetPixelType().GetTypeId();                                 \
  const mitk::Image* constImage = mitkImage; \
  const_cast<mitk::Image*>(constImage)->Update(); \
  assert(mitkImage->GetDimension()==dimension);                                                        \
  _accessByItk_2(mitkImage, itkImageTypeFunction, pixeltype, dimension, param1, param2)                \
}

//----------------------- cast functions. Will be moved to mitkImageCast.h -----------------
namespace mitk 
{
  template < typename TPixel, unsigned int VImageDimension, class ItkOutputImageType > 
  void _CastToItkImage2Access( itk::Image<TPixel, VImageDimension>* itkInputImage, itk::SmartPointer<ItkOutputImageType>& itkOutputImage)
  {
    typedef itk::Image<TPixel, VImageDimension> ItkInputImageType;
    typedef itk::CastImageFilter< ItkInputImageType, ItkOutputImageType > CastImageFilterType;
    typename CastImageFilterType::Pointer castImageFilter = CastImageFilterType::New();
    castImageFilter->SetInput( itkInputImage );
    castImageFilter->Update();
    itkOutputImage = castImageFilter->GetOutput();
  }

  template <typename ItkOutputImageType> void CastToItkImage(const mitk::Image * mitkImage, itk::SmartPointer<ItkOutputImageType>& itkOutputImage)
  {
    AccessByItk_1(mitkImage, _CastToItkImage2Access, itkOutputImage);;
  }
}

#endif // of MITKIMAGEACCESSBYITK_H_HEADER_INCLUDED
