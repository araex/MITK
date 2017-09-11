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

#ifndef WrlFileWriterService_h
#define WrlFileWriterService_h

#include <mitkAbstractFileWriter.h>

namespace mitk
{
    /**
     * @brief Used to write Surfaces to the PLY format.
     *
     * Currently, this writer uses the binary format as standard. Should the ASCII Format be required,
     * it is suggested to incorporate Options.
     *
     * @ingroup IOExt
     */
    class WrlFileWriterService : public AbstractFileWriter
    {
    public:
        WrlFileWriterService();
        virtual ~WrlFileWriterService();

        using AbstractFileWriter::Write;
        virtual void Write() override;

    private:
        WrlFileWriterService(const WrlFileWriterService &other);

        virtual mitk::WrlFileWriterService *Clone() const override;
    };
}

#endif
