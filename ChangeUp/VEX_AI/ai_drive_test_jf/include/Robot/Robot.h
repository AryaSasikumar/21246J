
#define PI 3.14159265

typedef struct{
  float x;  
  float y;
}Point;

typedef struct{
  Point point;
  float heading;  
}Place;

typedef struct{
  float distance;
  float heading;  
}Move_Vector;

class Robot{
  private:
    Place place;
  public:
    Robot();

    Place get_place();
    void refresh_place();

    int go_to_place(float x_new, float y_new, float heading_new);
    Move_Vector calc_move_vector(Place place_new);
};

