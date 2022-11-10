#include "include/millionaire-application.h"
 
int main (int argc, char * argv[])
{
    g_autoptr(MillionaireApplication) app = NULL;

    app = millionaire_application_new ("lv.martinsz.millionaire", G_APPLICATION_FLAGS_NONE);
    g_application_run (G_APPLICATION (app), argc, argv);
}
