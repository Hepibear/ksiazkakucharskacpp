#include "recipemanager.h"

QVector<Recipe> RecipeManager::getRecipes() const
{
    return m_recipes;
}

RecipeManager::RecipeManager()
{
    this->loadRecipesFromDatabase();
}

void RecipeManager::loadRecipesFromDatabase()
{
    QResource common(":/database/database.txt");

    QFile commonFile(common.absoluteFilePath());

    if (!commonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Unable to open file: " << commonFile.fileName() << " because of error " << commonFile.errorString() << '\n';

        return;
    }

    QTextStream in(&commonFile);

    QString content = in.readAll();

    QRegExp rx("(\\;)");

    QVector<QString> queries = content.split(rx).toVector();
    QVector<QVector<QString>> raw_recipes;

    QVector<QString> temp_query;
    for(auto query : queries)
    {
        temp_query.push_back(query);

        if((query == "sniadanie") ||
                (query == "obiad") ||
                (query == "kolacja")  )
        {
            raw_recipes.push_back(temp_query);
            temp_query.clear();
        }
    }

    for(auto rec : raw_recipes)
    {
        Recipe temp_recipe;
        temp_recipe.setId(rec[0].toInt());
        temp_recipe.setTitle(rec[1]);

        int i=2;

        QVector<QString> temp_ingredients;
        QVector<QString> temp_quantity;
        while(rec[i] != "koniec skladnikow")
        {
            temp_ingredients.push_back(rec[i]);
            i++;
            temp_quantity.push_back(rec[i]);
            i++;
        }
        i++;//pomijamy "koniec skladnikow"

        temp_recipe.setIngredients(temp_ingredients);
        temp_recipe.setQuantity(temp_quantity);

        QVector<QString> temp_steps;
        while(rec[i] != "koniec krokow")
        {
            temp_steps.push_back(rec[i]);
            i++;
        }
        i++;//pomijamy "koniec krokow"

        temp_recipe.setSteps(temp_steps);

        temp_recipe.setTime(rec[i]);
        i++;

        if(rec[i] == "sniadanie")
            temp_recipe.setType(Recipe::Type::Sniadanie);
        else if(rec[i] == "obiad")
            temp_recipe.setType(Recipe::Type::Obiad);
        else if(rec[i] == "kolacja")
            temp_recipe.setType(Recipe::Type::Kolacja);


        m_recipes.push_back(temp_recipe);
    }


}

QVector<QString> RecipeManager::getAllIngredients()
{
    QVector<QString> temp_ingredients;

    for(auto rec : m_recipes)
    {
        for(auto ing : rec.ingredients())
        {
            if(!temp_ingredients.contains(ing))
                temp_ingredients.push_back(ing);
        }

    }

    return temp_ingredients;

}
