#include <QCoreApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString mPath = "C:/Users/user/Documents/Qt Projects/Dirs/Tests";
    QDir mDir;

if (!mDir.exists(mPath)) {
    mDir.mkpath(mPath);
    qDebug() << "Created";
}
else {

    qDebug() << "Already exists";

}

    return a.exec();
}
