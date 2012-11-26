<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Jfxq.aspx.cs" Inherits="QPS.Web.AdminControl.Jfxq" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>积分详情</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <asp:DataGrid ID="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White"
            BorderColor="Black" CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6"
            AutoGenerateColumns="False" AllowSorting="True" Font-Names="Verdana" AllowPaging="True"
            runat="server" Width="80%" OnItemDataBound="dgExamProj_ItemDataBound" OnItemCommand="dgExamProj_ItemCommand">
            <SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080" />
            <AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
            <ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False"
                Font-Strikeout="False" Font-Underline="False"></ItemStyle>
            <HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False"
                Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False">
            </HeaderStyle>
            <Columns>
                <%--棋牌室  时间 消费金额 积分--%>
                <%-- 
                <asp:TemplateColumn HeaderText="棋牌室" Visible=false>
                    <ItemTemplate>
                        <asp:Label ID="lblRoom" runat="server" CommandName="JiFen" Text='<%# GetName(DataBinder.Eval(Container, "DataItem.name").ToString()) %>'></asp:Label>
                    </ItemTemplate>
                </asp:TemplateColumn>
                <asp:TemplateColumn HeaderText="消费金额" Visible="false">
                    <ItemTemplate>
                        <asp:Label ID="lblJinE" runat="server"  Text='<%# DataBinder.Eval(Container, "DataItem.Content") %>'></asp:Label>
                    </ItemTemplate>
                </asp:TemplateColumn>
                <asp:TemplateColumn HeaderText="时间" Visible=false>
                    <ItemTemplate>
                        <asp:Label ID="lblShiJ" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.CreateTime") %>'></asp:Label>
                    </ItemTemplate>
                </asp:TemplateColumn>
                --%>
                <asp:TemplateColumn HeaderText="积分">
                    <ItemTemplate>
                        <asp:Label ID="lblJiFen" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.TotalMoney") %>'></asp:Label>
                    </ItemTemplate>
                </asp:TemplateColumn>
                <asp:TemplateColumn HeaderText="修改">
                    <ItemTemplate>
                         <asp:LinkButton ID="lbtnDetail" runat="server" CommandName="Update" CommandArgument='<%# DataBinder.Eval(Container, "DataItem.UserID") %>' >修改</asp:LinkButton>
                                    </ItemTemplate>
                </asp:TemplateColumn>
     <%----------------------------------------------------------%>         
                <asp:TemplateColumn HeaderText="删除">
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete" CommandArgument='<%# DataBinder.Eval(Container, "DataItem.UserID") %>' OnClientClick="javascript:return confirm('将会删除此用户的所以积分记录，确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
                
            </Columns>
            <PagerStyle Visible="False"></PagerStyle>
        </asp:DataGrid>
    </div>
    </form>
</body>
</html>
