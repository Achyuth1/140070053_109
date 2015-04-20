 // checks collision with brick at every boundary
 
bool validCollision (  int x , int y , int a , int b , int velocity){

  if ((x > a || x ==a) && (x < a + 70 || x == a + 70) && (y == b + 35 || y < b +35 && y > b + 33))
  {
    return true;
  }

  if((x+20>a || x==a) && (x+20<a+70 || x==a+70) && (y+20==b+35 || y+20<b+35 && y+20 > b+33))
  {
    return true;
  }

  if(y+20>b && y+20<b+35 && (x+20==a+70 || x+20== a||(x+20>a && x+20 < a+70)))
  {
    return true;
  }

  if (y > b && y < b + 35 && (x == a + 70 || x == a || (x > a && x < a+70) ) )
  {
    return true;
  }
 
  if (y > b && y < b + 35 && (x+20 == a + 70 || x+20 == a || (x+20 > a && x+20 < a+70) ) )
  {
    return true;
  }
 
  else return false;
}