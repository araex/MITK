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

#include "org_mitk_gui_qt_cest_Activator.h"
#include "QmitkCESTStatisticsView.h"
#include "QmitkCESTNormalizeView.h"

void mitk::org_mitk_gui_qt_cest_Activator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS(QmitkCESTStatisticsView, context)
  BERRY_REGISTER_EXTENSION_CLASS(QmitkCESTNormalizeView, context)
}

void mitk::org_mitk_gui_qt_cest_Activator::stop(ctkPluginContext*)
{
}
