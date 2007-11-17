/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmTransferSyntax_h
#define __gdcmTransferSyntax_h

#include "gdcmSwapCode.h"

namespace gdcm
{

/**
 * \brief Class to manipulate Transfer Syntax
 * \note
 * TRANSFER SYNTAX (Standard and Private): A set of encoding rules that
 * allow Application Entities to unambiguously negotiate the encoding 
 * techniques (e.g., Data Element structure, byte ordering, compression) 
 * they are able to support, thereby allowing these Application Entities
 * to communicate.
 * \TODO: The implementation is completely retarded
 * We need: IsSupported
 * We need preprocess of raw/xml file
 * We need GetFullName()
 *
 * Need a notion of Private Syntax. As defined in Ps 3.5. Section 9.2
 */
class GDCM_EXPORT TransferSyntax
{
public:
  typedef enum {
    Unknown = 0,
    Explicit,
    Implicit
  } NegociatedType;

#if 0
  //NOT FLEXIBLE, since force user to update lib everytime new module
  //comes out...
  // TODO
  typedef enum {
    NoSpacing = 0,
    PixelSpacing,
    ImagerPixelSpacing,
    PixelAspectRatio
  } ImageSpacingType;
  ImageSpacingType GetImageSpacing();
#endif

  typedef enum {
    ImplicitVRLittleEndian = 0,
    ImplicitVRBigEndianPrivateGE,
    ExplicitVRLittleEndian,
    DeflatedExplicitVRLittleEndian,
    ExplicitVRBigEndian,
    JPEGBaselineProcess1,
    JPEGExtendedProcess2_4,
    JPEGExtendedProcess3_5,
    JPEGSpectralSelectionProcess6_8,
    JPEGFullProgressionProcess10_12,
    JPEGLosslessProcess14,
    JPEGLosslessProcess14_1,
    JPEGLSLossless,
    JPEGLSNearLossless,
    JPEG2000Lossless,
    JPEG2000,
    RLELossless,
    MPEG2MainProfile,
    ImplicitVRBigEndianACRNEMA,
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    WeirdPapryus,
#endif
    TS_END
  } TSType;

  // Return the string as written in the official DICOM dict from
  // a custom enum type
  static const char* GetTSString(const TSType &ts);
  static const TSType GetTSType(const char *str);

  NegociatedType GetNegociatedType() const;

  // Return the SwapCode associated with the Transfer Syntax. Be carefull
  // with the special GE private syntax the DataSet is written in little
  // endian but the Pixel Data is in Big Endian.
  SwapCode GetSwapCode() const;

  // TODO
  SwapCode GetPixelDataSwapCode() const { abort(); };

  bool IsValid() const { return TSField != TS_END; }

  operator TSType () const { return TSField; }

  TransferSyntax(TSType type = ImplicitVRLittleEndian):TSField(type) {}

  // return if dataset is encoded or not (Deflate Explicit VR)
  bool IsEncoded() const;

private:
  // DO NOT EXPOSE the following. Internal details of TransferSyntax
bool IsImplicit(const TSType &ts) const;
bool IsExplicit(const TSType &ts) const;
bool IsLittleEndian(const TSType &ts) const;
bool IsBigEndian(const TSType &ts) const;

  TSType TSField;
};

} // end namespace gdcm

#endif //__gdcmTransferSyntax_h

