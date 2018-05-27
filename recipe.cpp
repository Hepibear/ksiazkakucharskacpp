#include "recipe.h"



Recipe::Recipe(int i_id, QString i_title, QVector<QString> i_ingredients, QVector<QString> i_quantity, QVector<QString> i_steps, Recipe::Type i_type)
    : m_id(i_id),
      m_title(i_title),
      m_ingredients(i_ingredients),
      m_quantity(i_quantity),
      m_steps(i_steps),
      m_type(i_type)
{

}


int Recipe::id() const
{
    return m_id;
}

void Recipe::setId(int id)
{
    m_id = id;
}

QString Recipe::title() const
{
    return m_title;
}

void Recipe::setTitle(const QString &title)
{
    m_title = title;
}

QVector<QString> Recipe::ingredients() const
{
    return m_ingredients;
}

void Recipe::setIngredients(const QVector<QString> &ingredients)
{
    m_ingredients = ingredients;
}

QVector<QString> Recipe::quantity() const
{
    return m_quantity;
}

void Recipe::setQuantity(const QVector<QString> &quantity)
{
    m_quantity = quantity;
}

QVector<QString> Recipe::steps() const
{
    return m_steps;
}

void Recipe::setSteps(const QVector<QString> &steps)
{
    m_steps = steps;
}

Recipe::Type Recipe::type() const
{
    return m_type;
}

void Recipe::setType(const Type &type)
{
    m_type = type;
}

QString Recipe::getDinnerType() const
{
    if(m_type == Type::Sniadanie)
        return QString("śniadanie");
    else if(m_type == Type::Obiad)
        return QString("obiad");
    else if(m_type == Type::Kolacja)
        return QString("kolację");
    else return QString("EROR 404");

}

QString Recipe::time() const
{
    return m_time;
}

void Recipe::setTime(const QString &time)
{
    m_time = time;
}

