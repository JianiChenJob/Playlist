#include "qstringhelper.h"

#include <cctype>

using namespace Core;

QString QStringHelper::makeValidFolderName(QString folder_name)
{
	if (folder_name.isEmpty())
	{
		return QStringLiteral("folder");
	}

	for (unsigned int i = 0; i != folder_name.size(); ++i)
	{
		QChar c = folder_name.at(i);

		bool ok = false;

		if (c.isLetter())
		{
			ok = true;
		}

		if (i > 0 && c.isNumber())
		{
			ok = true;
		}

		if (!ok)
		{
			folder_name[i] = '-';
		}
	}

	return folder_name;
}