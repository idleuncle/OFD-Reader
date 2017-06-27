#ifndef OFDMODEL_H
#define OFDMODEL_H

#include <QCoreApplication>
#include <QMutex>
#include <QScopedPointer>
#include "ofd/Page.h"
#include "ofd/Document.h"

#include <cairo/cairo.h>

class QCheckBox;
class QComboBox;
class QFormLayout;
class QSettings;


namespace Ofd
{
class Package;
class Document;
class Page;
}

#include "model.h"
namespace ofdreader
{

class OfdPlugin;
namespace Model
{
//    class OFDFile: public IFile
//    {
//        Q_DECLARE_TR_FUNCTIONS(Model::OfdPackage)
//        friend class ofdreader::OfdPlugin;
//    public:
//        ~OFDFile(){}
//        virtual IDocument* document() const;
//    private:
//        Q_DISABLE_COPY(OFDFile)

//         OFDFile(ofd::OFDFile* file);

//         mutable QMutex m_mutex;

//         ofd::OFDFile* m_file;
//    };

//    class OfdPackage: public IPackage
//    {
//        Q_DECLARE_TR_FUNCTIONS(Model::OfdPackage)
//        friend class ofdreader::OfdPlugin;
//    public:
//        ~OfdPackage();
//        virtual IDocument* document() const;
//    private:
//        Q_DISABLE_COPY(OfdPackage)

//         OfdPackage(ofd::OFDPackage* package);

//         mutable QMutex m_mutex;

//         ofd::OFDPackage* m_package;
//    };

    class OfdPage : public IPage
    {
        Q_DECLARE_TR_FUNCTIONS(Model::OfdPage)
        friend class ofdreader::OfdPlugin;

    public:
        OfdPage(QMutex* mutex, ofd::PagePtr page);
        virtual ~OfdPage();

        virtual QSizeF size() const;

        virtual QImage render(qreal horizontalResolution = 72.0, qreal verticalResolution = 72.0, Rotation rotation = RotateBy0, const QRect& boundingRect = QRect()) const;

    private:

        mutable QMutex* m_mutex;
        ofd::PagePtr m_page;
        cairo_surface_t* m_surface;
    };



    class OfdDocument : public IDocument
    {
        Q_DECLARE_TR_FUNCTIONS(Model::OfdDocument)

        friend class ofdreader::OfdPlugin;

    public:
        Q_DISABLE_COPY(OfdDocument)

        OfdDocument(ofd::DocumentPtr document);

        ~OfdDocument();

        int numberOfPages() const;

        IPage* page(int index) const;

    //    bool isLocked() const;
    //    bool unlock(const QString& password);

    //    QStringList saveFilter() const;

    //    bool canSave() const;
    //    bool save(const QString& filePath, bool withChanges) const;

    //    bool canBePrintedUsingCUPS() const;

    //    void setPaperColor(const QColor& paperColor);

    //    Outline loadOutline() const;
    //    Properties loadProperties() const;

    //    QAbstractItemModel* loadFonts() const;

    //    bool wantsContinuousMode() const;
    //    bool wantsSinglePageMode() const;
    //    bool wantsTwoPagesMode() const;
    //    bool wantsTwoPagesWithCoverPageMode() const;
    //    bool wantsRightToLeftMode() const;

    private:


        mutable QMutex m_mutex;
//        ofd::OFDDocument* m_document;
        ofd::DocumentPtr document;

    };
}

class OfdPlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_INTERFACES(ofdreader::Plugin)

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)

    Q_PLUGIN_METADATA(IID "local.qpdfview.Plugin")

#endif // QT_VERSION

public:
    OfdPlugin(QObject* parent = 0);

    Model::IDocument* loadDocument(const QString& filePath) const;

//    SettingsWidget* createSettingsWidget(QWidget* parent) const;

    ofd::PackagePtr ofdFile;// = std::make_shared<ofd::OFDPackage>();



private:
    Q_DISABLE_COPY(OfdPlugin)

    QSettings* m_settings;

};


}

#endif // OFDMODEL_H
