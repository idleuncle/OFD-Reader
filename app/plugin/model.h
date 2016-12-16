#ifndef DOCUMENT_MODEL_H
#define DOCUMENT_MODEL_H
#include "typedef.h"
#include "global.h"
namespace ofdreader
{

    namespace Model
    {
        class IOutline;
        class IPage;

        class IDocument
        {
        public:
            virtual ~IDocument() {}
            virtual int numberOfPages() const = 0;

            virtual IPage* page(int index) const = 0;

//            virtual IOutline loadOutline() const { return Outline(); }
        };


        class IPage
        {
        public:
            virtual ~IPage() {}
            virtual QSizeF size() const = 0;

            virtual QImage render(qreal horizontalResolution = 72.0, qreal verticalResolution = 72.0, Rotation rotation = RotateBy0, const QRect& boundingRect = QRect()) const = 0;
        };

        class IOutline
        {
        public:
            virtual ~IOutline() {}

        };


        class IPackage
        {
        public:
            virtual ~IPackage() {}
            virtual IDocument* document() const = 0;
        };

    }

    class Plugin
    {
    public:
        virtual ~Plugin() {}

        virtual Model::IDocument* loadDocument(const QString& filePath) const = 0;



    };

}
Q_DECLARE_INTERFACE(ofdreader::Plugin, "local.ofdreader.Plugin")


#endif // DOCUMENT_MODEL_H
