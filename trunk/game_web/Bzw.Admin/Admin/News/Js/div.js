function switchDiv(div_id)
{
  var style_sheet = getStyleObject(div_id);
  if (style_sheet)
  {
    hideAll(div_id);
    changeObjectVisibility(div_id, "visible","static");
  }
  else 
  {
    alert("sorry, this only works in browsers that do Dynamic HTML");
  }
}

function getStyleObject(objectId) {
  if(document.getElementById && document.getElementById(objectId)) {
	return document.getElementById(objectId).style;
   }
   else if (document.all && document.all(objectId)) {  
	return document.all(objectId).style;
   } 
   else if (document.layers && document.layers[objectId]) { 
	return document.layers[objectId];
   } else {
	return false;
   }
}

function changeObjectVisibility(objectId, newVisibility, newPosition) {
    var styleObject = getStyleObject(objectId);
    if (styleObject) {
	styleObject.visibility = newVisibility;
	styleObject.position = newPosition;
	return true;
    } else {
	return false;
    }
}

function hideAll(div_id)
{
   changeObjectVisibility(div_id,"hidden","absolute");
}