/* millionaire-application.c
 *
 * Copyright 2022 Martins
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include "millionaire-application.h"
#include "millionaire-window.h"

struct _MillionaireApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_TYPE (MillionaireApplication, millionaire_application, ADW_TYPE_APPLICATION)

MillionaireApplication *
millionaire_application_new (const char        *application_id,
                             GApplicationFlags  flags)
{
  g_return_val_if_fail (application_id != NULL, NULL);

  return g_object_new (MILLIONAIRE_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
millionaire_application_activate (GApplication *app)
{
  GtkWindow *window;

  g_assert (MILLIONAIRE_IS_APPLICATION (app));

  window = gtk_application_get_active_window (GTK_APPLICATION (app));
  if (window == NULL)
    window = g_object_new (MILLIONAIRE_TYPE_WINDOW,
                           "application", app,
                           NULL);

  gtk_window_present (window);
}

static void
millionaire_application_class_init (MillionaireApplicationClass *klass)
{
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  app_class->activate = millionaire_application_activate;
}

static void
millionaire_application_about_action (GSimpleAction *action,
                                      GVariant      *parameter,
                                      gpointer       user_data)
{
  static const char *developers[] = {"Martins", NULL};
  MillionaireApplication *self = user_data;
  GtkWindow *window = NULL;

  g_assert (MILLIONAIRE_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  adw_show_about_window (window,
                         "application-name", "millionaire",
                         "application-icon", "lv.martinsz.millionaire",
                         "developer-name", "Martins",
                         "version", "0.1.0",
                         "developers", developers,
                         "copyright", "© 2022 Martins",
                         NULL);
}

static void
millionaire_application_quit_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer       user_data)
{
  MillionaireApplication *self = user_data;

  g_assert (MILLIONAIRE_IS_APPLICATION (self));

  g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
  { "quit", millionaire_application_quit_action },
  { "about", millionaire_application_about_action },
};

static void
millionaire_application_init (MillionaireApplication *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   app_actions,
                                   G_N_ELEMENTS (app_actions),
                                   self);
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "app.quit",
                                         (const char *[]) { "<primary>q", NULL });
}

