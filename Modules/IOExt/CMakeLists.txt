MITK_CREATE_MODULE(DEPENDS MitkDataTypesExt MitkMapperExt MitkSceneSerialization MitkLegacyIO
                   PACKAGE_DEPENDS PRIVATE ITK|ITKIOImageBase VTK|vtkIOPLY+vtkIOExport+vtkIOParallelXML+vtkIOImport
                   WARNINGS_AS_ERRORS
                   AUTOLOAD_WITH MitkCore
                  )
