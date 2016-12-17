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
        Q_DISABLE_COPY(PluginHandler)

        static PluginHandler* s_instance;

        QMap<FileType, Plugin*> m_plugins;

        // =查找文件类型=
        FileType findFileType(const QString& filePath);
        // =保存静态对象插件=
        QMultiMap< FileType, QString > m_objectNames;

        QMultiMap< FileType, QString > m_fileNames;

        bool loadPlugin(FileType fileType);

        QString fileTypeName(PluginHandler::FileType fileType);
    };

}
#endif // PLUGINHANDLER_H
