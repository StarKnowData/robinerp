<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.ShowGameHtml"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" >
    <title><%=GameName%>游戏规则</title>
    <link href="/images/rule/css.css" rel="stylesheet" type="text/css">
</head>
<body>
    <form id="form1" runat="server">
        <table width="674" border="0" align="center" cellpadding="0" cellspacing="0">
          <tr>
            <td><img src="/images/rule/top.gif" width="674" height="72"></td>
          </tr>
        </table>
        <table width="674" height="314" border="0" align="center" cellpadding="0" cellspacing="0">
          <tr>
            <td height="314" valign="top" background="/images/rule/bg.gif"><table width="531" border="0" align="center" cellpadding="0" cellspacing="0">
              <tr>
                <td width="107"><img src="/images/rule/title_l.gif" width="107" height="54"></td>
                <td width="424" background="/images/rule/title_r.gif"><span class="title_blue"><%=GameName%>游戏规则</span></td>
              </tr>
            </table>
              <br>
              <table width="506" height="197" border="0" align="center" cellpadding="0" cellspacing="0">
                <tr>
                  <td width="506" valign="top" style=" padding-top:5px;">
		          <%=GameInfo%>
                  </td>
                </tr>
              </table></td>
          </tr>
        </table>
        <table width="674" border="0" align="center" cellpadding="0" cellspacing="0">
          <tr>
            <td><img src="/images/rule/foot.gif" width="674" height="40"></td>
          </tr>
        </table>
    </form>
</body>
</html>