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

#ifndef QMITKEVENTADAPTER_H_
#define QMITKEVENTADAPTER_H_

#include <QMouseEvent>
#include <QKeyEvent>
#include <mitkEventTypedefs.h>

class QMITK_EXPORT QmitkEventAdapter
{
public:
  
  static mitk::MouseEvent AdaptMouseEvent(mitk::BaseRenderer* sender, QMouseEvent* mouseEvent);
  static mitk::MouseEvent AdaptWheelEvent(mitk::BaseRenderer* sender, QWheelEvent* wheelEvent);
  static mitk::KeyEvent AdaptKeyEvent(QKeyEvent* keyEvent, const QPoint& point);
};

#endif /*QMITKEVENTADAPTER_H_*/
