#include "pluginhandler.h"
#include "model.h"
#include <QApplication>
#include <QMimeDatabase>
#include <QImageReader>
#include <QMessageBox>
const char* const ofdMimeType = "application/zip";

using namespace ofdreader;
PluginHandler* PluginHandler::s_instance = NULL;
PluginHandler::PluginHandler(QObject* parent):
    QObject(parent),
    m_plugins()
{
    //    m_plugins.insert()
}

PluginHandler::~PluginHandler()
{
    //由 QObject 继承,父类自动释放
    s_instance = NULL;
    //    if(s_instance)
    //    {
    //        delete s_instance;
    //        s_instance = NULL;
    //    }
}

PluginHandler* PluginHandler::instance()
{
    if(s_instance == 0)
    {
        s_instance = new PluginHandler(qApp);
    }

    return s_instance;
}

QString PluginHandler::fileTypeName(PluginHandler::FileType fileType)
{
    switch(fileType)
    {
    default:
    case PluginHandler::Unknown:
        return QLatin1String("Unknown");
    case PluginHandler::OFD:
        return QLatin1String("OFD");
    case PluginHandler::PDF:
        return QLatin1String("PDF");
    case PluginHandler::Image:
        return QLatin1String("Image");
    }
}



Model::IDocument* PluginHandler::loadDocument(const QString& filePath)
{
    const FileType fileType = this->findFileType(filePath);
    if(fileType == Unknown)
    {
        qWarning() << tr("Could not match file type of '%1'!").arg(filePath);

        return 0;
    }

    if(!loadPlugin(fileType))
    {
        QMessageBox::critical(0, tr("Critical"), tr("Could not load plug-in for file type '%1'!").arg(fileTypeName(fileType)));

        return 0;
    }

    return m_plugins.value(fileType)->loadDocument(filePath);
}



bool isSupportedImageFormat(const QMimeType& mimeType)
{
    const QByteArray name = mimeType.name().toLocal8Bit();

    return QImageReader::supportedMimeTypes().contains(name);
}

bool PluginHandler::loadPlugin(FileType fileType)
{
    if(m_plugins.contains(fileType))
    {
        return true;
    }

    return false;
}


PluginHandler::FileType PluginHandler::findFileType(const QString &filePath)
{
    PluginHandler::FileType fileType = PluginHandler::Unknown;


    const QMimeType mimeType = QMimeDatabase().mimeTypeForFile(filePath, QMimeDatabase::MatchContent);
    if(mimeType.inherits(ofdMimeType))
    {
        fileType = PluginHandler::OFD;
    }
    else if(isSupportedImageFormat(mimeType))
    {
        fileType = PluginHandler::Image;
    }
    else
    {
        qDebug() << "Unknown MIME type:" << mimeType.name();
    }
    return fileType;

}
