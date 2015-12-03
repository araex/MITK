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

#ifndef mitkIGTActivator_H
#define mitkIGTActivator_H

#include <usModuleActivator.h>
#include <mitkTrackingDeviceTypeCollection.h>

#include <memory>

#include "mitkTrackingTypes.h"

namespace mitk {

  /** Documentation:
  *   \brief  The load function of this class is executed every time, the module is loaded.
  *           Attention: no static variables of any class in IGT Module are initialized at this moment!
  *   \ingroup IGT
  */
class IGTExtActivator : public us::ModuleActivator
{
public:
  IGTExtActivator();
  virtual ~IGTExtActivator();
  void Load(us::ModuleContext*context) override;
  void Unload(us::ModuleContext* context) override;

private:

  TrackingDeviceTypeCollection m_DeviceTypeCollection;

};

}

#endif // mitkIGTActivator_H
