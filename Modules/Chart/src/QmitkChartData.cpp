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

#include <QmitkChartData.h>

QmitkChartData::QmitkChartData()
  : m_ShowSubchart(true)
  , m_YAxisScale("")
  , m_StackedData(false)
{
}

void QmitkChartData::SetAppearance(bool showSubChart, bool usePercentageInPieChart)
{
  m_ShowSubchart = showSubChart;
  m_UsePercentageInPieChart = usePercentageInPieChart;
}