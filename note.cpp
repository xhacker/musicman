#include "note.h"

Note::Note() : _pressed(false)
{}

bool Note::pressed()
{
    return _pressed;
}

void Note::setPressed(bool pressed)
{
    _pressed = pressed;
}
