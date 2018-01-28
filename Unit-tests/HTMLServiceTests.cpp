#include "GlobalUnitTest.h"
#include "HTMLService.h"

TEST(HTMLServiceClass, OpenTagTest)
{
    HTMLService htmlService;
    ASSERT_EQ(htmlService.OpenTag("Test"), "<Test>");
}

TEST(HTMLServiceClass, CloseTagTest)
{
    HTMLService htmlService;
    ASSERT_EQ(htmlService.CloseTag("Test"), "</Test>");
}

TEST(HTMLServiceClass, ChainTest)
{
    HTMLService htmlService;
    htmlService.StartHTMLFile().
                    Paragraph("Test paragraph").NewLine().
                    HyperLink("Test link", "url").NewLine().
                    StartTable().IncIndent().
                                StartTableRow().TableColumn("First").EndTableRow().NewLine().
                                StartTableRow().TableCell("23").EndTableRow().DecIndent().
                    EndTable().
                EndHTMLFile();
    ASSERT_EQ(htmlService.GetHTML(),    "<html>\n"
                                        "\t<body>\n"
                                        "\t\t<p>Test paragraph</p><br>\n"
                                        "\t\t<a href=\"url\">Test link</a><br>\n"
                                        "\t\t<table border=\"1\">\n"
                                        "\t\t\t<tr><th>First</th></tr><br>\n"
                                        "\t\t\t<tr><td>23</td></tr>\n"
                                        "\t\t</table>\n"
                                        "\t</body>\n"
                                        "</html>");
}


TEST(HTMLServiceClass, AddAttributeTest)
{
    HTMLService htmlService;
    ASSERT_EQ(htmlService.AddAttribute("<Test>", "border", "1"), "<Test border=\"1\">");
}
