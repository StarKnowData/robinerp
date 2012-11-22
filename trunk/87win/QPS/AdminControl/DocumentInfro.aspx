<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DocumentInfro.aspx.cs" Inherits="QPS.Web.AdminControl.DocumentInfro" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>文档管理</title>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center;">
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
                    <asp:TemplateColumn HeaderText="标题">
                         <ItemTemplate>
                             <asp:Label ID="lblTitl" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "Dtity") %>'></asp:Label>
                         </ItemTemplate>
                     </asp:TemplateColumn>
                     
                     <asp:TemplateColumn HeaderText="时间">
                         <ItemTemplate>
                             <asp:Label ID="lblContent" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "DTime") %>'></asp:Label>
                         </ItemTemplate>
                     </asp:TemplateColumn>
                     
                     <asp:TemplateColumn HeaderText="查看" Visible="false">
                         <ItemTemplate>
                             <asp:LinkButton ID="lkbntSelect" runat="server" CommandName="Select" CommandArgument='<%# Eval("Id") %>' >查看</asp:LinkButton>  
                         </ItemTemplate>
                     </asp:TemplateColumn>
                     
                     <asp:TemplateColumn HeaderText="编辑">
                         <ItemTemplate>
                             <asp:LinkButton ID="lkbntUpdate" runat="server" CommandName="Update" CommandArgument='<%# Eval("Id") %>' >编辑</asp:LinkButton>  
                         </ItemTemplate>
                     </asp:TemplateColumn>
                    
                    </Columns>
                    </asp:DataGrid>
    </div>
    </form>
</body>
</html>
