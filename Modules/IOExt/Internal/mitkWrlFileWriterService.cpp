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
#include "mitkWrlFileWriterService.h"
#include <mitkIOMimeTypes.h>
#include <mitkSurface.h>

// VTK
#include <vtkDataObject.h>
#include <vtkVRMLExporter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkExtractEdges.h>
#include <vtkPolyDataMapper.h>
#include <vtkIndent.h>

#include <locale.h>

mitk::WrlFileWriterService::WrlFileWriterService()
  : AbstractFileWriter(mitk::Surface::GetStaticNameOfClass(),
                       CustomMimeType(IOMimeTypes::WRL_MIMETYPE()),
                       "WRL Writer")
{
  RegisterService();
}

mitk::WrlFileWriterService::WrlFileWriterService(const mitk::WrlFileWriterService &other) : AbstractFileWriter(other)
{
}

mitk::WrlFileWriterService::~WrlFileWriterService()
{
}

void mitk::WrlFileWriterService::Write()
{
  char *oldLocale = strdup(setlocale(LC_NUMERIC,nullptr));
  setlocale(LC_NUMERIC,"C");
  vtkSmartPointer<vtkVRMLExporter> writer = vtkSmartPointer<vtkVRMLExporter>::New();
  writer->SetFileName(GetOutputLocation().c_str());

  const mitk::Surface *surface = static_cast<const mitk::Surface *>(this->GetInput());


  vtkSmartPointer<vtkDataSetMapper> mapper =
            vtkSmartPointer<vtkDataSetMapper>::New();

  mapper->SetInputData(surface->GetVtkPolyData());
  mapper->ScalarVisibilityOff();


  vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  writer->SetRenderWindow(renderWindow);

  writer->Write();
  // restore the local
  if (oldLocale)
  {
    setlocale(LC_NUMERIC,oldLocale);
    free(oldLocale);
  }

}

mitk::WrlFileWriterService *mitk::WrlFileWriterService::Clone() const
{
  return new WrlFileWriterService(*this);
}
