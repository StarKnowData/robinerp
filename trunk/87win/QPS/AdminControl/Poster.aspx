<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Poster.aspx.cs" Inherits="QPS.Web.AdminControl.Poster" %>

<%@ Register Assembly="SdCms.Controls" Namespace="SdCms.Controls" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>广告管理</title>
</head>
<body>
    <form id="form1" runat="server">
 <div style="text-align:center;">

	<table width=90% border=0 cellpadding="3">

	    <tr>
	        <td colspan=5 align=center>
                <asp:DataGrid ID="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White"
                    BorderColor="Black" CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6"
                    AutoGenerateColumns="False" AllowSorting="True" Font-Names="Verdana" AllowPaging="True"
                    runat="server" Width="100%" OnItemDataBound="dgExamProj_ItemDataBound" OnItemCommand="dgExamProj_ItemCommand">
                    <SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080" />
                    <AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
                    <ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False"
                        Font-Strikeout="False" Font-Underline="False"></ItemStyle>
                    <HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False"
                        Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False">
                    </HeaderStyle>
                    <Columns>
                        <asp:TemplateColumn HeaderText="图片地址">
                            <ItemTemplate>
                                <asp:Label ID="lblPack" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.Id") %>' Visible="False"></asp:Label>
                                <asp:Label ID="lblName" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.PhotoUrl") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateColumn>
                        
                        <asp:TemplateColumn HeaderText="链接地址">
                            <ItemTemplate>
                                <asp:Label ID="lblUrl" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.URL") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateColumn>



                        <asp:TemplateColumn HeaderText="修改">
                            <ItemTemplate>
                                <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="LinkTo" CommandArgument='<%# DataBinder.Eval(Container, "DataItem.Id") %>' >修改</asp:LinkButton>
                                
                            </ItemTemplate>
                            <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"  Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"  Font-Underline="False" HorizontalAlign="Center" />
                        </asp:TemplateColumn>

                                                                                 <asp:TemplateColumn HeaderText="删除" Visible="false">
                             <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
                              <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# Eval("Id") %>' OnClientClick="javascript:return confirm('确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
                        
                        
                    </Columns>
                    <PagerStyle Visible="False"></PagerStyle>
                </asp:DataGrid>
                   
             </td>
	    </tr>
	     <tr><td width="100%" colspan="5"> 
	         
             <cc1:Pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" 
                 oncommand="Pager1_Command1"/>   
                 
                  </td></tr>

   
	</table>
	
	</div>
    </form>
</body>
</html>
