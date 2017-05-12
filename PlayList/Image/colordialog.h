#pragma once

#include <QWidget>
#include <QColorDialog>

namespace Platform
{
	class ColorDialog : public QObject
	{
		Q_OBJECT

	public:
		ColorDialog(QWidget *parent = 0);
		~ColorDialog();

		void show(int x, int y);

		void showCenterMat();

		void hide();

	signals:
		void colorSelected(QColor color);

	private slots:
		void colorPickSelected(QColor color);

	private:
		QColorDialog *m_color_dialog;
	};
}
