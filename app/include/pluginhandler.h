#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include<QObject>
#include "model.h"
namespace ofdreader
{
    class Plugin;
    class PluginHandler: public QObject
    {
        Q_OBJECT
    public:
    public:
        static PluginHandler* instance();

        PluginHandler(QObject* parent = 0);

        Model::IDocument* loadDocument(const QString& filePath);

        ~PluginHandler();

        enum FileType
        {
            Unknown = 0,
            OFD = 1,
            Image = 2,
            PDF = 3,
        };

    private:

        static PluginHandler* s_instance;

        QMap<FileType, Plugin*> m_plugins;

        // 查找文件类型
        FileType findFileType(const QString& filePath);

        bool loadPlugin(FileType fileType);

        QString fileTypeName(PluginHandler::FileType fileType);
    };

}
#endif // PLUGINHANDLER_H
