#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_recipes(r_manager.getRecipes()),
    m_totalRecipeQuantity(r_manager.getAmountOfRecipes()),
    m_actualRecipeQuantity(m_totalRecipeQuantity),
    gen(std::chrono::system_clock::now().time_since_epoch().count())
{
    ui->setupUi(this);

    m_actualRecipes = m_recipes;
    showRecipe(0);
    m_actualIndex=0;
    ui->labelQuantity->setText("Wyświetlono wszystkie "+ QString::number(m_totalRecipeQuantity) +" przepisów!");

    QDateTime actualDate = QDateTime::currentDateTime();

    QTime actualTime = actualDate.time();

    if(actualTime.hour()>5 && actualTime.hour()<12)
        m_actualTypeOfDinner = Recipe::Type::Sniadanie;
    else if(actualTime.hour()>12 && actualTime.hour()<17)
        m_actualTypeOfDinner = Recipe::Type::Obiad;
    else
        m_actualTypeOfDinner = Recipe::Type::Kolacja;


    QString dinnerType;
    if(m_actualTypeOfDinner == Recipe::Type::Sniadanie)
        dinnerType="śniadanie";
    else if(m_actualTypeOfDinner == Recipe::Type::Obiad)
        dinnerType="obiad";
    else if(m_actualTypeOfDinner == Recipe::Type::Kolacja)
        dinnerType="kolację";


    ui->buttonRandomDinner->setText("Zaproponuj "+dinnerType);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonLeftArrow_clicked()
{
    int index = this->getPreviousIndex(m_actualIndex);
    m_actualIndex=index;
    showRecipe(index);
}

void MainWindow::on_buttonRandom_clicked()
{
    std::uniform_int_distribution<int> r(0, m_actualRecipeQuantity-1);
    int random_number = r(gen);

    showRecipe(random_number);
}

void MainWindow::on_buttonRightArrow_clicked()
{
    int index = this->getNextIndex(m_actualIndex);
    m_actualIndex=index;
    showRecipe(index);
}

void MainWindow::on_buttonShowAll_clicked()
{
    m_actualRecipes = m_recipes;
    m_actualRecipeQuantity = m_totalRecipeQuantity;
    ui->labelQuantity->setText("Wyświetlono wszystkie "+ QString::number(m_totalRecipeQuantity) +" przepisy!");

    showRecipe(0);
}

void MainWindow::on_buttonIngredients_clicked()
{
    ingredientDialog = new chooseIngredientsDialog();
    QVector<QString> temp_ingredients = r_manager.getAllIngredients();

    //for(auto x : temp_ingredients)
    //qDebug()<<x;

    ingredientDialog->setIngredients(temp_ingredients);

    if(ingredientDialog->exec() == QDialog::Accepted )
    {
        QVector<QString> t_ingredients = ingredientDialog->getChosenIngredients();

        if(!t_ingredients.isEmpty())
            showOnlyRecipesContaing(t_ingredients);
    }

    ingredientDialog->~chooseIngredientsDialog();

}

int MainWindow::getNextIndex(int i_index) const
{
    if(i_index == m_actualRecipeQuantity-1)
        return 0;
    else return  i_index+1;
}

int MainWindow::getPreviousIndex(int i_index) const
{
    if(i_index == 0)
        return m_actualRecipeQuantity-1;
    else return  i_index-1;
}

void MainWindow::showRecipe(int i_index)
{
    QString contentRecipe;
    contentRecipe = contentRecipe + "<h1>" + m_actualRecipes[i_index].title() + "</h1>";

    contentRecipe = contentRecipe + "<b>Czas Przygotowania:</b> "+m_actualRecipes[i_index].time();


    contentRecipe = contentRecipe + "<h3>Składniki:</h3>";


    for(int i=0; i<m_actualRecipes[i_index].ingredients().size();i++)
    {
        contentRecipe = contentRecipe + "-" + m_actualRecipes[i_index].ingredients().at(i) + ", " + m_actualRecipes[i_index].quantity().at(i) + "<br>";
    }

    contentRecipe = contentRecipe + "<h3>Sposób przygotowania:</h3>";

    int i = 0;
    for(auto step : m_actualRecipes[i_index].steps())
    {
        i++;
        contentRecipe = contentRecipe + "<b>Krok "+QString::number(i)+":</b><br>"+step+"<br><br>";
    }
    contentRecipe = contentRecipe + "<br><i>Polecane na "+m_actualRecipes[i_index].getDinnerType()+".</i>";


    ui->recipeBrowser->setText(contentRecipe);
    ui->labelId->setText("Przepis numer "+QString::number(m_actualRecipes[i_index].id()));
}

void MainWindow::showOnlyRecipesContaing(QVector<QString> i_ingredients)
{
    m_actualRecipes.clear();
    for(auto recipe : m_recipes)
    {
        for(auto ing : recipe.ingredients())
        {
            if(i_ingredients.contains(ing))
                m_actualRecipes.push_back(recipe);
        }
    }

    m_actualRecipeQuantity = m_actualRecipes.size();
    showRecipe(0);
    ui->labelQuantity->setText("Przepisów z podanymi składnikami jest łącznie "+QString::number(m_actualRecipeQuantity));
}

void MainWindow::on_buttonRandomDinner_clicked()
{

    QVector<Recipe> temp_typeRecipes;

    for(auto recipe : m_actualRecipes)
    {
        if(recipe.type() == m_actualTypeOfDinner)
            temp_typeRecipes.push_back(recipe);
    }

    m_actualRecipes = temp_typeRecipes;
    m_actualRecipeQuantity = m_actualRecipes.size();

    QString dinnerType;
    if(m_actualTypeOfDinner == Recipe::Type::Sniadanie)
        dinnerType="sniadania";
    else if(m_actualTypeOfDinner == Recipe::Type::Obiad)
        dinnerType="obiady";
    else if(m_actualTypeOfDinner == Recipe::Type::Kolacja)
        dinnerType="kolacje";

    ui->labelQuantity->setText("Wyswietlam "+QString::number(m_actualRecipeQuantity) + " przepisy na " + dinnerType);
    on_buttonRandom_clicked();

}
