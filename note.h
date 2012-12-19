#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
    Note();
    int key;
    int start;
    int end;
    bool pressed();
    void setPressed(bool);
private:
    bool _pressed;
};

#endif // NOTE_H
