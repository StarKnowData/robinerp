<%@ Page Language="C#"  validateRequest="false"  AutoEventWireup="true" CodeBehind="ClearList.aspx.cs" Inherits="Admin_SConfig_ClearList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>清理表数据</title>
     <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
      <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/DatePicker/WdatePicker.js"></script>
</head>
<body>
    <form id="form1" runat="server" >
      <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>清理表数据</strong>  </td>
            </tr>
            
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
	        <tr>
	            <td style=" color:red; font-size:13px; ">
	                请谨慎使用此功能：
	                <br />1、建议您在清理数据之前先对数据库进行备份，对于参与玩家金币计算的数据，如游戏记录、玩家充值等等数据，要确认
	                数据是已经参与了计算，并且是处理完毕的
	                <br />2、建议您清理数据在两万笔以上的表，但是最好保留近一个月或15天前的数据
	                <br />3、如果清理某个表数据时，该页面提示“无法显示”或报错，请把“清理的截止时间”与“记录的最小时间”之间的时间段缩短，或者直接到网站服务器上登录网站后台，打开该网页进行操作
					<script type="text/javascript">
					    function ClearData(typeid, typename, txttm, tabname) {
					        var txttmObj = document.getElementById(txttm);
					        if (txttmObj.value.trim().length == 0) {
					            alert('清理前请先选择截止时间！');
					            txttmObj.focus();
					            return false;
					        }

					        if (confirm('确定要清理【' + typename + '】吗？\n执行清理后将不能恢复数据!!')) {
					            window.location.href = 'ClearList.aspx?action=clear&typeid=' + typeid + '&tm=' + txttmObj.value.trim() + '&tabname=' + tabname + '&typename=' + escape(typename);
					        }

					        return false;
					    }
					</script>
                    
	            </td>
	        </tr>
	        <tr>
	            <td align="center" style=" color:Blue; font-size:13px; ">
                    <asp:Literal ID="ltMsg" runat="server"></asp:Literal></td>
	        </tr>
		</table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
           <tr align="center">
                <th>
                    编号</th>
                <th>
                    表数据分类</th>
                <th>
                    总记录数</th>
                <th>
                    记录的最小时间</th>
                <th>
                    记录的最大时间</th>
                <th>
                    清理的截止时间</th>
                <th>
                    操作</th>
            </tr>
            <asp:Repeater ID="rpList" runat="server">
                <ItemTemplate>
                    <%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
                        <td><%# Eval("TypeID")%></td>
                        <td><%# Eval("TypeName")%></td>
                        <td><%# Eval("CountTotal")%></td>
                        <td><%# Eval("StartTime")%>&nbsp;</td>
                        <td><%# Eval("EndTime")%>&nbsp;</td>
                        <td><input type="text" readonly="readonly" class="put" id="txtTM<%#Eval("TypeID")%>" name="txtTM<%#Eval("TypeID")%>" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd'});" size="8" /></td>
                        <td><input type="button" value=" 点击清理 " class="put" onclick="return  ClearData('<%# Eval("TypeID")%>','<%# Eval("TypeName")%>','txtTM<%#Eval("TypeID")%>','<%# Eval("TableName")%>');" /></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
        </table>
    </form>
</body>
</html>
