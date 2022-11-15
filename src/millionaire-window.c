#include "include/millionaire-window.h"

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
};

struct MyParameters {
    GtkWidget * widget;
    MillionaireWindow * window;
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
}

static void millionaire_window_init (MillionaireWindow * self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    g_signal_connect(self->btn_answer_a, "clicked", G_CALLBACK(millionaire_window_gameplay_answer_a), self);

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
    strcpy(self->questions[0].lifeline_audience_answer, "The audience has voted:\nA: 2%\nB: 7%\nC: 38%\nD: 53%");

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
    strcpy(self->questions[1].lifeline_audience_answer, "The audience has voted:\nA: 7%\nB: 3%\nC: 80%\nD: 10%");

    strcpy(self->questions[2].question, "What does the word loquacious mean?");
    strcpy(self->questions[2].answers[0], "Angry");
    strcpy(self->questions[2].answers[1], "Chatty");
    strcpy(self->questions[2].answers[2], "Beautiful");
    strcpy(self->questions[2].answers[3], "Shy");
    strcpy(self->questions[2].correct_answer, "B");
    strcpy(self->questions[2].money_earned_if_answered, "$300,000");
    strcpy(self->questions[2].lifeline_fifty_fifty_hide[0], "C");
    strcpy(self->questions[2].lifeline_fifty_fifty_hide[1], "D");
    strcpy(self->questions[2].lifeline_call_answer, "Hmm, I don't know... But if I had to guess I would say chatty.");
    strcpy(self->questions[2].lifeline_audience_answer, "The audience has voted:\nA: 3%\nB: 87%\nC: 4%\nD: 6%");

    strcpy(self->questions[3].question, "What does the word loquacious mean?");
    strcpy(self->questions[3].answers[0], "Angry");
    strcpy(self->questions[3].answers[1], "Chatty");
    strcpy(self->questions[3].answers[2], "Beautiful");
    strcpy(self->questions[3].answers[3], "Shy");
    strcpy(self->questions[3].correct_answer, "B");
    strcpy(self->questions[3].money_earned_if_answered, "$400,000");
    strcpy(self->questions[3].lifeline_fifty_fifty_hide[0], "C");
    strcpy(self->questions[3].lifeline_fifty_fifty_hide[1], "D");
    strcpy(self->questions[3].lifeline_call_answer, "Hmm, I don't know... But if I had to guess I would say chatty.");
    strcpy(self->questions[3].lifeline_audience_answer, "The audience has voted:\nA: 3%\nB: 87%\nC: 4%\nD: 6%");

    strcpy(self->questions[4].question, "Construction of which of these famous landmarks was completed first?");
    strcpy(self->questions[4].answers[0], "Empire State Building");
    strcpy(self->questions[4].answers[1], "Royal Albert Hall");
    strcpy(self->questions[4].answers[2], "Eiffel Tower");
    strcpy(self->questions[4].answers[3], "Big Ben Clock Tower");
    strcpy(self->questions[4].correct_answer, "D");
    strcpy(self->questions[4].money_earned_if_answered, "$500,000");
    strcpy(self->questions[4].lifeline_fifty_fifty_hide[0], "A");
    strcpy(self->questions[4].lifeline_fifty_fifty_hide[1], "B");
    strcpy(self->questions[4].lifeline_call_answer, "To be honest, I really don't know. My wild guess is the Eiffel Tower.");
    strcpy(self->questions[4].lifeline_audience_answer, "The audience has voted:\nA: 9%\nB: 7%\nC: 24%\nD: 62%");

    strcpy(self->questions[5].question, "What is the Celsius equivalent of 77 degrees Fahrenheit?");
    strcpy(self->questions[5].answers[0], "15");
    strcpy(self->questions[5].answers[1], "20");
    strcpy(self->questions[5].answers[2], "25");
    strcpy(self->questions[5].answers[3], "30");
    strcpy(self->questions[5].correct_answer, "C");
    strcpy(self->questions[5].money_earned_if_answered, "$600,000");
    strcpy(self->questions[5].lifeline_fifty_fifty_hide[0], "D");
    strcpy(self->questions[5].lifeline_fifty_fifty_hide[1], "B");
    strcpy(self->questions[5].lifeline_call_answer, "I think that 100 F is about 30 in celsius. So I will say 15.");
    strcpy(self->questions[5].lifeline_audience_answer, "The audience has voted:\nA: 11%\nB: 21%\nC: 59%\nD: 9%");

    strcpy(self->questions[6].question, "The word \"aristocracy\" literally means power in the hands of whom?");
    strcpy(self->questions[6].answers[0], "The few");
    strcpy(self->questions[6].answers[1], "The best");
    strcpy(self->questions[6].answers[2], "The barons");
    strcpy(self->questions[6].answers[3], "The rich");
    strcpy(self->questions[6].correct_answer, "A");
    strcpy(self->questions[6].money_earned_if_answered, "$700,000");
    strcpy(self->questions[6].lifeline_fifty_fifty_hide[0], "B");
    strcpy(self->questions[6].lifeline_fifty_fifty_hide[1], "C");
    strcpy(self->questions[6].lifeline_call_answer, "I know it's not the best. I think it's the few or the rich.");
    strcpy(self->questions[6].lifeline_audience_answer, "The audience has voted:\nA: 85%\nB: 3%\nC: 27%\nD: 16%");

    strcpy(self->questions[7].question, "A sports team playing in its own arena is said to have what type of advantage?");
    strcpy(self->questions[7].answers[0], "Homecoming");
    strcpy(self->questions[7].answers[1], "Home depot");
    strcpy(self->questions[7].answers[2], "Home court");
    strcpy(self->questions[7].answers[3], "Home sweet home");
    strcpy(self->questions[7].correct_answer, "C");
    strcpy(self->questions[7].money_earned_if_answered, "$800,000");
    strcpy(self->questions[7].lifeline_fifty_fifty_hide[0], "D");
    strcpy(self->questions[7].lifeline_fifty_fifty_hide[1], "A");
    strcpy(self->questions[7].lifeline_call_answer, "I'm pretty sure it's home court.");
    strcpy(self->questions[7].lifeline_audience_answer, "The audience has voted:\nA: 1%\nB: 0%\nC: 99%\nD: 0%");

    strcpy(self->questions[8].question, "In which of these games do players use a paddle to hit the ball?");
    strcpy(self->questions[8].answers[0], "Ping-Pong");
    strcpy(self->questions[8].answers[1], "Water polo");
    strcpy(self->questions[8].answers[2], "Shuffleboard");
    strcpy(self->questions[8].answers[3], "Football");
    strcpy(self->questions[8].correct_answer, "A");
    strcpy(self->questions[8].money_earned_if_answered, "$900,000");
    strcpy(self->questions[8].lifeline_fifty_fifty_hide[0], "B");
    strcpy(self->questions[8].lifeline_fifty_fifty_hide[1], "D");
    strcpy(self->questions[8].lifeline_call_answer, "I don't know what Shuffleboard is but that would be my answer.");
    strcpy(self->questions[8].lifeline_audience_answer, "The audience has voted:\nA: 90%\nB: 2%\nC: 3%\nD: 5%");

    strcpy(self->questions[9].question, "A dermatologist is best suited to treat which of these medical conditions?");
    strcpy(self->questions[9].answers[0], "Headache");
    strcpy(self->questions[9].answers[1], "Cavity");
    strcpy(self->questions[9].answers[2], "Heart murmur");
    strcpy(self->questions[9].answers[3], "Skin rash");
    strcpy(self->questions[9].correct_answer, "D");
    strcpy(self->questions[9].money_earned_if_answered, "$1,000,000");
    strcpy(self->questions[9].lifeline_fifty_fifty_hide[0], "C");
    strcpy(self->questions[9].lifeline_fifty_fifty_hide[1], "A");
    strcpy(self->questions[9].lifeline_call_answer, "It's definitely a heart murmur. Just kidding, I think derma means skin.");
    strcpy(self->questions[9].lifeline_audience_answer, "The audience has voted:\nA: 19%\nB: 28%\nC: 14%\nD: 58%");

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

void millionaire_window_gameplay_answer_a(GtkWidget * widget, gpointer data)
{
    MillionaireWindow * window = MILLIONAIRE_WINDOW(data);

    if (window->game_locked == TRUE) return;

    window->game_locked = TRUE;

    GtkStyleContext * context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, "btn-answer-pulse");

    struct MyParameters * params = malloc(sizeof(struct MyParameters));
    params->widget = widget;
    params->window = window;

    window->timer = g_timeout_add(1000, millionaire_window_gameplay_answer_a_check, params);
}

gboolean millionaire_window_gameplay_answer_a_check(gpointer user_data)
{
    g_print("millionaire_window_gameplay_answer_a_check()");

    struct MyParameters * params = (struct MyParameters *) user_data;

    MillionaireWindow * window = MILLIONAIRE_WINDOW(params->window);

    g_print("gtk_label_set_text()");
    gtk_label_set_text(window->lbl_money, "$1,000,000");

    /* Returning FALSE here will stop the timer */
    return FALSE;
}
