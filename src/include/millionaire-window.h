#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define MILLIONAIRE_TYPE_WINDOW (millionaire_window_get_type())

G_DECLARE_FINAL_TYPE (MillionaireWindow, millionaire_window, MILLIONAIRE, WINDOW, AdwApplicationWindow)

GtkWindow * millionaire_window_create_and_show (GApplication * app);

G_END_DECLS
