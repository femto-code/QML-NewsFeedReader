#include <QGuiApplication>
#include <QtQuick>

#include <iostream>
#include <string>
#include <vector>
#include <rapidxml.hpp>

using namespace std;
using namespace rapidxml;

xml_document<> doc;
xml_node<> * root_node = NULL;
int main(int argc, char* argv[])
{

    cout << "\nParsing my students data (sample.xml)....." << endl;



    string text = "<?xml version='1.0' encoding='utf-8'?><MyStudentsData><Student student_type='Part-time'><Name>John</Name></Student><Student student_type='Full-time'><Name>Sean</Name></Student><Student student_type='Part-time'><Name>Sarah</Name></Student></MyStudentsData>";
    vector<char> bytes(text.begin(), text.end());
    bytes.push_back('\0');
    char *c = &bytes[0];
    // c needs to be a zero-terminated string according to documentation: http://rapidxml.sourceforge.net/manual.html#classrapidxml_1_1xml__document_8338ce6042e7b04d5a42144fb446b69c_18338ce6042e7b04d5a42144fb446b69c
    // zero-terminated string explained: https://www.tutorialspoint.com/what-is-a-null-terminated-string-in-c-cplusplus
    doc.parse<0>(c);

    // Find out the root node
    root_node = doc.first_node("MyStudentsData");

    // Iterate over the student nodes
    for (xml_node<> * student_node = root_node->first_node("Student"); student_node; student_node = student_node->next_sibling())
    {
        cout << "\nStudent Type =   " << student_node->first_attribute("student_type")->value();
        cout << endl;

            // Interate over the Student Names
        for(xml_node<> * student_name_node = student_node->first_node("Name"); student_name_node; student_name_node = student_name_node->next_sibling())
        {
            cout << "Student Name =   " << student_name_node->value();
            cout << endl;
        }
        cout << endl;
    }

    return 0;

    QGuiApplication app(argc, argv);

    qputenv("QT_QUICK_BACKEND", "software");

    QScopedPointer<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
    engine->addImportPath(":/");

    engine->load(QUrl("qrc:/main.qml"));

    return app.exec();
}
