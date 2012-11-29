<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ApplyRoomEdit.aspx.cs"
    Inherits="Admin_Games_ApplyRoomEdit" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        -- ></style>

     <script src="/Public/Js/jquery.js" ></script>

	<script src="/Public/Js/public.js"></script>
 
	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

    <script src="/Public/Js/admin.js" type="text/javascript"></script>

</head>
<body>
    <form method="POST" id="myform" action="" runat="server"  >
    <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
                <strong>查看\审核租赁房间信息</strong>
            </td>
        </tr>
        <tr>
            <td align="right" style="height: 32px">
                申请用户名：
            </td>
            <td align="left" style="height: 32px">
                <asp:Literal ID="ltlUserName" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                电子邮箱：
            </td>
            <td>
                <asp:Literal ID="ltlEmail" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                QQ：
            </td>
            <td>
                <asp:Literal ID="ltlQQ" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                手机号码：
            </td>
            <td>
                <asp:Literal ID="ltlMobile" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                游戏名：
            </td>
            <td>
                <asp:Literal ID="ltlComName" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                房间名：
            </td>
            <td>
                <asp:Literal ID="ltlRoomName" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                租赁房间日期：
            </td>
            <td>
                
                <asp:TextBox ID="txtOpenRoomDate" runat="server" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td align="right">
                租赁天数：
            </td>
            <td>
                <asp:Literal ID="ltlApplyDays" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                租金：
            </td>
            <td>
                <asp:Literal ID="ltlPayMoney" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                房间密码：
            </td>
            <td>
                <asp:Literal ID="ltlRoomPwd" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                桌子数：
            </td>
            <td>
                <asp:Literal ID="ltlDeskCount" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                人数上限：
            </td>
            <td>
                <asp:Literal ID="ltlMaxPeople" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                房间收费类型：
            </td>
            <td>
                <asp:Literal ID="ltlTax" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                倍数：
            </td>
            <td>
                <asp:Literal ID="ltlBasePoint" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                最少<%=UiCommon.StringConfig.MoneyName %>限制：
            </td>
            <td>
                <asp:Literal ID="ltlLessPoint" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                最高<%=UiCommon.StringConfig.MoneyName %>限制：
            </td>
            <td>
                <asp:Literal ID="ltlMaxPoint" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                房间欢迎信息：
            </td>
            <td>
                <asp:Literal ID="ltlRoomMsg" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                游戏时欢迎信息：
            </td>
            <td>
                <asp:Literal ID="ltlGameMsg" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                备注：
            </td>
            <td>
                <asp:Literal ID="ltlRemark" runat="server"></asp:Literal>
            </td>
        </tr>
        <tr>
            <td align="right">
                状态：
            </td>
            <td>
                <input type="radio" name="status" value="0" class="put" <%= ( Convert.ToString(ViewState["status"]) =="0" ? "checked" : "" )%> />未审核
                <input type="radio" name="status" value="1" class="put" <%= (Convert.ToString(ViewState["status"]) =="1"  ? "checked" : "" )%> />通过
                <input type="radio" name="status" value="2" class="put" <%= (Convert.ToString(ViewState["status"]) =="2" ? "checked" : "" )%> />不通过
                &nbsp&nbsp;注：通过后状态值不能再更改
            </td>
        </tr>
        <tr>
            <td>
            </td>
            <td>
                <asp:Button ID="Button1" runat="server" Text="提 交" class="put" OnClick="Button1_Click" />&nbsp;
                <input type="button" id="btnBack" name="btnBack" class="put" onclick="document.location.href='ApplyRoomList.aspx'"
                    value=" 返 回 " />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
