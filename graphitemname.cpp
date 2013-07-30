#include "graphitemname.h"

GraphItemName::GraphItemName(QString name, QPointF position)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}
