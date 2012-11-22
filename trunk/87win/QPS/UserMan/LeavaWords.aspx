<%@ Page Title="" Language="C#" MasterPageFile="~/UserMan/PersonMaster.Master" AutoEventWireup="true" CodeBehind="LeavaWords.aspx.cs" Inherits="QPS.Web.UserMan.LeavaWords" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
        <div class="grright">
               <div class="grtitlea">
                    <span>留言信息</span>
               </div>
               <!--grbox[[-->
    <div class="grbox">
                   <asp:GridView ID="GridView1" runat="server" CellPadding="4" ForeColor="#333333" 
                    Width="100%"    GridLines="None">
                       <RowStyle BackColor="#EFF3FB" />
                       <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                       <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                       <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                       <HeaderStyle BackColor="#FE6A6A" Font-Bold="True" ForeColor="White" />
                       <EditRowStyle BackColor="#2461BF" />
                       <AlternatingRowStyle BackColor="White" />
                   </asp:GridView>
               </div>
               <!--grbox]]-->
          </div>
</asp:Content>
