<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="TrendsList.aspx.cs" Inherits="QPS.Web.AdminControl.TrendsList" %>

<%@ Register Assembly="SdCms.Controls" Namespace="SdCms.Controls" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>动态列表</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <table width=90% border=0 cellpadding="3" runat="server">
    <tr>
    <td>
        <asp:Button ID="bntInsert" runat="server" Text="添加动态" 
            onclick="bntInsert_Click" />
        </td>
    </tr>
        <tr>
            <td colspan=5 align=center>
                    <asp:datagrid id="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White" BorderColor="Black" CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6" 
           AutoGenerateColumns="False" AllowSorting="True" Font-Names="Verdana" AllowPaging="True" Runat="server" Width="100%" 
                    OnItemDataBound="dgExamProj_ItemDataBound" 
                    OnItemCommand="dgExamProj_ItemCommand">
							<SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080"/>
							<AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
							<ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></ItemStyle>
							<HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"> </HeaderStyle>
							<Columns>
								
								<asp:TemplateColumn HeaderText="标题">
									<ItemTemplate>
									<asp:Label id="lbltitle" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "title") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
								
								<asp:TemplateColumn HeaderText="时间">
									<ItemTemplate>
									<asp:Label id="lbltime" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "time") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
								
                                <asp:TemplateColumn HeaderText="查看">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="LinkTo" CommandArgument='<%# Eval("Id") %>' >查看</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                <asp:TemplateColumn HeaderText="删除">
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
        <tr>
            <td>
                <cc1:Pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" oncommand="Pager1_Command"/>
            </td>
        </tr>
    </table>
    
    </div>
    </form>
</body>
</html>
