<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Jfgl.aspx.cs" Inherits="QPS.Web.AdminControl.Jfgl" %>

<%@ Register Assembly="SdCms.Controls" Namespace="SdCms.Controls" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>积分管理</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        	<table width=90% border=0 cellpadding="3">

	    <tr>
	        <td align=left style="width: 90px">用户名</td>
	        <td style="width: 167px" align=left>
	            <asp:TextBox ID=txlogin runat=server></asp:TextBox>
	           
	        </td>
	        <td align=left style="width: 90px">
                <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" />
	        </td>
	        <td style="width: 167px" align=left>
	            &nbsp;</td>
	        <td align=left>
                &nbsp;</tr>
	    <tr>
	        <td colspan=5 align=center>
	        <asp:datagrid id="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White" BorderColor="Black"
							CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6" AutoGenerateColumns="False"
							AllowSorting="True" Font-Names="Verdana" AllowPaging="True" Runat="server" Width="100%" OnItemDataBound="dgExamProj_ItemDataBound" OnItemCommand="dgExamProj_ItemCommand">
							<SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080"/>
							<AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
							<ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></ItemStyle>							<HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></HeaderStyle>
							<Columns>
							
							<asp:TemplateColumn HeaderText="用户名">
									<ItemTemplate>
									<asp:Label id="lblUserIDItem" runat="server"  CommandName="JiFen" Text='<%# DataBinder.Eval(Container, "DataItem.Id") %>' Visible="False" ></asp:Label>
							<%--<asp:Label id="lblUserNameItem" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.UserName") %>' ></asp:Label>--%>
                        <asp:LinkButton ID="LkbtUserNameItem" runat="server" CommandName="JiFen"  CommandArgument='<%# Eval("Id") %>'>
                          <%# GetName(DataBinder.Eval(Container.DataItem, "Username").ToString())%>
                        </asp:LinkButton>
									</ItemTemplate>
								</asp:TemplateColumn>
							
				    <asp:TemplateColumn HeaderText="总积分数">
						<ItemTemplate>
<%--                            <asp:LinkButton ID="lkbtPhone" runat="server" CommandName="JiFen"><%# DataBinder.Eval(Container, "DataItem.Content") %></asp:LinkButton>--%>
						<asp:Label id="lblPhone" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.integral") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
								
                                <asp:TemplateColumn HeaderText="修改" Visible="false">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnDetail" CommandName="editItem" runat="server" CommandArgument='<%# Eval("ID") %>' >修改</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                
                                <asp:TemplateColumn HeaderText="删除" >
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# Eval("ID") %>' OnClientClick="javascript:return confirm('确认删除此条积分记录?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
								
							</Columns>
							<PagerStyle  Visible="False"></PagerStyle>
						</asp:datagrid>
                   
            </td>
	    </tr>
	     <tr><td width="100%" colspan="5"> 
             <cc1:pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" OnCommand="pager_Command" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" />
             
             </td></tr>
   
	</table>
    </div>
    </form>
</body>
</html>
