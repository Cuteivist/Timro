#ifndef PROJECTWORKHISTORYMODEL_H
#define PROJECTWORKHISTORYMODEL_H

#include "SqlModel.h"

class ProjectWorkHistoryModel : public SqlModel
{
    Q_OBJECT
public:
    enum ModelRole {
        ProjectIdRole = Qt::UserRole + 1,
        NameRole,
        MaxWorkTimeRole,
        WorkTimeRole
    };

    explicit ProjectWorkHistoryModel(QObject *parent = nullptr);

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    void init();

public slots:
    void onWorkTimeRunningChanged(const bool running);
    void refresh();
};

#endif // PROJECTWORKHISTORYMODEL_H
