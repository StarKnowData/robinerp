<%@ Page Title="" Language="C#" MasterPageFile="~/UserMan/PersonMaster.Master"AutoEventWireup="true" CodeBehind="OrderMan.aspx.cs" Inherits="QPS.Web.UserMan.OrderMan" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="grright">
               <div class="grtitlea">
                    <span>订单历史记录</span>
               </div>
               <!--grbox[[-->
               <div class="glbox">
                   <asp:GridView ID="gdvPersonnalOrder" runat="server" CellPadding="4" 
                       ForeColor="#333333" GridLines="None"  Width="100%"
                               DataKeyNames="棋牌室编号" 
                       onrowdeleting="gdvPersonnalOrder_RowDeleting"  >
                       <RowStyle BackColor="#EFF3FB" />  　 　

                       <Columns>
                                          <asp:TemplateField HeaderText="操作" ShowHeader="False" >
                   <ItemTemplate>
                   　<asp:LinkButton ID="BtnDelete" runat="server" CausesValidation="False" CommandName="Delete"
Text="退订" ForeColor="Black"  OnClientClick="return confirm('确认要退订吗？')"></asp:LinkButton>
                   </ItemTemplate></asp:TemplateField>
                       </Columns>
                       <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                       <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                       <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                       <HeaderStyle BackColor="#FE6A6A" Font-Bold="True" ForeColor="White" 
                           BorderStyle="None" />
                       <EditRowStyle BackColor="#2461BF" />
                       <AlternatingRowStyle BackColor="White" />
                   </asp:GridView>
               </div>
               <!--grbox]]-->
          </div>
</asp:Content>
