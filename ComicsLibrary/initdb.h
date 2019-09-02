#ifndef INITDB_H
#define INITDB_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>
#include <QDebug>

QList<QList<QString> > schemaList;

bool executeQuery(const QSqlDatabase& db, const QString& sql)
{
    QSqlQuery query(db);

    bool result = query.exec(sql);

    if (!result) {
        QSqlError err = query.lastError();
        qWarning() << QString("InitDb: Database error: %1").arg(err.text());
    }

    return result;
}

void createDatabaseSchema() {
    QList<QString> versionQueries;

    // Version 1
    versionQueries << "CREATE TABLE info(id INTEGER PRIMARY KEY, version INTEGER NOT NULL);";
    versionQueries << "INSERT INTO info(version) VALUES(1);";
    schemaList << versionQueries;
    versionQueries.clear();

    // Version 2
    versionQueries << "CREATE TABLE comic(id INTEGER PRIMARY KEY, name TEXT, price INTEGER, quantity INTEGER);";
    versionQueries << "UPDATE info SET version = 2;";
    schemaList << versionQueries;
    versionQueries.clear();
}

int getDatabaseVersion(const QSqlDatabase& db)
{
    int version = 0;

    QString sql("SELECT version FROM info");

    QSqlQuery query(db);

    bool result = query.exec(sql);

    if (result && query.next()) {
        version = query.value(0).toInt();
    }

    return version;
}

bool initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    int version;
    bool result;

    db.setDatabaseName("comics.db");

    if (!db.open()) {
        qWarning() << "InitDb: Cannot open database" << db.lastError().text();
    }

    createDatabaseSchema();

    version = getDatabaseVersion(db);

    if (version >= schemaList.count()) {
        qDebug() << "InitDb: Database is up-to-date";
        return true;
    }

    else if (!db.transaction()) {
        qWarning() << "InitDb: Cannot start transaction";
        return false;
    }

    for (int i=version; i<schemaList.count(); i++) {
        qDebug() << QString("InitDb: Applying update %1").arg(i+1);
        QString schema;

        foreach(schema, schemaList.at(i)) {
            result = executeQuery(db, schema);
            if (!result)
                break;
        }
    }

    if (!result) {
        qWarning() << "InitDb: Upgrade failed! Transaction rolled back";
        db.rollback();
    }
    else {
        db.commit();
        qDebug() << QString("InitDb: Database successfully upgraded to version %1").arg(schemaList.count());
    }

    return result;
}


#endif // INITDB_H
