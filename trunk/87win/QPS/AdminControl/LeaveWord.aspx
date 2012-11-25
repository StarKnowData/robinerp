<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LeaveWord.aspx.cs" Inherits="QPS.Web.Manage.AdminControl.LeaveWord" %>

<%@ Register Assembly="SdCms.Controls" Namespace="SdCms.Controls" TagPrefix="cc1" %>

<%--<%@ Register Assembly="MyPagerNet" Namespace="MyPager" TagPrefix="SuperSoft" %>--%>

<%-- 留言--%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >

<head id="Head1" runat="server">
    <title>留言列表</title>
    
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR" />
	<meta content="C#" name="CODE_LANGUAGE" />
	<meta content="JavaScript" name="vs_defaultClientScript" />
	<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema" />
	<%--<link href="Css/Style.css" rel="stylesheet" type="text/css" />--%>
    
	<script language="javascript" type="text/javascript" src="../script/Common.js"></script>
	<script language="JavaScript" type="text/JavaScript" src="../script/Modality.js"></script>
    <style type="text/css">
        .style1
        {
            width: 88px;
        }
        .style2
        {
            width: 65px;
        }
    </style>
</head> 

<body>
    <form id="form1" runat="server" method="post" >
    <div style="text-align:center;">
	<table width=90% border=0 cellpadding="3" runat="server">

	    <tr>
	        <td align=left class="style2">姓名</td><td align=left class="style1"><asp:TextBox ID=txlinkman runat=server></asp:TextBox></td>
	        <td align=left style="width: 90px">
                <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" />
                </td><td style="width: 167px" align=left><asp:TextBox ID=txlogin runat=server Visible=false></asp:TextBox></td>
	        <td align=left>
                &nbsp;
            </td>
	    </tr>
	    <tr valign=top>
	        <td colspan=5 align=center>
	        <asp:datagrid id="dgExamProj" PageSize="20" GridLines="Horizontal" 
                    BackColor="White" BorderColor="Black"
							CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6" AutoGenerateColumns="False"
							AllowSorting="True" Font-Names="Verdana" AllowPaging="True" Runat="server" Width="100%" 
                    OnItemDataBound="dgExamProj_ItemDataBound" 
                    OnItemCommand="dgExamProj_ItemCommand">
							<SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080"/>
							<AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
							<ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></ItemStyle>
							<HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></HeaderStyle>
							<Columns>
							
							<asp:TemplateColumn HeaderText="姓名">
									<ItemTemplate>
									<asp:Label id="lblPack" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "Id") %>' Visible="False">
									</asp:Label>
									
                                    <asp:Label id="lblTestItems" runat="server" Text='<%# GetName(DataBinder.Eval(Container.DataItem, "username").ToString()) %>' ></asp:Label>
          
                                    <%--<asp:Label ID="lblname" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "UserName") %>' ></asp:Label>--%>
          
									</ItemTemplate>
								</asp:TemplateColumn>
								
								<asp:TemplateColumn HeaderText="标题">
									<ItemTemplate>
									<asp:Label id="lblTitleItems" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "title") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
								
                                <asp:TemplateColumn HeaderText="查看">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="LinkTo" CommandArgument='<%# Eval("Id") %>' >查看</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                <asp:TemplateColumn HeaderText="删除" >
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# DataBinder.Eval(Container.DataItem, "Id") %>' OnClientClick="javascript:return confirm('确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
								
							</Columns>
							<PagerStyle  Visible="False"></PagerStyle>
						</asp:datagrid>
                   
            </td>
	    </tr>
	     <tr><td width="100%" colspan="5">
             <cc1:Pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" 
                 oncommand="Pager1_Command"  />
	     
          </td></tr>
   
	</table>
	
	</div>
    </form>
</body>

</html>
