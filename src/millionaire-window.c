#include "include/millionaire-window.h"

struct _MillionaireWindow
{
    AdwApplicationWindow parent_instance;
};

G_DEFINE_FINAL_TYPE (MillionaireWindow, millionaire_window, ADW_TYPE_APPLICATION_WINDOW)

static void millionaire_window_class_init (MillionaireWindowClass * klass)
{
    GtkWidgetClass * widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/lv/martinsz/millionaire/millionaire-window.ui");
}

static void millionaire_window_init (MillionaireWindow * self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}

GtkWindow * millionaire_window_create_and_show (GApplication * app)
{
    GtkWindow * window;

    window = gtk_application_get_active_window (GTK_APPLICATION (app));

    if (window == NULL) {
        window = g_object_new (MILLIONAIRE_TYPE_WINDOW, "application", app, NULL);
    }

    gtk_window_set_resizable(window, FALSE);

    gtk_window_present (window);

    return window;
}


