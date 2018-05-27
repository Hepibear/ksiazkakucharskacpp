#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateTime>

#include "recipemanager.h"
#include "recipe.h"
#include "chooseingredientsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonLeftArrow_clicked();

    void on_buttonRandom_clicked();

    void on_buttonRightArrow_clicked();

    void on_buttonShowAll_clicked();

    void on_buttonIngredients_clicked();

    void on_buttonRandomDinner_clicked();

private:
    Ui::MainWindow *ui;

    chooseIngredientsDialog * ingredientDialog;

    RecipeManager r_manager;

    QVector<Recipe> m_recipes;
    QVector<Recipe> m_actualRecipes;

    int m_totalRecipeQuantity;
    int m_actualRecipeQuantity;

    int m_actualIndex;

    int getNextIndex(int i_index) const;
    int getPreviousIndex(int i_index) const;

    void showRecipe(int i_index);

    void showOnlyRecipesContaing(QVector<QString> i_ingredients);

    std::mt19937 gen;

    Recipe::Type m_actualTypeOfDinner;

};

#endif // MAINWINDOW_H
