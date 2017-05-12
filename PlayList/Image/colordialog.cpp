#include "colordialog.h"

using namespace Platform;

ColorDialog::ColorDialog(QWidget *parent)
{
	m_color_dialog = new QColorDialog(parent);
	m_color_dialog->setOptions(QColorDialog::ShowAlphaChannel |
		QColorDialog::DontUseNativeDialog);

	m_color_dialog->setWindowModality(Qt::WindowModal);

	connect(m_color_dialog, &QColorDialog::colorSelected,
		this, &ColorDialog::colorPickSelected);

	foreach(QObject *obj, m_color_dialog->children()) 
	{
		if (obj->isWidgetType()) 
		{
			QWidget *w = qobject_cast<QWidget *>(obj);
			QString className(w->metaObject()->className());
			if (className.contains("QColorPicker") ||
				className.contains("QDialogButtonBox") ||
				className.contains("QWellArray"))

			{
				// w->setStyleSheet("QPushButton { border-style: outset; border-color: gray; border-width: 2px; border-radius: 4px;}");
				w->show();
			}
			else {
				w->hide();
			}
		}
	}
}

ColorDialog::~ColorDialog()
{
    delete m_color_dialog;
}

void ColorDialog::colorPickSelected(QColor color)
{
	emit colorSelected(color);
}

void ColorDialog::show(int x, int y)
{
	m_color_dialog->move(x, y);
	m_color_dialog->show();
	m_color_dialog->raise();
}

void ColorDialog::showCenterMat()
{
	show(710, 1300);
}

void ColorDialog::hide()
{
	m_color_dialog->hide();
}
