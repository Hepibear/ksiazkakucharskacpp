#ifndef CHOOSEINGREDIENTSDIALOG_H
#define CHOOSEINGREDIENTSDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDebug>

namespace Ui {
class chooseIngredientsDialog;
}

class chooseIngredientsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chooseIngredientsDialog(QWidget *parent = 0);
    ~chooseIngredientsDialog();

    void setIngredients(QVector<QString> i_ingredients);
    QVector<QString> getChosenIngredients();



public slots:
    void onAccept();


private:
    Ui::chooseIngredientsDialog *ui;
    QListWidget * listWidget;

    QStringList m_ingredients;
    QStringList m_chosenIngredients;

    void setListView();
};

#endif // CHOOSEINGREDIENTSDIALOG_H
