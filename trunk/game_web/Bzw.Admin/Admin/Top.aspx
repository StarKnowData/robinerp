<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Top" Codebehind="Top.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>顶部管理导航菜单</title>
    
<style type='text/css'>
a:link { color:#ffffff;text-decoration:none}
a:hover {color:#ffffff;}
a:visited {color:#f0f0f0;text-decoration:none}
td {FONT-SIZE: 9pt; FILTER: Glow(Color=#0F42A6, Strength=1) dropshadow(Color=#0F42A6, OffX=1, OffY=1,); COLOR: #ffffff; FONT-FAMILY: '宋体'}
img {filter:Alpha(opacity:100); chroma(color=#FFFFFF)}
</style>

    <base target='main'>
    <script language='JavaScript' type='text/JavaScript'>
function preloadImg(src) {
  var img=new Image();
  img.src=src
}
preloadImg('Images/admin_top_open.gif');

var displayBar=true;
function switchBar(obj) {
  if (displayBar) {
    parent.frame.cols='0,*';
    displayBar=false;
    obj.src='Images/admin_top_open.gif';
    obj.title='打开左边管理导航菜单';
  } else {
    parent.frame.cols='180,*';
    displayBar=true;
    obj.src='Images/admin_top_close.gif';
    obj.title='关闭左边管理导航菜单';
  }
}
    </script>

</head>


<body background='Images/admin_top_bg.gif' leftmargin='0' topmargin='0'>
    <table height='100%' width='100%' border='0' cellpadding='0' cellspacing='0'>
  <tr valign='middle'>
    <td width=96>
      &nbsp;<img onclick='switchBar(this)' src='Images/admin_top_close.gif' title='关闭左边管理导航菜单' style='cursor:hand'>
    </td>
    <td width=20>
      <img src='Images/admin_top_icon_1.gif'>
    </td>
    <td width=90>
      <a href="UserAdmin/Edit_AdminUsers.aspx" target=main>修改管理密码</a>    </td>
    <%=(GetSession != "2" ? string.Empty : "<td width=20><img src='Images/admin_top_icon_5.gif'></td><td width=80><a href='UserAdmin/Add_AdminUser.aspx' target='main'>管理员管理</a></td>")%>
    <td width=20>
      <img src='Images/admin_top_icon_5.gif'>
    </td>
    <td width=72>
      <a href="Admin_Logout.aspx" target='_top' onclick='{if(confirm("确定要退出吗?")){return true;}return false;}'>退出管理</a>
    </td>
    <td width=20>
      <img src='Images/admin_top_icon_6.gif'>
    </td>
    <td width=60>
      <a href="SConfig/SystemStat.aspx" target=main>返回首页</a>
    </td>
    <td align='right'>
      <font color='#B5CBF2'>Design By： <a href="" title="深圳市正易龙科技有限公司" onclick="openUrl();">深圳市正易龙科技有限公司</a></font>&nbsp;
    </td>
  </tr>
</table>
</body>
<script>
    function openUrl() {
        window.open("http://www.kfgame.com");
    }
</script>
</html>
