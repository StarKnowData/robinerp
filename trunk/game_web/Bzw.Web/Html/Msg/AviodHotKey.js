document.onkeydown = function()
 {
          if(event.keyCode==116) 
          {
              event.keyCode=0;
              event.returnValue = false;
          }
}
document.oncontextmenu = function() 
{
    event.returnValue = false;
}
