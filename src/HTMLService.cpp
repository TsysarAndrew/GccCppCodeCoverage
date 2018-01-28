#include "HTMLService.h"

HTMLService::HTMLService()
{
    //ctor
}

HTMLService::~HTMLService()
{
    //dtor
}


std::string HTMLService::OpenTag(std::string tagName)
{
    return "<" + tagName + ">";
}


std::string HTMLService::CloseTag(std::string tagName)
{
    return "</" + tagName + ">";
}

std::string HTMLService::HyperLinkTag(std::string content, std::string linkURL)
{
    return AddAttribute(OpenTag("a"), "href", linkURL) + content + CloseTag("a");
}

std::string HTMLService::AddAttribute(std::string tagName, std::string attributeName, std::string attributeValue)
{
    std::string result = tagName;
    result.insert(result.size() - 1, " " + attributeName + "=\"" + attributeValue + "\"");
    return result;
}

HTMLService& HTMLService::StartTableRow(std::string color)
{
    if(color != "")
    {
        html += AddAttribute(OpenTag("tr"), "bgcolor", color);
    }
    else
    {
        html += OpenTag("tr");
    }
    return *this;
}

HTMLService& HTMLService::HyperLink(std::string content, std::string linkURL)
{
    html += HyperLinkTag(content, linkURL);
    return *this;
}

std::string HTMLService::GetHTML()
{
    return html;
}

HTMLService& HTMLService::IncIndent()
{
    indent += "\t";
    html += "\n" + indent;
    return *this;
}

HTMLService& HTMLService::DecIndent()
{
    indent = indent.substr(0, indent.size() - 1);
    html += "\n" + indent;
    return *this;
}

HTMLService& HTMLService::NewLine()
{
    html += "<br>\n" + indent;
    return *this;
}

HTMLService& HTMLService::StartHTMLFile()
{
    return StartHTML().IncIndent().StartBody().IncIndent();
}

HTMLService& HTMLService::EndHTMLFile()
{
    return DecIndent().EndBody().DecIndent().EndHTML();
}
