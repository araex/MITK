/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef WrlFileReaderService_h
#define WrlFileReaderService_h

#include <mitkAbstractFileReader.h>
#include <mitkIOMimeTypes.h>

namespace mitk
{
    class BaseData;

    /**
    * @brief Used to read surfaces from the PLY format.
    *
    * This reader can read binary and ASCII versions of the format transparently.
    *
    * @ingroup IOExt
    */
    class WrlFileReaderService : public AbstractFileReader
    {
    public:
        WrlFileReaderService();
        virtual ~WrlFileReaderService();

        using AbstractFileReader::Read;
        virtual std::vector<itk::SmartPointer<BaseData>> Read() override;

        static mitk::CustomMimeType mimeType;

    private:
        WrlFileReaderService *Clone() const override;
    };

} // namespace mitk

#endif /* WrlFileReaderService_h */
