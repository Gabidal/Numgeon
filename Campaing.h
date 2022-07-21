#ifndef _CAMPAING_H_
#define _CAMPAIGN_H_

class Object;

namespace CAMPAING{

    void Campaing();

    void Draw_Map();
    void Move(Object* o);
    void Act(Object* o);
    void Detect_Collision_X(Object* o, int X);
    void Detect_Collision_Y(Object* o, int Y);
    void Update_World();

}

#endif