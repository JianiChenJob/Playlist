#pragma once

#include <QString>

namespace Core
{
	class QStringHelper
	{
	public:

		static QString makeValidFolderName(QString folder_name);
	};
}
