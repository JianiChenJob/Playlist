#pragma once

#include <QImage>
#include <QPixmap>

namespace Platform
{
    class ImageHelper
    {
    public:

        static float getAverageColor(QImage& image, int channel);

        static int getMedianColor(QImage& image, int channel);

        static int getMaxColor(QImage& image, int channel);

        static int getMinColor(QImage& image, int channel);

        static QString pixmapToPngString(QPixmap pixmap);

        static QPixmap pngStringToPixmap(QString encoded_string);

		static QPixmap combineImages(QList<QPixmap> pixmaps, QList<QPoint> positions);

		static QPixmap combineImages(QList<QPixmap> pixmaps, QList<QPoint> positions, QPointF& upper_left, float position_scale = 1.0f);

		static QPixmap scaleToHeightCenter(QPixmap pixmap, int height, QColor color);

		static QPixmap scaleToWidthCenter(QPixmap pixmap, int width, QColor color);

		static QPixmap scaleToCenter(QPixmap pixmap, int width, int height, QColor color = Qt::transparent);

		static QPixmap scale(QPixmap pixmap, int width, int height);

		static bool savePixmapAsPng(QPixmap pixmap, QString file_path);

		static bool savePixmapAsJpg(QPixmap pixmap, QString file_path);
    };
}
