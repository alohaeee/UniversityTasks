#include "Core/customuiloader.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QtUiTools/QUiLoader>
#include <stdexcept>

#include <QFont>
#include <QGridLayout>
#include <QHeaderView>
#include <QListWidget>
#include <QMetaEnum>
#include <QMetaObject>
#include <QRect>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

CustomUILoader::Attribute *CustomUILoader::GetAttributeOrThrow(AttributeList &attributes, const QString &name)
{
    auto iter = std::find_if(attributes.begin(), attributes.end(), [name](auto &&v) { return v.name() == name; });

    if (iter == attributes.end())
    {
        throw std::invalid_argument(QString("Can't find attribute: %1").arg(name).toStdString());
    }
    return iter;
}

void CustomUILoader::ExpectNext(const QString &name)
{
    ReadNext();
    Expect(name);
}

void CustomUILoader::ExpectNext(CustomUILoader::TokenType type)
{
    ReadNext();
    Expect(type);
}

void CustomUILoader::Expect(const QString &name)
{
    if (!IsElement(name))
    {
        throw std::invalid_argument(
            QString("Expect %1 but found %2").arg(name).arg(m_reader.qualifiedName()).toStdString());
    }
}

void CustomUILoader::Expect(CustomUILoader::TokenType type)
{
    if (!IsElement(type))
    {
        throw std::invalid_argument(
            QString("Expect %1 but found %2").arg(type).arg(m_reader.tokenType()).toStdString());
    }
}

bool CustomUILoader::IsEndElement(const QString &itemName)
{
    if (m_reader.isEndElement() && IsElement(itemName))
    {
        return true;
    }
    return false;
}

bool CustomUILoader::IsStartElement(const QString &itemName)
{
    if (m_reader.isStartElement() && IsElement(itemName))
    {
        return true;
    }
    return false;
}

void CustomUILoader::ReadWhileNotEndOf(const QString &element, std::function<void()> handler)
{
    while (!IsEndElement(element))
    {
        ReadNext();
        if (IsStartElement())
        {
            handler();
        }
    }
    ReadNext();
}

std::pair<QString, QString> CustomUILoader::ClassAndNameAttribute()
{
    auto attributes = Attributes();
    auto type = GetAttributeOrThrow(attributes, CLASS)->value().toString();
    auto name = GetAttributeOrThrow(attributes, NAME)->value().toString();

    return {type, name};
}

QWidget *CustomUILoader::VisitForWidget()
{
    while (!IsStartElement(WIDGET))
    {
        ReadNext();
    }
    auto widget = CreateWidget(nullptr);

    return widget;
}

QSet<QString> CustomUILoader::VisitForSourceGen(const QString &content)
{
    Reader reader(content);

    QSet<QString> uniqueTypes;

    while (reader.tokenType() != TokenType::EndDocument)
    {
        auto token = reader.readNext();
        if (token == TokenType::StartElement)
        {
            if (reader.qualifiedName() == "widget" || reader.qualifiedName() == "layout")
            {
                auto attributes = reader.attributes();
                auto type = GetAttributeOrThrow(attributes, "class")->value();

                uniqueTypes.insert(type.toString());

                QFont f;
                //                Q_ARG(int, 32);
                //                QMetaObject::
                //                QMetaObject::invokeMethod(f,"setFamily");
                //                QWidget w;
                //                QTreeWidget wt;
                //                QTreeWidget
            }
        }
    }
    return uniqueTypes;
}

void CustomUILoader::ReadProperty(QObject *object)
{
    auto propertyName = GetAttributeOrThrow(NAME).value().toString();
    auto stdString = propertyName.toStdString();
    const char *propertyNameCString = stdString.c_str();
    QVariant propertyValue;

    ReadToNextStart();
    if (IsElement(ENUM))
    {
        // read <enum>
        ExpectNext(TokenType::Characters);
        auto meta = object->metaObject();

        auto index = meta->indexOfProperty(propertyNameCString);
        auto property = meta->property(index);

        auto enumKey = m_reader.text().toString();
        propertyValue = property.enumerator().keyToValue(enumKey.toStdString().data());
    }
    else
    {
        // read <"any">
        // ReadNext();
        propertyValue = CreateVariant(Name().toString());
    }

    object->setProperty(propertyNameCString, propertyValue);
}

QString OpenFileAndReadAll(const QString &filename)
{
    QFile file(filename);

    file.open(QFile::ReadOnly);

    if (!file.isOpen())
    {
        throw std::invalid_argument(QString("Can't open file: %1").arg(file.fileName()).toStdString());
    }

    QTextStream stream(&file);

    stream.setCodec("UTF-8");

    return stream.readAll();
}
