#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QSqlTableModel>

class SqlModel : public QSqlTableModel
{
public:
    SqlModel(QObject *parent = nullptr);
    virtual ~SqlModel();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    static int roleToColumnIndex(const int role);

protected:
    bool insertNewRecord(const QSqlRecord &record, const int row = -1);    
};

#endif // SQLMODEL_H
