// JScript 文件

document.write("<div id=\"success\" style=\"position:absolute;z-index:300;height:120px;width:284px;left:50%;top:50%;margin-left:-150px;margin-top:-80px;\">");
document.write("	<div id=\"Layer2\" style=\"position:absolute;z-index:300;width:270px;height:90px;background-color: #FFFFFF;border:solid #000000 1px;font-size:14px;\">");
document.write("		<div id=\"Layer4\" style=\"height:26px;background:#f1f1f1;line-height:26px;padding:0px 3px 0px 3px;font-weight:bolder;\">操作提示</div>");
document.write("		<div id=\"Layer5\" style=\"height:64px;line-height:150%;padding:0px 3px 0px 3px;\" align=\"center\"><BR /><table><tr><td valign=top>");
document.write("		<img border=\"0\" src=\"../image/ajax_loading.gif\"  /></td><td valign=middle style=\"font-size: 14px;\" >正在执行当前操作, 请稍等...<BR />");
document.write("		</td></tr></table><BR /></div>");
document.write("	</div>");
document.write("	<div id=\"Layer3\" style=\"position:absolute;width:270px;height:90px;z-index:299;left:4px;top:5px;background-color: #E8E8E8;\"></div>");
document.write("</div>");
document.getElementById('success').style.display = "none"; 


function count()
{ 
    var bar=0; bar=bar+1; 
     if (bar<99) 
        setTimeout(count(),50);
      else {
        document.getElementById('success').style.display = "none";
        HideOverSels('success');
      }
}   

    
function DialogStr(str)
{
     document.getElementById('success').style.display = "block";  
     document.getElementById('Layer5').innerHTML = str ; 
     //count() ; 
    // window.onload = function(){HideOverSels('success')};
}
