#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

#include <QVector>
#include <QString>
#include <QResource>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "recipe.h"

class RecipeManager
{
    QVector<Recipe> m_recipes;
        void loadRecipesFromDatabase();

public:
    RecipeManager();

    QVector<QString> getAllIngredients();
    QVector<Recipe> getRecipes() const;
    //numeration from zero
    int getAmountOfRecipes() const { return m_recipes.size(); }
};

#endif // RECIPEMANAGER_H
