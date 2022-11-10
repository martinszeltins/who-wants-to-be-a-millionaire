#include "config.h"
#include <glib/gi18n.h>
#include "include/millionaire-application.h"
 
int main (int argc, char * argv[])
{
    g_autoptr(MillionaireApplication) app = NULL;

    bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    app = millionaire_application_new ("lv.martinsz.millionaire", G_APPLICATION_FLAGS_NONE);
    g_application_run (G_APPLICATION (app), argc, argv);
}
