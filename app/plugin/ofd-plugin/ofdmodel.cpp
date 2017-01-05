#include "ofdmodel.h"
#include <QSettings>
#include <QDebug>

#include <OFDFile.h>
#include <OFDPage.h>
#include <OFDDocument.h>
#include <QImage>

#include <cairo/cairo.h>
#define LOCK_ANNOTATION
#define LOCK_FORM_FIELD
#define LOCK_PAGE
#define LOCK_DOCUMENT

namespace
{

using namespace ofdreader;
using namespace ofdreader::Model;


}
namespace ofdreader
{

    namespace Model
    {
    OFDFile::OFDFile(ofd::OFDFile* file)
    {

    }

    IDocument* OFDFile::document() const
    {
//        ofd::OfdDocument* pDocument = new ofd::OfdDocument(this->m_file->GetDefaultDocument());
//        return pDocument;
        ofd::OFDDocumentPtr document = ofd::OFDDocumentPtr(this->m_file->GetDefaultDocument());
        return (IDocument*)document.get();
    }

//    OfdPackage::OfdPackage(ofd::OFDPackage* package)
//    {


//    }


//    OfdPackage::~OfdPackage()
//    {
//    }

//    IDocument* OfdPackage::document() const
//    {
////        OfdDocument* pDocument = new OfdDocument(this->m_package->GetOFDDocument());
//        return new OfdDocument(NULL);

//    }



    OfdDocument::OfdDocument(ofd::OFDDocument *document):
        m_mutex(),
        m_document(document)
    {
        qDebug()<<"Ofd Oducment ssss";
    }
    OfdDocument::~OfdDocument()
    {
        delete m_document;
    }




        int OfdDocument::numberOfPages() const
        {
            LOCK_DOCUMENT
            qDebug()<<"get numberOfPages";
            return 2;
//            return m_document->GetPagesCount();


        }

        IPage* OfdDocument::page(int index) const
        {
            ofd::OFDPage* page =NULL;// m_document->GetOFDPage(index);
//            if(page)
            {
                return new OfdPage(&m_mutex,page);
            }
            return 0;
        }



        OfdPage::OfdPage(QMutex *mutex, ofd::OFDPage *page):
            m_mutex(mutex),
            m_page(page)
        {
//            cairo_surface_t *surface;
            cairo_t *cr;

            m_surface =
                cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 320, 48);
            cr = cairo_create (m_surface);

            cairo_set_source_rgb (cr, 0.627, 0, 0);
            cairo_select_font_face (cr, "Simsun",
                                    CAIRO_FONT_SLANT_NORMAL,
                                    CAIRO_FONT_WEIGHT_NORMAL);

            cairo_set_source_rgb(cr, 0.5, 0.4, 0.3);
            cairo_set_font_size (cr, 24.0);
            cairo_move_to (cr, 10.0, 34.0);

            std::string ss="aa我我我aabb";
            cairo_show_text (cr, ss.c_str());

            //cout<<mystring.c_str();
            //cout<<my1.c_str();
//            cairo_surface_write_to_png (surface, "image.png");

            cairo_destroy (cr);
//            cairo_surface_destroy (surface);
        }

        OfdPage::~OfdPage()
        {

        }


        QSizeF OfdPage::size() const
        {

            return QSizeF(cairo_image_surface_get_width(m_surface) * 72.0 ,
                          cairo_image_surface_get_height(m_surface) * 72.0 );
        }

        QImage OfdPage::render(qreal horizontalResolution , qreal verticalResolution , Rotation rotation , const QRect& boundingRect) const
        {
//            return QImage();
            LOCK_PAGE
                    QTransform transform;

//                    transform.scale(horizontalResolution / dotsPerInchX(m_image),
//                                    verticalResolution / dotsPerInchY(m_image));

//            Poppler::Page::Rotation rotate;

                    switch(rotation)
                    {
                    default:
                    case RotateBy0:
                        break;
                    case RotateBy90:
                        transform.rotate(90.0);
                        break;
                    case RotateBy180:
                        transform.rotate(180.0);
                        break;
                    case RotateBy270:
                        transform.rotate(270.0);
                        break;
                    }


            int x = -1;
            int y = -1;
            int w = -1;
            int h = -1;

            if(!boundingRect.isNull())
            {
                x = boundingRect.x();
                y = boundingRect.y();
                w = boundingRect.width();
                h = boundingRect.height();
            }

//            return m_page->renderToImage(horizontalResolution, verticalResolution, x, y, w, h, rotate);
//            QImage image(horizontalResolution, iHverticalResolution QImage::Format_ARGB32);
//            unsigned char* pData =image.bits();
//            int iLineStride = image.bytesPerLine();

            QImage* image = new QImage(cairo_image_surface_get_data(m_surface),
                                        cairo_image_surface_get_width(m_surface),
                                        cairo_image_surface_get_height(m_surface),
                                        QImage::Format_ARGB32);
            return *image;

        }

    }

OfdPlugin::OfdPlugin(QObject* parent) : QObject(parent)
{
    setObjectName("OfdPlugin");

    m_settings = new QSettings("qpdfview", "pdf-plugin", this);
}

Model::IDocument* OfdPlugin::loadDocument(const QString& filePath) const
{

//    cairo_surface_t *surface;
//    cairo_t *cr;

//    surface =
//        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 320, 48);
//    cr = cairo_create (surface);

//    cairo_set_source_rgb (cr, 0.627, 0, 0);
//    cairo_select_font_face (cr, "Simsun",
//                            CAIRO_FONT_SLANT_NORMAL,
//                            CAIRO_FONT_WEIGHT_NORMAL);

//    cairo_set_source_rgb(cr, 0.5, 0.4, 0.3);
//    cairo_set_font_size (cr, 24.0);
//    cairo_move_to (cr, 10.0, 34.0);

//    std::string ss="aa我我我aabb";
//    cairo_show_text (cr, ss.c_str());

//    //cout<<mystring.c_str();
//    //cout<<my1.c_str();
////            cairo_surface_write_to_png (surface, "image.png");

//    cairo_destroy (cr);
////            cairo_surface_destroy (surface);

//    ofd::OFDPackage *package = new ofd::OFDPackage();
//    Model::OfdPackage* pOfdPackage = NULL;
////    bool bret = package->Open(filePath.toStdString());
//    bool bret = true;
//    if(bret)
//    {
//        qDebug()<<"OFDpackage "<<"xxxopen ok";
//        pOfdPackage = new Model::OfdPackage(package);

//        return pOfdPackage->document();
//    }
//    qDebug()<<"Ofd open fail";
//    return 0;
}

//SettingsWidget* OfdPlugin::createSettingsWidget(QWidget* parent) const
//{
//    return new PdfSettingsWidget(m_settings, parent);
//}


}
//#if QT_VERSION < QT_VERSION_CHECK(5,0,0)

//Q_EXPORT_PLUGIN2(qpdfview_ofd, qpdfview::OfdPlugin)

//#endif // QT_VERSION
