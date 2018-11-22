#include <QCoreApplication>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>

FILE *output = NULL;

#if (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
/* Qt4版本写法 */
void outputRedirection(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(output, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(output, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(output, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(output, "Fatal: %s\n", msg);
        abort();
    }
}
#else
/* Qt5版本写法 */
void outputRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(output, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(output, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(output, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(output, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(output, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
#endif

int main(int argc, char **argv)
{
#if (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
    output = fopen("output.txt", "a"); //重定向于文件
    qInstallMsgHandler(outputRedirection);
#else
//    output = stdout; // 重定向于打印输出
    output = stderr; // 重定向与错误输出
    qInstallMessageHandler(outputRedirection);
#endif

    QCoreApplication app(argc, argv);
    qDebug()<<"Test Test Test";

    if (output)
        fclose(output);
    return app.exec();
}
