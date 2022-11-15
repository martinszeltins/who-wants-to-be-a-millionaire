#include "include/millionaire-window.h"
#include "include/millionaire-application.h"

struct _MillionaireApplication
{
    AdwApplication parent_instance;
};

G_DEFINE_TYPE (MillionaireApplication, millionaire_application, ADW_TYPE_APPLICATION)

MillionaireApplication * millionaire_application_new (const char * application_id, GApplicationFlags flags)
{
    return g_object_new (MILLIONAIRE_TYPE_APPLICATION, "application-id", application_id, "flags", flags, NULL);
}

static void millionaire_application_activate (GApplication * app)
{
    millionaire_application_force_dark_scheme();
    millionaire_application_add_css_stylesheet();
    millionaire_window_create_and_show(app);
}

static void millionaire_application_class_init (MillionaireApplicationClass * klass)
{
    GApplicationClass * app_class = G_APPLICATION_CLASS (klass);

    app_class->activate = millionaire_application_activate;
}

static void millionaire_application_quit_action (GSimpleAction * action, GVariant * parameter, gpointer user_data)
{
    MillionaireApplication * self = user_data;

    g_application_quit (G_APPLICATION (self));
}

static void millionaire_application_init (MillionaireApplication * self)
{
    static const GActionEntry app_actions[] = {
        { "quit", millionaire_application_quit_action },
    };

    g_action_map_add_action_entries (G_ACTION_MAP (self), app_actions, G_N_ELEMENTS (app_actions), self);
    gtk_application_set_accels_for_action (GTK_APPLICATION (self), "app.quit", (const char *[]) { "<primary>q", NULL });
}

void millionaire_application_add_css_stylesheet ()
{
    GtkCssProvider * css_provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_resource (css_provider, "/lv/martinsz/millionaire/style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void millionaire_application_force_dark_scheme ()
{
    AdwStyleManager * style_manager = adw_style_manager_get_default ();
    adw_style_manager_set_color_scheme (style_manager, ADW_COLOR_SCHEME_FORCE_DARK);
}
