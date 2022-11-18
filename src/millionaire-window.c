#include "include/millionaire-window.h"
#include "include/millionaire-questions.h"

struct _MillionaireWindow
{
    AdwApplicationWindow parent_instance;
    guint                timer;
    guint                timer_value;
    int                  current_question;
    struct question      questions[10];
    gboolean             game_locked;
    GtkLabel *           lbl_money;
    GtkButton *          btn_fifty_fifty;
    GtkButton *          btn_call;
    GtkButton *          btn_audience;
    GtkLabel *           lbl_question;
    GtkButton *          btn_answer_a;
    GtkButton *          btn_answer_b;
    GtkButton *          btn_answer_c;
    GtkButton *          btn_answer_d;
    GtkLabel *           lbl_answer_a;
    GtkLabel *           lbl_answer_b;
    GtkLabel *           lbl_answer_c;
    GtkLabel *           lbl_answer_d;
    GtkLabel *           lbl_lifeline_answer;
};

struct ParamBtnAnswer {
    MillionaireWindow * window;
    GtkWidget *         widget;
    gchar               answer[1];
}; 

GApplication * app_instance;

G_DEFINE_FINAL_TYPE (MillionaireWindow, millionaire_window, ADW_TYPE_APPLICATION_WINDOW)

static void millionaire_window_class_init (MillionaireWindowClass * klass)
{
    GtkWidgetClass * widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/lv/martinsz/millionaire/ui/millionaire-window.ui");
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_money);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_fifty_fifty);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_call);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_audience);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_question);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_answer_a);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_answer_b);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_answer_c);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, btn_answer_d);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_answer_a);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_answer_b);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_answer_c);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_answer_d);
    gtk_widget_class_bind_template_child (widget_class, MillionaireWindow, lbl_lifeline_answer);
}

static void millionaire_window_init (MillionaireWindow * self)
{
    gtk_widget_init_template (GTK_WIDGET (self));

    // Answer A clicked
    struct ParamBtnAnswer * param_answer_a = malloc(sizeof(struct ParamBtnAnswer));
    param_answer_a->window = self;
    param_answer_a->widget = GTK_WIDGET(self->btn_answer_a);
    strcpy(param_answer_a->answer, "A");
    g_signal_connect(self->btn_answer_a, "clicked", G_CALLBACK(millionaire_window_gameplay_answer), param_answer_a);

    // Answer B clicked
    struct ParamBtnAnswer * param_answer_b = malloc(sizeof(struct ParamBtnAnswer));
    param_answer_b->window = self;
    param_answer_b->widget = GTK_WIDGET(self->btn_answer_b);
    strcpy(param_answer_b->answer, "B");
    g_signal_connect(self->btn_answer_b, "clicked", G_CALLBACK(millionaire_window_gameplay_answer), param_answer_b);

    // Answer C clicked
    struct ParamBtnAnswer * param_answer_c = malloc(sizeof(struct ParamBtnAnswer));
    param_answer_c->window = self;
    param_answer_c->widget = GTK_WIDGET(self->btn_answer_c);
    strcpy(param_answer_c->answer, "C");
    g_signal_connect(self->btn_answer_c, "clicked", G_CALLBACK(millionaire_window_gameplay_answer), param_answer_c);

    // Answer D clicked
    struct ParamBtnAnswer * param_answer_d = malloc(sizeof(struct ParamBtnAnswer));
    param_answer_d->window = self;
    param_answer_d->widget = GTK_WIDGET(self->btn_answer_d);
    strcpy(param_answer_d->answer, "D");
    g_signal_connect(self->btn_answer_d, "clicked", G_CALLBACK(millionaire_window_gameplay_answer), param_answer_d);

    // Lifeline - Call
    g_signal_connect(self->btn_call, "clicked", G_CALLBACK(millionaire_window_gameplay_lifeline_call), self);

    // Lifeline - Audience
    g_signal_connect(self->btn_audience, "clicked", G_CALLBACK(millionaire_window_gameplay_lifeline_audience), self);

    millionaire_window_gameplay_start(self);
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

void millionaire_window_gameplay_start(MillionaireWindow * self)
{
    self->timer = 0;
    self->current_question = 0;
    self->game_locked = FALSE;

    struct question * questions = millionaire_questions_get();

    for (int i = 0; i < 10; i++) {
        self->questions[i] = questions[i];
    }

    gtk_widget_set_visible(GTK_WIDGET(self->btn_fifty_fifty), TRUE);
    gtk_widget_set_visible(GTK_WIDGET(self->btn_call), TRUE);
    gtk_widget_set_visible(GTK_WIDGET(self->btn_audience), TRUE);

    gtk_label_set_text(self->lbl_money, "$0");

    gtk_label_set_text(self->lbl_question, self->questions[self->current_question].question);
    gtk_label_set_text(self->lbl_answer_a, self->questions[self->current_question].answers[0]);
    gtk_label_set_text(self->lbl_answer_b, self->questions[self->current_question].answers[1]);
    gtk_label_set_text(self->lbl_answer_c, self->questions[self->current_question].answers[2]);
    gtk_label_set_text(self->lbl_answer_d, self->questions[self->current_question].answers[3]);
}

void millionaire_window_gameplay_answer(GtkWidget * widget, gpointer data)
{
    struct ParamBtnAnswer * param_btn_answer = (struct ParamBtnAnswer *) data;

    MillionaireWindow * window = MILLIONAIRE_WINDOW(param_btn_answer->window);

    if (window->game_locked == TRUE) return;

    window->game_locked = TRUE;

    GtkStyleContext * context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, "btn-answer-pulse");

    window->timer = g_timeout_add(1500, millionaire_window_gameplay_answer_check, param_btn_answer);
}

gboolean millionaire_window_gameplay_answer_check(gpointer user_data)
{
    struct ParamBtnAnswer * param_btn_answer = (struct ParamBtnAnswer *) user_data;

    MillionaireWindow * window = MILLIONAIRE_WINDOW(param_btn_answer->window);
    GtkStyleContext *   context = gtk_widget_get_style_context(param_btn_answer->widget);

    // Stop the timer
    g_source_remove(window->timer);
    window->timer = 0;

    gtk_style_context_remove_class(context, "btn-answer-pulse");

    if (param_btn_answer->answer[0] == window->questions[window->current_question].correct_answer[0]) {
            if (param_btn_answer->answer[0] == 'A') {
            gtk_style_context_add_class(context, "btn-answer-a-correct");
        } else if (param_btn_answer->answer[0] == 'B') {
            gtk_style_context_add_class(context, "btn-answer-b-correct");
        } else if (param_btn_answer->answer[0] == 'C') {
            gtk_style_context_add_class(context, "btn-answer-c-correct");
        } else if (param_btn_answer->answer[0] == 'D') {
            g_print("Correct D");
            gtk_style_context_add_class(context, "btn-answer-d-correct");
        }

        window->timer = g_timeout_add(1000, millionaire_window_gameplay_answer_correct, user_data);
    } else {
        if (param_btn_answer->answer[0] == 'A') {
            gtk_style_context_add_class(context, "btn-answer-a-incorrect");
        } else if (param_btn_answer->answer[0] == 'B') {
            gtk_style_context_add_class(context, "btn-answer-b-incorrect");
        } else if (param_btn_answer->answer[0] == 'C') {
            gtk_style_context_add_class(context, "btn-answer-c-incorrect");
        } else if (param_btn_answer->answer[0] == 'D') {
            gtk_style_context_add_class(context, "btn-answer-d-incorrect");
        }

        window->timer = g_timeout_add(1000, millionaire_window_gameplay_answer_incorrect, user_data);
    }

    return TRUE;
}

gboolean millionaire_window_gameplay_answer_correct(gpointer user_data)
{
    struct ParamBtnAnswer * param_btn_answer = (struct ParamBtnAnswer *) user_data;

    MillionaireWindow * window = MILLIONAIRE_WINDOW(param_btn_answer->window);
    GtkStyleContext *   context_btn_answer_a = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_a));
    GtkStyleContext *   context_btn_answer_b = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_b));
    GtkStyleContext *   context_btn_answer_c = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_c));
    GtkStyleContext *   context_btn_answer_d = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_d));

    // Stop the timer
    g_source_remove(window->timer);
    window->timer = 0;

    gtk_label_set_text(window->lbl_money, window->questions[window->current_question].money_earned_if_answered);

    window->current_question++;
    window->game_locked = FALSE;

    gtk_label_set_text(window->lbl_question, window->questions[window->current_question].question);
    gtk_label_set_text(window->lbl_answer_a, window->questions[window->current_question].answers[0]);
    gtk_label_set_text(window->lbl_answer_b, window->questions[window->current_question].answers[1]);
    gtk_label_set_text(window->lbl_answer_c, window->questions[window->current_question].answers[2]);
    gtk_label_set_text(window->lbl_answer_d, window->questions[window->current_question].answers[3]);

    gtk_style_context_remove_class(context_btn_answer_a, "btn-answer-a-correct");
    gtk_style_context_remove_class(context_btn_answer_a, "btn-answer-a-incorrect");
    gtk_style_context_remove_class(context_btn_answer_b, "btn-answer-b-correct");
    gtk_style_context_remove_class(context_btn_answer_b, "btn-answer-b-incorrect");
    gtk_style_context_remove_class(context_btn_answer_c, "btn-answer-c-correct");
    gtk_style_context_remove_class(context_btn_answer_c, "btn-answer-c-incorrect");
    gtk_style_context_remove_class(context_btn_answer_d, "btn-answer-d-correct");
    gtk_style_context_remove_class(context_btn_answer_d, "btn-answer-d-incorrect");

    gtk_widget_set_visible(GTK_WIDGET(window->lbl_lifeline_answer), FALSE);

    return TRUE;
}

gboolean millionaire_window_gameplay_answer_incorrect(gpointer user_data)
{
    struct ParamBtnAnswer * param_btn_answer = (struct ParamBtnAnswer *) user_data;

    MillionaireWindow * window = MILLIONAIRE_WINDOW(param_btn_answer->window);
    GtkStyleContext *   context_btn_answer_a = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_a));
    GtkStyleContext *   context_btn_answer_b = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_b));
    GtkStyleContext *   context_btn_answer_c = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_c));
    GtkStyleContext *   context_btn_answer_d = gtk_widget_get_style_context(GTK_WIDGET(window->btn_answer_d));

    // Stop the timer
    g_source_remove(window->timer);
    window->timer = 0;

    window->current_question = 0;
    window->game_locked = FALSE;

    gtk_label_set_text(window->lbl_money, "$0");
    gtk_label_set_text(window->lbl_question, window->questions[window->current_question].question);
    gtk_label_set_text(window->lbl_answer_a, window->questions[window->current_question].answers[0]);
    gtk_label_set_text(window->lbl_answer_b, window->questions[window->current_question].answers[1]);
    gtk_label_set_text(window->lbl_answer_c, window->questions[window->current_question].answers[2]);
    gtk_label_set_text(window->lbl_answer_d, window->questions[window->current_question].answers[3]);

    gtk_style_context_remove_class(context_btn_answer_a, "btn-answer-a-correct");
    gtk_style_context_remove_class(context_btn_answer_a, "btn-answer-a-incorrect");
    gtk_style_context_remove_class(context_btn_answer_b, "btn-answer-b-correct");
    gtk_style_context_remove_class(context_btn_answer_b, "btn-answer-b-incorrect");
    gtk_style_context_remove_class(context_btn_answer_c, "btn-answer-c-correct");
    gtk_style_context_remove_class(context_btn_answer_c, "btn-answer-c-incorrect");
    gtk_style_context_remove_class(context_btn_answer_d, "btn-answer-d-correct");
    gtk_style_context_remove_class(context_btn_answer_d, "btn-answer-d-incorrect");

    gtk_widget_set_visible(GTK_WIDGET(window->lbl_lifeline_answer), FALSE);

    gtk_widget_set_visible(GTK_WIDGET(window->btn_call), TRUE);
    gtk_widget_set_visible(GTK_WIDGET(window->btn_fifty_fifty), TRUE);
    gtk_widget_set_visible(GTK_WIDGET(window->btn_audience), TRUE);

    return TRUE;
}

void millionaire_window_gameplay_lifeline_call(GtkWidget * widget, MillionaireWindow * window)
{
    gtk_label_set_text(window->lbl_lifeline_answer, window->questions[window->current_question].lifeline_call_answer);

    gtk_widget_set_visible(widget, FALSE);
    gtk_widget_set_visible(GTK_WIDGET(window->lbl_lifeline_answer), TRUE);
}

void millionaire_window_gameplay_lifeline_audience(GtkWidget * widget, MillionaireWindow * window)
{
    gtk_label_set_text(window->lbl_lifeline_answer, window->questions[window->current_question].lifeline_audience_answer);

    gtk_widget_set_visible(widget, FALSE);
    gtk_widget_set_visible(GTK_WIDGET(window->lbl_lifeline_answer), TRUE);
}
