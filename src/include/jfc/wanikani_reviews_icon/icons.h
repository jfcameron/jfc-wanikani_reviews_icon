// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI
#define JFC_WANIKANI

#include <gdk-pixbuf/gdk-pixbuf.h>

namespace jfc
{
    GdkPixbuf *get_init_image();

    GdkPixbuf *get_no_connection_image();

    GdkPixbuf *get_reviews_available_image();
    
    GdkPixbuf *get_reviews_complete_image();
}

#endif

