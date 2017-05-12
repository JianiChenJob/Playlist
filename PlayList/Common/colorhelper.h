#pragma once

#include <QColor>

namespace Core
{
	class ColorHelper
	{
	public:
        static const QColor Black;
        static const QColor White;
        static const QColor Red;
        static const QColor Green;
        static const QColor Blue;
        static const QColor Yellow;
        static const QColor BlueGreen;
        static const QColor Purple;
        static const QColor CornflowerBlue;
        static const QColor Wheat;
        static const QColor LightGray;

        static QColor randomColor();

	private:
		ColorHelper();
		ColorHelper(const ColorHelper& rhs);
		ColorHelper& operator=(const ColorHelper& rhs);
	};
}
