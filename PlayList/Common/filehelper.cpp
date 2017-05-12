#include "filehelper.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QImage>
#include <QDirIterator>

using namespace Platform;

void FileHelper::readBinaryFile(const QString& filename, std::vector<char>& data)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray array = file.readAll();
    if(array.size() == 0)
    {
        return;
    }

    data.insert(data.end(), array.begin(), array.end());
}

QString FileHelper::readFile(const QString& filename, bool utf8)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return "";
    }

    QTextStream infile(&file);

    if(utf8)
    {
        infile.setCodec("UTF-8");
    }

    QString file_contents = infile.readAll();

    return file_contents;
}

bool FileHelper::fileExists(const QString& filename)
{
    QFileInfo file(filename);
    return file.exists();
}

bool FileHelper::fileIsFolder(const QString& filename)
{
	QFileInfo file(filename);
	return file.isDir();
}

unsigned char* FileHelper::loadImage(const QString& filename,
                                     int *width, int *height, int *channels)
{
    QImage image;
    if(!image.load(filename))
    {
        return nullptr;
    }

    *width = image.width();
    *height = image.height();
    *channels = image.colorCount();

    return image.bits();
}

std::vector<QString> FileHelper::findAllFoldersTime(const QString& directory_path, bool recursive, QString folder_name)
{
	QStringList filters;
	if (folder_name != "")
	{
		filters.append("*" + folder_name + "*");
	}

	QDir dir(directory_path);
	QStringList entries = dir.entryList(filters, QDir::Dirs | QDir::NoDot | QDir::NoDotDot, QDir::Time);

	std::vector<QString> final_entries;
	for (unsigned int i = 0; i != entries.size(); ++i)
	{
		final_entries.push_back(directory_path + "/" + entries[i]);
	}

	return final_entries;
}

std::vector<QString> FileHelper::findAllFolders(const QString& directory_path, bool recursive, QString folder_name)
{
	QDir directory(directory_path);

	if (!directory.exists())
	{
		return std::vector<QString>();
	}

	directory.setFilter(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	if (folder_name != "")
	{
		QStringList filters;
		filters.append("*" + folder_name + "*");
		directory.setNameFilters(filters);
	}

	QDirIterator iterator(directory, 
		recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);

	std::vector<QString> folder_paths;

	while (iterator.hasNext())
	{
		folder_paths.push_back(iterator.next());
	}

	return folder_paths;
}

std::vector<QString> FileHelper::findAllFiles(const QString& directory_path, bool recursive, QString file_extension)
{
	QDir directory(directory_path);

	if (!directory.exists())
	{
		return std::vector<QString>();
	}

	directory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

	if (file_extension != "")
	{
		QStringList filters;
		filters.append("*." + file_extension);
		directory.setNameFilters(filters);
	}

	QDirIterator iterator(directory,
		recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);

	std::vector<QString> file_paths;

	while (iterator.hasNext())
	{
		file_paths.push_back(iterator.next());
	}

	return file_paths;
}

bool FileHelper::removeFile(QString file_path)
{
	QFileInfo file_info(file_path);
	if (!file_info.exists())
	{
		return true; // File is already removed
	}

	QFile file(file_path);
	return file.remove();
}

bool FileHelper::removeFolder(QString directory_path)
{
	bool result = true;
	QDir dir(directory_path);

	if (dir.exists()) 
	{
		Q_FOREACH(QFileInfo info, 
		dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) 
		{
			if (info.isDir()) 
			{
				result = removeFolder(info.absoluteFilePath());
			}
			else 
			{
				result = QFile::remove(info.absoluteFilePath());
			}

			if (!result) 
			{
				return result;
			}
		}
		result = dir.rmdir(directory_path);
	}
	return result;
}

bool FileHelper::copyDir(QString source_path, QString destination_path, bool overwrite)
{
	QDir source_dir(source_path);
	if (!source_dir.exists())
	{
		return false;
	}

	QDir dest_dir(destination_path);
	if (!dest_dir.exists())
	{
		dest_dir.mkdir(destination_path);
	}
	
	QStringList files = source_dir.entryList(QDir::Files);
	for (int i = 0; i< files.count(); i++)
	{
		QString src_name = source_path + "/" + files[i];
		QString dest_name = destination_path + "/" + files[i];

		if (overwrite || !QFileInfo(dest_name).exists())
		{
			QFile::copy(src_name, dest_name);
		}
	}

	files.clear();
	files = source_dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
	for (int i = 0; i < files.count(); ++i)
	{
		QString src_name = source_path + "/" + files[i];
		QString dest_name = destination_path + "/" + files[i];
		copyDir(src_name, dest_name);
	}

	return true;
}
