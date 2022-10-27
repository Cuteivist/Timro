#include "ProjectWorkHistoryModel.h"

#include <QSqlQuery>
#include <QSqlError>

using namespace Qt::Literals::StringLiterals;

ProjectWorkHistoryModel::ProjectWorkHistoryModel(QObject *parent)
    : SqlModel{parent}
{
}

bool ProjectWorkHistoryModel::setData(const QModelIndex&, const QVariant&, int)
{
    return false;
}

QHash<int, QByteArray> ProjectWorkHistoryModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { ProjectIdRole, "projectId"_ba },
        { NameRole, "name"_ba },
        { MaxWorkTimeRole, "maxWorkTime"_ba },
        { WorkTimeRole, "workTime"_ba }
    };
    return roles;
}

void ProjectWorkHistoryModel::init()
{
    QSqlQuery query(database());
    query.prepare(u"SELECT"
                  " p.id,"
                  " p.name,"
                  " p.max_work_time,"
                  " (SELECT work_time FROM worklog w_sum WHERE w_sum.project_id=p.id AND w_sum.session_id=s.id) as work_time"
                  " FROM project p, work_session s, worklog w"
                  " WHERE"
                  " s.finished = false"
                  " AND w.session_id = s.id"
                  " AND p.id = w.project_id"
                  " AND p.deleted = false"
                  " GROUP BY p.id"
                  " ORDER BY w.update_time DESC"_s);
    query.exec();
    setQuery(std::move(query));
}

void ProjectWorkHistoryModel::refresh()
{
    QSqlQuery sqlQuery = query();
    sqlQuery.exec();
    setQuery(std::move(sqlQuery));
}

void ProjectWorkHistoryModel::onWorkTimeRunningChanged(const bool running)
{
    if (running) {
        refresh();
    }
}
