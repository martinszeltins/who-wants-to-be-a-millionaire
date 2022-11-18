#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define MILLIONAIRE_TYPE_WINDOW (millionaire_window_get_type())

G_DECLARE_FINAL_TYPE (MillionaireWindow, millionaire_window, MILLIONAIRE, WINDOW, AdwApplicationWindow)

/* Questions and their associated answers, money and lifelines */
struct question {
    gchar question[255];
    gchar answers[4][255];
    gchar correct_answer[1];
    gchar money_earned_if_answered[255];
    gchar lifeline_fifty_fifty_hide[2][1];
    gchar lifeline_call_answer[255];
    gchar lifeline_audience_answer[255];
};

void     millionaire_window_create_and_show (GApplication * app);
void     millionaire_window_gameplay_start (MillionaireWindow * window);
void     millionaire_window_gameplay_answer (GtkWidget * widget, gpointer data);
gboolean millionaire_window_gameplay_answer_check(gpointer user_data);
gboolean millionaire_window_gameplay_answer_correct(gpointer user_data);
gboolean millionaire_window_gameplay_answer_incorrect(gpointer user_data);
void     millionaire_window_gameplay_lifeline_call(GtkWidget * widget, MillionaireWindow * window);
void     millionaire_window_gameplay_lifeline_audience(GtkWidget * widget, MillionaireWindow * window);

G_END_DECLS
