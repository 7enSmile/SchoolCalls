#include "include/view/tabledelegate.h"
#include "qapplication.h"
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPainter>
TableDelegate::TableDelegate(int value,QObject *parent) : QStyledItemDelegate(parent)
{
    maxValue= value;
}




QWidget* TableDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setAlignment(Qt::AlignHCenter);
    QDoubleValidator* val = new QDoubleValidator(editor);
    val->setBottom(0);
    val->setTop(maxValue);
    val->setNotation(QDoubleValidator::StandardNotation);
    editor->setValidator(val);
    return editor;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index,Qt::EditRole).toDouble();
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    line->setText(QString().setNum(value));
}

void TableDelegate::setModelData(QWidget* editor,QAbstractItemModel* model,const QModelIndex &index) const
{
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index,value);
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1 || index.column() == 0){
        QString text = index.model()->data(index, Qt::DisplayRole).toString();
        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignCenter;
        QApplication::style()->drawItemText ( painter, myOption.rect , myOption.displayAlignment, QApplication::palette(), true,text );
    }
}


