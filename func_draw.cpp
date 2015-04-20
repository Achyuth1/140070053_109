

/// brick variable
class Brick
{
  public:
  float x;
  float y;
  float length;
  float height;
};

///func to draw bricks


void draw( Brick b)
{
  glColor4ub(255,50,255,255);
    glBegin(GL_QUADS);
    glVertex2f(b.x,b.y);
    glVertex2f(b.x+b.length , b.y);
    glVertex2f(b.x+b.length , b.y +b.height );
    glVertex2f(b.x , b.y + b.height );
    glEnd();    
    return ;
}