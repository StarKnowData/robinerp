<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameTypesAdd" Codebehind="GameTypesAdd.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" language="javascript" src="/Public/Js/jquery.js"></script>
    <style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>

    <script language="javascript" type="text/javascript">

function CheckForm() {
  if(document.getElementById("KindName").value == '') {
    alert('温馨提示：\n\n请输入游戏类别名称！');
    document.getElementById("KindName").focus();
    return false;
  }
  if(document.getElementById("IDSort").value == '') {
    alert('温馨提示：\n\n请输入游戏排列号！');
    document.getElementById("IDSort").focus();
    return false;
  }
}
    </script>

</head>
<body>
    <form id="form1" runat="server" onsubmit='return CheckForm();'>
        <div>
            <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
                bgcolor="F2F8FF" class="admin_table">
                <tr>
                    <td class="title_03" colspan="2">
                        <strong>添加游戏类别</strong></td>
                </tr>
                <tr>
                    <td align="right">
                        类别名称：</td>
                    <td align="left">
                        <input type="text" id="KindName" name="KindName" class="put" value='' /></td>
                </tr>
                <tr>
                    <td align="right">
                        排列号：</td>
                    <td align="left">
                        <input type="text" id="IDSort" name="IDSort" value="0" class="put" maxlength="4"/></td>
                </tr>
                <tr>
                    <td align="right">
                        是否激活：</td>
                    <td align="left">
                        <input name="Enable" type="radio" value="1" checked="checked" class="put"/>激活
                        <input name="Enable" type="radio" value="0" class="put"/>未激活
                    </td>
                </tr>
                <tr >
                 <td align="right">
                        是否添加：</td>
                    <td align="left">
                     <input type="button" id="btnAddChildRoom"  value="添加二级游戏目录"  onclick="ShowChild()"/>
                    </td>
                </tr>
                <tr  style="display:none">
                    <td class="title_03" colspan="2">
                        <strong>添加二级游戏目录</strong></td>
                </tr>
                <tr style="display:none">
                    <td align="right">
                        类别名称：</td>
                    <td align="left">
                        <input type="text" id="KindName2" name="KindName2" class="put" value='' /></td>
                </tr>
                <tr style="display:none">
                    <td align="right">
                        排列号：</td>
                    <td align="left">
                        <input type="text" id="IDSort2" name="IDSort2" value="0" class="put" maxlength="4"/></td>
                </tr>
                <tr style="display:none">
                    <td align="right">
                        是否激活：</td>
                    <td align="left">
                        <input name="Enable2" type="radio" value="1" checked="checked" class="put"/>激活
                        <input name="Enable2" type="radio" value="0" class="put"/>未激活
                    </td>
                </tr>
                <tr>
                    <td align="right">
                        <input type="hidden" name="action" value="add" />
                        <input type="hidden" name="action2" value="add" />
                    </td>
                    <td align="left">
                        <asp:Button ID="Button1" runat="server" Text=" 提 交 "  class="put" OnClick="GameTypeAdd"/>
                        <input name="reback" type="button" value="返回上一页" class="put" onclick="javascript:history.back();" />
                    </td>
                </tr>
            </table>
        </div>
    </form>
      
    <script type="text/javascript">
        function ShowChild() {
            $("tr").css("display", "");
        }
    </script>
    
</body>
</html>
