<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Prizes_PrizesEdit" Codebehind="PrizesEdit.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
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
  if(document.getElementById("Award_Name").value == '') {
    alert('温馨提示：\n\n请输入奖品名称！');
    document.getElementById("Award_Name").focus();
    return false;
  }
}
    </script>
<script src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form1" runat="server" onsubmit='return CheckForm();'>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td colspan="2" class="title_03">
                    <strong>添加奖品资料</strong></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品名称：</td>
                <td width="83%" align="left">
                    <input type="text" name="Award_Name" id="Award_Name" value="<%=Award_Name %>" class="put" maxlength="20" /></td>
            </tr>
            <tr style="display:none;">
                <td height="17%" align="right">
                    奖品分类：</td>
                <td align="left">
                    <select name="leitype">
                        <option value="1" <%=(Award_Name=="1" ? "selected" : "") %>>虚拟类</option>
                        <option value="2" <%=(Award_Name=="2" ? "selected" :  "")%>>实物类</option>
                        <option value="3" <%=(Award_Name=="3" ? "selected" : "") %>>现金类</option>
                    </select>
                </td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品所需<%=UiCommon.StringConfig.GoldName %>数：</td>
                <td width="83%" align="left">
                    <input type="text" name="Award_MoneyCost" id="Award_MoneyCost" value="<%=Award_MoneyCost %>" class="put" maxlength="9" /></td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品所需游戏时长数：</td>
                <td width="83%" align="left">
                    <input type="text" name="Award_OnLineTime" id="Award_OnLineTime" value="<%=Award_OnLineTime %>" class="put" maxlength="5" />小时</td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    奖品数量：</td>
                <td width="83%" align="left">
                    <input type="text" name="Award_Num" id="Award_Num" value="<%=Award_Num %>" class="put" maxlength="7" /></td>
            </tr>
            <tr>
                <td align="right">
                    奖品图片：</td>
                <td align="left">
					<asp:PlaceHolder runat="server" ID="phImageUrl">
						<asp:TextBox runat="server" ID="txtImageUrl" CssClass="put"></asp:TextBox>&nbsp;
						<input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageUrl.Text.Trim() %>',0,0);" />&nbsp;
						<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />
					</asp:PlaceHolder>
					<asp:PlaceHolder runat="server" ID="phFileImage">
						<asp:FileUpload runat="server" ID="fuImage" />(300K以内，允许的类型：jpg,jpeg,gif)
					</asp:PlaceHolder>
                    <%--<input name="picture" type="text" id="picture" value="<%=picture %>" size="50"
                        maxlength="100" class="put" /></td>--%>
            </tr>
            <%--<tr>
                <td align="right">
                    奖品图片：</td>
                <td align="left">
                    <iframe src='../inc/Pupload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>
                </td>
            </tr>--%>
            <tr>
                <td align="right" valign="top">
                    奖品介绍：</td>
                <td align="left" valign="top">
                    <FCKeditorV2:FCKeditor ID="Award_Info" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
            <tr style="display:none;">
                <td width="17%" align="right">
                    是否热换奖品：</td>
                <td width="83%" align="left">
                    <input type="radio" name="Award_hot" value="1" class="put" <%=Award_hot.ToString().ToLower()=="true"  ? "checked" : "" %>/>
                    热换
                    <input name="Award_hot" type="radio" value="0" class="put" <%=Award_hot.ToString().ToLower()=="false"  ? "checked" : "" %>/>
                    非热换</td>
            </tr>
            <tr>
                <td width="17%" align="right">
                    &nbsp;</td>
                <td width="83%" align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 修 改 " class="put" OnClick="Prizes_Edit" />
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
