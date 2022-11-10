#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define MILLIONAIRE_TYPE_APPLICATION (millionaire_application_get_type())

G_DECLARE_FINAL_TYPE (MillionaireApplication, millionaire_application, MILLIONAIRE, APPLICATION, AdwApplication)

MillionaireApplication *millionaire_application_new (const char * application_id, GApplicationFlags flags);

G_END_DECLS
