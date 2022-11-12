#include "include/millionaire-window.h"
#include "include/millionaire-gameplay.h"

struct _MillionaireWindow
{
    AdwApplicationWindow parent_instance;
    GtkLabel *           lbl_money;
};

GApplication * app_instance;

G_DEFINE_FINAL_TYPE (MillionaireWindow, millionaire_window, ADW_TYPE_APPLICATION_WINDOW)

static void millionaire_window_class_init (MillionaireWindowClass * klass)
{
    GtkWidgetClass * widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/lv/martinsz/millionaire/millionaire-window.ui");
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_money);
}

static void millionaire_window_init (MillionaireWindow * self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    gtk_label_set_text(self->lbl_money, "It works here!!!!!!");
    millionaire_gameplay_start(app_instance, self);
}

void millionaire_window_create_and_show (GApplication * app)
{
    GtkWindow * window;

    app_instance = app;
    window = gtk_application_get_active_window (GTK_APPLICATION (app));

    if (window == NULL) {
        window = g_object_new (MILLIONAIRE_TYPE_WINDOW, "application", app, NULL);
    }

    gtk_window_set_resizable(window, FALSE);
    gtk_window_present (window);
}


