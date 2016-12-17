#include "pluginhandler.h"
#include "model.h"
#include <QApplication>
#include <QMimeDatabase>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QPluginLoader>
const char* const ofdMimeType = "application/zip";

using namespace ofdreader;
PluginHandler* PluginHandler::s_instance = NULL;
PluginHandler::PluginHandler(QObject* parent):
    QObject(parent),
    m_plugins()
{
#ifdef STATIC_IMAGE_PLUGIN
    m_objectNames.insertMulti(Image, QLatin1String("ImagePlugin"));
#else
    m_fileNames.insertMulti(Image, QLatin1String(IMAGE_PLUGIN_NAME));
#endif

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



Plugin* loadStaticPlugin(const QString& objectName)
{

    foreach(QObject* object, QPluginLoader::staticInstances())
    {
        if(object->objectName() == objectName)
        {
            Plugin* plugin = qobject_cast< Plugin* >(object);

            if(plugin != 0)
            {
                return plugin;
            }
        }
    }


    qCritical() << "Could not load static plug-in:" << objectName;

    return 0;
}


Plugin* loadPlugin(const QString& fileName)
{
    QPluginLoader pluginLoader;

    const QString localFileName = QDir(QApplication::applicationDirPath()).absoluteFilePath(fileName);
    qDebug()<<"localFileName"<<localFileName;
    pluginLoader.setFileName(localFileName);

    if(!pluginLoader.load())
    {
        const QString localErrorString = pluginLoader.errorString();

        const QString globalFileName = QDir(PLUGIN_INSTALL_PATH).absoluteFilePath(fileName);
        pluginLoader.setFileName(globalFileName);

        if(!pluginLoader.load())
        {
            const QString globalErrorString = pluginLoader.errorString();

            qCritical() << "Could not load local plug-in:" << localFileName;
            qCritical() << localErrorString;

            qCritical() << "Could not load global plug-in:" << globalFileName;
            qCritical() << globalErrorString;

            return 0;
        }
    }

    Plugin* plugin = qobject_cast< Plugin* >(pluginLoader.instance());

    if(plugin == 0)
    {
        qCritical() << "Could not instantiate plug-in:" << pluginLoader.fileName();
        qCritical() << pluginLoader.errorString();
    }

    return plugin;
}

bool PluginHandler::loadPlugin(FileType fileType)
{
//    QPluginLoader pluginLoader;

//    const QString localFileName = QDir(QApplication::applicationDirPath()).absoluteFilePath(fileName);
//    pluginLoader.setFileName(localFileName);
    if(m_plugins.contains(fileType))
    {
        return true;
    }


    foreach(const QString& objectName, m_objectNames.values(fileType))
    {

        if(Plugin* plugin = ::loadStaticPlugin(objectName))
        {
            m_plugins.insert(fileType, plugin);

            return true;
        }
    }

    foreach(const QString& fileName, m_fileNames.values(fileType))
       {
           if(Plugin* plugin = ::loadPlugin(fileName))
           {
               m_plugins.insert(fileType, plugin);

               return true;
           }
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
