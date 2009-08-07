/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
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


#ifndef BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4
#define BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4

#include "mitkDataStorage.h"
#include "mitkGeometry2D.h"
#include "mitkTimeSlicedGeometry.h"
#include "mitkDisplayGeometry.h"
#include "mitkGeometry2DData.h"
#include "mitkCameraController.h"
#include "mitkEventTypedefs.h"

#include "mitkSliceNavigationController.h"
#include "mitkCameraController.h"
#include "mitkCameraRotationController.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <map>
#include <set>

namespace mitk 
{

class NavigationController;
class SliceNavigationController;
class CameraRotationController;
class CameraController;
class DataStorage;

//##Documentation
//## @brief Organizes the rendering process
//##
//## Organizes the rendering process. A Renderer contains a reference to a
//## DataStorage and asks the mappers of the data objects to render
//## the data into the renderwindow it is associated to.
//##
//## \#Render() checks if rendering is currently allowed by calling
//## RenderWindow::PrepareRendering(). Initialization of a rendering context
//## can also be performed in this method.
//##
//## The actual rendering code has been moved to \#Repaint()
//## Both \#Repaint() and \#Update() are declared protected now.
//##
//## Note: Separation of the Repaint and Update processes (rendering vs
//## creating a vtk prop tree) still needs to be worked on. The whole
//## rendering process also should be reworked to use VTK based classes for
//## both 2D and 3D rendering.
//## @ingroup Renderer
class MITK_CORE_EXPORT BaseRenderer : public itk::Object
{
public:
  typedef std::map<vtkRenderWindow*,BaseRenderer*> BaseRendererMapType;
  static BaseRendererMapType baseRendererMap;

  static BaseRenderer* GetInstance(vtkRenderWindow * renWin);
  static void AddInstance(vtkRenderWindow* renWin, BaseRenderer* baseRenderer);
  static void RemoveInstance(vtkRenderWindow* renWin);

  static BaseRenderer* GetByName( const std::string& name );
  static vtkRenderWindow* GetRenderWindowByName( const std::string& name );

  itkEventMacro( RendererResetEvent, itk::AnyEvent );

  /** Standard class typedefs. */
  mitkClassMacro(BaseRenderer, itk::Object);

  BaseRenderer( const char* name = NULL, vtkRenderWindow * renWin = NULL );

  //##Documentation
  //## @brief MapperSlotId defines which kind of mapper (e.g., 2D or 3D) shoud be used.
  typedef int MapperSlotId;

  enum StandardMapperSlot{Standard2D=1, Standard3D=2};


  virtual void SetDataStorage( mitk::DataStorage* storage );  ///< set the datastorage that will be used for rendering

  //##Documentation
  //## return the DataStorage that is used for rendering
  virtual mitk::DataStorage::Pointer GetDataStorage() const
  {
    return m_DataStorage.GetPointer();
  };

  //##Documentation
  //## @brief Access the RenderWindow into which this renderer renders.
  vtkRenderWindow* GetRenderWindow() const
  {
    return m_RenderWindow;
  }
  vtkRenderer* GetVtkRenderer() const
  {
    return m_VtkRenderer;
  }



  //##Documentation
  //## @brief Default mapper id to use.
  static const MapperSlotId defaultMapper;

  //##Documentation
  //## @brief Do the rendering and flush the result.
  virtual void Paint();

  //##Documentation
  //## @brief Initialize the RenderWindow. Should only be called from RenderWindow.
  virtual void Initialize();

  //##Documentation
  //## @brief Called to inform the renderer that the RenderWindow has been resized.
  virtual void Resize(int w, int h);

  //##Documentation
  //## @brief Initialize the renderer with a RenderWindow (@a renderwindow).
  virtual void InitRenderer(vtkRenderWindow* renderwindow);

  //##Documentation
  //## @brief Set the initial size. Called by RenderWindow after it has become
  //## visible for the first time.
  virtual void InitSize(int w, int h);

  //##Documentation
  //## @brief Draws a point on the widget.
  //## Should be used during conferences to show the position of the remote mouse
  virtual void DrawOverlayMouse(Point2D& p2d);

  //##Documentation
  //## @brief Set/Get the WorldGeometry (m_WorldGeometry) for 3D and 2D rendering, that describing the
  //## (maximal) area to be rendered.
  //##
  //## Depending of the type of the passed Geometry3D more or less information can be extracted:
  //## \li if it is a Geometry2D (which is a sub-class of Geometry3D), m_CurrentWorldGeometry2D is
  //## also set to point to it. m_TimeSlicedWorldGeometry is set to NULL.
  //## \li if it is a TimeSlicedGeometry, m_TimeSlicedWorldGeometry is also set to point to it.
  //## If m_TimeSlicedWorldGeometry contains instances of SlicedGeometry3D, m_CurrentWorldGeometry2D is set to
  //## one of geometries stored in the SlicedGeometry3D according to the value of m_Slice;  otherwise
  //## a PlaneGeometry describing the top of the bounding-box of the Geometry3D is set as the
  //## m_CurrentWorldGeometry2D.
  //## \li otherwise a PlaneGeometry describing the top of the bounding-box of the Geometry3D
  //## is set as the m_CurrentWorldGeometry2D. m_TimeSlicedWorldGeometry is set to NULL.
  //## @todo add calculation of PlaneGeometry describing the top of the bounding-box of the Geometry3D
  //## when the passed Geometry3D is not sliced.
  //## \sa m_WorldGeometry
  //## \sa m_TimeSlicedWorldGeometry
  //## \sa m_CurrentWorldGeometry2D
  virtual void SetWorldGeometry(Geometry3D* geometry);

  itkGetConstObjectMacro(WorldGeometry, Geometry3D);

  //##Documentation
  //## @brief Get the current 3D-worldgeometry (m_CurrentWorldGeometry) used for 3D-rendering
  itkGetConstObjectMacro(CurrentWorldGeometry, Geometry3D);

  //##Documentation
  //## @brief Get the current 2D-worldgeometry (m_CurrentWorldGeometry2D) used for 2D-rendering
  itkGetConstObjectMacro(CurrentWorldGeometry2D, Geometry2D);

  //##Documentation
  //## Calculates the bounds of the DataStorage (if it contains any valid data),
  //## creates a geometry from these bounds and sets it as world geometry of the renderer.
  //##
  //## Call this method to re-initialize the renderer to the current DataStorage
  //## (e.g. after loading an additional dataset), to ensure that the view is
  //## aligned correctly.
  //## \warn This is not implemented yet.
  virtual bool SetWorldGeometryToDataStorageBounds()
  {
    return false;
  }

  //##Documentation
  //## @brief Set/Get the DisplayGeometry (for 2D rendering)
  //##
  //## The DisplayGeometry describes which part of the Geometry2D m_CurrentWorldGeometry2D
  //## is displayed.
  virtual void SetDisplayGeometry(DisplayGeometry* geometry2d);

  itkGetConstObjectMacro(DisplayGeometry, DisplayGeometry);

  itkGetObjectMacro(DisplayGeometry, DisplayGeometry);

  //##Documentation
  //## @brief Set/Get m_Slice which defines together with m_TimeStep the 2D geometry
  //## stored in m_TimeSlicedWorldGeometry used as m_CurrentWorldGeometry2D
  //##
  //## \sa m_Slice
  virtual void SetSlice(unsigned int slice);

  itkGetConstMacro(Slice, unsigned int);

  //##Documentation
  //## @brief Set/Get m_TimeStep which defines together with m_Slice the 2D geometry
  //## stored in m_TimeSlicedWorldGeometry used as m_CurrentWorldGeometry2D
  //##
  //## \sa m_TimeStep
  virtual void SetTimeStep(unsigned int timeStep);

  itkGetConstMacro(TimeStep, unsigned int);

  //##Documentation
  //## @brief Get the time-step of a BaseData object which
  //## exists at the time of the currently displayed content
  //##
  //## Returns -1 or mitk::BaseData::m_TimeSteps if there
  //## is no data at the current time.
  //## \sa GetTimeStep, m_TimeStep
  int GetTimeStep(const BaseData* data) const;

  //##Documentation
  //## @brief Get the time in ms of the currently displayed content
  //##
  //## \sa GetTimeStep, m_TimeStep
  ScalarType GetTime() const;

  //##Documentation
  //## @brief SetWorldGeometry is called according to the geometrySliceEvent,
  //## which is supposed to be a SliceNavigationController::GeometrySendEvent
  virtual void SetGeometry(const itk::EventObject & geometrySliceEvent);

  //##Documentation
  //## @brief UpdateWorldGeometry is called to re-read the 2D geometry from the
  //## slice navigation controller
  virtual void UpdateGeometry(const itk::EventObject & geometrySliceEvent);

  //##Documentation
  //## @brief SetSlice is called according to the geometrySliceEvent,
  //## which is supposed to be a SliceNavigationController::GeometrySliceEvent
  virtual void SetGeometrySlice(const itk::EventObject & geometrySliceEvent);

  //##Documentation
  //## @brief SetTimeStep is called according to the geometrySliceEvent,
  //## which is supposed to be a SliceNavigationController::GeometryTimeEvent
  virtual void SetGeometryTime(const itk::EventObject & geometryTimeEvent);

  //##Documentation
  //## @brief Get a data object containing the DisplayGeometry (for 2D rendering)
  itkGetObjectMacro(DisplayGeometryData, Geometry2DData);
  //##Documentation
  //## @brief Get a data object containing the WorldGeometry (for 2D rendering)
  itkGetObjectMacro(WorldGeometryData, Geometry2DData);

  //##Documentation
  //## @brief Get a DataTreeNode pointing to a data object containing the WorldGeometry (3D and 2D rendering)
  itkGetObjectMacro(WorldGeometryNode, DataTreeNode);
  //##Documentation
  //## @brief Get a DataTreeNode pointing to a data object containing the DisplayGeometry (for 2D rendering)
  itkGetObjectMacro(DisplayGeometryNode, DataTreeNode);
  //##Documentation
  //## @brief Get a DataTreeNode pointing to a data object containing the current 2D-worldgeometry m_CurrentWorldGeometry2D (for 2D rendering)
  itkGetObjectMacro(CurrentWorldGeometry2DNode, DataTreeNode);

  //##Documentation
  //## @brief Get timestamp of last call of SetCurrentWorldGeometry2D
  unsigned long GetCurrentWorldGeometry2DUpdateTime() { return m_CurrentWorldGeometry2DUpdateTime; };
  //##Documentation
  //## @brief Get timestamp of last call of SetDisplayGeometry
  unsigned long GetDisplayGeometryUpdateTime() { return m_CurrentWorldGeometry2DUpdateTime; };
  //##Documentation
  //## @brief Get timestamp of last change of current TimeStep
  unsigned long GetTimeStepUpdateTime() { return m_TimeStepUpdateTime; };

  //##Documentation
  //## @brief Perform a picking: find the x,y,z world coordinate of a
  //## display x,y coordinate.
  //## @warning Has to be overwritten in subclasses for the 3D-case.
  //##
  //## Implemented here only for 2D-rendering by using
  //## m_DisplayGeometry
  virtual void PickWorldPoint(const Point2D& diplayPosition, Point3D& worldPosition) const;

  //##Documentation
  //## @brief Get the MapperSlotId to use.
  itkGetMacro(MapperID, MapperSlotId);
  //##Documentation
  //## @brief Set the MapperSlotId to use.
  itkSetMacro(MapperID, MapperSlotId);

  //##Documentation
  //## @brief Has the renderer the focus?
  itkGetMacro(Focused, bool);
  //##Documentation
  //## @brief Tell the renderer that it is focused. The caller is responsible for focus management,
  //## not the renderer itself.
  itkSetMacro(Focused, bool);

  //##Documentation
  //## @brief Sets whether depth peeling is enabled or not
  void SetDepthPeelingEnabled(bool enabled);  //##Documentation
  //## @brief Sets maximal number of peels
  void SetMaxNumberOfPeels(int maxNumber);

  itkGetMacro(Size, int*);

  void SetSliceNavigationController(SliceNavigationController* SlicenavigationController);
  void SetCameraController(CameraController* cameraController);
  itkGetObjectMacro(CameraController, CameraController);
  itkGetObjectMacro(SliceNavigationController, SliceNavigationController);
  itkGetObjectMacro(CameraRotationController, CameraRotationController);

  itkGetMacro(EmptyWorldGeometry, bool);

  //##Documentation
  //## @brief Mouse event dispatchers
  //## @note for internal use only. preliminary.
  virtual void MousePressEvent(MouseEvent*);
  //##Documentation
  //## @brief Mouse event dispatchers
  //## @note for internal use only. preliminary.
  virtual void MouseReleaseEvent(MouseEvent*);
  //##Documentation
  //## @brief Mouse event dispatchers
  //## @note for internal use only. preliminary.
  virtual void MouseMoveEvent(MouseEvent*);
  //##Documentation
  //## @brief Wheel event dispatcher
  //## @note for internal use only. preliminary.
  virtual void WheelEvent(mitk::WheelEvent* we);
  //##Documentation
  //## @brief Key event dispatcher
  //## @note for internal use only. preliminary.
  virtual void KeyPressEvent(KeyEvent*);

  //##Documentation
  //## @brief get the name of the Renderer
  //## @note
  const char * GetName() const
  {
    return m_Name.c_str();
  }

  //##Documentation
  //## @brief get the x_size of the RendererWindow
  //## @note
  int GetSizeX() const
  {
    return m_Size[0];
  }

  //##Documentation
  //## @brief get the y_size of the RendererWindow
  //## @note
  int GetSizeY() const
  {
    return m_Size[1];
  }

  const double* GetBounds() const;

  void RequestUpdate();
  void ForceImmediateUpdate();


  /** Returns number of mappers which are visible and have level-of-detail
   * rendering enabled */
  unsigned int GetNumberOfVisibleLODEnabledMappers() const;


protected:

  virtual ~BaseRenderer();

  //##Documentation
  //## @brief Call update of all mappers. To be implemented in subclasses.
  virtual void Update() = 0;

  vtkRenderWindow* m_RenderWindow;
  vtkRenderer*     m_VtkRenderer;

  //##Documentation
  //## @brief MapperSlotId to use. Defines which kind of mapper (e.g., 2D or 3D) shoud be used.
  MapperSlotId m_MapperID;

  //##Documentation
  //## @brief The DataStorage that is used for rendering.
  mitk::DataStorage::Pointer m_DataStorage;

  //##Documentation
  //## @brief Timestamp of last call of Update().
  unsigned long m_LastUpdateTime;

  //##Documentation
  //## @brief CameraController for 3D rendering
  //## @note preliminary.
  CameraController::Pointer           m_CameraController;
  SliceNavigationController::Pointer  m_SliceNavigationController;
  CameraRotationController::Pointer   m_CameraRotationController;


  //##Documentation
  //## @brief Size of the RenderWindow.
  int m_Size[2];

  //##Documentation
  //## @brief Contains whether the renderer that it is focused. The caller of
  //## SetFocused is responsible for focus management, not the renderer itself.
  //## is doubled because of mitk::FocusManager in GlobalInteraction!!! (ingmar)
  bool m_Focused;

  //##Documentation
  //## @brief Sets m_CurrentWorldGeometry2D
  virtual void SetCurrentWorldGeometry2D(Geometry2D* geometry2d);

  //##Documentation
  //## @brief Sets m_CurrentWorldGeometry
  virtual void SetCurrentWorldGeometry(Geometry3D* geometry);


private:
  //##Documentation
  //## Pointer to the worldgeometry, describing the maximal area to be rendered
  //## (3D as well as 2D).
  //## It is const, since we are not allowed to change it (it may be taken
  //## directly from the geometry of an image-slice and thus it would be
  //## very strange when suddenly the image-slice changes its geometry).
  //## \sa SetWorldGeometry
  Geometry3D::Pointer m_WorldGeometry;

  //##Documentation
  //## m_TimeSlicedWorldGeometry is set by SetWorldGeometry if the passed Geometry3D is a
  //## TimeSlicedGeometry (or a sub-class of it). If it contains instances of SlicedGeometry3D,
  //## m_Slice and m_TimeStep (set via SetSlice and SetTimeStep, respectively) define
  //## which 2D geometry stored in m_TimeSlicedWorldGeometry (if available)
  //## is used as m_CurrentWorldGeometry2D.
  //## \sa m_CurrentWorldGeometry2D
  TimeSlicedGeometry::Pointer m_TimeSlicedWorldGeometry;

  //##Documentation
  //## Pointer to the current 3D-worldgeometry.
  Geometry3D::Pointer m_CurrentWorldGeometry;

  //##Documentation
  //## Pointer to the current 2D-worldgeometry. The 2D-worldgeometry
  //## describes the maximal area (2D manifold) to be rendered in case we
  //## are doing 2D-rendering. More precisely, a subpart of this according
  //## to m_DisplayGeometry is displayed.
  //## It is const, since we are not allowed to change it (it may be taken
  //## directly from the geometry of an image-slice and thus it would be
  //## very strange when suddenly the image-slice changes its geometry).
  Geometry2D::Pointer m_CurrentWorldGeometry2D;

  //##Documentation
  //## Pointer to the displaygeometry. The displaygeometry describes the
  //## geometry of the \em visible area in the window controlled by the renderer
  //## in case we are doing 2D-rendering.
  //## It is const, since we are not allowed to change it.
  DisplayGeometry::Pointer m_DisplayGeometry;

  //##Documentation
  //## Defines together with m_Slice which 2D geometry stored in m_TimeSlicedWorldGeometry
  //## is used as m_CurrentWorldGeometry2D: m_TimeSlicedWorldGeometry->GetGeometry2D(m_Slice, m_TimeStep).
  //## \sa m_TimeSlicedWorldGeometry
  unsigned int m_Slice;
  //##Documentation
  //## Defines together with m_TimeStep which 2D geometry stored in m_TimeSlicedWorldGeometry
  //## is used as m_CurrentWorldGeometry2D: m_TimeSlicedWorldGeometry->GetGeometry2D(m_Slice, m_TimeStep).
  //## \sa m_TimeSlicedWorldGeometry
  unsigned int m_TimeStep;

  //##Documentation
  //## @brief timestamp of last call of SetWorldGeometry
  itk::TimeStamp m_CurrentWorldGeometry2DUpdateTime;

  //##Documentation
  //## @brief timestamp of last call of SetDisplayGeometry
  itk::TimeStamp m_DisplayGeometryUpdateTime;

  //##Documentation
  //## @brief timestamp of last change of the current time step
  itk::TimeStamp m_TimeStepUpdateTime;

protected:
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

  //##Documentation
  //## Data object containing the m_WorldGeometry defined above.
  Geometry2DData::Pointer m_WorldGeometryData;
  //##Documentation
  //## Data object containing the m_DisplayGeometry defined above.
  Geometry2DData::Pointer m_DisplayGeometryData;
  //##Documentation
  //## Data object containing the m_CurrentWorldGeometry2D defined above.
  Geometry2DData::Pointer m_CurrentWorldGeometry2DData;

  //##Documentation
  //## DataTreeNode objects containing the m_WorldGeometryData defined above.
  DataTreeNode::Pointer m_WorldGeometryNode;
  //##Documentation
  //## DataTreeNode objects containing the m_DisplayGeometryData defined above.
  DataTreeNode::Pointer m_DisplayGeometryNode;
  //##Documentation
  //## DataTreeNode objects containing the m_CurrentWorldGeometry2DData defined above.
  DataTreeNode::Pointer m_CurrentWorldGeometry2DNode;

  //##Documentation
  //## @brief test only
  unsigned long m_DisplayGeometryTransformTime;
  //##Documentation
  //## @brief test only
  unsigned long m_CurrentWorldGeometry2DTransformTime;

  std::string m_Name;

  double m_Bounds[6];

  bool m_EmptyWorldGeometry;

  bool m_DepthPeelingEnabled;

  int m_MaxNumberOfPeels; 

  typedef std::set< Mapper * > LODEnabledMappersType;

  /** Number of mappers which are visible and have level-of-detail
   * rendering enabled */
  unsigned int m_NumberOfVisibleLODEnabledMappers;

};

} // namespace mitk

#endif /* BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4 */
