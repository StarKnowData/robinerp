<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GMAwardTypeSet.aspx.cs" Inherits="Bzw.Web.Admin.SConfig.GMAwardTypeSet" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>
    <style type="text/css">
		body {
			background-color: #FFFFFF;
			margin-top: 0px;
		}
		td{
			text-align:center;
			height:30px;
		}
	</style>
</head>
<body>
    <form id="form1" runat="server"  onsubmit="return onFormSubmit(this)">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td style="text-align:left; font-weight:bold;">
                    GM奖励方案设置</td>
            </tr>
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height:5px;"></td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="7" style="height:20px; text-align:left;">
					<a href="GMAwardTypeSetEdit.aspx?type=add" target="main">添加方案</a>
				</td>
			</tr>
            <tr>
                <td>方案名</td>
                <td>赠送金币数</td>
                <td>赠送的道具1</td>
                <td>赠送的道具2</td>
                <td>赠送的道具3</td>
                 <td>赠送的道具4</td>
				<td>操作</td>
            </tr>
			<asp:Repeater ID="rptMain" runat="server">
				<ItemTemplate>
					<tr>
						<td>方案<%# line++ %></td>
						<td>
							<%# Eval("Gold").ToString()%>
						</td>
						<td>
							<%# Eval( "PropID1" ).ToString() != "" && Eval( "PropCount1" ).ToString() != "" && Eval( "PropID1" ).ToString() != "0" && Eval( "PropCount1" ).ToString() != "0" ? GetPropName( Eval( "PropID1" ).ToString() ) + Eval( "PropCount1" ).ToString() + "个" : ""%>
							
						</td>
						<td>
							<%# Eval( "PropID2" ).ToString() != "" && Eval( "PropCount2" ).ToString() != "" && Eval( "PropID2" ).ToString() != "0" && Eval( "PropCount2" ).ToString() != "0" ? GetPropName( Eval( "PropID2" ).ToString() ) + Eval( "PropCount2" ).ToString() + "个" : ""%>
					
						</td>
						<td>
							<%# Eval( "PropID3" ).ToString() != "" && Eval( "PropCount3" ).ToString() != "" && Eval( "PropID3" ).ToString() != "0" && Eval( "PropCount3" ).ToString() != "0" ? GetPropName( Eval( "PropID3" ).ToString() ) + Eval( "PropCount3" ).ToString() + "个" : ""%>
				
						</td>
						<td>
							<%# Eval( "PropID4" ).ToString() != "" && Eval( "PropCount4" ).ToString() != "" && Eval( "PropID4" ).ToString() != "0" && Eval( "PropCount4" ).ToString() != "0" ? GetPropName( Eval( "PropID4" ).ToString() ) + Eval( "PropCount4" ).ToString() + "个" : ""%>
						
						</td>
						<td><a href="GMAwardTypeSetEdit.aspx?type=edit&id=<%# Eval("SeriNo").ToString()%>">修改</a> <a href="GMAwardTypeSet.aspx?type=delete&id=<%# Eval("SeriNo").ToString()%>">删除</a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
        </table>
    </form>
</body>
</html>