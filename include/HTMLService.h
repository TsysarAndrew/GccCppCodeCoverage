#ifndef HTMLSERVICE_H
#define HTMLSERVICE_H

#include <Global.h>

#define CLOSEHTMLTAG(Name,Presentation)  \
    HTMLService& End##Name() { \
        html += CloseTag(Presentation); \
        return *this; \
     };

#define HTMLTAG(Name,Presentation)  \
    HTMLService& Start##Name() { \
        html += OpenTag(Presentation); \
        return *this; \
     }; \
    HTMLService& End##Name() { \
        html += CloseTag(Presentation); \
        return *this; \
     };

#define HTMLTAG_WITH_ATTRIBUTE(Name,Presentation,Attribute,Value)  \
    HTMLService& Start##Name() { \
        html += AddAttribute(OpenTag(Presentation), Attribute, Value); \
        return *this; \
     }; \
    HTMLService& End##Name() { \
        html += CloseTag(Presentation); \
        return *this; \
     };


#define HTMLTAGCONTENT(Name,Presentation)  \
    HTMLService& Name(std::string content) { \
        html += OpenTag(Presentation) + content + CloseTag(Presentation); \
        return *this;\
    }

class HTMLService
{
    public:
        HTMLService();
        virtual ~HTMLService();

        std::string GetHTML();
        std::string OpenTag(std::string tagName);
        std::string CloseTag(std::string tagName);
        std::string HyperLinkTag(std::string content, std::string linkURL);
        std::string AddAttribute(std::string tagName, std::string attributeName, std::string attributeValue);

        HTMLTAG(HTML, "html");
        HTMLTAG(Body, "body");
        HTMLTAG_WITH_ATTRIBUTE(Table, "table", "border", "1");
        CLOSEHTMLTAG(TableRow, "tr");
        HTMLService& StartTableRow(std::string color = "");

        HTMLTAGCONTENT(Paragraph, "p");
        HTMLTAGCONTENT(TableColumn, "th");
        HTMLTAGCONTENT(TableCell, "td");

        HTMLService& HyperLink(std::string content, std::string linkURL);
        HTMLService& IncIndent();
        HTMLService& DecIndent();
        HTMLService& NewLine();

        HTMLService& StartHTMLFile();
        HTMLService& EndHTMLFile();

        HTMLService& AddAttribute();


    protected:

    private:
        std::string html;
        std::string indent;
};

#endif // HTMLSERVICE_H
