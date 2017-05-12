#include "imagehelper.h"

#include "stringhelper.h"

#include <QDebug>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QFile>

static const int BLUE = 0;
static const int GREEN = 1;
static const int RED = 2;
static const int BGR = 3;

using namespace Platform;

float ImageHelper::getAverageColor(QImage& image, int channel)
{
    if(image.width() == 0 || image.height() == 0)
    {
        return 0;
    }

    const int N = image.width() * image.height();
	float color = 0;

    for (int y = 0; y != image.height(); ++y)
    {
        for (int x = 0; x != image.width(); ++x)
        {
            QRgb intensity = image.pixel(x, y);

            switch (channel)
            {
			case BLUE:
                color += qBlue(intensity);
				break;
			case GREEN:
                color += qGreen(intensity);
				break;
			case RED:
                color += qRed(intensity);
				break;
            case BGR:
            {// all
                color += qBlue(intensity);
                color += qGreen(intensity);
                color += qRed(intensity);
            }
                break;
			}
		}
	}
    if (channel == BGR)
    {
        color /= (3 * N); // 3 channels to must divide by 3 times N
    }
    else
    {
        color /= N;
    }

	return color;
}

int ImageHelper::getMedianColor(QImage& image, int channel)
{
    if(image.width() == 0 || image.height() == 0)
    {
        return 0;
    }

    std::vector<int> colors;

    for (int y = 0; y != image.height(); ++y)
    {
        for (int x = 0; x != image.width(); ++x)
        {
            int color = 0;

            QRgb intensity = image.pixel(x, y);

            switch (channel)
            {
            case BLUE:
                color = qBlue(intensity);
                colors.push_back(color);
                break;
            case GREEN:
                color = qGreen(intensity);
                colors.push_back(color);
                break;
            case RED:
                color = qRed(intensity);
                colors.push_back(color);
                break;
            case BGR:
            {// all
                color += qBlue(intensity);
                color += qGreen(intensity);
                color += qRed(intensity);
                colors.push_back(color);
            }
                break;
            }
		}
    }

    if (channel == BGR)
    {
        for (int c : colors) { c /= 3; }
    }

	sort(colors.begin(), colors.end()); // sort the colors

	return colors.at(colors.size() / 2); // return the middle element
}

int ImageHelper::getMaxColor(QImage& image, int channel)
{
	int max = -1; // impossible max
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            QRgb intensity = image.pixel(x, y);
            int color = 0;
            switch (channel)
            {
            case BLUE:
                color = qBlue(intensity);
                break;
            case GREEN:
                color = qGreen(intensity);
                break;
            case RED:
                color = qRed(intensity);
                break;
            }

            if (max < color)
            {
                max = color;
            }
        }
    }

	return max;
}

int ImageHelper::getMinColor(QImage& image, int channel)
{
	int min = 256; // impossible min
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            QRgb intensity = image.pixel(x, y);
            int color = 256;
            switch (channel)
            {
            case BLUE:
                color = qBlue(intensity);
                break;
            case GREEN:
                color = qGreen(intensity);
                break;
            case RED:
                color = qRed(intensity);
                break;
            }

            if (min > color)
            {
                min = color;
            }
        }
    }

	return min;
}

QString ImageHelper::pixmapToPngString(QPixmap pixmap)
{
    if(pixmap.isNull())
    {
        return "";
    }

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);

    pixmap.save(&buffer, "PNG");

    return QString(bytes.toBase64());
}

QPixmap ImageHelper::pngStringToPixmap(QString encoded_string)
{
    if(encoded_string.isEmpty())
    {
        return QPixmap();
    }

    QByteArray bytes = encoded_string.toLocal8Bit();

    QImage image;
    image.loadFromData(QByteArray::fromBase64(bytes), "PNG");

    return QPixmap::fromImage(image);
}

QPixmap ImageHelper::combineImages(QList<QPixmap> pixmaps, QList<QPoint> positions)
{
	QPointF upper_left;
	return combineImages(pixmaps, positions, upper_left);
}

QPixmap ImageHelper::combineImages(QList<QPixmap> pixmaps, QList<QPoint> positions, QPointF& upper_left, float position_scale)
{
	if (pixmaps.size() != positions.size())
	{
		return QPixmap();
	}

	if (pixmaps.empty())
	{
		return QPixmap();
	}

	if (pixmaps.size() == 1)
	{
		upper_left = positions[0] * position_scale;
		return pixmaps[0];
	}

	int min_x = 1000000, min_y = 1000000;
	int max_x = 0, max_y = 0;
	
	for (unsigned int i = 0; i != pixmaps.size(); ++i)
	{
		const QPixmap& pixmap = pixmaps[i];
		QPoint point = positions[i] * position_scale;

        min_x = point.x() < min_x ? point.x() : min_x;
        min_y = point.y() < min_y ? point.y() : min_y;

        max_x = point.x() + pixmap.width() > max_x ? point.x() + pixmap.width() : max_x;
        max_y = point.y() + pixmap.height() > max_y ? point.y() + pixmap.height() : max_y;
	}

	const int width = max_x - min_x;
	const int height = max_y - min_y;

	QPixmap group_pixmap(QSize(width, height));
	group_pixmap.fill(Qt::transparent);

	QPainter painter(&group_pixmap);

	for (unsigned int i = 0; i != pixmaps.size(); ++i)
	{
		const QPixmap& pixmap = pixmaps[i];
		const QPoint& point = positions[i] * position_scale;

		painter.drawPixmap(point.x() - min_x, point.y() - min_y, pixmap);
	}

	upper_left.setX(min_x);
	upper_left.setY(min_y);

	return group_pixmap;
}

QPixmap ImageHelper::scale(QPixmap pixmap, int width, int height)
{
	if (pixmap.isNull())
	{
		return pixmap;
	}

	return pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QPixmap ImageHelper::scaleToHeightCenter(QPixmap pixmap, int height, QColor color)
{
	if (pixmap.isNull())
	{
		return pixmap;
	}

	if (pixmap.height() >= height)
	{
		return pixmap;
	}

	const int width = pixmap.width();

	QPixmap center_pixmap(QSize(width, height));
	center_pixmap.fill(color);

	int y_offset = (height - pixmap.height()) / 2;

	QPainter painter(&center_pixmap);

	painter.fillRect(0, 0, width, height, QBrush(color));

	painter.drawPixmap(0, y_offset, pixmap);

	return center_pixmap;
}

QPixmap ImageHelper::scaleToWidthCenter(QPixmap pixmap, int width, QColor color)
{
	if (pixmap.isNull())
	{
		return pixmap;
	}

	if (pixmap.width() >= width)
	{
		return pixmap;
	}

	const int height = pixmap.height();

	QPixmap center_pixmap(QSize(width, height));
	center_pixmap.fill(color);

	int x_offset = (width - pixmap.width()) / 2;

	QPainter painter(&center_pixmap);

	painter.fillRect(0, 0, width, height, QBrush(color));

	painter.drawPixmap(x_offset, 0, pixmap);

	return center_pixmap;
}

QPixmap ImageHelper::scaleToCenter(QPixmap pixmap, int width, int height, QColor color)
{
	if (pixmap.isNull())
	{
		return pixmap;
	}

	QPixmap scaled_pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	if (scaled_pixmap.width() == width &&
		scaled_pixmap.height() == height)
	{
		return scaled_pixmap;
	}

	int x_offset = 0, y_offset = 0;

	if (scaled_pixmap.width() < width)
	{
		x_offset = (width - scaled_pixmap.width()) / 2;
	}
	else if (scaled_pixmap.height() < height)
	{
		y_offset = (height - scaled_pixmap.height()) / 2;
	}

	QPixmap center_pixmap(QSize(width, height));
	center_pixmap.fill(color);

	QPainter painter(&center_pixmap);

	painter.fillRect(0, 0, width, height, QBrush(color));

	painter.drawPixmap(x_offset, y_offset, scaled_pixmap);

	return center_pixmap;
}

bool ImageHelper::savePixmapAsPng(QPixmap pixmap, QString file_path)
{
	if (pixmap.isNull())
	{
		return false;
	}

	QFile file(file_path);
	file.open(QIODevice::WriteOnly);
	return pixmap.save(&file, "PNG");
}

bool ImageHelper::savePixmapAsJpg(QPixmap pixmap, QString file_path)
{
	if (pixmap.isNull())
	{
		return false;
	}

	QFile file(file_path);
	file.open(QIODevice::WriteOnly);
	return pixmap.save(&file, "jpg", 100);
}
