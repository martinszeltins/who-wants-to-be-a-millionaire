#include "include/millionaire-questions.h"

struct question * millionaire_questions_get()
{
    struct question * questions = malloc(10 * sizeof(struct question));

    strcpy(questions[0].question, "Which of these names is not in the title of a Shakespeare play?");
    strcpy(questions[0].answers[0], "Hamlet");
    strcpy(questions[0].answers[1], "Romeo");
    strcpy(questions[0].answers[2], "Macbeth");
    strcpy(questions[0].answers[3], "Darren");
    strcpy(questions[0].correct_answer, "D");
    strcpy(questions[0].money_earned_if_answered, "$100,000");
    strcpy(questions[0].lifeline_fifty_fifty_hide[0], "A");
    strcpy(questions[0].lifeline_fifty_fifty_hide[1], "B");
    strcpy(questions[0].lifeline_call_answer, "I know that Hamlet and Romeo\n are but Darren looks like\n it could be the one that is not.");
    strcpy(questions[0].lifeline_audience_answer, "The audience has voted:\nA: 2%\nB: 7%\nC: 38%\nD: 53%");

    strcpy(questions[1].question, "What sort of animal is Walt Disney's Dumbo?");
    strcpy(questions[1].answers[0], "Deer");
    strcpy(questions[1].answers[1], "Rabbit");
    strcpy(questions[1].answers[2], "Elephant");
    strcpy(questions[1].answers[3], "Donkey");
    strcpy(questions[1].correct_answer, "C");
    strcpy(questions[1].money_earned_if_answered, "$200,000");
    strcpy(questions[1].lifeline_fifty_fifty_hide[0], "A");
    strcpy(questions[1].lifeline_fifty_fifty_hide[1], "D");
    strcpy(questions[1].lifeline_call_answer, "Dumbo was the Elephant,\n wasn't it?");
    strcpy(questions[1].lifeline_audience_answer, "The audience has voted:\nA: 7%\nB: 3%\nC: 80%\nD: 10%");

    strcpy(questions[2].question, "What does the word loquacious mean?");
    strcpy(questions[2].answers[0], "Angry");
    strcpy(questions[2].answers[1], "Chatty");
    strcpy(questions[2].answers[2], "Beautiful");
    strcpy(questions[2].answers[3], "Shy");
    strcpy(questions[2].correct_answer, "B");
    strcpy(questions[2].money_earned_if_answered, "$300,000");
    strcpy(questions[2].lifeline_fifty_fifty_hide[0], "C");
    strcpy(questions[2].lifeline_fifty_fifty_hide[1], "D");
    strcpy(questions[2].lifeline_call_answer, "Hmm, I don't know... But\n if I had to guess I would\n say chatty.");
    strcpy(questions[2].lifeline_audience_answer, "The audience has voted:\nA: 3%\nB: 87%\nC: 4%\nD: 6%");

    strcpy(questions[3].question, "The Ancient Incan Ruins Of Machu Picchu Are In Which Country?");
    strcpy(questions[3].answers[0], "Peru");
    strcpy(questions[3].answers[1], "Argentina");
    strcpy(questions[3].answers[2], "Chile");
    strcpy(questions[3].answers[3], "Mexico");
    strcpy(questions[3].correct_answer, "A");
    strcpy(questions[3].money_earned_if_answered, "$400,000");
    strcpy(questions[3].lifeline_fifty_fifty_hide[0], "C");
    strcpy(questions[3].lifeline_fifty_fifty_hide[1], "D");
    strcpy(questions[3].lifeline_call_answer, "I saw this on Discovery channel\n - it's in Peru.");
    strcpy(questions[3].lifeline_audience_answer, "The audience has voted:\nA: 51%\nB: 30%\nC: 13%\nD: 21%");

    strcpy(questions[4].question, "Construction of which of these famous landmarks was completed first?");
    strcpy(questions[4].answers[0], "Empire State Building");
    strcpy(questions[4].answers[1], "Royal Albert Hall");
    strcpy(questions[4].answers[2], "Eiffel Tower");
    strcpy(questions[4].answers[3], "Big Ben Clock Tower");
    strcpy(questions[4].correct_answer, "D");
    strcpy(questions[4].money_earned_if_answered, "$500,000");
    strcpy(questions[4].lifeline_fifty_fifty_hide[0], "A");
    strcpy(questions[4].lifeline_fifty_fifty_hide[1], "B");
    strcpy(questions[4].lifeline_call_answer, "To be honest, I really don't know.\n My wild guess is the Eiffel Tower.");
    strcpy(questions[4].lifeline_audience_answer, "The audience has voted:\nA: 9%\nB: 7%\nC: 24%\nD: 62%");

    strcpy(questions[5].question, "What is the Celsius equivalent of 77 degrees Fahrenheit?");
    strcpy(questions[5].answers[0], "15");
    strcpy(questions[5].answers[1], "20");
    strcpy(questions[5].answers[2], "25");
    strcpy(questions[5].answers[3], "30");
    strcpy(questions[5].correct_answer, "C");
    strcpy(questions[5].money_earned_if_answered, "$600,000");
    strcpy(questions[5].lifeline_fifty_fifty_hide[0], "D");
    strcpy(questions[5].lifeline_fifty_fifty_hide[1], "B");
    strcpy(questions[5].lifeline_call_answer, "I think that 100 F is about 30 in\n celsius. So I will say 15.");
    strcpy(questions[5].lifeline_audience_answer, "The audience has voted:\nA: 11%\nB: 21%\nC: 59%\nD: 9%");

    strcpy(questions[6].question, "The word \"aristocracy\" literally means power in the hands of whom?");
    strcpy(questions[6].answers[0], "The few");
    strcpy(questions[6].answers[1], "The best");
    strcpy(questions[6].answers[2], "The barons");
    strcpy(questions[6].answers[3], "The rich");
    strcpy(questions[6].correct_answer, "A");
    strcpy(questions[6].money_earned_if_answered, "$700,000");
    strcpy(questions[6].lifeline_fifty_fifty_hide[0], "B");
    strcpy(questions[6].lifeline_fifty_fifty_hide[1], "C");
    strcpy(questions[6].lifeline_call_answer, "I know it's not the best. I think\n it's the few or the rich.");
    strcpy(questions[6].lifeline_audience_answer, "The audience has voted:\nA: 85%\nB: 3%\nC: 27%\nD: 16%");

    strcpy(questions[7].question, "A sports team playing in its own arena is said to have what type of advantage?");
    strcpy(questions[7].answers[0], "Homecoming");
    strcpy(questions[7].answers[1], "Home depot");
    strcpy(questions[7].answers[2], "Home court");
    strcpy(questions[7].answers[3], "Home sweet home");
    strcpy(questions[7].correct_answer, "C");
    strcpy(questions[7].money_earned_if_answered, "$800,000");
    strcpy(questions[7].lifeline_fifty_fifty_hide[0], "D");
    strcpy(questions[7].lifeline_fifty_fifty_hide[1], "A");
    strcpy(questions[7].lifeline_call_answer, "I'm pretty sure it's home court.");
    strcpy(questions[7].lifeline_audience_answer, "The audience has voted:\nA: 1%\nB: 0%\nC: 99%\nD: 0%");

    strcpy(questions[8].question, "In which of these games do players use a paddle to hit the ball?");
    strcpy(questions[8].answers[0], "Ping-Pong");
    strcpy(questions[8].answers[1], "Water polo");
    strcpy(questions[8].answers[2], "Shuffleboard");
    strcpy(questions[8].answers[3], "Football");
    strcpy(questions[8].correct_answer, "A");
    strcpy(questions[8].money_earned_if_answered, "$900,000");
    strcpy(questions[8].lifeline_fifty_fifty_hide[0], "B");
    strcpy(questions[8].lifeline_fifty_fifty_hide[1], "D");
    strcpy(questions[8].lifeline_call_answer, "I don't know what Shuffleboard\n is but that would be my answer.");
    strcpy(questions[8].lifeline_audience_answer, "The audience has voted:\nA: 90%\nB: 2%\nC: 3%\nD: 5%");

    strcpy(questions[9].question, "A dermatologist is best suited to treat which of these medical conditions?");
    strcpy(questions[9].answers[0], "Headache");
    strcpy(questions[9].answers[1], "Cavity");
    strcpy(questions[9].answers[2], "Heart murmur");
    strcpy(questions[9].answers[3], "Skin rash");
    strcpy(questions[9].correct_answer, "D");
    strcpy(questions[9].money_earned_if_answered, "$1,000,000");
    strcpy(questions[9].lifeline_fifty_fifty_hide[0], "C");
    strcpy(questions[9].lifeline_fifty_fifty_hide[1], "A");
    strcpy(questions[9].lifeline_call_answer, "It's definitely a heart murmur.\n Just kidding, I think derma\n means skin.");
    strcpy(questions[9].lifeline_audience_answer, "The audience has voted:\nA: 19%\nB: 28%\nC: 14%\nD: 58%");

    return questions;
}
