#include <TXLib.h>
#include <windows.h>
#include <math.h>

void draw_box(int x1, int y1, int x2, int y2);
void draw_ball(int x, int y, int r, COLORREF color);
struct ball math(struct box a, struct ball b);
bool collision(struct ball a, struct ball b);

struct box
{
    int x1, y1, x2, y2;
};

struct ball
{
    int x, y, r, vx, vy;
    COLORREF color;
};

int main()
{
    box a = {200, 30, 1000, 770};

    ball fb, sb, tb;
    fb = {100, 200, 60, 20, 5, TX_LIGHTMAGENTA};
    sb = {400, 300, 40, -8, 10, TX_ORANGE};
    tb = {700, 500, 30, 7, 15, TX_BLUE};

    txCreateWindow(1200, 800);
    int k;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSleep(30);
        txSetFillColor(TX_WHITE);
        txClear();

        draw_box(a.x1, a.y1, a.x2, a.y2);

        if(collision(fb, sb) == TRUE)
        {
            k = fb.vx;
            fb.vx = sb.vx;
            sb.vx = k;

            k = fb.vy;
            fb.vy = sb.vy;
            sb.vy = k;
        }
        if(collision(sb, tb) == TRUE)
        {
            k = sb.vx;
            sb.vx = tb.vx;
            tb.vx = k;

            k = sb.vy;
            sb.vy = tb.vy;
            tb.vy = k;
        }
        if(collision(fb, tb) == TRUE)
        {
            k = fb.vx;
            fb.vx = tb.vx;
            tb.vx = k;

            k = fb.vy;
            fb.vy = tb.vy;
            tb.vy = k;
        }
        fb = math(a, fb);
        sb = math(a, sb);
        tb = math(a, tb);

        draw_ball(fb.x, fb.y, fb.r , fb.color);
        draw_ball(sb.x, sb.y, sb.r , sb.color);
        draw_ball(tb.x, tb.y, tb.r , tb.color);
    }

    return 0;
}

void draw_ball(int x, int y, int r, COLORREF color)
{
    txSetFillColor(color);
    txCircle(x, y, r);
}

void draw_box(int x1, int y1, int x2, int y2)
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    txRectangle(x1, y1, x2, y2);
    txSetColor(TX_WHITE);
}

struct ball math(struct box a, struct ball b)
{
    int d;

    b.x += b.vx;
    b.y += b.vy;

    if(b.x > a.x2 - b.r)
    {
        d = b.x + b.r - a.x2;
        b.x -= d;
        b.vx = -b.vx;
    }
    else
    {
        if(b.x < b.r + a.x1)
        {
            d = a.x1 - (b.x - b.r);
            b.x += d;
            b.vx = -b.vx;
        }
    }

    if(b.y > a.y2 - b.r)
    {
        d = b.y + b.r - a.y2;
        b.y -= d;
        b.vy = -b.vy;
    }
    else
    {
        if(b.y < a.y1 + b.r)
        {
            d = a.y1 - (b.y - b.r);
            b.y += d;
            b.vy = -b.vy;
        }
    }
    return b;
}

bool collision(struct ball a, struct ball b)
{
    double r = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    if(r < a.r + b.r)
        return TRUE;
    else
        return FALSE;
}
