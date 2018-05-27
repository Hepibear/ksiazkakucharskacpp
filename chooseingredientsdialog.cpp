#include "chooseingredientsdialog.h"
#include "ui_chooseingredientsdialog.h"



chooseIngredientsDialog::chooseIngredientsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseIngredientsDialog),
    listWidget(ui->listWidget)
{
    ui->setupUi(this);

    QDialogButtonBox * btnBox = ui->buttonBox;
    QObject::connect(btnBox, SIGNAL(accepted()), this, SLOT(onAccept()));


}

chooseIngredientsDialog::~chooseIngredientsDialog()
{
    //delete ui->listWidget;
    delete ui;
}

void chooseIngredientsDialog::setIngredients(QVector<QString> i_ingredients)
{
    m_ingredients = i_ingredients.toList();
    this->setListView();
}

QVector<QString> chooseIngredientsDialog::getChosenIngredients()
{

    return m_chosenIngredients.toVector();
}

void chooseIngredientsDialog::onAccept()
{

    m_chosenIngredients.clear();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->checkState() == Qt::Checked)
            m_chosenIngredients.push_back(ui->listWidget->item(i)->text());
    }
}

void chooseIngredientsDialog::setListView()
{
    for(auto ingredient : m_ingredients)
    {
        QListWidgetItem *listItem = new QListWidgetItem(ingredient);

        listItem->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(listItem);
    }

    ui->listWidget->sortItems();
}
