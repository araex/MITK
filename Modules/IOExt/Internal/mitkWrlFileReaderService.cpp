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

// MITK
#include "mitkWrlFileReaderService.h"
#include <mitkCustomMimeType.h>
#include <mitkIOMimeTypes.h>
#include <mitkSurface.h>

// VTK
#include <vtkVRMLImporter.h>
#include <vtkSmartPointer.h>

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkRenderer.h>
#include <vtkProperty.h>

#include <vtkPolyData.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkAppendPolyData.h>

#include <vtkDataSetSurfaceFilter.h>

mitk::WrlFileReaderService::WrlFileReaderService()
        : AbstractFileReader(CustomMimeType(IOMimeTypes::WRL_MIMETYPE()), "WRL Reader")
{
    this->RegisterService();
}

mitk::WrlFileReaderService::~WrlFileReaderService()
{
}

std::vector<itk::SmartPointer<mitk::BaseData>> mitk::WrlFileReaderService::Read()
{
    char *oldLocale = strdup(setlocale(LC_NUMERIC,nullptr));
    setlocale(LC_NUMERIC,"C");


    std::vector<itk::SmartPointer<BaseData>> result;
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    vtkVRMLImporter* reader = vtkVRMLImporter::New();
    reader->SetFileName(GetInputLocation().c_str());
    reader->Update();
    vtkSmartPointer<vtkDataSet> pDataset;
    vtkSmartPointer<vtkActorCollection> actors = reader->GetRenderer()->GetActors();
    actors->InitTraversal();
    //vtkIdType i = 0;
    for(vtkIdType i = 0; i < actors->GetNumberOfItems(); i++)
    {
        vtkSmartPointer<vtkPolyData> polydatatmp = vtkSmartPointer<vtkPolyData>::New();
        vtkSmartPointer<vtkActor> nextActor = actors->GetNextActor();
        nextActor->GetMapper()->Update();
        pDataset = nextActor->GetMapper()->GetInput();
        polydatatmp = vtkPolyData::SafeDownCast(pDataset);

        vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
        appendFilter->AddInputData(polydatatmp);
        appendFilter->Update();

        polydata = appendFilter->GetOutput();

    }

    if (polydata != NULL)
    {
        mitk::Surface::Pointer surface = mitk::Surface::New();
        surface->SetVtkPolyData(polydata);
        result.push_back(dynamic_cast<mitk::BaseData *>(surface.GetPointer()));
    }

    if (oldLocale)
    {
        setlocale(LC_NUMERIC,oldLocale);
        free(oldLocale);
    }

    return result;
}

mitk::WrlFileReaderService *mitk::WrlFileReaderService::Clone() const
{
    return new WrlFileReaderService(*this);
}
