bool cs (int j, int i)
{
  if( (j== 4) || ( j== 3 && (i==0|| i==1 || i== 3 || i==4))||(i==1 &&(j==6 || j==7))||(i==3&&(j==5 || j==6)))
  {
    return true;
  } 
  if((j==1 && (i==1 || i==2 || i==3))||(j==2&&(i==1|| i==2 || i==3)))
  {
    return true;
  }
  else return false;
}