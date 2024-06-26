#include "Boss.h"
BossObject::BossObject()
{
    x_val = SCREEN_WIDTH;
    y_val = (SCREEN_HEIGHT - BOSS_HEIGHT) / 2;
    lastBulletTime = SDL_GetTicks();
    is_alive = false;

    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
    bullets.push_back(std::vector<Bullet*>());
}
BossObject::~BossObject()
{
    Free();
}
void BossObject::update()
{
    if (x_val <= SCREEN_WIDTH - BOSS_WIDTH)
    {
        y_val += step;

        if (y_val <= 0 || y_val + BOSS_HEIGHT >= SCREEN_HEIGHT)
        {
            step = -step;
        }
    }
    else 
    {
        x_val -= step;
    }
}

void BossObject::destroy_all_bullet()
{
    for (int j = 0; j < MAX_BULLET_BOSS; j++)
    {
        for (int i = 0; i < bullets[j].size(); i++)
        {
            Bullet* bullet = bullets[j].at(i);
            bullet = NULL;
            bullets[j].erase(bullets[j].begin() + i);
        }
    }
}

void BossObject::Init_bullet_(std::vector<Bullet*>& bullets_, int x_val_, int y_val_, int w, int h)
{
    if (bullets_.size() < 5)
    {

        Bullet* bullet = new Bullet();
        bullet->SetWidthHeight(w, h);
        bullet->SetRect(this->x_val + x_val_, this->y_val + y_val_ + BOSS_HEIGHT / 2 - h / 2, w, h);
        bullet->set_is_move(true);

        bullets_.push_back(bullet);


    }
}

void BossObject::check_bullet_out()
{
    for (int j = 0; j < MAX_BULLET_BOSS; j++)
    {
        for (int i = 0; i < bullets[j].size(); i++)
        {
            Bullet* bullet = bullets[j].at(i);
            if (bullet->get_x_val() < 0)
            {
                bullet = NULL;
                bullets[j].erase(bullets[j].begin() + i);
            }
        }
    }
}

void BossObject::Init_bullet()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastBulletTime >= 2000)
    {
        Init_bullet_(bullets[0], 0, 0, BULLET_WIDTH, BULLET_HEIGHT);
        Init_bullet_(bullets[1], 20, 30, ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);
        Init_bullet_(bullets[2], 20, -30, ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);
        Init_bullet_(bullets[3], 40, 60, BULLET_WIDTH, BULLET_HEIGHT);
        Init_bullet_(bullets[4], 40, -60, BULLET_WIDTH, BULLET_HEIGHT);
        Init_bullet_(bullets[5], 60, -90, ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);
        Init_bullet_(bullets[6], 60, 90, ICE_BULLET_WIDTH, ICE_BULLET_HEIGHT);
        lastBulletTime = currentTime;
    }


}

void BossObject::reset_boss()
{
    x_val = SCREEN_WIDTH;
    y_val = (SCREEN_HEIGHT - BOSS_HEIGHT) / 2;
    is_alive = false;
    destroy_all_bullet();
}