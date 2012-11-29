<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameTypesEdit" Codebehind="GameTypesEdit.aspx.cs" %>
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
    if(document.getElementById("KindID").value == '') {
    alert('温馨提示：\n\n请输入类别号！');
    document.getElementById("KindID").focus();
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
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>修改游戏类别</strong></td>
            </tr>
            <tr>
                <td align="right">
                    类别名称：</td>
                <td align="left">
                    <input type="text" id="KindName" name="KindName" value="<%=KindName %>" class="put" /></td>
            </tr>
            <tr style="display:none;">
                <td align="right">
                    类别号：</td>
                <td align="left">
                    <input type="text" id="KindID" name="KindID" value="<%=KindID %>" readonly class="put" />（无需修改）</td>
            </tr>
            <tr>
                <td align="right">
                    排列号：</td>
                <td align="left">
                    <input type="text" id="IDSort" name="IDSort" value="<%=IDSort %>" class="put" maxlength="4"/>（值越小排列的位置越靠前）</td>
            </tr>
            <tr>
                <td align="right">
                    是否激活：</td>
                <td align="left">
                    <input name="Enable" type="radio" value="1" <%= (Enable.ToString().ToLower()=="1" ? "checked" : "") %> Class="put"/>激活
                    <input name="Enable" type="radio" value="0" <%= (Enable.ToString().ToLower()=="0" ? "checked" : "") %> Class="put"/>未激活
                </td>
            </tr>
            <%if (ParentKindId == "0")
              { %>
             <tr >
                 <td align="right">
                        是否添加：</td>
                    <td align="left">
                     <input type="button" id="btnAddChildRoom"  value="添加二级游戏目录"  onclick="ShowChild()"/>
                    </td>
                </tr>
                <%} %>
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
                    <input type="hidden" name="action" value="edit" />
                    <input type="hidden" name="action2" value="edit" />
                    <input type="hidden" name="id" value="10" />
                </td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text=" 提 交 " Class="put" OnClick="GameTypeEdit"/>
                    <input name="reback" type="button" value="返回上一页"  Class="put" onclick="javascript:history.back();" />
                </td>
            </tr>
        </table>
        <%if (ParentKindId == "0")
          { %>
        <p></p>
        
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="11">
                    <strong>游戏类别管理</strong></td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                    类别名称</td>
                <td>
                    类别号</td>
                 <td>隶属类别</td>
                <td>
                    排列号</td>
                <td>
                    是否激活</td>
                <td>
                    操作</td>
            </tr>
            <asp:Repeater ID="GameTypesList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
                            <%=tableids=tableids+1 %>
                        </td>
                        <td>
                            <%# Eval("KindName") %></td>
                        <td>
                            <%# Eval("KindID") %></td>
                            <td><%#Eval("KindParentName")%></td>
                        <td>
                            <%# Eval("IDSort")%></td>
                        <td>
                            <%# Eval("Enable").ToString().ToLower() == "1" ? "<font color=\"red\">已激活</font>" : "未激活"%></td>
                        <td>
                            <a href='GameTypesEdit.aspx?id=<%# Eval("KindID") %>'>修改</a>&nbsp;&nbsp; <a href='GameTypesDel.aspx?id=<%# Eval("KindID") %>' onclick="javascript:return confirm('确定删除该游戏名称吗？删除后将不能恢复!');">
                                删除</a></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
        </table><%} %>
    <p></p>  
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="10">
					<strong>游戏信息管理</strong></td>
			</tr>
			<tr>
				<td>
					序号</td>
				<td>
					游戏类别</td>
				<td>
					游戏名称</td>
				<td>
					游戏ID号</td>
				<td>
					客户端ICO文件名</td>
				<td>
					排列号</td>
				<td>
					激活状态</td>
				<td>
					服务端文件名</td>
				<td>
					桌子上人数</td>
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="GameNamesList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%=tableids = tableids+1%>
						</td>
						<td>
							<%# Eval("kindname")%>
						</td>
						<td>
							<%# Eval("ComName") %>
						</td>
						<td>
							<%# Eval("NameID") %>
						</td>
						<td>
							<%# Eval("ComProcess")%>
						</td>
						<td>
							<%# Eval("IDSort") %>
						</td>
						<td>
							<%# Eval("Enable").ToString().ToLower() == "1" ? "已激活" : "未激活"%>
						</td>
						<td>
							<%# Eval("DLLFileName")%>
						</td>
						<td>
							<%# Eval("DeskPeople")%>
						</td>
						<td>
							<a href='GameNamesEdit.aspx?id=<%#Eval("Nameid") %>'>修改</a>&nbsp;&nbsp;<a href='GameNamesDel.aspx?id=<%#Eval("Nameid") %>' onclick="javascript:return confirm('确定删除该游戏信息吗？删除后将不能恢复!');">删除</a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
		</table>
		
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5">
				</td>
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
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
	   <script type="text/javascript">
	       function ShowChild() {
	           $("tr").css("display", "");
	       }
    </script>
</body>
</html>
