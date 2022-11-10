#include "config.h"
#include "millionaire-window.h"

struct _MillionaireWindow
{
    AdwApplicationWindow  parent_instance;
    GtkHeaderBar *        header_bar;
    GtkLabel *            label;
};

G_DEFINE_FINAL_TYPE (MillionaireWindow, millionaire_window, ADW_TYPE_APPLICATION_WINDOW)

static void millionaire_window_class_init (MillionaireWindowClass * klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/lv/martinsz/millionaire/millionaire-window.ui");
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, header_bar);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, label);
}

static void millionaire_window_init (MillionaireWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}
