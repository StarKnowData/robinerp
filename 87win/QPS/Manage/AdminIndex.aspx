<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AdminIndex.aspx.cs" Inherits="QPS.Web.Manage.AdminIndex" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >

<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>后台</title>
        <meta name="keywords" content="ASP.net,论坛" />
    <meta name="description" content="Discuz!NT,论坛,asp.net" />
    <link href="styles/dntmanager.css" rel="stylesheet" type="text/css" />
<style>
	body {margin:0;}
</style>
<meta http-equiv="X-UA-Compatible" content="IE=7" />
</head>


<frameset rows="43,*" frameborder="no" border="0" framespacing="0">
  <frame src="framepage/top.aspx" name="topFrame" scrolling="No" noresize="noresize" id="topFrame"  />
  <%if (Request.Params["fromurl"]==null){%>				
			<frame src="framepage/managerbody.aspx"  name="mainFrame" id="mainFrame" onresize="mainFrame.setscreendiv();" scrolling="No" />
  <%}else{%>			
            <frame src="framepage/managerbody.aspx?fromurl=<%=Request.Params["fromurl"]%>"  name="mainFrame" id="mainFrame" onresize="mainFrame.setscreendiv();" scrolling="No" />
  <%}%>
 
</frameset>


<%--<body>
    <form id="form1" runat="server">
    <div>
    后台后台后台后台后台后台后台
    </div>
    </form>
</body>--%>
</html>
