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
#ifndef QMITK_STRINGPROPERTYONDEMANDDEDITOR_H_INCLUDED
#define QMITK_STRINGPROPERTYONDEMANDDEDITOR_H_INCLUDED

#include "MitkQtWidgetsExtExports.h"
#include <QLabel>
#include <QLayout>
#include <mitkPropertyObserver.h>
#include <mitkStringProperty.h>

class MITKQTWIDGETSEXT_EXPORT QClickableLabel2 : public QLabel
{
  Q_OBJECT

signals:
  void clicked();

public:
  QClickableLabel2(QWidget *parent, Qt::WindowFlags f = nullptr) : QLabel(parent, f) {}
  void mouseReleaseEvent(QMouseEvent *) override { emit clicked(); }
};

/// @ingroup Widgets
class MITKQTWIDGETSEXT_EXPORT QmitkStringPropertyOnDemandEdit : public QFrame, public mitk::PropertyEditor
{
  Q_OBJECT

public:
  QmitkStringPropertyOnDemandEdit(mitk::StringProperty *, QWidget *parent);
  ~QmitkStringPropertyOnDemandEdit() override;

protected:
  void PropertyChanged() override;
  void PropertyRemoved() override;

  mitk::StringProperty *m_StringProperty;

  QHBoxLayout *m_layout;
  QLabel *m_label;
  QClickableLabel2 *m_toolbutton;

protected slots:

  void onToolButtonClicked();
};

#endif
