#include "include/millionaire-window.h"

struct _MillionaireWindow
{
    AdwApplicationWindow parent_instance;
    GtkLabel *           lbl_money;
    int                  current_question;
    struct question      questions[10];
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
    self->current_question = 0;

    strcpy(self->questions[0].question, "Which of these names is not in the title of a Shakespeare play?");
    strcpy(self->questions[0].answers[0], "Hamlet");
    strcpy(self->questions[0].answers[1], "Romeo");
    strcpy(self->questions[0].answers[2], "Macbeth");
    strcpy(self->questions[0].answers[3], "Darren");
    strcpy(self->questions[0].correct_answer, "D");
    strcpy(self->questions[0].money_earned_if_answered, "$100,000");
    strcpy(self->questions[0].lifeline_fifty_fifty_hide[0], "A");
    strcpy(self->questions[0].lifeline_fifty_fifty_hide[1], "B");
    strcpy(self->questions[0].lifeline_call_answer, "I know that Hamlet and Romeo are but Darren looks like it could be the one that is not.");
    strcpy(self->questions[0].lifeline_audience_answer, "The audience has voted:\nA: 0%\nB:0%\nC:40%\nD:60%");

    strcpy(self->questions[1].question, "What sort of animal is Walt Disney's Dumbo?");
    strcpy(self->questions[1].answers[0], "Deer");
    strcpy(self->questions[1].answers[1], "Rabbit");
    strcpy(self->questions[1].answers[2], "Elephant");
    strcpy(self->questions[1].answers[3], "Donkey");
    strcpy(self->questions[1].correct_answer, "C");
    strcpy(self->questions[1].money_earned_if_answered, "$200,000");
    strcpy(self->questions[1].lifeline_fifty_fifty_hide[0], "A");
    strcpy(self->questions[1].lifeline_fifty_fifty_hide[1], "D");
    strcpy(self->questions[1].lifeline_call_answer, "Dumbo was the Elephant, wasn't it?");
    strcpy(self->questions[1].lifeline_audience_answer, "The audience has voted:\nA: 13%\nB:24%\nC:80%\nD:10%");
}

