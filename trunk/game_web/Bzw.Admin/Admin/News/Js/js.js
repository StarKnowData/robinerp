//防止错误出现
function killErrors() {
return true;}
window.onerror = killErrors;
//选定代码
function CheckAll(form){
  for (var i=0;i<form.elements.length;i++)
    {
    var e = form.elements[i];
    if (e.Name != "chkAll"&&e.disabled==false)
       e.checked = form.chkAll.checked;
    }
  }
function unselectall(){
    if(document.form.chkAll.checked){
	document.form.chkAll.checked=document.form.chkAll.checked;
    } 	
}
function downdel()
{
if(document.form.Action.value=="Del")
{
document.form.action="del.asp";
if(confirm("确定要删除选中的记录吗？"))
return true;
else
return false;
}
}
function display(ID)
{
	if (document.getElementById(ID).style.display == "none") {
		document.getElementById(ID).style.display = "";
	}else{
		document.getElementById(ID).style.display = "none";
	}
}
//分页代码
function showPageLink(sUrl,iPage,iCount){
	var i;
	i=Math.max(1,iPage-1);
	document.write("<a href=\"" + sUrl + "1\" title='第 1 页'><FONT face=Webdings>9</FONT></a> ");
	document.write("<a href=\"" + sUrl + i + "\" title='上一页(第 " + i + " 页)'><FONT face=Webdings>7</FONT></a> ");
	for(i=Math.max(1,iPage-5);i<iPage;i++){
		document.write("<a href=\""+sUrl + i + "\" title='第 " + i + " 页'><b>" + i + "</b></a> ");
	}
	document.write("<font color='#ff3333'><b>" + iPage + "</b></font> ");
	for(i=iPage+1;i<=Math.min(iCount,iPage+5);i++){
		document.write("<a href=\""+sUrl + i + "\" title='第 " + i + " 页'><b>" + i + "</b></a> ");
	}
	i=Math.min(iCount,iPage+1);
	if(iCount>iPage+5) document.write("<span style='font-size:8px'>···</span> ");
	document.write("<a href=\"" + sUrl + i + "\" title='下一页(第 " + i + " 页)'><FONT face=Webdings>8</FONT></a> ");
	document.write("<a href=\"" + sUrl + iCount + "\" title='最后一页(第 " + iCount + " 页)'><FONT face=Webdings>:</FONT></a> ");
}