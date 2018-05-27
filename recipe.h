#ifndef RECIPE_H
#define RECIPE_H

#include <QVector>
#include <QString>

class Recipe
{
public:
    enum class Type : char
    {
        Sniadanie,
        Obiad,
        Kolacja
    };

    Recipe() = default;
    Recipe(int i_id,
           QString i_title,
           QVector<QString> i_ingredients,
           QVector<QString> i_quantity,
           QVector<QString> i_steps,
           Type i_type);


    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    QVector<QString> ingredients() const;
    void setIngredients(const QVector<QString> &ingredients);

    QVector<QString> quantity() const;
    void setQuantity(const QVector<QString> &quantity);

    QVector<QString> steps() const;
    void setSteps(const QVector<QString> &steps);

    Type type() const;
    void setType(const Type &type);
    QString getDinnerType() const;

    QString time() const;
    void setTime(const QString &time);

private:
    int m_id;
    QString m_title;
    QVector<QString> m_ingredients;
    QVector<QString> m_quantity;
    QVector<QString> m_steps;
    Type m_type;
    QString m_time;



};

#endif // RECIPE_H
