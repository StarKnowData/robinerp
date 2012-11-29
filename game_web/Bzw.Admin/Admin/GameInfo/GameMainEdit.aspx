<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameMainEdit" Codebehind="GameMainEdit.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
        <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
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

  if(document.getElementById("Down_address").value == '') {
    alert('温馨提示：\n\n请输入下载地址！');
    document.getElementById("Down_address").focus();
    return false;
  }
    if(document.getElementById("Game_TypeID").value=='')
  {
    alert('温馨提示：\n\n您还没添加游戏类别！');
    document.getElementById("Game_TypeID").focus();
    return false;
  
  }
  if(document.getElementById("Provice").value == '') {
    alert('温馨提示：\n\n请输入所属省份！');
    document.getElementById("Provice").focus();
    return false;
  }
  
  if(document.getElementById("Provice").value != '全国')
  {
  if(document.getElementById("area").value == '') {
    alert('温馨提示：\n\n请输入所属地区！');
    document.getElementById("area").focus();
    return false;
  }
  }
  
}
    </script>
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form1" runat="server" onsubmit='return CheckForm();'>
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>修改游戏页面</strong></td>
            </tr>
            <tr>
                <td align="right" style="width:100px;">
                    游戏名称</td>
                <td align="left">
                <%=Game_Name %>
                 </td>
            </tr>
            <tr>
                <td align="right">
                    下载地址</td>
                <td align="left">
                    <input name="Down_address" type="text" id="Down_address" class="put" value="<%=Down_address %>" /></td>
            </tr>
            <tr>
                <td align="right">
                    文件大小</td>
                <td align="left">
                    <input name="FileSize" type="text" id="FileSize" class="put" value="<%=FileSize %>" maxlength="7" />
                    (文件大小的单位是KB,但不能写单位)</td>
            </tr>
            <tr>
                <td align="right">
                    所属省份</td>
                <td align="left">
                    <input name="Provice" type="text" id="Provice" class="put"  value="<%=Provice %>"/>(全国性游戏请直接写"全国")</td>
            </tr>
            <tr>
                <td align="right">
                    所属地区</td>
                <td align="left">
                    <input name="area" type="text" id="area" class="put" value="<%=area %>" />(当是全国性游戏时，地区请留空)</td>
            </tr>
            <tr>
                <td align="right">
                    游戏分类</td>
                <td align="left">
                    <asp:DropDownList ID="Game_TypeID" runat="server">
                    </asp:DropDownList>
                    
                </td>
            </tr>
            <tr>
                <td align="right">
                    游戏图片</td>
                <td align="left">
					<asp:PlaceHolder runat="server" ID="phImageUrl">
						<asp:TextBox runat="server" ID="txtImageUrl" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageUrl.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileUpload">
						<asp:FileUpload runat="server" ID="fuImageUrl" />（300K以内，仅允许jpg,jpeg及gif格式）
					</asp:PlaceHolder>
                    <%--<iframe src='../inc/upload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                </td>
            </tr>
            <tr>
                <td align="right">
                    游戏排列号</td>
                <td align="left">
                    <input name="Game_Order" type="text" id="Game_Order" class="put" value="<%=Game_Order %>" maxlength="4"/></td>
            </tr>
            <tr>
                <td align="right">
                    游戏ICO地址</td>
                <td align="left">
                    <input name="Game_Process" type="text" id="Game_Process" class="put" value="<%=Game_Process %>" /></td>
            </tr>
            <tr>
                <td align="right">
                    游戏房间表</td>
                <td align="left">
                    <input name="MatchTable" type="text" id="MatchTable" class="put" value="<%=MatchTable %>"/></td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    游戏介绍</td>
                <td align="left">
                    <FCKeditorV2:FCKeditor ID="Game_Info" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
            <tr>
                <td align="right" valign="top">
                    游戏规则</td>
                <td align="left">
                    <FCKeditorV2:FCKeditor ID="Game_Rule" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
            <tr>
                <td align="right">
                    是否审核</td>
                <td align="left">
                    <input name="Through" type="radio" value="1" <%=Through.ToString().ToLower() =="true" ? "checked" : ""%>  />
                    是
                    <input type="radio" name="Through" value="0" <%=Through.ToString().ToLower() =="false" ? "checked" : ""%> />
                    否</td>
            </tr>
             <tr>
				<td align="right">
					是否是热门游戏</td>
				<td align="left">
					<asp:CheckBox ID="cbIsHot" runat="server"/>
				</td>
			</tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 提 交 " class="put"  OnClick="GameMainEdit" />
                    <input type="reset" name="Submit2" value="返回" class="put" onclick="javascript:history.back();" />
                    <input type="hidden" name="action" value="add" />
                    <input type="hidden" name="action2" value="add" />
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
