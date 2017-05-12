#include "colorhelper.h"

#include "randomhelper.h"

using namespace Core;

const QColor ColorHelper::Black =			QColor(0.0f, 0.0f, 0.0f, 1.0f);
const QColor ColorHelper::White =			QColor(1.0f, 1.0f, 1.0f, 1.0f);
const QColor ColorHelper::Red =			QColor(1.0f, 0.0f, 0.0f, 1.0f);
const QColor ColorHelper::Green =			QColor(0.0f, 1.0f, 0.0f, 1.0f);
const QColor ColorHelper::Blue =			QColor(0.0f, 0.0f, 1.0f, 1.0f);
const QColor ColorHelper::Yellow =		QColor(1.0f, 1.0f, 0.0f, 1.0f);
const QColor ColorHelper::BlueGreen =		QColor(0.0f, 1.0f, 1.0f, 1.0f);
const QColor ColorHelper::Purple =		QColor(1.0f, 0.0f, 1.0f, 1.0f);
const QColor ColorHelper::CornflowerBlue = QColor(0.392f, 0.584f, 0.929f, 1.0f);
const QColor ColorHelper::Wheat =			QColor(0.961f, 0.871f, 0.702f, 1.0f);
const QColor ColorHelper::LightGray =		QColor(0.5f, 0.5f, 0.5f, 1.0f);

QColor ColorHelper::randomColor()
{
    float r = RandomHelper::randomUnit();
    float g = RandomHelper::randomUnit();
    float b = RandomHelper::randomUnit();

    return QColor(r, g, b, 1.0f);
}
