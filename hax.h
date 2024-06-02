#ifndef HAX_H_INCLUDED
#define HAX_H_INCLUDED

#include <cstdlib>
#include <string>
#include <cmath>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct Hax
{
    // Generate random float between 0 - range.
    static float RandFloat(float x)
    {
        return static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/x));
    }

    // Generate random float within range.
    static float RandFloatRange(float low, float high)
    {
        return low + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/(high-low)));
    }

    static int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str)
    {
        const char *c = str.c_str();
        return al_get_text_width(f, c);
    }

    static void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text)
    {
        const char *c = text.c_str();
        al_draw_text(font, color, x, y, flags, c);
    }

    static void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text)
    {
        const char *c = text.c_str();
        al_draw_multiline_text(font, color, x, y, max_width, line_height, flags, c);
    }

/// ### Mark Oates' do_multiline_text functions ###
    static bool multiline_text_draw_callback(int line_num, const char* line, int size, void* user_data)
    {
        *((int*)user_data) = line_num;
        return true;
    }

    static int count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text)
    {
        if (text.empty()) return 0;

        int multiline_text_line_number = 0;
        al_do_multiline_text(font, max_width, text.c_str(), multiline_text_draw_callback, &multiline_text_line_number);

        // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
        return multiline_text_line_number + 1;
    }
/// ###############################################

    /*int string_al_show_native_message_box(ALLEGRO_DISPLAY *display, std::string title, std::string heading, std::string text, char const *buttons, int flags);*/

};

#endif // HAX_H_INCLUDED
