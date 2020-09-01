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
    versionQueries << "CREATE TABLE courses(id INTEGER PRIMARY KEY, semester TEXT NOT NULL, code TEXT NOT NULL, letter TEXT NOT NULL, credit INTEGER NOT NULL);";
    versionQueries << "UPDATE info SET version = 2;";
    schemaList << versionQueries;
    versionQueries.clear(); 

    // Version 3
    versionQueries << "CREATE TABLE details(id INTEGER PRIMARY KEY, code TEXT NOT NULL, midterm INTEGER, final INTEGER, quiz INTEGER, hw INTEGER, FOREIGN KEY(code) REFERENCES courses(code));";
    versionQueries << "UPDATE info SET version = 3;";
    schemaList << versionQueries;
    versionQueries.clear();

    // Version 4
    versionQueries << "DROP TABLE details;";
    versionQueries << "CREATE TABLE details(id INTEGER PRIMARY KEY, code TEXT NOT NULL, midterm INTEGER, final INTEGER, quiz1 INTEGER, quiz2 INTEGER, quiz3 INTEGER,"
                      "quiz4 INTEGER, quiz5 INTEGER, quiz6 INTEGER, hw1 INTEGER, hw2 INTEGER, hw3 INTEGER, hw4 INTEGER, hw5 INTEGER, FOREIGN KEY(code) REFERENCES courses(code));";
    versionQueries << "UPDATE info SET version = 4;";
    schemaList << versionQueries;
    versionQueries.clear();

    // Version 5
    versionQueries << "DROP TABLE details;";
    versionQueries << "DROP TABLE courses;";
    versionQueries << "CREATE TABLE courses(code TEXT PRIMARY KEY, semester TEXT NOT NULL, letter TEXT NOT NULL, credit INTEGER NOT NULL);";
    versionQueries << "CREATE TABLE details(id INTEGER PRIMARY KEY, code TEXT NOT NULL, midterm INTEGER, final INTEGER, quiz1 INTEGER, quiz2 INTEGER, quiz3 INTEGER,"
                      "quiz4 INTEGER, quiz5 INTEGER, quiz6 INTEGER, hw1 INTEGER, hw2 INTEGER, hw3 INTEGER, hw4 INTEGER, hw5 INTEGER, FOREIGN KEY(code) REFERENCES courses(code));";
    versionQueries << "UPDATE info SET version = 5;";
    schemaList << versionQueries;
    versionQueries.clear();

    // Version 6
    versionQueries << "DROP TABLE details;";
    versionQueries << "DROP TABLE courses;";
    versionQueries << "CREATE TABLE courses(id INTEGER PRIMARY KEY, semester TEXT NOT NULL, code TEXT NOT NULL, letter TEXT NOT NULL, credit INTEGER NOT NULL);";

    versionQueries << "CREATE TABLE details(id INTEGER PRIMARY KEY, code TEXT NOT NULL, midterm INTEGER, final INTEGER, quiz1 INTEGER, quiz2 INTEGER, quiz3 INTEGER,"
                      "quiz4 INTEGER, quiz5 INTEGER, quiz6 INTEGER, hw1 INTEGER, hw2 INTEGER, hw3 INTEGER, hw4 INTEGER, hw5 INTEGER, FOREIGN KEY(code) REFERENCES courses(code));";
    versionQueries << "UPDATE info SET version = 6;";
    schemaList << versionQueries;
    versionQueries.clear();

    // Version 7
    versionQueries << "DROP TABLE details;";
    versionQueries << "DROP TABLE courses;";
    versionQueries << "CREATE TABLE courses(id INTEGER PRIMARY KEY, semester TEXT NOT NULL, code TEXT NOT NULL UNIQUE, letter TEXT NOT NULL, credit INTEGER NOT NULL);";

    versionQueries << "CREATE TABLE details(id INTEGER PRIMARY KEY, code TEXT NOT NULL UNIQUE, midterm INTEGER, final INTEGER, quiz1 INTEGER, quiz2 INTEGER, quiz3 INTEGER,"
                      "quiz4 INTEGER, quiz5 INTEGER, quiz6 INTEGER, hw1 INTEGER, hw2 INTEGER, hw3 INTEGER, hw4 INTEGER, hw5 INTEGER, FOREIGN KEY(code) REFERENCES courses(code));";
    versionQueries << "UPDATE info SET version = 7;";
    schemaList << versionQueries;
    versionQueries.clear();

}

int getDbVersion(const QSqlDatabase& db)
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
    QSqlQuery q;
    int version;
    bool result;

    db.setDatabaseName("courses.db");

    if (!db.open()) {
        qWarning() << "InitDb: Cannot open database" << db.lastError().text();
    }

    createDatabaseSchema();

    version = getDbVersion(db);

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
