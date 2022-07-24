#ifndef _CAMPAING_H_
#define _CAMPAIGN_H_

#include <vector>

using namespace std;

class Object;

namespace CAMPAING{

    void Campaing();

    void Draw_Map();
    void Move(Object* o);
    void Act(vector<Object*> Entities);
    void Detect_Collision_X(Object* o, int X);
    void Detect_Collision_Y(Object* o, int Y);
    void Update_World();

}

#endif