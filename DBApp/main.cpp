#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString servername = "DESKTOP-OUDNVSB\\SQLEXPRESS";
    QString dbname = "test";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setConnectOptions();

    //  QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;Database=%2;UID=sa;PWD=;").arg(servername).arg(dbname);

    QString dsn = QString("DRIVER={SQL Server};SERVER=%1;Database=%2;Trusted_Connections=Yes;").arg(servername).arg(dbname);

    db.setDatabaseName(dsn);

    if (db.open()) {

        qDebug() << "Opened !!";
        QString sQuery = "INSERT INTO [dbo].[People] ([FirstName],[LastName]) VALUES (:first,:last)";
        QSqlQuery qry;
        qry.prepare(sQuery);
        qry.bindValue(":first","Heather");
        qry.bindValue(":last","Cairns");

        if(qry.exec()) {
            qDebug() << "Record Inserted ";
        }

        /*
        QSqlQuery qry;
        if (qry.exec("SELECT * FROM [dbo].[People]")) {
            while (qry.next()) {
                qDebug() << qry.value(1).toString() << qry.value(2).toString();
            }
        }

        else {
            qDebug() << "Error!! "<< db.lastError().text() ;
        }
        */
        qDebug() << "Closing...";
        db.close();

    }

    else {
        qDebug() << "Error!! "<< db.lastError().text() ;
    }

    return a.exec();
}
